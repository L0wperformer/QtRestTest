import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Item {
    property string method: "GET"
    id: root
    width: 640
    height: 480
    visible: true
    //title: qsTr("TestRest")
    Row {
        id: buttonRow
        height: 50
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        RadioButton {
            checked: true
            id: getButton
            text: "GET"
            onClicked: method = "GET"
        }
        RadioButton {
            id: postButton
            text: "POST"
            onClicked: method = "POST"
        }
        RadioButton {
            id: patchButton
            text: "PATCH"
            onClicked: method = "PATCH"
        }
        RadioButton {
            id: deleteButton
            text: "DELETE"
            onClicked: method = "PATCH"
        }
        RoundButton {

            radius: 5
            text: "SEND"
            width: 70
            height: 30
            onClicked: device.request(method, enterLink.text.toString())
        }
    }
    Rectangle {
        id: enterLinkRect
        anchors {
            top: buttonRow.bottom
            horizontalCenter: parent.horizontalCenter
            margins: 10
        }
        width: root.width - 10
        height: 20
        border {
            color: "black"
            width: 2
        }
        radius: 5
        TextInput {
            id: enterLink
            anchors {
                fill: parent
                margins: 5
            }

            text: "link"
        }
    }

    Row {

        spacing: 5
        anchors {
            bottom: parent.bottom
            top: enterLinkRect.bottom
            horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: root.width / 2 - 10
            height: parent.height - 10
            border {
                color: "black"
                width: 2
            }
            radius: 5

            TextEdit {
                text: "Request"
                anchors.fill: parent
                anchors.margins: 10
            }
        }
        Rectangle {
            width: root.width / 2 - 10
            height: parent.height - 10
            border {
                color: "black"
                width: 2
            }
            radius: 5

            TextEdit {
                text: "Response"
                anchors.fill: parent
                anchors.margins: 10
            }
        }
    }
}
