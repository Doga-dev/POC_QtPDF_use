#ifndef DPDFDOCUMENT_H
#define DPDFDOCUMENT_H

#include <QImage>
#include <QObject>
#include <QString>

class QPdfDocument;

class DPdfDocument : public QObject
{
    Q_OBJECT
public:
    enum EnPdfDocumentError {
        CePdeAllocationError = 100,
        CePde
    };
    enum EnPdfDocumentStatus {
        CePdsUnavailable,
        CePdsLoading,
        CePdsReady,
        CePdsUnloading,
        CePdsError,
        _cePdsNumber
    };
    Q_ENUM(EnPdfDocumentStatus)

    Q_PROPERTY(EnPdfDocumentStatus  status          READ status                                 NOTIFY statusChanged)
    Q_PROPERTY(int                  errorCode       READ errorCode                              NOTIFY errorCodeChanged)
    Q_PROPERTY(QString              errorMessage    READ errorMessage                           NOTIFY errorCodeChanged)
    Q_PROPERTY(int                  pageCount       READ pageCount                              NOTIFY pageCountChanged)
    Q_PROPERTY(int                  pageNumber      READ pageNumber     WRITE setPageNumber     NOTIFY pageNumberChanged)
    Q_PROPERTY(bool                 isFirstPage     READ isFirstPage                            NOTIFY isFirstPageChanged)
    Q_PROPERTY(bool                 isLastPage      READ isLastPage                             NOTIFY isLastPageChanged)
    Q_PROPERTY(QImage               page            READ page                                   NOTIFY pageChanged)

    explicit            DPdfDocument        (QObject * parent = nullptr);
                        ~DPdfDocument       ();

    EnPdfDocumentStatus status              () const    {   return m_status;    }
    int                 errorCode           () const    {   return m_error;     }
    QString             errorMessage        () const;

    Q_INVOKABLE bool    load                (const QString & filePath);
    Q_INVOKABLE bool    close               ();

    int                 pageCount           () const    {   return m_pageCount;     }
    int                 pageNumber          () const    {   return m_pageNumber;    }
    bool                isFirstPage         () const    {   return m_pageNumber <= 1;   }
    bool                isLastPage          () const    {   return m_pageNumber == m_pageCount;   }
    QImage              page                () const    {   return m_page;          }

public slots:
    void                setPageNumber       (int pageNumber);
    void                goToFirstPage       ()          {   setPageNumber(1);                   }
    void                goToPreviousPage    ()          {   setPageNumber(m_pageNumber - 1);    }
    void                goToNextPage        ()          {   setPageNumber(m_pageNumber + 1);    }
    void                goToLastPage        ()          {   setPageNumber(m_pageCount);         }

signals:
    void                statusChanged       (EnPdfDocumentStatus status);
    void                errorCodeChanged    ();
    void                pageCountChanged    (int pageCount);
    void                pageNumberChanged   (int pageNumber);
    void                isFirstPageChanged  (bool isFirstPage);
    void                isLastPageChanged   (bool isLastPage);
    void                pageChanged         (const QImage & page);

private slots:
    void                setStatus           (int status);
    void                setErrorCode        (int errorCode);
    void                setPageCount        (int pageCount);
    void                setPage             ();

private:
    EnPdfDocumentStatus m_status;
    int                 m_error;
    QPdfDocument *      m_document;
    int                 m_pageCount;
    int                 m_pageNumber;
    QImage              m_page;
};

#endif // DPDFDOCUMENT_H
