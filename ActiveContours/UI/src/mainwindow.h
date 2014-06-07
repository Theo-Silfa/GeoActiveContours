#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImageReader>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "smartqgraphicsscene.h"
#include "region_based_active_contour_yuv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void changeStatusBar(int x, int y);

private:
    Ui::MainWindow *ui;

    ofeli::ActiveContour * ac;

    QGraphicsView * graphicsView;

    SmartQGraphicsScene * graphicScene;

    QImageReader * imageReader;

    QGraphicsPixmapItem * item;
    QImage originalImg;

};

#endif // MAINWINDOW_H
