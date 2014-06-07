#ifndef SMARTQGRAPHICSSCENE_H
#define SMARTQGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class SmartQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SmartQGraphicsScene(QObject *parent = 0);

protected:
    void mouseMoveEvent (QGraphicsSceneMouseEvent *mouseEvent );

signals:
    void sendMouseEventMessage(const int&, const int&);

public slots:

};

#endif // SMARTQGRAPHICSSCENE_H
