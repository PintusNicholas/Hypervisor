/**
 * @file main.cpp
 * @brief Main entry point for the TrafficLight application.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MqttHandler.h"
#include "IMessageBus.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    MqttHandler mqttHandler;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("messageBus", &mqttHandler);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("semaphore", "TrafficLightView");

    return QCoreApplication::exec();
}
