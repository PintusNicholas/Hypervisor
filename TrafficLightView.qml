import QtQuick
import QtQuick.Controls

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Dashboard")
    color: "#000000"

    property int oilTemperatureLED: 0
    property int engineFaultLED: 0

    // ------------ Only for debug purpose ------------------
    Item {
        focus: true
        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_1) oilTemperatureLED = 1;
            if (event.key === Qt.Key_2) oilTemperatureLED = 0;
            if (event.key === Qt.Key_3) engineFaultLED = 1;
            if (event.key === Qt.Key_4) engineFaultLED = 0;
        }
    }
    // --------------------------------------------------------

    component Needle : Image {
        id: needleImage
        property real value: 0
        property real minValue: 0
        property real maxValue: 100
        property real startAngle: -130
        property real endAngle: 130

        fillMode: Image.PreserveAspectFit
        antialiasing: true
        smooth: true

        property real currentAngle: {
            let ratio = (Math.max(minValue, Math.min(maxValue, value)) - minValue) / (maxValue - minValue);
            return startAngle + (ratio * (endAngle - startAngle));
        }

        transform: Rotation {
            origin.x: needleImage.width / 2
            origin.y: needleImage.height * 0.869
            angle: needleImage.currentAngle
        }

        Behavior on currentAngle {
            SpringAnimation {
                spring: 0.5
                damping: 0.9
                mass: 1.2
                epsilon: 0.25
            }
        }
    }

    Image {
        id: dashboard
        source: "Dashboard3.png"
        anchors.fill: parent
        anchors.margins: 20
        fillMode: Image.PreserveAspectFit

        Item {
            id: drawingArea
            anchors.centerIn: parent
            width: dashboard.paintedWidth
            height: dashboard.paintedHeight

            // LEDs section
            Image {
                id: oilLight
                x: drawingArea.width * 0.45 - width / 2
                y: drawingArea.height * 0.40 - height / 2
                width: drawingArea.width * 0.11
                height: drawingArea.height * 0.14
                fillMode: Image.PreserveAspectFit
                source: oilTemperatureLED === 1 ? "Led_oil_on_r.png" : "LED_oil_off_r.png"
            }

            Image {
                id: engineLight
                x: drawingArea.width * 0.55 - width / 2
                y: drawingArea.height * 0.40 - height / 2
                width: drawingArea.width * 0.14
                height: drawingArea.height * 0.14
                fillMode: Image.PreserveAspectFit
                source: engineFaultLED === 1 ? "led_engine_on_r.png" : "led_engine_off_r.png"
            }

            // rpm
            Item {
                x: drawingArea.width * 0.191
                y: drawingArea.height * 0.60
                width: 1; height: 1
                Needle {
                    source: "needle_red.png"
                    height: dashboard.paintedHeight * 0.29
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: -height * 0.369
                    minValue: 0
                    maxValue: 80
                }
            }

            // speed
            Item {
                x: drawingArea.width * 0.809
                y: drawingArea.height * 0.602
                width: 1; height: 1
                Needle {
                    source: "needle_white.png"
                    height: dashboard.paintedHeight * 0.29
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: -height * 0.369
                    minValue: 0
                    maxValue: 240
                }
            }
        }
    }

    Connections {
        target: messageBus
        function onStateOilTemperature(OilState) {
            console.log("Flag received: " + OilState)
            if(OilState === 0) oilTemperatureLED = 0;
            else if (OilState === 1) oilTemperatureLED = 1;
        }
        function onStateEngineFault(engineFault) {
            console.log("Flag received: " + engineFault)
            if(engineFault === 0) engineFaultLED = 0;
            else if (engineFault === 1) engineFaultLED = 1;
        }
    }
}