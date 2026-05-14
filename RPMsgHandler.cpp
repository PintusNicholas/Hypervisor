/**
 * @file RPMsgHandler.cpp
 * @brief Implementation of the RPMsgHandler class for handling Remote Processor Messaging (RPMsg).
 *
 * This file contains the logic for opening the RPMsg device, monitoring it for incoming
 * data using QSocketNotifier, and parsing the raw byte stream into CAN frame structures.
 */

#include "RPMsgHandler.h"
#include <QSocketNotifier>
#include <QDebug>

/**
 * @brief The path to the raw RPMsg character device.
 */
const QString RPMSG_PATH = "/dev/rpmsg_raw";

RPMsgHandler::RPMsgHandler(QObject *parent) : QObject(parent) {
    m_rpmsg.setFileName(RPMSG_PATH);

    if(!m_rpmsg.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR: Impossible open RPMSG: " << RPMSG_PATH;
        //return;
    }

    // Monitor the file handle for Read activity
    QSocketNotifier *notify = new QSocketNotifier(m_rpmsg.handle(), QSocketNotifier::Read, this);
    connect(notify, &QSocketNotifier::activated, this, &RPMsgHandler::handleReadyRead);

    qDebug() << "Ready";
}

/**
 * @brief Slot triggered when data is available on the RPMsg device.
 *
 * Reads all available bytes from the device. If the data size matches or exceeds
 * the expected CAN frame structure, it casts the raw data and emits signals
 * representing the engine fault and oil temperature states.
 */
void RPMsgHandler::handleReadyRead() {
    QByteArray rawData = m_rpmsg.readAll();

    if(rawData.size() < sizeof(rpmsg_can_frame_t)) {
        //return;
    }

    // Cast the raw data buffer to the CAN frame structure
    const rpmsg_can_frame_t *frame = reinterpret_cast<const rpmsg_can_frame_t*>(rawData.constData());

    // Emit parsed states to the UI or other handlers
    emit stateEngineFault(frame->engine_fault);
    emit stateOilTemperature(frame->oil_temperature);
}