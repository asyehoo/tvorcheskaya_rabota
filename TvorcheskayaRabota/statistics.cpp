#include "statistics.h"
#include "ui_statistics.h"
#include <QFile>
#include "mainwindow.h"
#include <vector>


statistics::statistics(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::statistics)
{
    ui->setupUi(this);
    stats_of_completed();
    stats_of_deleted();
    stats_of_active();
    connect(ui->closeB, &QPushButton::clicked, this, &statistics::closeWin);
}

statistics::~statistics()
{
    delete ui;
}


void statistics::stats_of_completed()
{
    std::vector<Time> com;
    QFile comp("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\completedTasks.txt");
    comp.open(QIODevice::ReadOnly);
    QString name;
    int day = 0, month = 0, year = 0, v = 0, price = 0;
    bool validRecord = false;

    while (!comp.atEnd()) {
        QString line = comp.readLine();
        if (line.startsWith("Название:")) {
            name = line.mid(line.indexOf(":") + 2).trimmed();
            validRecord = true;
        } else if (line.startsWith("Дата сдачи:")) {
            QString dateString = line.mid(line.indexOf(":") + 2).trimmed();
            QStringList dateParts = dateString.split('.');
            if (dateParts.size() == 3) {
                bool ok;
                day = dateParts[0].toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid day format: " << dateParts[0];
                    validRecord = false;
                    continue;
                }
                month = dateParts[1].toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid month format: " << dateParts[1];
                    validRecord = false;
                    continue;
                }
                year = dateParts[2].toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid year format: " << dateParts[2];
                    validRecord = false;
                    continue;
                }
            } else {
                qDebug() << "Неверный формат даты: " << dateString;
                validRecord = false;
                continue;
            }
        } else if (line.startsWith("Время на выполнение:")) {
            bool ok;
            v = line.mid(line.indexOf(":") + 2).trimmed().toInt(&ok);
            if (!ok) {
                qDebug() << "Invalid v format: " << line.mid(line.indexOf(":") + 2).trimmed();
                validRecord = false;
                continue;
            }
        } else if (line.startsWith("Стоимость работы:")) {
            bool ok;
            price = line.mid(line.indexOf(":") + 2).trimmed().toInt(&ok);
            if (!ok) {
                qDebug() << "Invalid price format: " << line.mid(line.indexOf(":") + 2).trimmed();
                validRecord = false;
                continue;
            }
            if (validRecord) {
                Time task(name, day, month, year, v, price);
                com.push_back(task);
                validRecord = false;
            }
        }
    }
    comp.close();
    double sredPrice = 0;
    double sredDayPrice = 0;
    int totalPrice = 0;
    int totalDays = 0;
    for(int i = 0; i < com.size(); i++)
    {
        totalPrice += com[i].get_price();
        totalDays += com[i].get_v();
    }
    sredPrice = totalPrice / com.size();
    sredDayPrice = totalPrice / totalDays;
    QString text;
    text += "Количество выполненных задач: " + QString::number(com.size()) + "\n";
    text += "Заработано всего: " + QString::number(totalPrice, 'f', 2) + "\n";
    text += "Дней потрачено на работу: " + QString::number(totalDays) + "\n";
    text += "Заработано в среднем за задачу: " + QString::number(sredPrice, 'f', 2) + "\n";
    text += "Заработано в среднем в день: " + QString::number(sredDayPrice, 'f', 2) + "\n";

    ui->textEdit->setText(text);
}
void statistics::stats_of_deleted()
{
    std::vector<Time> del;
    QFile delet("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\deletedTasks.txt");
    delet.open(QIODevice::ReadOnly);
    QString name;
    int day = 0, month = 0, year = 0, v = 0, price = 0;
    bool validRecord = false;

    while (!delet.atEnd()) {
        QString line = delet.readLine();
        if (line.startsWith("Название:")) {
            name = line.mid(line.indexOf(":") + 2).trimmed();
            validRecord = true;
        } else if (line.startsWith("Дата сдачи:")) {
            QString dateString = line.mid(line.indexOf(":") + 2).trimmed();
            QStringList dateParts = dateString.split('.');
            if (dateParts.size() == 3) {
                bool ok;
                day = dateParts[0].toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid day format: " << dateParts[0];
                    validRecord = false;
                    continue;
                }
                month = dateParts[1].toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid month format: " << dateParts[1];
                    validRecord = false;
                    continue;
                }
                year = dateParts[2].toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid year format: " << dateParts[2];
                    validRecord = false;
                    continue;
                }
            } else {
                qDebug() << "Неверный формат даты: " << dateString;
                validRecord = false;
                continue;
            }
        } else if (line.startsWith("Время на выполнение:")) {
            bool ok;
            v = line.mid(line.indexOf(":") + 2).trimmed().toInt(&ok);
            if (!ok) {
                qDebug() << "Invalid v format: " << line.mid(line.indexOf(":") + 2).trimmed();
                validRecord = false;
                continue;
            }
        } else if (line.startsWith("Стоимость работы:")) {
            bool ok;
            price = line.mid(line.indexOf(":") + 2).trimmed().toInt(&ok);
            if (!ok) {
                qDebug() << "Invalid price format: " << line.mid(line.indexOf(":") + 2).trimmed();
                validRecord = false;
                continue;
            }
            if (validRecord) {
                Time task(name, day, month, year, v, price);
                del.push_back(task);
                validRecord = false;
            }
        }
    }
    delet.close();
    double sredPrice = 0;
    double sredDayPrice = 0;
    int totalPrice = 0;
    int totalDays = 0;
    for(int i = 0; i < del.size(); i++)
    {
        totalPrice += del[i].get_price();
        totalDays += del[i].get_v();
    }
    sredPrice = totalPrice / del.size();
    sredDayPrice = totalPrice / totalDays;
    QString text1;
    text1 += "Количество отмененных задач: " + QString::number(del.size()) + "\n";
    text1 += "Не заработано: " + QString::number(totalPrice, 'f', 2) + "\n";
    text1 += "Освобожденных дней: " + QString::number(totalDays) + "\n";

    ui->textEdit_2->setText(text1);
}

void statistics::stats_of_active()
{
        std::vector<Time> act;
        QFile activeTasks("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\Tasks.txt");
        activeTasks.open(QIODevice::ReadOnly);
        if(activeTasks.size() == 0)
        {
            activeTasks.close();
            return;
        }
        QString name;
        int day = 0, month = 0, year = 0, v = 0, price = 0;
        bool validRecord = false;

        while (!activeTasks.atEnd()) {
            QString line = activeTasks.readLine();
            if (line.startsWith("Название:")) {
                name = line.mid(line.indexOf(":") + 2).trimmed();
                validRecord = true;
            } else if (line.startsWith("Дата сдачи:")) {
                QString dateString = line.mid(line.indexOf(":") + 2).trimmed();
                QStringList dateParts = dateString.split('.');
                if (dateParts.size() == 3) {
                    bool ok;
                    day = dateParts[0].toInt(&ok);
                    if (!ok) {
                        qDebug() << "Invalid day format: " << dateParts[0];
                        validRecord = false;
                        continue;
                    }
                    month = dateParts[1].toInt(&ok);
                    if (!ok) {
                        qDebug() << "Invalid month format: " << dateParts[1];
                        validRecord = false;
                        continue;
                    }
                    year = dateParts[2].toInt(&ok);
                    if (!ok) {
                        qDebug() << "Invalid year format: " << dateParts[2];
                        validRecord = false;
                        continue;
                    }
                } else {
                    qDebug() << "Неверный формат даты: " << dateString;
                    validRecord = false;
                    continue;
                }
            } else if (line.startsWith("Время на выполнение:")) {
                bool ok;
                v = line.mid(line.indexOf(":") + 2).trimmed().toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid v format: " << line.mid(line.indexOf(":") + 2).trimmed();
                    validRecord = false;
                    continue;
                }
            } else if (line.startsWith("Стоимость работы:")) {
                bool ok;
                price = line.mid(line.indexOf(":") + 2).trimmed().toInt(&ok);
                if (!ok) {
                    qDebug() << "Invalid price format: " << line.mid(line.indexOf(":") + 2).trimmed();
                    validRecord = false;
                    continue;
                }
                if (validRecord) {
                    Time task(name, day, month, year, v, price);
                    act.push_back(task);
                    validRecord = false;
                }
            }
        }
        activeTasks.close();
        double sredPrice = 0;
        double sredDayPrice = 0;
        int totalPrice = 0;
        int totalDays = 0;
        for(int i = 0; i < act.size(); i++)
        {
            totalPrice += act[i].get_price();
            totalDays += act[i].get_v();
        }
        sredPrice = totalPrice / act.size();
        sredDayPrice = totalPrice / totalDays;
        QString text2;
        text2 += "Количество задач: " + QString::number(act.size()) + "\n";
        text2 += "Будет заработано: " + QString::number(totalPrice, 'f', 2) + "\n";
        text2 += "Необходимо дней на работу: " + QString::number(totalDays) + "\n";
        text2 += "Заработок за все задачи: " + QString::number(sredPrice, 'f', 2) + "\n";
        text2 += "Будет заработано в среднем в день: " + QString::number(sredDayPrice, 'f', 2) + "\n";

        ui->textEdit_3->setText(text2);
}

void statistics::closeWin()
{
    close();
}
