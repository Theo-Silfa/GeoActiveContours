#include "tooldialog.h"
#include "ui_tooldialog.h"

ToolDialog::ToolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolDialog)
{
    ui->setupUi(this);
}

ToolDialog::~ToolDialog()
{
    delete ui;
}
