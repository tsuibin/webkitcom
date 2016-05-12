#include <QtWidgets>
#include <QtWebKitWidgets>
#include "listener.h"

class MainWindow : public QMainWindow, public ListenerParent
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);
    //实现ListenerParent的接口
    virtual void callback(qlonglong a, QString b);

public:
    Q_INVOKABLE QString getPath();
    Q_INVOKABLE void toggleFullScreen();

protected slots:
    void loadDone();
    void windowObjReady();

private:
    QWebView *view;
    DBusListener *listener;
};
