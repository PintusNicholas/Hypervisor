/**
 * @file RPMsgHandler.h
 * @brief Header file for the RPMsgHandler class.
 * * This file defines the class responsible for Inter-Process Communication (IPC)
 * between the Linux Guest and Windows Host environments using Named Pipes.
 */

#ifndef RPMSGHANDLER_H
#define RPMSGHANDLER_H

#include "IMessageBus.h"
#include <QObject>
#include <QLocalSocket>

/**
 * @class RPMsgHandler
 * @brief Handles communication between Linux (Guest) and Windows (Host) via Named Pipes.
 * * This class implements the IMessageBus interface to manage data reception
 * from a QLocalSocket connected to a VirtualBox serial pipe. It processes
 * incoming raw bytes into clean string commands for the UI.
 */
class RPMsgHandler : public QObject, public IMessageBus {
    Q_OBJECT
public:
    explicit RPMsgHandler(QObject *parent = nullptr);

    /**
     * @brief Sends a message over the bus.
     * @param topic The category or target of the message.
     * @param message The actual data to be sent.
     */
    void send(const QString &topic, const QString &message) override;

    /**
     * @brief Processes the received message and notifies the system.
     * @param message The cleaned string command (e.g., "red", "green", "yellow").
     */
    void receive(const QString &message) override;

signals:
    /**
     * @brief Emitted when a valid color command is received from the pipe.
     * @param color The new state of the traffic light.
     * @param time Time before a state change
     */
    void stateColorChanged(QString color, int time);

private:
    QLocalSocket *m_socket;

};

#endif // RPMSGHANDLER_H
