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
