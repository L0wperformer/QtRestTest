import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Rectangle {
    property string method: "GET"
    id: root
    width: 900
    height: 500
    visible: true
    color: "lightgrey"

    Connections {
        target: device
        function onResponseReceived(_response) {
            response.text = _response
        }
    }

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
            anchors.verticalCenter: parent.verticalCenter
        }
        RadioButton {
            id: postButton
            text: "POST"
            onClicked: method = "POST"
            anchors.verticalCenter: parent.verticalCenter
        }
        RadioButton {
            id: patchButton
            text: "PATCH"
            onClicked: method = "PATCH"
            anchors.verticalCenter: parent.verticalCenter
        }
        RadioButton {
            id: deleteButton
            text: "DELETE"
            onClicked: method = "DELETE"
            anchors.verticalCenter: parent.verticalCenter
        }
        RoundButton {

            radius: 5
            text: "SEND"

            width: 70
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                radius: parent.radius
                anchors.fill: parent
                color: "lightgrey"
                border {
                    color: parent.pressed ? "red" : "black"
                    width: 1
                }
            }

            onClicked: {

                device.newRequest(method, enterLink.text.toString(),
                                  request.text.toString())
            }
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
            selectByMouse: true
            text: "http://foo/bar/"
            Component.onCompleted: {
                let isSetting = device.getUrl()
                if (isSetting)
                    this.text = isSetting
            }
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
            ScrollView {
                anchors.fill: parent
                clip: true
                TextArea {
                    id: request
                    placeholderText: "{\"JsonRequest\":\"foo\"}"
                    selectByMouse: true
                    color: "black"
                    anchors.margins: 10
                    Component.onCompleted: {
                        let isSetting = device.getRequest()
                        if (isSetting)
                            this.text = isSetting
                    }
                }
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

            ScrollView {
                anchors.fill: parent
                clip: true
                TextArea {

                    id: response
                    placeholderText: "Response"
                    readOnly: true
                    selectByMouse: true
                    color: "black"
                    anchors.margins: 10
                }
            }
        }
    }
}
