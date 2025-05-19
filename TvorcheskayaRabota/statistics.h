#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>

namespace Ui {
class statistics;
}

class statistics : public QDialog
{
    Q_OBJECT

public:
    explicit statistics(QWidget *parent = nullptr);
    ~statistics();

private slots:

    void stats_of_completed();
    void stats_of_deleted();
    void stats_of_active();
    void closeWin();


private:
    Ui::statistics *ui;
};

#endif // STATISTICS_H
