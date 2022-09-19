#ifndef INC_PDF_DOC_H
#define INC_PDF_DOC_H

#define QT_PDF

#ifdef QT_PDF

#include <QtPdf/QtPdf>

#else

class QPdfDocument : public QObject
{
    Q_OBJECT

public:
    enum Status {
        Null,
        Loading,
        Ready,
        Unloading,
        Error
    };

    enum DocumentError {
        NoError,
        UnknownError,
        DataNotYetAvailableError,
        FileNotFoundError,
        InvalidFileFormatError,
        IncorrectPasswordError,
        UnsupportedSecuritySchemeError
    };

    explicit QPdfDocument(QObject *parent = nullptr){}
    ~QPdfDocument(){}

    DocumentError load(const QString &fileName) {return NoError;}

    Status status() const   { return Ready;  }

    DocumentError error() const {return NoError;}

    void close(){}

    int pageCount() const{return 1;}

    QSizeF pageSize(int page) const {return QSizeF(640,480);}

    QImage render(int page, QSize imageSize) {return QImage();}

Q_SIGNALS:
    void statusChanged(QPdfDocument::Status status);
    void pageCountChanged(int pageCount);
};

#endif

#endif // INC_PDF_DOC_H
