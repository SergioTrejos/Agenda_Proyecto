#include "userregistrationwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <QDir>
#include <QDebug>
#include <filesystem>


namespace fs = std::filesystem;

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
    QString folderName = username;
    QString folderPath = QDir::currentPath() + "/" + folderName;
    QString loginFileName = (username + ".txt");
    QString loginFilePath = QDir::currentPath() + "/" + folderName + "/" + loginFileName;
    QFile loginfile(loginFilePath);
    QDir folder(folderPath);


    if (folder.exists()) {
        QStringList files = folder.entryList(QDir::Files);
        // Comprueba si el archivo específico está presente
        if (files.contains(loginFileName)) {
            QMessageBox::critical(this, "Error", "El Usuario ya existe.");
            return;
        }
        else {
            if(loginfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&loginfile);
                stream << "Username: " << username << Qt::endl;
                stream << "Password: " << password << Qt::endl;
                loginfile.close();
            }
        }
    }
    else {
        if (QDir().mkpath(folderPath)) {
            qDebug() << "La carpeta se creó correctamente.";
            if (loginfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&loginfile);
                stream << "Username: " << username << Qt::endl;
                stream << "Password: " << password << Qt::endl;
                loginfile.close();
                QString filename = username + "_events.txt";
                QFile file(filename);
            }
            else{
                QMessageBox::critical(this, "Error", "No se pudo crear el usuario.");
            }
        }
    }
    QMessageBox::information(this, "Éxito", "El usuario ha sido creado correctamente.");
    close();
}

