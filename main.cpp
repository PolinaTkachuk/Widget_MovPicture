#include "widget.h"
#include <QApplication>

//main.cpp в заготовке создает объект-приложение a и окно w,
//визуализирует окно и запускает цикл обработки сообщений
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//создает объект-приложение a
    Window w;//создает окно w
    w.show();// визуализация окна
    return a.exec();// запуск цикла обработки сообщений приложения
}
