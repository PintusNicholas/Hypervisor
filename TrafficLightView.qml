/**
 * @file TrafficLightView.qml
 * @brief User Interface for the Double Semaphore system.
 * * This file implements a visual representation of two traffic lights:
 * - A "Local" semaphore controlled by an internal logic (Timer).
 * - A "Remote" semaphore controlled by external messages via the IMessageBus.
 */

import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Double Semaphore")

    property int localSemaphoreState: 0
    property int remoteSemaphoreState: 0

    Rectangle {
        id: container
        anchors.centerIn: parent
        width: layoutRow.width + 40
        height: layoutRow.height + 40
        color: "#333333"
        radius: 15
        border.color: "black"
        border.width: 2

        Row {
            id: layoutRow
            anchors.centerIn: parent
            spacing: 50

            // --- LOCAL SEMAPHORE ---
            Column {
                spacing: 20
                Rectangle { width: 80; height: 80; radius: 40; color: localSemaphoreState === 0 ? "red" : "darkred" }
                Rectangle { width: 80; height: 80; radius: 40; color: localSemaphoreState === 1 ? "yellow" : "#666600" }
                Rectangle { width: 80; height: 80; radius: 40; color: localSemaphoreState === 2 ? "green" : "darkgreen" }
            }

            // --- REMOTE SEMAPHORE ---
            Column {
                spacing: 20
                Rectangle { width: 80; height: 80; radius: 40; color: remoteSemaphoreState === 0 ? "red" : "darkred" }
                Rectangle { width: 80; height: 80; radius: 40; color: remoteSemaphoreState === 1 ? "yellow" : "#666600" }
                Rectangle { width: 80; height: 80; radius: 40; color: remoteSemaphoreState === 2 ? "green" : "darkgreen" }
            }
        }
    }

    Timer {
        id: local_semaphore
        interval: getInterval();
        running: true
        repeat: true

        onTriggered: {
            switch(localSemaphoreState) {
                case 0:
                    localSemaphoreState = 2; // red -> green
                    break;
                case 1:
                    localSemaphoreState = 0; // yellow -> red
                    break;
                case 2:
                    localSemaphoreState = 1; // green -> yellow
                    break;
            }
        }
    }

    /**
    * @brief Helper function to determine the duration of each light phase.
    * @return int Interval in milliseconds.
    */
    function getInterval() {
        if (localSemaphoreState === 0) return 5000;
        if (localSemaphoreState === 1) return 2000;
        if (localSemaphoreState === 2) return 5000;
        return 1000;
    }

    Connections{
        target: messageBus

        /**
        * @handler onStateColorChanged
        * @brief Updates the remote semaphore based on signals from the bus.
        * @param color String representing the new state ("red", "yellow", "green").
        */
        function onStateColorChanged(color) {
            console.log("Color received: " + color)

            if(color === "green") remoteSemaphoreState = 2;
            else if (color === "yellow") remoteSemaphoreState = 1;
            else if (color === "red") remoteSemaphoreState = 0;
            else console.log(color + " is not a valid command")
        }
    }
}



