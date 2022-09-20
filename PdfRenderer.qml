import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

import myLib 1.0

Rectangle {
    id: rootItem; objectName: "PdfRenderer"
    implicitWidth: 800
    implicitHeight: 600
    color: "transparent"

    property string source: ""
    property bool showButtons: true
    property bool autoHideButtons: true
    property bool showFilename: false

    property bool error: (doc.errorCode !== 0)
    property bool loaded: (doc.status === PdfDoc.CePdsReady)
    property bool empty: (doc.status === PdfDoc.CePdsUnavailable)

    onSourceChanged: {
        //console.log("Renderer source changed to '" + source + "'.");
        if (source.length === 0) {
            doc.close();
        } else {
            doc.load(source);
        }
    }
    function resetError() {
        doc.reset();
    }

    PdfDoc {
        id: doc
        onPageChanged: idPage.update();
    }

    PdfImage {
        id: idPage
        anchors.fill: parent
        image: doc.page
        smooth: true
        visible: loaded
    }

    Row {
        id: idCommands
        height: btGoToFirst.height
        anchors.right: parent.right
        anchors.top: parent.top
        spacing: 4
        visible: rootItem.loaded && (doc.pageCount > 1)
        opacity: 0.7
        Behavior on opacity { NumberAnimation { duration: 500; }}

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
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
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

    Text {
        id: idErrMsg
        text: doc.errorMessage
        anchors.fill: idPage
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        wrapMode: Text.Wrap
        visible: error
    }

    Text {
        id: idFilename
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 8
        height: parent.height / 16
        text: source
        fontSizeMode: Text.Fit
        visible: showFilename
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}D{i:1}
}
##^##*/
