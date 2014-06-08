#include <QDebug>

#include <QMouseEvent>
#include <QPointF>
#include <QPoint>
#include <QCursor>

#include "smartqgraphicsview.h"

SmartQGraphicsView::SmartQGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    insideWidget = false;
    paintImage = nullptr;
    pixMapItem = nullptr;
}

SmartQGraphicsView::~SmartQGraphicsView()
{

}

void SmartQGraphicsView::mouseMoveEvent ( QMouseEvent * mouseEvent )
{
    QGraphicsScene * graphicScene = scene();

    if(graphicScene != nullptr)
    {
        if(insideWidget)
        {
            QPointF scenePoint = mapToScene(mouseEvent->x(), mouseEvent->y());

            if(scenePoint.x() >= 0 && scenePoint.x() < graphicScene->width() && scenePoint.y() >= 0 && scenePoint.y() < graphicScene->height())
            {
                emit sendMouseEventMessage(scenePoint.x(), scenePoint.y());
            }
            else
            {
                emit sendMouseEventMessage(-1, -1);
            }
        }
    }
}

bool SmartQGraphicsView::event(QEvent *event)
{
    if (event->type() == QEvent::Enter)
        insideWidget = true;
    if (event->type()==QEvent::Leave)
    {
        insideWidget = false;
        emit sendMouseEventMessage(-1, -1);
    }

    return QGraphicsView::event(event);
}

void SmartQGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    if(pixMapItem != nullptr)
        pixMapItem->setPixmap(QPixmap::fromImage(*paintImage));
}

void SmartQGraphicsView::setImagePaintPointer(QImage *paintImage)
{
    this->paintImage = paintImage;
}

void SmartQGraphicsView::setPixmapItemPointer(QGraphicsPixmapItem *pixMapItem)
{
    this->pixMapItem = pixMapItem;
}
