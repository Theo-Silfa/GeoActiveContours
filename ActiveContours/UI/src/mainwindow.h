#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImageReader>
#include <QImage>

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

private:
    Ui::MainWindow *ui;

    ofeli::ActiveContour * ac;

    QImageReader * imageReader;

    QImage originalImg;

};

#endif // MAINWINDOW_H
