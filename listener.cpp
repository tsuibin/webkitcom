#include "listener.h"

DBusListener::DBusListener(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    this->parent = dynamic_cast<ListenerParent *>(parent);
}

void DBusListener::event_callback(qlonglong a, QString b)
{
    qDebug() << "msg received:" << a << "," << b;
    new ListenerRelayer(parent, a, b);
}

ListenerRelayer::ListenerRelayer(ListenerParent* lp, qlonglong a, QString b)
    : QTimer(0)
{
    parent = lp;
    this->a = a;
    this->b = b;
    connect(this, SIGNAL(timeout()), SLOT(relay()));
    setSingleShot(true);
    start(0);
}

void ListenerRelayer::relay()
{
    qDebug() << "msg relayed:" << a << "," << b;
    parent->callback(a, b);
}
