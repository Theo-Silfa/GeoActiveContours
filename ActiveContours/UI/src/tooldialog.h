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

protected:
    void wheelEvent ( QWheelEvent * event );

private:
    Ui::ToolDialog *ui;

private slots:
    void slidersChanged();

    void on_pushButtonStart_clicked();

signals:
    void sendShapeChangedSignal(const int&, const int&);
    void startConvergeSignal();
};

#endif // TOOLDIALOG_H
