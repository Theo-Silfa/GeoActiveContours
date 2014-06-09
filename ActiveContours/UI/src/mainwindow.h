#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImageReader>
#include <QImageWriter>
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
    void DrawPixel(int x, int y, QRgb color);
    void DrawEllipse(int x0, int y0, int width, int height, QRgb color);
    void initPhiMatrix();

    int identifyPixel(QRgb centerPixel, QRgb upPixel, QRgb downPixel, QRgb leftPixel, QRgb rightPixel, QRgb upLeftPixel, QRgb upRightPixel, QRgb downLeftPixel, QRgb downRightPixel);
    bool fourConnection(QRgb upPixel, QRgb downPixel, QRgb leftPixel, QRgb rightPixel, bool strict);
    bool eightConnection(QRgb upLeftPixel, QRgb upRightPixel, QRgb downLeftPixel, QRgb downRightPixel, bool strict);

private slots:
    void on_actionOpen_triggered();
    void onMouseMovementOnScene(int x, int y);
    void onMouseClickOnScene(int x, int y);

    void on_actionTool_Bar_triggered();

    void on_actionSave_triggered();

    void shapeChanged(int height, int width);
    void startConverge();

private:
    Ui::MainWindow *ui;

    ofeli::ActiveContour * ac;

    SmartQGraphicsView * graphicsView;

    SmartQGraphicsScene * graphicScene;

    QImageReader * imageReader;
    QImageWriter * imageWriter;

    QGraphicsPixmapItem * item;
    QImage originalImg;
    QPixmap originalImgPixmap;
    QPixmap pixmapPhi;
    QPainter * painterPhi;
    QPainter * painterImg;

    //UI
    ToolDialog * toolDialog;

    bool imageSet;

    int shapeHeight;
    int shapeWidth;

};

#endif // MAINWINDOW_H
