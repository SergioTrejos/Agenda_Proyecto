#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include "eventwindow.h"
#include "QPushButton"
#include <QMainWindow>
#include <QCalendarWidget>
#include <QWidget>

class QPushButton;


class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

private:
    EventWindow *eventWindow;
    QCalendarWidget *calendarWidget;


private slots:
    void abrirEventWindow();
    void guardarEvento(const QString& nombreEvento, const QString& fecha, const QString& hora);
};

#endif // MAINMENUWINDOW_H
