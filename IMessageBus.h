/**
 * @file IMessageBus.h
 * @brief Definition of the IMessageBus interface for decoupled communication.
 */

#ifndef IMESSAGEBUS_H
#define IMESSAGEBUS_H

#include <QString>

/**
 * @class IMessageBus
 * @brief Abstract interface representing a generic communication bus.
 * * This interface defines the mandatory contract for any message-based
 * communication handler.
 * It ensures that the high-level logic (UI/Application) remains
 * decoupled from the specific underlying protocol.
 */
class IMessageBus {
public:
    virtual ~IMessageBus() {}

    /**
     * @brief Sends a message over the bus.
     * * @param topic The destination or channel where the message will be published.
     * @param message The actual payload or data to be sent.
     */
        virtual void send(const QString &topic, const QString &message) = 0;

    /**
     * @brief Processes an incoming message.
     * * This method is called when the underlying protocol receives data.
     * Implementations should parse the message and notify the system.
     * * @param message The content of the received message.
     */
        virtual void receive(const QString &message) = 0;
};

#endif // IMESSAGEBUS_H
