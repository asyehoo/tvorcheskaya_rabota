#include "mainwindow.h"
#include <QPalette>
#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPalette pal = w.palette();
    QIcon icon("C:\\Users\\Professional\\Desktop\\TvorcheskayaRabota\\ICON.ico");
    w.setWindowIcon(icon);
    pal.setColor(QPalette::Window, QColor(22, 51, 62));
    w.setPalette(pal);
    w.setAutoFillBackground(true);
    w.setWindowTitle("Планировщик");
    w.show();
    return a.exec();
}
