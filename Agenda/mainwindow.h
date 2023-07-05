#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlineedit.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setup();

private:
    QPushButton *createUserButton;
    QPushButton *loginButton;
    QPushButton *resetPasswordButton;

private slots:
    void onCreateUserButtonClicked();
    void onLoginButtonClicked();
    void onResetPasswordButtonClicked();
    void onLoginSuccessful(const QString& user);


};

#endif // MAINWINDOW_H
