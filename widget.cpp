#include "widget.h"
#include "ui_widget.h"
#include <math.h>

void Figura::move(float Alpha, QPainter* Painter)
{
    dx = halflen * cos(Alpha); // задаем движение по Ох
    dy = halflen * sin(Alpha);//по Оу
    draw(Painter);               // рисуем
}

void MyLine::draw(QPainter* Painter)
{
    Painter->drawLine(x + dx, y + dy, x - dx, y - dy); // изображение линни по координатам
}

void MyRect::draw(QPainter* Painter)
{
    // изображение квадрата, рисуем 4 линии
    Painter->drawLine(x + dx, y + dy, x + dy, y - dx);
    Painter->drawLine(x + dy, y - dx, x - dx, y - dy);
    Painter->drawLine(x - dx, y - dy, x - dy, y + dx);
    Painter->drawLine(x - dy, y + dx, x + dx, y + dy);
}


Area::Area(QWidget* parent) :QWidget(parent)
{
    setFixedSize(QSize(300, 200));           // устанавливаем размер исходного виджета
    myline = new MyLine(80, 100, 50);  // создаем объект MyLine
    myrect = new MyRect(220, 100, 50);// создаем объект MyRect
    alpha = 0; //зануляем угол
}

void Area::showEvent(QShowEvent*)
{
    myTimer = startTimer(50); // создаем таймер 50
}

void Area::paintEvent(QPaintEvent*)  // рисуем событие
{
    QPainter painter(this);          // создаем объект Для рисования
    painter.setPen(Qt::red);    // устанавливаем красный цвет
     // рисуем движение фигур с помощью угла и рисовальщика
    myline->move(alpha, &painter);
    myrect->move(alpha * (-0.5), &painter);
}

void Area::timerEvent(QTimerEvent* event)  //инициация перерисовки Холста
{
    if (event->timerId() == myTimer) // если наш таймер
    {
        alpha = alpha + 0.2; //поварачиваем угол для движения
        update();                    // обновляем внешний вид
    }
    else
        QWidget::timerEvent(event);  // иначе передать для стандартной обработки
}

void Area::hideEvent(QHideEvent *)
{
    killTimer(myTimer);           // удаляем таймер
}

Area::~Area()                        // деструктор
{
    delete myline;
    delete myrect;
}


Window::Window()
{
    this->setWindowTitle("Обработка событий");            // название окна Обработка событий
    area = new Area( this );                        // создаем холст
    btn = new QPushButton("Завершить", this ); // создаем кнопку завершения
    QVBoxLayout* layout = new QVBoxLayout(this);    // создаем компановщик
    layout->addWidget(area);                              // добавляем виджеты
    layout->addWidget(btn);
    // сигнал, закрывающий окно при нажатии
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(close()));
};
