#include "mainwindow.h"
#include "resetpassword.h"
#include "login.h"
#include "userregistrationwindow.h"
#include "mainmenuwindow.h"


#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Menú de inicio");
    loginButton = new QPushButton("Iniciar Sesión", this);
    loginButton->setGeometry(50, 30, 200, 30);
    connect(loginButton, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));

    createUserButton = new QPushButton("Crear Usuario", this);
    createUserButton->setGeometry(50, 70, 200, 30);
    connect(createUserButton, SIGNAL(clicked()), this, SLOT(onCreateUserButtonClicked()));

    resetPasswordButton = new QPushButton("Restaurar contraseña", this);
    resetPasswordButton->setGeometry(50, 110, 200, 30);
    connect(resetPasswordButton, SIGNAL(clicked()), this, SLOT(onResetPasswordButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete createUserButton;
    delete loginButton;
    delete resetPasswordButton;
}

void MainWindow::onLoginButtonClicked()
{
    // Crear una instancia de la ventana de inicio de sesión
    Login *login = new Login(this);

    // Conectar la señal de inicio de sesión exitoso a un slot personalizado
    connect(login, SIGNAL(loginSuccessful()), this, SLOT(onLoginSuccessful()));

    // Mostrar la ventana de inicio de sesión
    login->show();
}

void MainWindow::onCreateUserButtonClicked()
{
    UserRegistrationWindow *registrationWindow = new UserRegistrationWindow(); // Crear una instancia de la nueva ventana
    registrationWindow->show(); // Mostrar la nueva ventana
}

void MainWindow::onResetPasswordButtonClicked()
{
    ResetPassword *resetPassword = new ResetPassword(this);
    resetPassword->exec();
}

void MainWindow::onLoginSuccessful()
{
    // Cerrar la ventana principal
    close();

    // Abrir la ventana del menú principal
    MainMenuWindow *mainMenuWindow = new MainMenuWindow();
    mainMenuWindow->show();
}
