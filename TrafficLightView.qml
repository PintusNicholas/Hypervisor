/**
 * @file TrafficLightView.qml
 * @brief User Interface for the Double Traffic Light system.
 * * This file implements a visual representation of two traffic lights:
 * - A "Local" TrafficLight controlled by an internal logic (Timer).
 * - A "Remote" TrafficLight controlled by external messages via the IMessageBus.
 */

import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Double Traffic Light")

    //MACROs
    readonly property int green_light: 5000
    readonly property int yellow_light: 2000
    readonly property int red_light: 5000
    readonly property int delay: 1000
    readonly property int red_state: 0
    readonly property int yellow_state: 1
    readonly property int green_state: 2


    property int localTrafficLightState: 0
    property int remoteTrafficLightState: 0

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

            // --- LOCAL TRAFFIC LIGHT ---
            Column {
                spacing: 20
                Rectangle { width: 80; height: 80; radius: 40; color: localTrafficLightState === red_state ? "red" : "darkred" }
                Rectangle { width: 80; height: 80; radius: 40; color: localTrafficLightState === yellow_state ? "yellow" : "#666600" }
                Rectangle { width: 80; height: 80; radius: 40; color: localTrafficLightState === green_state ? "green" : "darkgreen" }
            }

            // --- REMOTE TRAFFIC LIGHT ---
            Column {
                spacing: 20
                Rectangle { width: 80; height: 80; radius: 40; color: remoteTrafficLightState === red_state ? "red" : "darkred" }
                Rectangle { width: 80; height: 80; radius: 40; color: remoteTrafficLightState === yellow_state ? "yellow" : "#666600" }
                Rectangle { width: 80; height: 80; radius: 40; color: remoteTrafficLightState === green_state ? "green" : "darkgreen" }
            }
        }
    }

    Timer {
        id: local_traffic_light
        interval: getInterval();
        running: true
        repeat: true

        onTriggered: {
            switch(localTrafficLightState) {
                case red_state:
                    localTrafficLightState = green_state; // red -> green
                    break;
                case yellow_state:
                    localTrafficLightState = red_state; // yellow -> red
                    break;
                case green_state:
                    localTrafficLightState = yellow_state; // green -> yellow
                    break;
            }
        }
    }

    /**
    * @brief Helper function to determine the duration of each light phase.
    * @return int Interval in milliseconds.
    */
    function getInterval() {
        if (localTrafficLightState === red_state) return red_light;
        if (localTrafficLightState === yellow_state) return yellow_light;
        if (localTrafficLightState === green_state) return green_light;
        return delay;
    }

    Connections{
        target: messageBus

        /**
        * @handler onStateColorChanged
        * @brief Updates the remote Traffic Light based on signals from the bus.
        * @param color String representing the new state ("red", "yellow", "green").
        */
        function onStateColorChanged(color) {
            console.log("Color received: " + color)

            if(color === "green") remoteTrafficLightState = green_state;
            else if (color === "yellow") remoteTrafficLightState = yellow_state;
            else if (color === "red") remoteTrafficLightState = red_state;
            else console.log(color + " is not a valid command")
        }
    }
}



