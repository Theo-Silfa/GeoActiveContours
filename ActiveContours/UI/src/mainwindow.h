#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImageReader>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

#include "smartqgraphicsscene.h"
#include "smartqgraphicsview.h"
#include "region_based_active_contour_yuv.hpp"
#include "tooldialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void DrawPixel(int x, int y);
    void DrawEllipse(int x0, int y0, int width, int height);

private slots:
    void on_actionOpen_triggered();
    void onMouseMovementOnScene(int x, int y);

    void on_actionTool_Bar_triggered();

private:
    Ui::MainWindow *ui;

    ofeli::ActiveContour * ac;

    SmartQGraphicsView * graphicsView;

    SmartQGraphicsScene * graphicScene;

    QImageReader * imageReader;

    QGraphicsPixmapItem * item;
    QImage originalImg;
    QImage originalImgPaintCopy;

    //UI
    ToolDialog * toolDialog;

    bool imageSet;

};

#endif // MAINWINDOW_H
