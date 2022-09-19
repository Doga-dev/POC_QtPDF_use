#ifndef D_PDF_IMAGE_H
#define D_PDF_IMAGE_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>

class DPdfImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    explicit            DPdfImage       (QQuickItem * parent = nullptr);
    Q_INVOKABLE void    setImage        (const QImage & image);
    void                paint           (QPainter * painter);
    QImage              image           () const;

signals:
    void                imageChanged    ();

private:
    QImage      m_current_image;
};

#endif // D_PDF_IMAGE_H
