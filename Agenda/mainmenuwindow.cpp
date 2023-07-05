#include "mainmenuwindow.h"
#include "eventwindow.h"

#include "global.h"

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
    setWindowTitle("Menú principal");

    // Crear el widget del calendario
    calendarWidget = new QCalendarWidget(this);

///
    QPushButton *crearEventoButton = new QPushButton("Crear Evento", this);
    connect(crearEventoButton, &QPushButton::clicked, this, &MainMenuWindow::abrirEventWindow);
    setCentralWidget(crearEventoButton);
/*    connect(crearEventoButton, SIGNAL(clicked()), this, SLOT(crearEvento()));
*/
    eventWindow = nullptr;
////
    // Crear el layout de caja vertical
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(calendarWidget); // Agregar el calendario al layout
    verticalLayout->addWidget(crearEventoButton); // Agregar el botón 1 al layout

    verticalLayout->addStretch(); // Agregar espacio adicional

    // Crear un widget central y asignarle el layout de caja vertical
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(verticalLayout);

    // Configurar el widget central en la ventana principal
    setCentralWidget(centralWidget);
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
