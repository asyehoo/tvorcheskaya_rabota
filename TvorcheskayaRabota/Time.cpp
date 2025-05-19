#define _CRT_SECURE_NO_WARNINGS
#include "mainwindow.h"
#include <cmath>
#include <ctime>
#include <algorithm>
Time::Time() {
    time_t timer = time(0);
    tm* now = localtime(&timer);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
    v = 0;
    name = " ";
    price = 0;
}
Time::Time(QString name1, int day1, int month1, int year1, int v1, int price1)
{
    name = name1;
    day = day1;
    month = month1;
    year = year1;
    v = v1;
    price = price1;
}
Time::~Time() {}
QString Time::get_name() const
{
    return name;
}
int Time::get_day() const
{
    return day;
}

int Time::get_month() const
{
    return month;
}

int Time::get_year() const
{
    return year;
}

int Time::get_v() const
{
    return v;
}
int Time::get_price() const
{
    return price;
}

void Time::set_day(int d) {
    day = d;
}

void Time::set_month(int m) {
    month = m;
}

void Time::set_year(int y) {
    year = y;
}

void Time::set_v(int V) {
    v = V;
}
void Time::set_name(QString n)
{
    name = n;
}

void Time::set_price(int p)
{
    price = p;
}

bool Time::operator==(const Time& p)
{
    if (day == p.day && month == p.month && year == p.year)
    {
        return true;
    }
    else {
        return false;
    }
}

Time& Time::operator=(const Time& p) {
    day = p.day;
    month = p.month;
    year = p.year;
    name = p.name;
    v = p.v;
    price = p.price;
    return *this;
}
QString Time::toString() const { //Метод для удобного преобразования в строку
    if(day < 10)
    {
        if(month < 10) {
    return QString("Название: %1\nДата сдачи: 0%2/0%3/%4\nВремя на выполнение: %5\nСтоимость: %6")
        .arg(name)
        .arg(day)
        .arg(month)
        .arg(year)
        .arg(v)
        .arg(price);
        }
        else
        {
            return QString("Название: %1\nДата сдачи: 0%2/%3/%4\nВремя на выполнение: %5\nСтоимость: %6")
                .arg(name)
                .arg(day)
                .arg(month)
                .arg(year)
                .arg(v)
                .arg(price);
        }
    }
    if(month < 10)
    {
        return QString("Название: %1\nДата сдачи: %2/0%3/%4\nВремя на выполнение: %5\nСтоимость: %6")
            .arg(name)
            .arg(day)
            .arg(month)
            .arg(year)
            .arg(v)
            .arg(price);
    }
    return QString("Название: %1\nДата сдачи: %2/%3/%4\nВремя на выполнение: %5\nСтоимость: %6")
        .arg(name)
        .arg(day)
        .arg(month)
        .arg(year)
        .arg(v)
        .arg(price);
}
