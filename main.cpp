#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>

#include "d_pdf_document.h"
#include "d_pdf_image.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<DPdfDocument>("myLib", 1, 0, "PdfDoc");
    qmlRegisterType<DPdfImage>("myLib", 1, 0, "PdfImage");

//    const QString filename("/home/doga/dev/demo_files/pdf/000000000002-20210120-154238-PV_OK.pdf");

//    DPdfDocument cPdf(& app);

//    if (! cPdf.load(filename)) {
//        qDebug() << "ERROR: Failure to load file" << filename << ":" << cPdf.errorMessage();
//        return 1;
//    }

//    qDebug() << "PDF file" << filename << "loaded, it contains" << cPdf.pageCount() << "pages.";




    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
