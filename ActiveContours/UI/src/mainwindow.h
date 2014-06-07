#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    ofeli::ActiveContour * ac;
};

#endif // MAINWINDOW_H
