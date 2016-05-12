#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    //载入外部URL: MainWindow *main = new MainWindow(QUrl("http://www.baidu.com"));
    QString index = QCoreApplication::applicationDirPath() + "/a.html";
    MainWindow *main = new MainWindow(QUrl::fromLocalFile(index));
    main->show();
    return app.exec();
}
