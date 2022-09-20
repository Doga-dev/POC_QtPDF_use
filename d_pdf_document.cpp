
#include <QtPdf/QtPdf>

#include "d_pdf_document.h"


DPdfDocument::DPdfDocument(QObject * parent) : QObject(parent)
  , m_status(CePdsUnavailable)
  , m_error(0)
  , m_document(nullptr)
  , m_pageCount(0)
  , m_pageNumber(-1)
  , m_page()
{
    m_document = new QPdfDocument();
    if (m_document) {
        QObject::connect(m_document, & QPdfDocument::statusChanged      , this, & DPdfDocument::setStatus);
        QObject::connect(m_document, & QPdfDocument::pageCountChanged   , this, & DPdfDocument::setPageCount);
    } else {
        setErrorCode(CePdeAllocationError);
    }
}

DPdfDocument::~DPdfDocument()
{
    if (m_document) {
        m_document->close();
        m_document->deleteLater();
    }
}

QString DPdfDocument::errorMessage() const
{
    QString msg;
    switch (m_error) {
        case QPdfDocument::NoError                          :   msg = "No error occurred.";                                                         break;
        case QPdfDocument::UnknownError                     :   msg = "Unknown type of error.";                                                     break;
        case QPdfDocument::DataNotYetAvailableError         :   msg = "The document is still loading, it's too early to attempt the operation.";    break;
        case QPdfDocument::FileNotFoundError                :   msg = "This file was not found.";                                                   break;
        case QPdfDocument::InvalidFileFormatError           :   msg = "This file is not a valid PDF file.";                                         break;
        case QPdfDocument::IncorrectPasswordError           :   msg = "Wrong password given to open this file.";                                    break;
        case QPdfDocument::UnsupportedSecuritySchemeError   :   msg = "Failure to unlock this kind of PDF file.";                                   break;
        case CePdeAllocationError                           :   msg = "Failure to create document object";                                          break;
        default                                             :   msg = "Invalide error code" + QString::number(m_error);                             break;
    }
    return msg;
}

bool DPdfDocument::load(const QString & filePath)
{
    bool doneOk = m_document;
    if (doneOk) {
        setErrorCode(m_document->load(filePath));       // maybe do it in another thread, file can be large
        doneOk = (m_error == QPdfDocument::NoError);
    }
    if (doneOk) {
        setPageCount(m_document->pageCount());
    }
    setPage();
    return doneOk;
}

bool DPdfDocument::close()
{
    bool doneOk = m_document;
    if (doneOk) {
        m_document->close();
        m_pageNumber = -1;
    }
    return doneOk;
}

void DPdfDocument::setPageNumber(int pageNumber)
{
    int nextPageNumber = ((m_pageCount == 0)
                          ? 0
                          : ((pageNumber < 0 )
                             ? 0
                             : ((pageNumber >= m_pageCount)
                                ? m_pageCount - 1
                                : pageNumber)));

    if (m_pageNumber == nextPageNumber)
        return;

    m_pageNumber = nextPageNumber;
    emit pageNumberChanged(m_pageNumber);
    setPage();
}

void DPdfDocument::setStatus(int status)
{
    if (m_status == status)
        return;

    if (status == QPdfDocument::Error) {
        setErrorCode(m_document->error());
    }
    m_status = static_cast<EnPdfDocumentStatus>(status);
    emit statusChanged(m_status);
}

void DPdfDocument::setErrorCode(int errorCode)
{
    if (m_error == errorCode)
        return;

    m_error = errorCode;
    emit errorCodeChanged();
}

void DPdfDocument::setPageCount(int pageCount)
{
    if (m_pageCount == pageCount)
        return;

    m_pageCount = pageCount;
    emit pageCountChanged(m_pageCount);
    if (m_pageNumber != 0) {
        goToFirstPage();
    } else {
        emit pageChanged();
    }
}

void DPdfDocument::setPage()
{
    if ((! m_document) || (m_document->status() != QPdfDocument::Ready))
        return;
    QSizeF pageSize = m_document->pageSize(m_pageNumber);
    m_page = m_document->render(m_pageNumber, pageSize.toSize());
    emit pageChanged();
}
