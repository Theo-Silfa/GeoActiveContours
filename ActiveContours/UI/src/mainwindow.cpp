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
    imageWriter = new QImageWriter();

    graphicScene = new SmartQGraphicsScene(this);

    graphicsView = new SmartQGraphicsView(this);

    graphicsView->setProperty("mouseTracking", true);
    ui->horizontalLayout->addWidget(graphicsView);

    ac = nullptr;

    item = nullptr;

    imageSet = false;

    painterPhi = nullptr;

    shapeHeight = 50;
    shapeWidth = 50;

    toolDialog = new ToolDialog(this);
    toolDialog->setWindowFlags(Qt::Tool);
    toolDialog->show();

    //connect(graphicScene, SIGNAL(sendMouseEventMessage(int,int)), this, SLOT(changeStatusBar(int,int)));
    connect(graphicsView, SIGNAL(sendMouseMoveSignal(int,int)), this, SLOT(onMouseMovementOnScene(int,int)));
    connect(graphicsView, SIGNAL(sendMouseClickSignal(int,int)), this, SLOT(onMouseClickOnScene(int,int)));
    connect(toolDialog, SIGNAL(sendShapeChangedSignal(int,int)), this, SLOT(shapeChanged(int,int)));
    connect(toolDialog, SIGNAL(startConvergeSignal()), this, SLOT(startConverge()));
}

MainWindow::~MainWindow()
{
    delete imageReader;

    delete imageWriter;

    if(item != nullptr)
        delete item;

    if(painterPhi != nullptr)
        delete painterPhi;

    delete ui;
}

void MainWindow::DrawPixel(int x, int y, QRgb color)
{
    //originalImg.setPixel(x, y, color);
}

void MainWindow::DrawEllipse(int x0, int y0, int width, int height, QRgb color)
{
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;

    /* first half */
    for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
    {
        DrawPixel (x0 + x, y0 + y, color);
        DrawPixel (x0 - x, y0 + y, color);
        DrawPixel (x0 + x, y0 - y, color);
        DrawPixel (x0 - x, y0 - y, color);
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
        DrawPixel (x0 + x, y0 + y, color);
        DrawPixel (x0 - x, y0 + y, color);
        DrawPixel (x0 + x, y0 - y, color);
        DrawPixel (x0 - x, y0 - y, color);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
}

void MainWindow::initPhiMatrix()
{
    QImage testMatrix(originalImg.size(), QImage::Format_RGB16);
    testMatrix.fill(Qt::green);

    QImage imgPhi = pixmapPhi.toImage();
    QRgb *rowData = nullptr;
    QRgb *rowDataUp = nullptr;
    QRgb *rowDataDown = nullptr;

    QRgb centerPixel = 0;

    QRgb upPixel = 0;
    QRgb downPixel = 0;
    QRgb leftPixel = 0;
    QRgb rightPixel = 0;

    QRgb upLeftPixel = 0;
    QRgb upRightPixel = 0;
    QRgb downLeftPixel = 0;
    QRgb downRightPixel = 0;


    int heightPhi = imgPhi.height();
    int widthPhi = imgPhi.width();
    int result = 0;

    for(int y = 0; y < heightPhi; y++)
    {
        rowData = (QRgb*)imgPhi.scanLine(y);

        if( y != 0)
            rowDataUp = (QRgb*)imgPhi.scanLine(y - 1);
        else
            rowDataUp = nullptr;

        if(y != heightPhi - 1)
            rowDataDown = (QRgb*)imgPhi.scanLine(y + 1);
        else
            rowDataDown = nullptr;

        for(int x = 0; x < widthPhi; x++)
        {
            centerPixel = rowData[x] & ((1 << 6) - 1);

            if(x != 0)
                leftPixel = rowData[x - 1] & ((1 << 6) - 1);
            if(x != widthPhi - 1)
                rightPixel = rowData[x + 1] & ((1 << 6) - 1);

            if(rowDataUp != nullptr)
            {
                upPixel = rowDataUp[x] & ((1 << 6) - 1);

                if(x != 0)
                    upLeftPixel = rowDataUp[x - 1] & ((1 << 6) - 1);
                if(x != widthPhi - 1)
                    upRightPixel = rowDataUp[x + 1] & ((1 << 6) - 1);
            }

            if(rowDataDown != nullptr)
            {
                downPixel = rowDataDown[x] & ((1 << 6) - 1);

                if(x != 0)
                    downLeftPixel = rowDataDown[x - 1] & ((1 << 6) - 1);
                if(x != widthPhi - 1)
                    downRightPixel = rowDataDown[x + 1] & ((1 << 6) - 1);
            }

            result = identifyPixel(centerPixel, upPixel, downPixel, leftPixel, rightPixel,
                                   upLeftPixel, upRightPixel, downLeftPixel, downRightPixel);

            if(result == 3)
            {
                testMatrix.setPixel(x,y,qRgb(0,0,255));
            }

            if(result == -3)
            {
                testMatrix.setPixel(x,y,qRgb(255,0,0));
            }

            if(result == 1)
            {
                testMatrix.setPixel(x,y,qRgb(0,0,0));
            }

            if(result == -1)
            {
                testMatrix.setPixel(x,y,qRgb(255,255,255));
            }
        }

        upPixel = 0;
        downPixel = 0;
        leftPixel = 0;
        rightPixel = 0;

        upLeftPixel = 0;
        upRightPixel = 0;
        downLeftPixel = 0;
        downRightPixel = 0;

        result = 0;
    }

    testMatrix.save("D:/testMatrix.bmp", 0, 100);
}

int MainWindow::identifyPixel(QRgb centerPixel, QRgb upPixel, QRgb downPixel, QRgb leftPixel, QRgb rightPixel,
                           QRgb upLeftPixel, QRgb upRightPixel, QRgb downLeftPixel, QRgb downRightPixel)
{
    bool four_connection_strict = fourConnection(upPixel, downPixel, leftPixel, rightPixel, true);
    bool eight_connection_strict = eightConnection(upLeftPixel, upRightPixel, downLeftPixel, downRightPixel, true);
    bool four_connection = fourConnection(upPixel, downPixel, leftPixel, rightPixel, false);
    bool eight_connection = eightConnection(upLeftPixel, upRightPixel, downLeftPixel, downRightPixel, false);

    if(centerPixel != 0) //pixel is white
    {
        if(four_connection_strict == true && eight_connection_strict == true)
            return -3;
        else
            return -1;
    }
    else //pixel is black
    {
        if(four_connection == false && eight_connection == false) //TODO: This helps! Need to investigate!
            return 3;
        else
            return 1;
    }

    return 0;
}

bool MainWindow::fourConnection(QRgb upPixel, QRgb downPixel, QRgb leftPixel, QRgb rightPixel, bool strict)
{
    if(strict)
    {
        if (upPixel != 0 && downPixel != 0 && leftPixel != 0 && rightPixel != 0)
            return true;
    }
    else
    {
        if (upPixel != 0)
            return true;

        if (downPixel != 0)
            return true;

        if (leftPixel != 0)
            return true;

        if (rightPixel != 0)
            return true;
    }

    return false;
}

bool MainWindow::eightConnection(QRgb upLeftPixel, QRgb upRightPixel, QRgb downLeftPixel, QRgb downRightPixel, bool strict)
{
    if(strict)
    {
        if (upLeftPixel != 0 && upRightPixel != 0 && downLeftPixel != 0 && downRightPixel != 0)
            return true;
    }
    else
    {
        if (upLeftPixel != 0)
            return true;

        if (upRightPixel != 0)
            return true;

        if (downLeftPixel != 0)
            return true;

        if (downRightPixel != 0)
            return true;
    }

    return false;
}

void MainWindow::onMouseMovementOnScene(int x, int y)
{
    if(imageSet)
    {

    }

    //Update Status Bar
    QString coordinates_string = QString("(%1 | %2)").arg(QString::number(x), QString::number(y));
    ui->statusBar->showMessage(coordinates_string);
}

void MainWindow::onMouseClickOnScene(int x, int y)
{

    painterImg->drawEllipse(x - (shapeWidth/2), y - (shapeHeight/2), shapeWidth, shapeHeight);
    painterPhi->drawEllipse(x - (shapeWidth/2), y - (shapeHeight/2),shapeWidth,shapeHeight);
    item->setPixmap(originalImgPixmap);
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

    originalImgPixmap = QPixmap::fromImage(originalImg);

    painterImg = new QPainter(&originalImgPixmap);

    QBrush imgBrush(Qt::red, Qt::Dense7Pattern);
    painterImg->setBrush(imgBrush);
    painterImg->setPen(Qt::blue);

    pixmapPhi = QPixmap(originalImg.size());

    pixmapPhi.fill(Qt::black);

    painterPhi = new QPainter(&pixmapPhi);
    QBrush phiBrush(Qt::white, Qt::SolidPattern);
    painterPhi->setBrush(phiBrush);
    painterPhi->setPen(Qt::NoPen);

    item = new QGraphicsPixmapItem(originalImgPixmap);

    graphicScene->addItem(item);

    graphicsView->setScene(graphicScene);

    graphicsView->setSceneRect(originalImg.rect());

    graphicsView->show();

    imageSet = true;
}

void MainWindow::on_actionTool_Bar_triggered()
{
    toolDialog->show();
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
         tr("Save Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp *.tif)"));

    pixmapPhi.save(filename, 0, 100);

    //imageWriter->write(ImgPhi);
}

void MainWindow::shapeChanged(int height, int width)
{
    shapeHeight = height;
    shapeWidth = width;
}

void MainWindow::startConverge()
{
    initPhiMatrix();
}
