#include "login.h"
#include "mainwindow.h"
#include "mainmenuwindow.h"
#include "global.h"
#include "qboxlayout.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>

Login::Login(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Inicio de sesión");

    // Crear los objetos de la interfaz de usuario
    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Nombre de usuario");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Contraseña");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Iniciar sesión", this);

    // Configurar el diseño de la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    setLayout(layout);

    // Conectar la señal del botón de inicio de sesión a un slot personalizado
    connect(loginButton, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
}

void Login::onLoginButtonClicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text().trimmed();


    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor, complete todos los campos.");
        return;
    }

    if (Login::authenticate(username, password)) {
        //user = username;
        QMessageBox::information(this, "Éxito", "Inicio de sesión exitoso.");

        // Emitir la señal de inicio de sesión exitoso
        emit loginSuccessful(username);


        // Cerrar la ventana de inicio de sesión
        close();

    } else {
        QMessageBox::critical(this, "Error", "Credenciales incorrectas. Inténtelo de nuevo.");
        // Limpiar los campos de entrada
        usernameLineEdit->clear();
        passwordLineEdit->clear();
        // Dar foco al campo de nombre de usuario
        usernameLineEdit->setFocus();
    }
}

bool Login::authenticate(const QString &username, const QString &password)
{
    QString filename = username + ".txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QString line = in.readLine();
    if (line != "Username: " + username) {
        file.close();
        return false;
    }

    line = in.readLine();
    if (line != "Password: " + password) {
        file.close();
        return false;
    }

    file.close();
    return true;

    // Credenciales inválidas o usuario no encontrado
    file.close();
    return false;
}
