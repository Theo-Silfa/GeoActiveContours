#ifndef SMARTQGRAPHICSVIEW_H
#define SMARTQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsPixmapItem>

class SmartQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SmartQGraphicsView(QWidget *parent = 0);
    ~SmartQGraphicsView();
    void setImagePaintPointer (QImage * paintImage);
    void setPixmapItemPointer (QGraphicsPixmapItem * pixMapItem);

protected:
    void mouseMoveEvent ( QMouseEvent * mouseEvent );
    void mousePressEvent ( QMouseEvent * mouseEvent );
    bool event ( QEvent * event );
    void paintEvent ( QPaintEvent * event );

signals:
    void sendMouseMoveSignal(const int&, const int&);
    void sendMouseClickSignal(const int&, const int&);

public slots:

protected:
    bool insideWidget;
    QImage * paintImage;
    QGraphicsPixmapItem * pixMapItem;
};

#endif // SMARTQGRAPHICSVIEW_H
