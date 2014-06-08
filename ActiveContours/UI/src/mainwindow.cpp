#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QGraphicsPixmapItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageReader = new QImageReader();

    graphicScene = new SmartQGraphicsScene(this);

    graphicsView = new SmartQGraphicsView(this);

    graphicsView->setProperty("mouseTracking", true);
    ui->horizontalLayout->addWidget(graphicsView);

    ac = nullptr;

    item = nullptr;

    //connect(graphicScene, SIGNAL(sendMouseEventMessage(int,int)), this, SLOT(changeStatusBar(int,int)));
    connect(graphicsView, SIGNAL(sendMouseEventMessage(int,int)), this, SLOT(changeStatusBar(int,int)));
}

MainWindow::~MainWindow()
{
    delete imageReader;

    if(item != nullptr)
        delete item;

    delete ui;
}

void MainWindow::changeStatusBar(int x, int y)
{
    QString coordinates_string = QString("(%1 | %2)").arg(QString::number(x), QString::number(y));
    ui->statusBar->showMessage(coordinates_string);
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

    item = new QGraphicsPixmapItem(QPixmap::fromImage(originalImg));

    graphicScene->addItem(item);

    graphicsView->setScene(graphicScene);

    graphicsView->setSceneRect(originalImg.rect());

    graphicsView->show();

}
