TEMPLATE = app

# apt-get install libqt5webkit5-dev libqt5opengl5-dev

QT += dbus webkitwidgets

SOURCES += main.cpp mainwindow.cpp listener.cpp

HEADERS += listener.h mainwindow.h

TARGET = qtwebkit

