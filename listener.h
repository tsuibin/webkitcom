#include <QtCore/QtCore>
#include <QtDBus/QtDBus>

class ListenerParent
{
public:
    virtual void callback(qlonglong a, QString b) = 0;
};

class ListenerRelayer : public QTimer
{
    Q_OBJECT

public:
    ListenerRelayer(ListenerParent *lp, qlonglong a, QString b);

public slots:
    void relay();

private:
    ListenerParent *parent;
    qlonglong a;
    QString b;
};

class DBusListener : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "qtwebkit.demo.interface")

public:
    DBusListener(QObject* parent);

public slots:
    void event_callback(qlonglong a, QString b);

private:
    ListenerParent *parent;
};
