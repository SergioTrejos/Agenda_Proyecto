#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    static bool authenticate(const QString &username, const QString &password);

signals:
    void loginSuccessful();

private slots:
    void onLoginButtonClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
};

#endif // LOGIN_H
