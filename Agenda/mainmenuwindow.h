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
    QString getUser();
    void setUser(const QString& username);
    void setup();

private:
    EventWindow *eventWindow;
    QCalendarWidget *calendarWidget;
    QString user;

private slots:
    void abrirEventWindow();
    void guardarEvento(const QString& nombreEvento, const QString& day, const QString& month, const QString& year, const QString& hora);
    void onDateClicked(const QDate& date);
};

#endif // MAINMENUWINDOW_H
