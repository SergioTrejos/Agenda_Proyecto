#include "resetpassword.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

ResetPassword::ResetPassword(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Restaurar contraseña");

    resetPasswordButton = new QPushButton("Restaurar contraseña", this);
    resetPasswordButton->setGeometry(50, 150, 200, 30);
    connect(resetPasswordButton, SIGNAL(clicked()), this, SLOT(onResetPasswordButtonClicked()));

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setGeometry(50, 30, 200, 30);
    usernameLineEdit->setPlaceholderText("Ingrese el nombre de usuario");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setGeometry(50, 70, 200, 30);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setPlaceholderText("Ingrese la nueva contraseña");

    confirmPasswordLineEdit = new QLineEdit(this);
    confirmPasswordLineEdit->setGeometry(50, 110, 200, 30);
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLineEdit->setPlaceholderText("Confirme la nueva contraseña");
}

bool ResetPassword::changePassword(const QString& username, const QString& newPassword)
{
    QFile file(username + ".txt");
    if (!file.exists()) {
        QMessageBox::critical(nullptr, "Error", "El nombre de usuario no existe.");
        return false;
    }

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString fileContent = file.readAll();
        file.seek(0);

        QTextStream stream(&file);
        QStringList lines = fileContent.split('\n');

        for (const QString& line : lines) {
            if (line.startsWith("Password:")) {
                stream << "Password: " << newPassword << Qt::endl;
            } else {
                stream << line << Qt::endl;
            }
        }

        file.close();

        QMessageBox::information(nullptr, "Éxito", "La contraseña ha sido cambiada correctamente.");
        return true;
    } else {
        QMessageBox::critical(nullptr, "Error", "No se pudo abrir el archivo del usuario.");
        return false;
    }
}

ResetPassword::~ResetPassword()
{
    delete resetPasswordButton;
    delete usernameLineEdit;
    delete passwordLineEdit;
    delete confirmPasswordLineEdit;
}

void ResetPassword::onResetPasswordButtonClicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString newPassword = passwordLineEdit->text().trimmed();
    QString confirmPassword = confirmPasswordLineEdit->text().trimmed();

    if (username.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor, complete todos los campos.");
        return;
    }

    if (newPassword != confirmPassword) {
        QMessageBox::critical(this, "Error", "Las contraseñas no coinciden.");
            return;
    }

    if (ResetPassword::changePassword(username, newPassword)) {
        close();
    }
}
