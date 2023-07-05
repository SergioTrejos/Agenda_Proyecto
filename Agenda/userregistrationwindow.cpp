#include "userregistrationwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

UserRegistrationWindow::UserRegistrationWindow(QWidget *parent)
    : QDialog(parent)
{
    registerButton = new QPushButton("Registrar", this);
    registerButton->setGeometry(50, 150, 200, 30);
    connect(registerButton, SIGNAL(clicked()), this, SLOT(onRegisterButtonClicked()));

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setGeometry(50, 30, 200, 30);
    usernameLineEdit->setPlaceholderText("Ingrese el nombre de usuario");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setGeometry(50, 70, 200, 30);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setPlaceholderText("Ingrese la contraseña");

    confirmPasswordLineEdit = new QLineEdit(this);
    confirmPasswordLineEdit->setGeometry(50, 110, 200, 30);
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLineEdit->setPlaceholderText("Confirme la contraseña");
}

UserRegistrationWindow::~UserRegistrationWindow()
{
    delete registerButton;
    delete usernameLineEdit;
    delete passwordLineEdit;
    delete confirmPasswordLineEdit;
}

void UserRegistrationWindow::onRegisterButtonClicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text().trimmed();
    QString confirmPassword = confirmPasswordLineEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor, complete todos los campos.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::critical(this, "Error", "Las contraseñas no coinciden.");
            return;
    }

    QFile file(username + ".txt");
    if (file.exists()) {
        QMessageBox::critical(this, "Error", "El nombre de usuario ya existe.");
        return;
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "Username: " << username << Qt::endl;
        stream << "Password: " << password << Qt::endl;
        file.close();

        QString filename = username + "_events.txt";
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << "Archivo de eventos para el usuario: " << username << "\n";
            file.close();
            // El archivo se ha creado correctamente
        } else {
            QMessageBox::critical(this, "Error", "No se pudo crear el archivo de los eventos de usuario.");
        }
        QMessageBox::information(this, "Éxito", "El usuario ha sido creado correctamente.");
            close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo crear el archivo del usuario.");
    }
}

