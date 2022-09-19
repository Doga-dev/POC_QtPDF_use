import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

import myLib 1.0

Rectangle {
    id: rootItem; objectName: "PdfRenderer"
    implicitWidth: 800
    implicitHeight: 600
    color: "#ddeeff"

    PdfDoc {
        id: doc
        onPageChanged: idPage.update();
    }

    RowLayout {
        id: idCommands
        height: 96
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 8

        Rectangle {
            id: itemFilename
            Layout.fillWidth: true
            height: parent.height
            color: "transparent"

            Label {
                id: labelFilename
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 0
                height: parent.height / 4
                text: qsTr("Filename")
                fontSizeMode: Text.HorizontalFit
                minimumPixelSize: 8
            }

            TextInput {
                id: textInputFilename
                anchors.left: parent.left
                anchors.top: labelFilename.bottom
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: "/home/doga/Downloads/testPdf12pages.pdf"
                font.pixelSize: height / 2
            }
        }

        Button {
            id: btLoadClose
            text: ((doc.status === PdfDoc.CePdsReady)
                   ? qsTr("Close")
                   : ((doc.status === PdfDoc.CePdsUnavailable)
                      ? qsTr("Load")
                      : qsTr("Reset")))
            enabled: ((doc.status !== PdfDoc.CePdsLoading) || (doc.status === PdfDoc.CePdsUnloading))
            onClicked: {
                if (doc.status === PdfDoc.CePdsReady) {
                    doc.close();
                } else if (doc.status === PdfDoc.CePdsUnavailable) {
                    doc.load(textInputFilename.text)
                } else {
                    // todo
                }
            }
        }

        Item {
            id: idSeparator
            height: parent.height
            width: height / 2
        }

        Button {
            id: btGoToFirst
            text: qsTr("First")
            enabled: ! doc.isFirstPage
            onClicked: doc.goToFirstPage();
        }

        Button {
            id: btGoToPrevious
            text: qsTr("Previous")
            enabled: ! doc.isFirstPage
            onClicked: doc.goToPreviousPage();
        }

        Text {
            id: textPageNumber
            height: parent.height
            width: height
            text: (doc.pageNumber + 1) + " / " + doc.pageCount
        }

        Button {
            id: btGoToNext
            text: qsTr("Next")
            enabled: ! doc.isLastPage
            onClicked: doc.goToNextPage();
        }

        Button {
            id: btGoToLast
            text: qsTr("Last")
            enabled: ! doc.isLastPage
            onClicked: doc.goToLastPage();
        }
    }

    PdfImage {
        id: idPage
        anchors.left: parent.left
        anchors.top: idCommands.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8
        image: doc.page
        smooth: true
    }

    Text {
        id: idErrMsg
        text: doc.errorMessage
        anchors.fill: idPage
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        wrapMode: Text.Wrap
        visible: (doc.errorCode !== 0)
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}D{i:1}
}
##^##*/
