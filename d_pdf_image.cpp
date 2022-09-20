#include "d_pdf_image.h"

DPdfImage::DPdfImage(QQuickItem * parent) : QQuickPaintedItem(parent)
  , m_current_image()
{
}

void DPdfImage::paint(QPainter * painter)
{
    if (m_current_image.isNull())
        return;
    QRectF bounding_rect = boundingRect();
    QImage scaled = m_current_image.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if(center.x() < 0)
        center.setX(0);
    if(center.y() < 0)
        center.setY(0);
   painter->drawImage(center, scaled);
}

QImage DPdfImage::image() const
{    return m_current_image;
}

void DPdfImage::setImage(const QImage &image)
{
    m_current_image = image;
    update();
}
