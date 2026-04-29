/**
 * @brief Constructor for the RPMsgHandler class.
 * * Initializes the QLocalSocket and attempts to establish a connection with the
 * VirtualBox Named Pipe. It also sets up the event-driven signal-slot
 * connections for handling the lifecycle of the communication.
 */

#include "RPMsgHandler.h"
#include <QFile>
#include <QString>
#include <QDebug>

const QString SHARED_FILE_PATH = "C:/Users/perdar/Desktop/stati_semaforo/stato.txt";

/**
 * @brief Constructor for RPMsgHandler.
 * * Initializes the QLocalSocket and attempts to connect to the Windows Named Pipe
 * created by VirtualBox. It also sets up signals and slots for connection
 * status and data reception.
 */
RPMsgHandler::RPMsgHandler(QObject *parent) : QObject(parent) {
    m_socket = new QLocalSocket(this);
    m_socket->connectToServer("\\\\.\\pipe\\semaforo_rpmsg");

    connect(m_socket, &QLocalSocket::connected, [] () {
        qDebug() << "Successfully connected to a Pipe";
    });

    connect(m_socket, &QLocalSocket::readyRead, this, [=] () {
        QString flag = m_socket->readAll();
        qDebug() << "Flag received: " << flag;


        QFile file(SHARED_FILE_PATH);
        if(flag == '1') {
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in (&file);
                QString state = in.readAll().trimmed();
                file.close();

                qDebug() << "Command received: " << state;
                receive(state);
            }
        } else printf("flag not valid\n");
    });
}

/**
 * @brief Processes and emits the cleaned color command.
 * * Log the incoming command for debugging purposes and notifies the QML/UI
 * layer via the stateColorChanged signal.
 * * @param message The cleaned string command (e.g., "red", "yellow", "green").
 */
void RPMsgHandler::receive(const QString &message) {
    QStringList comand = message.split("|");
    QString color = comand[0].trimmed();
    int time = comand[1].trimmed().toInt();
    qDebug() << "Command from Pipe received: " << message;
    emit stateColorChanged(color, time);
}

/**
 * @brief Interface implementation for sending messages.
 * * Currently acts as a placeholder as the current implementation focuses
 * on unidirectional communication (Linux to Windows).
 * * @param topic The message category.
 * @param message The content to be sent.
 */
void RPMsgHandler::send(const QString &topic, const QString &message) {
    return;
}