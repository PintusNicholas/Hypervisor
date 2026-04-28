#include "RPMsgHandler.h"
#include <QString>
#include <QDebug>

RPMsgHandler::RPMsgHandler(QObject *parent) : QObject(parent) {
    m_socket = new QLocalSocket(this);
    m_socket->connectToServer("\\\\.\\pipe\\semaforo_rpmsg");

    connect(m_socket, &QLocalSocket::connected, [] () {
        qDebug() << "Successfully connected to a Pipe";
    });

    connect(m_socket, &QLocalSocket::readyRead, this, [=] () {
        while (m_socket->canReadLine()) {
            QByteArray data = m_socket->readLine();
            QString state = QString::fromUtf8(data).trimmed();

            receive(state);
        }
    });
}

void RPMsgHandler::receive(const QString &message) {
    qDebug() << "Command from Pipe received: " << message;
    emit stateColorChanged(message);
}

void RPMsgHandler::send(const QString &topic, const QString &message) {
    return;
}