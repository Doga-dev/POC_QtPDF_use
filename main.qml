import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("POC QtPDF use")

    PdfRenderer {
        id: renderer
        anchors.fill: parent
    }
}
