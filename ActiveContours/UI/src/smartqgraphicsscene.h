#ifndef SMARTQGRAPHICSSCENE_H
#define SMARTQGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>

class SmartQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
protected:
    QGraphicsEllipseItem * currentEllipse;
public:
    explicit SmartQGraphicsScene(QObject *parent = 0);

protected:
    //void mouseMoveEvent (QGraphicsSceneMouseEvent *mouseEvent );

signals:
    void sendMouseEventMessage(const int&, const int&);

public slots:

};

#endif // SMARTQGRAPHICSSCENE_H
