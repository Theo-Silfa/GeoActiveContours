#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageReader = new QImageReader();

    ac = nullptr;
}

MainWindow::~MainWindow()
{
    delete imageReader;
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
         tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp *.tif)"));

    imageReader->setFileName(filename);

    originalImg = imageReader->read();

    if(originalImg.isNull())
    {
        qDebug()<<"Error opening image: "<<imageReader->errorString();
        return;
    }

    qDebug()<<"Opened file: "<<filename;
    qDebug() << "Image size: " << originalImg.size();

}
