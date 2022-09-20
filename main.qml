import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtQuick.Window 2.12

Window {
    id: rootWindow
    width: 1920
    height: 1080
    visible: true
    title: qsTr("POC QtPDF use")

    readonly property real margin: 8
    ColumnLayout {
        id: idLayout
        x: rootWindow.margin; y: rootWindow.margin;
        width: rootWindow.width - 2 * x;
        height: rootWindow.height - 2 * y;
        spacing: rootWindow.margin

        Rectangle {
            id: idSourceRect
            height: 64
            width: parent.width
            color: "transparent"

            Label {
                id: labelFilename
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 0
                anchors.leftMargin: 8
                height: parent.height / 4
                text: qsTr("Filename")
                fontSizeMode: Text.VerticalFit
                font.bold: true
                minimumPixelSize: 8
            }

            Button {
                id: btLoadClose
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 0
                width: 128
                text: (renderer.loaded
                       ? qsTr("Close")
                       : (renderer.empty
                          ? qsTr("Load")
                          : (renderer.error
                             ? qsTr("Reset")
                             : "")))
                enabled: ((textInputFilename.text.length && renderer.empty) || renderer.loaded || renderer.error)
                onClicked: {
                    //console.log("Click on button '" + btLoadClose.text + "'.");
                    if (renderer.loaded) {
                        renderer.source = "";
                    } else if (renderer.empty) {
                        renderer.source = textInputFilename.text;
                    } else {
                        renderer.resetError();
                    }
                }
            }

            TextInput {
                id: textInputFilename
                anchors.left: parent.left
                anchors.top: labelFilename.bottom
                anchors.bottom: parent.bottom
                anchors.right: btLoadClose.left
                anchors.margins: 0
                anchors.rightMargin: 8
                text: "/home/doga/Downloads/testPdf12pages.pdf"
                font.pixelSize: parent.height / 2
            }
        }

        PdfRenderer {
            id: renderer
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: ""
        }
    }
}
