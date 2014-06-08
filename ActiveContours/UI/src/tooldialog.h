#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QDialog>

namespace Ui {
class ToolDialog;
}

class ToolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolDialog(QWidget *parent = 0);
    ~ToolDialog();

private:
    Ui::ToolDialog *ui;
};

#endif // TOOLDIALOG_H
