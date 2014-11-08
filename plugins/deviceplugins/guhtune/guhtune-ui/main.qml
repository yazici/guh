import QtQuick 1.1

Rectangle {
    id: page
    width: 128
    height: 160
    color: "#000000"
    Image {
        id: splashImage
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        source: "qrc:///images/logo.png"
        opacity: 0
        NumberAnimation on opacity {id: splashUpAnimation; to: 1; duration: 3000 }
    }


    states: [
        State {
            name: "splashScreenUp"
            PropertyChanges { target: signal; color: "green"}
            PropertyChanges { target: flag; state: "FLAG_DOWN"}
        },
        State {
            name: "CRITICAL"
            PropertyChanges { target: signal; color: "red"}
            PropertyChanges { target: flag; state: "FLAG_UP"}
        }
    ]


//    ColorAnimation on color {
//        id: splashScreenAnimation
//        to: "#9FC8A4";
//        duration: 3000
//    }

//    Text {
//        id: timeText
//        anchors.centerIn: parent
//        visible: false
//        color: "black"
//        font.pixelSize: 20
//        font.bold: true
//        text:  Qt.formatDateTime(new Date(), "hh:mm")
//    }



}
