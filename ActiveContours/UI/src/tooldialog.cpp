#include <QWheelEvent>

#include "tooldialog.h"
#include "ui_tooldialog.h"

ToolDialog::ToolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolDialog)
{
    ui->setupUi(this);

    connect(ui->horizontalSliderHeight,SIGNAL(valueChanged(int)), this, SLOT(slidersChanged()));
    connect(ui->horizontalSliderWidth,SIGNAL(valueChanged(int)), this, SLOT(slidersChanged()));
}

ToolDialog::~ToolDialog()
{
    delete ui;
}

void ToolDialog::wheelEvent(QWheelEvent *event)
{
    int one = 1;

    if(event->delta() > 0)
    {
        one = 1;
    }
    else
    {
        one = -1;
    }

    int valueHeight = ui->horizontalSliderHeight->property("value").toInt();
    int stepHeight = ui->horizontalSliderHeight->property("singleStep").toInt();
    ui->horizontalSliderHeight->setValue(valueHeight + stepHeight*one);

    int valueWidth = ui->horizontalSliderWidth->property("value").toInt();
    int stepWidth = ui->horizontalSliderWidth->property("singleStep").toInt();
    ui->horizontalSliderWidth->setValue(valueWidth + stepWidth*one);

    emit sendShapeChangedSignal(valueHeight + stepHeight*one, valueWidth + stepWidth*one);

    QDialog::wheelEvent(event);
}

void ToolDialog::slidersChanged()
{
    emit sendShapeChangedSignal(ui->horizontalSliderHeight->property("value").toInt(), ui->horizontalSliderWidth->property("value").toInt());
}

void ToolDialog::on_pushButtonStart_clicked()
{
    emit startConvergeSignal();
}
