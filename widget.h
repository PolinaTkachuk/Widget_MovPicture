#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


class Figura // класс фигура абстрактный
{
protected:
    int x, y, halflen, dx, dy, r;
    virtual void draw(QPainter* Painter) = 0; // метод для  изображения фигур
public:
    Figura(int X, int Y, int Halflen) :       // конструктор с аргументами
        x(X), y(Y), halflen(Halflen)
        {}
    void move(float Alpha, QPainter* Painter);// метод для движения фигур
};

//ИСПОЛЬЗУЕМ полиморфизм

class MyLine : public Figura //класс линия наследник Figura
{
protected:
    void draw(QPainter* Painter);   // переопределенный от родителя метод, изображ линию
public:
    MyLine(int x, int y, int halflen) :       // конструктор
        Figura(x, y, halflen)
        {}
};


class MyRect : public Figura//класс MyRect наследник Figura
{
protected:
    void draw(QPainter* Painter);             // переопределенный метод изображения у родителя
public:
    MyRect(int x, int y, int halflen) :       // конструктор
        Figura(x, y, halflen)
        {}
};


class Area : public QWidget              // класс холст
{

    int myTimer;                         // идентификатор таймера
    float alpha;                         // угол поворота
public:
    Area(QWidget* parent = nullptr);     // конструктор
    ~Area();                             // деструктор
    //классы MyLine и MyRect имеют отношение композиция с классом холст
    MyLine* myline;
    MyRect* myrect;
protected:
    // обработчики событий
    void paintEvent(QPaintEvent* event); // рисование пошагово перемещающихся фигур
    void timerEvent(QTimerEvent* event); //инициация перерисовки Холста
    void showEvent(QShowEvent* event);//включение таймера
    void hideEvent(QHideEvent* event);//выключение таймера
};


class Window : public QWidget // окно
{
protected:
    //класс холст имеет отношение композиция с классом Window
    Area * area;              // холст
    QPushButton * btn;        // кнопка завершения
public:
    Window(); //конструктор
};

#endif // WIDGET_H
