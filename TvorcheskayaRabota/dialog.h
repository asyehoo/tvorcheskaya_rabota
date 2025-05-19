#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void accepted();

private slots:
    void on_buttonBox_accepted();
    void line1(const QString &arg1);
    void line2(const QString &arg);
    void line3(const QString &arg);
    void line4(const QString &arg);
    void line5(const QString &arg);
    void line6(const QString &arg);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
