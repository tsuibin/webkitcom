#include <QtWidgets>
#include <QtWebKitWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(const QUrl& url)
{
    view = new QWebView(this);
    view->load(url);
    
    //设置当QWebView载入每个页面结束的时候(loadFinished)调用loadDone方法
    //参见 http://doc.qt.io/qt-4.8/qwebview.html
    connect(view, SIGNAL(loadFinished(bool)), SLOT(loadDone()));

    setCentralWidget(view);

    //初始化dbus连接
    QDBusConnection sess_bus = QDBusConnection::sessionBus();
    if (!sess_bus.isConnected())
    {
        qDebug() << "connect to d-bus failed";
        return;
    }

    //注册DBus总线名
    if (!sess_bus.registerService("qtwebkit.demo.dbus"))
    {
        qDebug() << "register service failed";
        return;
    }

    //注册DBus对象名
    listener = new DBusListener(this);
    sess_bus.registerObject("/qtwebkit/demo/object", this);
}

void MainWindow::callback(qlonglong a, QString b)
{
    qDebug() << "msg got in window:" << a << "," << b;
    //在当前页面上运行javascript代码
//    QVariant var = view->page()->mainFrame()->evaluateJavaScript("function aaa(){return 'aaa'}; aaa();");
//    qDebug() << var.toString();
      view->page()->mainFrame()->evaluateJavaScript("alert('(" + QString::number(a) + ", " + b + ") got');");
}

void MainWindow::loadDone()
{
    //设置页面窗口的window对象被重置时调用windowObjReady方法
    //参见 http://doc.qt.io/qt-4.8/qwebframe.html
    connect(view->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), SLOT(windowObjReady()));
    
    //将主窗口的标题设置为页面的标题
    setWindowTitle(view->title());
}

void MainWindow::windowObjReady()
{
    //为页面的window全局对象添加一个名为qt的对象，实际上是C++的this，这样javascript就可以调用this的Q_INVOKABLE方法了
    view->page()->mainFrame()->addToJavaScriptWindowObject("qt", this);
}

QString MainWindow::getPath()
{
    //被页面的javascript调用时返回程序的所在路径
//    return "weirong2016";
    return QCoreApplication::applicationDirPath();
}

void MainWindow::toggleFullScreen()
{
    if (isFullScreen())
        showNormal();
    else
        showFullScreen();
}
