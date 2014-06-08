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

    imageSet = false;

    toolDialog = new ToolDialog(this);
    toolDialog->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    toolDialog->show();

    //connect(graphicScene, SIGNAL(sendMouseEventMessage(int,int)), this, SLOT(changeStatusBar(int,int)));
    connect(graphicsView, SIGNAL(sendMouseEventMessage(int,int)), this, SLOT(onMouseMovementOnScene(int,int)));
}

MainWindow::~MainWindow()
{
    delete imageReader;

    if(item != nullptr)
        delete item;

    delete ui;
}

void MainWindow::DrawPixel(int x, int y)
{
    QRgb value;
    value = qRgb(255,0,0);
    originalImgPaintCopy.setPixel(x, y, value);
}

void MainWindow::DrawEllipse(int x0, int y0, int width, int height)
{
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;

    /* first half */
    for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
    {
        DrawPixel (x0 + x, y0 + y);
        DrawPixel (x0 - x, y0 + y);
        DrawPixel (x0 + x, y0 - y);
        DrawPixel (x0 - x, y0 - y);
        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    /* second half */
    for (x = width, y = 0, sigma = 2*a2+b2*(1-2*width); a2*y <= b2*x; y++)
    {
        DrawPixel (x0 + x, y0 + y);
        DrawPixel (x0 - x, y0 + y);
        DrawPixel (x0 + x, y0 - y);
        DrawPixel (x0 - x, y0 - y);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
}

void MainWindow::onMouseMovementOnScene(int x, int y)
{
    if(imageSet)
    {
        originalImgPaintCopy = originalImg;

        DrawEllipse(x,y,10,10);
        //Update Status Bar
        QString coordinates_string = QString("(%1 | %2)").arg(QString::number(x), QString::number(y));
        ui->statusBar->showMessage(coordinates_string);
    }
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

    originalImgPaintCopy = originalImg;

    item = new QGraphicsPixmapItem(QPixmap::fromImage(originalImgPaintCopy));

    graphicScene->addItem(item);

    graphicsView->setScene(graphicScene);

    graphicsView->setSceneRect(originalImgPaintCopy.rect());

    graphicsView->setImagePaintPointer(&originalImgPaintCopy);
    graphicsView->setPixmapItemPointer(item);

    graphicsView->show();

    imageSet = true;
}

void MainWindow::on_actionTool_Bar_triggered()
{
    toolDialog->show();
}
