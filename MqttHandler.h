/**
 * @file MqttHandler.h
 * @brief Concrete implementation of the IMessageBus interface using the MQTT protocol.
 */

#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <QObject>
#include <QtMqtt/qmqttclient.h>
#include "IMessageBus.h"

/**
 * @class MqttHandler
 * @brief Handles MQTT communication and bridges it with the QML User Interface.
 * * This class implements the IMessageBus interface to provide a standardized
 * way of sending and receiving messages via an MQTT broker. It inherits from
 * QObject to support Qt's signal/slot mechanism for UI updates.
 */
class MqttHandler : public QObject, public IMessageBus {
    Q_OBJECT
public:
    explicit MqttHandler(QObject *parent = nullptr);

    /**
     * @brief Publishes a message to a specific MQTT topic.
     * @param topic The MQTT topic string.
     * @param message The payload to be sent.
     */
    void send(const QString &topic, const QString &message) override;

    /**
     * @brief Processes messages received from the MQTT broker..
     * @param message The raw message received from the network.
     */
    void receive(const QString &message) override;

signals:
    /**
     * @brief Signal emitted when a new traffic light state is received.
     * @param color The new color state.
     */
    void stateColorChanged(QString color);

private:
    QMqttClient *m_client;
};

#endif // MQTTHANDLER_H
