
#include "mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "ui_statistics.h"
#include "statistics.h"
#include <QTimer>
#include "ui_mainwindow.h"
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QListWidget>
#include <QTextEdit>
#include <vector>
#include <sstream>
#include <algorithm>
#include <QDebug>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileSystemWatcher>
#include <QFont>
#include <QIcon>

QList<Time> MyList;
std::vector<Time> result;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemWatcher *fileWatcher = new QFileSystemWatcher(this);
    QString filePath = "C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\tasks.txt";
    fileWatcher->addPath(filePath);
    connect(fileWatcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::onFileChanged);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
    connect(ui->delTask, &QPushButton::clicked, this, &MainWindow::on_delTask_clicked);
    connect(ui->delTask_2, &QPushButton::clicked, this, &MainWindow::on_delTask_2_clicked);
    sortVEC();
    populateListWidget();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddTask_clicked()
{
    Dialog *Win = new Dialog;
    QPalette pal = Win->palette();
    QIcon icon("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\ICON.ico");
    Win->setWindowIcon(icon);
    pal.setColor(QPalette::Window, QColor(22, 51, 62));
    Win->setPalette(pal);
    Win->setAutoFillBackground(true);
    Win->setWindowTitle("Добавление задачи");
    Win->show();
}



void MainWindow::populateListWidget() {
    ui->listWidget->clear();
    for (const Time& time : MyList) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(time.toString());
        ui->listWidget->addItem(item);
    }
}


bool proverca(const Time& a, const Time& b) {
    if (a.get_price() != b.get_price()) {
        return a.get_price() > b.get_price();
    }
    if (a.get_year() != b.get_year()) {
        return a.get_year() < b.get_year();
    }
    if (a.get_month() != b.get_month()) {
        return a.get_month() < b.get_month();
    }
    if (a.get_day() != b.get_day()) {
        return a.get_day() < b.get_day();
    }
    return a.get_v() > b.get_v();
}

void sortirovka(std::vector<Time>& times) {
    bool swapped;
    for (size_t i = 0; i < times.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < times.size() - i - 1; j++) {
            if (proverca(times[j + 1], times[j])) {
                std::swap(times[j], times[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void MainWindow::sortVEC()
{
    result.clear();
    QFile file("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\tasks.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << file.fileName();
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    if(file.size() == 0)
    {
        file.close();
        populateListWidget();
        return;
    }

    QString name;
    int day = 0, month = 0, year = 0, v = 0, price = 0;
    bool validRecord = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
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
                result.push_back(task);
                validRecord = false;
            }
        }
    }
    MyList.clear();
    for (const Time& time : result) {
        MyList.append(time);
    }

    file.close();
    sortirovka(result);
    QFile file1("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\tasks.txt");
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи!";
        return;
    }

    QTextStream out(&file1);
    out.setEncoding(QStringConverter::Utf8);
    for (const Time& t : result)
    {
        out << "Название: " << t.name << '\n';
        out << "Дата сдачи: " << QString("%1.%2.%3").arg(t.day, 2, 10, QChar('0')).arg(t.month, 2, 10, QChar('0')).arg(t.year) << '\n';
        out << "Время на выполнение: " << t.v << '\n';
        out << "Стоимость работы: " << t.price << '\n';
        out << '\n';
    }

    file1.close();
    populateListWidget();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if (ui->listWidget->selectedItems().contains(item)) {
    } else {
        item->setSelected(true);
    }
}

void MainWindow::DeleteItem(QListWidgetItem *item)
{
    if (!item) {
        return;
    }

    QString itemText = item->text();
    QString filePath = "C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\tasks.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения/записи: " << filePath;
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    QString fileContent;
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileContent.append(line);
        fileContent.append("\n");
    }
    file.close();
    QString patternString =
        "Название: " + QRegularExpression::escape(getTimeNameFromText(itemText)) + ".*?" +
        "Дата сдачи: .*?\\n" +
        "Время на выполнение: .*?\\n" +
        "Стоимость работы: .*?\\n" +
        "(?:\\n|$)";

    QRegularExpression pattern(patternString, QRegularExpression::DotMatchesEverythingOption | QRegularExpression::MultilineOption);
    QRegularExpressionMatch match = pattern.match(fileContent);
    QString matchedText = match.captured(0);
    QFile delf("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\deletedTasks.txt");
    delf.open(QIODevice::Append);
    QTextStream outD(&delf);
    outD << matchedText;
    delf.close();

    if (match.hasMatch()) {
        fileContent.remove(match.capturedStart(), match.capturedLength());
    } else {
        qDebug() << "Элемент не найден в файле: " << itemText;
        return;
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Не удалось открыть файл для записи: " << filePath;
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << fileContent;

    file.close();
}


QString MainWindow::getTimeNameFromText(const QString& itemText)
{
    int nameStart = itemText.indexOf("Название: ") + QString("Название: ").length();
    if (nameStart != -1) {
        int nameEnd = itemText.indexOf("\n", nameStart);
        if (nameEnd != -1) {
            return itemText.mid(nameStart, nameEnd - nameStart).trimmed();
        } else {
            return itemText.mid(nameStart).trimmed();
        }
    }
    return "";
}


void MainWindow::onFileChanged(const QString &path)
{
    Q_UNUSED(path);
    sortVEC();
}

void MainWindow::on_delTask_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    DeleteItem(selectedItem);
    if (selectedItem)
        DeleteItem(selectedItem);
}

void MainWindow::CompleteItem(QListWidgetItem *item)
{
    if (!item) {
        return;
    }

    QString itemText = item->text();
    QString filePath = "C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\tasks.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения/записи: " << filePath;
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    QString fileContent;
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileContent.append(line);
        fileContent.append("\n");
    }
    file.close();
    QString patternString =
        "Название: " + QRegularExpression::escape(getTimeNameFromText(itemText)) + ".*?" +
        "Дата сдачи: .*?\\n" +
        "Время на выполнение: .*?\\n" +
        "Стоимость работы: .*?\\n" +
        "(?:\\n|$)";

    QRegularExpression pattern(patternString, QRegularExpression::DotMatchesEverythingOption | QRegularExpression::MultilineOption);
    QRegularExpressionMatch match = pattern.match(fileContent);
    QString matchedText = match.captured(0);
    QFile delf("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\completedTasks.txt");
    delf.open(QIODevice::Append);
    QTextStream outD(&delf);
    outD << matchedText;
    delf.close();

    if (match.hasMatch()) {
        fileContent.remove(match.capturedStart(), match.capturedLength());
    } else {
        qDebug() << "Элемент не найден в файле: " << itemText;
        return;
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Не удалось открыть файл для записи: " << filePath;
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << fileContent;

    file.close();
}

void MainWindow::on_delTask_2_clicked()
{
    QListWidgetItem *selectedItem1 = ui->listWidget->currentItem();
    CompleteItem(selectedItem1);
    if (selectedItem1)
        DeleteItem(selectedItem1);
}

void MainWindow::on_stats_clicked()
{
    statistics *stats = new statistics;
    QPalette pal = stats->palette();
    QIcon icon("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\ICON.ico");
    stats->setWindowIcon(icon);
    pal.setColor(QPalette::Window, QColor(22, 51, 62));
    stats->setPalette(pal);
    stats->setAutoFillBackground(true);
    stats->setWindowTitle("Статистика");
    stats->show();
}

