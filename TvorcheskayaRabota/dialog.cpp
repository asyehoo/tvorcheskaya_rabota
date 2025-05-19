#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QTextStream>
Time temp;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &Dialog::line1);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &Dialog::line2);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &Dialog::line3);
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &Dialog::line4);
    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &Dialog::line5);
    connect(ui->lineEdit_6, &QLineEdit::textChanged, this, &Dialog::line6);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{

    QFile file("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\tasks.txt");
    file.open(QIODevice::Append);
    QTextStream out(&file);
    out << "Название: " << temp.get_name() << '\n';
    if(temp.get_day() < 10)
    {
        if(temp.get_month() < 10)
            out << "Дата сдачи: " << '0' << temp.get_day() << ".0" << temp.get_month() << '.' << temp.get_year() << '\n';
        else
            out << "Дата сдачи: " << '0' << temp.get_day() << '.' << temp.get_month() << '.' << temp.get_year() << '\n';
    }
    if(temp.get_month() < 10)
        out << "Дата сдачи: " << temp.get_day() << ".0" << temp.get_month() << '.' << temp.get_year() << '\n';
    out << "Дата сдачи: " <<  temp.get_day() << '.' << temp.get_month() << '.' << temp.get_year() << '\n';
    out << "Время на выполнение: " << temp.get_v() << '\n';
    out << "Стоимость работы: " << temp.get_price() << '\n';
    out << '\n';
    file.close();
}

void Dialog::line1(const QString &arg1)
{
    temp.set_name(arg1);
}
void Dialog::line2(const QString &arg)
{
    QVariant myVariant = arg;
    int myInt = myVariant.toInt();
    temp.set_day(myInt);
}
void Dialog::line3(const QString &arg)
{
    QVariant myVariant = arg;
    int myInt = myVariant.toInt();
    temp.set_month(myInt);
}
void Dialog::line4(const QString &arg)
{
    QVariant myVariant = arg;
    int myInt = myVariant.toInt();
    temp.set_year(myInt);
}
void Dialog::line5(const QString &arg)
{
    QVariant myVariant = arg;
    int myInt = myVariant.toInt();
    temp.set_v(myInt);
}
void Dialog::line6(const QString &arg)
{
    QVariant myVariant = arg;
    int myInt = myVariant.toInt();
    temp.set_price(myInt);
}
