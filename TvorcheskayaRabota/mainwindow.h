#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#ifndef TIME
#define TIME
#include <QMainWindow>
#include <QTextEdit>
#include <Time.h>
#include <QListWidgetItem>
#include <QList>
#include <QFileSystemWatcher>

class Time
{
public:
    int day;
    int month;
    int year;
    int v;
    int price;
    QString name;
public:
    Time();
    Time(QString, int, int, int, int, int);
    ~Time();
    int get_day() const;
    int get_month() const;
    int get_year() const;
    int get_v() const;
    int get_price() const;
    void set_price(int p);
    QString get_name()const;
    void set_day(int day);
    void set_month(int month);
    void set_year(int year);
    void set_v(int v);
    void set_name(const QString n);
    friend std::fstream& operator>>(std::fstream&, Time&);
    friend std::fstream& operator<<(std::fstream&, const Time&);
    bool operator==(const Time& p);
    Time& operator=(const Time& p);
    QString toString() const;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getTimeNameFromText(const QString& itemText);


private slots:
    void on_AddTask_clicked();
    void sortVEC();
    void populateListWidget();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void DeleteItem(QListWidgetItem *item);
    void CompleteItem(QListWidgetItem *item);
    void onFileChanged(const QString &path);

    void on_delTask_clicked();
    void on_delTask_2_clicked();

    void on_stats_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher fileWatcher;
    QTimer *m_updateTimer;
    QTimer *m_updateTimer2;
};
#endif // MAINWINDOW_H
#endif
