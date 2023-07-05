#ifndef RESETPASSWORD_H
#define RESETPASSWORD_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class ResetPassword : public QDialog
{
    Q_OBJECT

public:
    ResetPassword(QWidget *parent = nullptr);
    ~ResetPassword();

private:
    QPushButton *resetPasswordButton;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *confirmPasswordLineEdit;

    static bool changePassword(const QString& username, const QString& newPassword);

private slots:
    void onResetPasswordButtonClicked();
};

#endif // RESETPASSWORDWINDOW_H
