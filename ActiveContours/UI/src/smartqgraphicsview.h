#ifndef SMARTQGRAPHICSVIEW_H
#define SMARTQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class SmartQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SmartQGraphicsView(QWidget *parent = 0);
    ~SmartQGraphicsView();

protected:
    void mouseMoveEvent ( QMouseEvent * mouseEvent );
    bool event ( QEvent * event );

signals:
    void sendMouseEventMessage(const int&, const int&);

public slots:

protected:
    bool insideWidget;
};

#endif // SMARTQGRAPHICSVIEW_H
