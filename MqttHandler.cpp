/**
 * @file MqttHandler.cpp
 * @brief Implementation of the MqttHandler class methods.
 */

#include "MqttHandler.h"
#include "IMessageBus.h"
#include <QDebug>

/**
 * @brief Constructor that initializes the MQTT client and sets up connections.
 * * Configures the broker address, handles the connection logic, and sets up
 * the subscription to the remote semaphore topic. When a message is received
 * via MQTT, it is passed to the abstract receive() method.
 * * @param parent The parent QObject.
 */
MqttHandler::MqttHandler(QObject *parent) : QObject(parent)
{
    m_client = new QMqttClient(this);
    m_client->setHostname("broker.emqx.io");
    m_client->setPort(1883);

    connect(m_client, &QMqttClient::connected, this, [this]() {
        qDebug() << "Connected to Broker";

        auto sub = m_client->subscribe(QMqttTopicFilter("semaforo/remote/state"));

        if(!sub) {
            qDebug() << "ERROR: Impossibile to connect to a topic";
            return;
        }

        connect(sub, &QMqttSubscription::messageReceived, this, [this](QMqttMessage msg) {
            QString command = msg.payload().trimmed().toLower();
            receive(command);
        });
    });

    m_client->connectToHost();
}

/**
 * @brief Publishes a message to the specified MQTT topic.
 * @param topic The destination topic name.
 * @param message The string message to be published.
 */
void MqttHandler::send(const QString &topic, const QString &message) {
    m_client->publish(QMqttTopicName(topic), message.toUtf8());
}

/**
 * @brief Standardized method to process incoming data.
 * * This method acts as the entry point for received data regardless of the protocol.
 * It logs the command and emits the Qt signal to notify the QML interface.
 * * @param message The command string (actually accept: "red", "green", "yellow").
 */
void MqttHandler::receive(const QString &message) {
    qDebug() << "Command received:" << message;
    emit stateColorChanged(message);
}