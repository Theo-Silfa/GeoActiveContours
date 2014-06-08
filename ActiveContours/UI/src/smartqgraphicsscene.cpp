#include <QPointF>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include "smartqgraphicsscene.h"

SmartQGraphicsScene::SmartQGraphicsScene(QObject *parent) :
    QGraphicsScene (parent)
{
    currentEllipse = nullptr;
}

/*void SmartQGraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent  )
{
    qreal x = mouseEvent->scenePos().x();
    qreal y = mouseEvent->scenePos().y();


    if(x >= 0 && x < width() && y >= 0 && y < height())
    {
        emit sendMouseEventMessage(x, y);

        QGraphicsScene::mouseMoveEvent(mouseEvent);

        if(x >= 25 && x < (width() - 25) && y >= 25 && y < (height() - 25))
        {
            if(currentEllipse == nullptr)
            {

                    QPen ellipsePen;
                    QBrush ellipseBrush;

                    ellipsePen.setStyle(Qt::SolidLine);
                    ellipsePen.setWidth(1);
                    ellipsePen.setBrush(Qt::blue);
                    ellipsePen.setCapStyle(Qt::FlatCap);
                    ellipsePen.setJoinStyle(Qt::MiterJoin);

                    ellipseBrush.setStyle(Qt::SolidPattern);
                    ellipseBrush.setColor(Qt::red);

                    currentEllipse = addEllipse(x-25,y-25,50,50,ellipsePen,ellipseBrush);

                    //currentEllipse->setFlag(QGraphicsItem::ItemIsMovable);
            }
            else
            {
                //currentEllipse->setPos(x, y);
            }
        }
    }
    else
    {
        emit sendMouseEventMessage(0, 0);

        if(currentEllipse != nullptr)
        {

            removeItem(currentEllipse);

            delete currentEllipse;

            currentEllipse = nullptr;
        }
    }

}*/
