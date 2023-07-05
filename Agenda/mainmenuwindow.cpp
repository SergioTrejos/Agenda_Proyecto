#include "mainmenuwindow.h"
#include "eventwindow.h"

#include "global.h"
#include "qlabel.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QCalendarWidget>
#include <QMainWindow>
#include <QObject>

#include <QString>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QTextStream>
#include <QString>
#include <QMessageBox>

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    eventWindow = nullptr;
}

MainMenuWindow::~MainMenuWindow()
{
    if (eventWindow)
        delete eventWindow;
}


void MainMenuWindow::abrirEventWindow()
{
    if (eventWindow)
        delete eventWindow;

    eventWindow = new EventWindow(this);
    connect(eventWindow, &EventWindow::eventoCreado, this, &MainMenuWindow::guardarEvento);
    eventWindow->show();
}

void MainMenuWindow::guardarEvento(const QString& nombreEvento, const QString& fecha, const QString& hora)
{
    QString nombreArchivo = user + "_events.txt";

    QFile archivo(nombreArchivo);
    if (archivo.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&archivo);
        out << "Evento: " << nombreEvento << "\n";
        out << "Fecha: " << fecha << "\n";
        out << "Hora: " << hora << "\n";
        archivo.close();
        QMessageBox::information(this, "Éxito", "Evento guardado exitosamente.");

    }
    else
    {
        // Error al abrir el archivo
    }
}

void MainMenuWindow::setUser(const QString& username)
{
    user = username;
}

QString MainMenuWindow::getUser()
{
    return user;
}


void MainMenuWindow::setup()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(50, 50, 50, 50); // Establecer márgenes


    setWindowTitle("Menú principal");

        // Crear el widget del calendario
    calendarWidget = new QCalendarWidget(this);

    QFont font("Helvetica", 16);  // Tipo de fuente y tamaño
    calendarWidget->setFont(font);

    calendarWidget->setStyleSheet("QCalendarWidget QTableView { background-color: cyan; }"
                                  "QCalendarWidget QTableView QHeaderView::section { background-color: gray; color: white; }"
                                  "QCalendarWidget QTableView QTableCornerButton::section { background-color: gray; }"
                                  "QCalendarWidget QWidget { color: black; }"
                                  "QCalendarWidget QAbstractItemView:selected { background-color: blue; color: white; }");



    QLabel *welcomeLabel = new QLabel("Bienvenido: " + user, this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px;");

    QString buttonStyle = "QPushButton {"
                          "    background-color: #4CAF50;"
                          "    color: white;"
                          "    border: none;"
                          "    padding: 10px;"
                          "    font-size: 16px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #45a049;"
                          "}";

    QPushButton *crearEventoButton = new QPushButton("Crear Evento", this);
    connect(crearEventoButton, &QPushButton::clicked, this, &MainMenuWindow::abrirEventWindow);
    setCentralWidget(crearEventoButton);

    crearEventoButton->setStyleSheet(buttonStyle);

    layout->addWidget(welcomeLabel);
    layout->addWidget(calendarWidget);
    layout->addWidget(crearEventoButton);

    setCentralWidget(centralWidget);
    adjustSize();

}
