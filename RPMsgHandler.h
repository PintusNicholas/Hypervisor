#ifndef RPMSGHANDLER_H
#define RPMSGHANDLER_H

#include "IMessageBus.h"
#include <QObject>
#include <QLocalSocket>

class RPMsgHandler : public QObject, public IMessageBus {
    Q_OBJECT
public:
    explicit RPMsgHandler(QObject *parent = nullptr);

    void send(const QString &topic, const QString &message) override;

    void receive(const QString &message) override;

    void readState();

signals:
    void stateColorChanged(QString color);

private:
    QLocalSocket *m_socket;

};

#endif // RPMSGHANDLER_H
