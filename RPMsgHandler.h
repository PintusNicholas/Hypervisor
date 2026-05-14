/**
 * @file RPMsgHandler.h
 * @brief Header file for the RPMsgHandler class.
 *
 * This file defines the class responsible for Inter-Process Communication (IPC)
 * between the Linux Guest and Windows Host environments using RPMSG.
 */

#ifndef RPMSGHANDLER_H
#define RPMSGHANDLER_H

#include <QObject>
#include <QFile>

#pragma pack(push, 1)
/**
 * @struct rpmsg_can_frame_t
 * @brief Structure representing the CAN data frame received via RPMSG.
 *
 * This structure is packed to ensure exact memory mapping when reading
 * raw bytes from the character device.
 */
typedef struct {
    uint16_t speed;
    uint16_t rpm;
    uint8_t  engine_fault;
    uint8_t  oil_temperature;
} rpmsg_can_frame_t;
#pragma pack(pop)

/**
 * @class RPMsgHandler
 * @brief Handles communication between Linux (Guest) and Windows (Host) via RPMSG.
 *
 * This class manages data reception from the RPMSG character device.
 * It monitors the device for incoming raw bytes and parses them into
 * structured data, emitting signals to update the UI components.
 */
class RPMsgHandler : public QObject {
    Q_OBJECT
public:
    explicit RPMsgHandler(QObject *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the engine fault state changes.
     * @param state The current state of the engine fault.
     */
    void stateEngineFault(int state);

    /**
     * @brief Signal emitted when the oil temperature warning state changes.
     * @param state The current state of the oil temperature warning.
     */
    void stateOilTemperature(int state);

private slots:
    /**
     * @brief Internal slot to handle the readyRead event from the RPMSG device.
     *
     * Triggered by a QSocketNotifier when new data is available to be read.
     */
    void handleReadyRead();

private:
    QFile m_rpmsg;

};

#endif // RPMSGHANDLER_H