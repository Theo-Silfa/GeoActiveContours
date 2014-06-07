#include <QPointF>
#include <QDebug>
#include "smartqgraphicsscene.h"

SmartQGraphicsScene::SmartQGraphicsScene(QObject *parent) :
    QGraphicsScene (parent)
{
}

void SmartQGraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent  )
{
    qreal x = mouseEvent->scenePos().x();
    qreal y = mouseEvent->scenePos().y();

    if(x >= 0 && x < width() && y >= 0 && y < height())
        emit sendMouseEventMessage(x, y);
}
