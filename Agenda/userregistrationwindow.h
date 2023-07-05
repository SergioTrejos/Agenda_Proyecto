#ifndef USERREGISTRATIONWINDOW_H
#define USERREGISTRATIONWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class UserRegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    UserRegistrationWindow(QWidget *parent = nullptr);
    ~UserRegistrationWindow();

private:
    QPushButton *registerButton;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *confirmPasswordLineEdit;

private slots:
    void onRegisterButtonClicked();
};

#endif // USERREGISTRATIONWINDOW_H
