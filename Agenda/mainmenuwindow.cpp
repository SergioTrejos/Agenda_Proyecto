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

#include <QDir>
#include <QDebug>
#include <filesystem>

namespace fs = std::filesystem;

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

    QDate selectedDate = calendarWidget->selectedDate();

    connect(eventWindow, &EventWindow::eventoCreado, this, &MainMenuWindow::guardarEvento);
    eventWindow->setup(selectedDate.day(),selectedDate.month(),selectedDate.year());
    eventWindow->show();
}

void MainMenuWindow::guardarEvento(const QString& nombreEvento, const QString& day, const QString &month, const QString &year, const QString& hora)
{
    QString nombreArchivo = user + "_events.txt";

    QFile archivo(nombreArchivo);
    if (archivo.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&archivo);
        out << "Evento: " << nombreEvento << "\n";
        out << "Día: " << day << "\n";
        out << "Mes: " << month << "\n";
        out << "Año: " << year << "\n";
        out << "Hora: " << hora << "\n";
        out << "\n";
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
    textEdit = new QTextEdit();

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(50, 50, 50, 50); // Establecer márgenes


    setWindowTitle("Menú principal");

        // Crear el widget del calendario
    calendarWidget = new QCalendarWidget(this);

    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainMenuWindow::onDateClicked);


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

    QDate selectedDate = calendarWidget->selectedDate();

    QString eventFilePath = QDir::currentPath() + "/" + user + QString("/%1/%2").arg(selectedDate.year()).arg(selectedDate.month());
    QString eventFileName = QString("%1.txt").arg(selectedDate.day());
    QDir folder(eventFilePath);
    QFile eventFile(eventFilePath + "/" + eventFileName);

    if (folder.exists()) {
        QStringList files = folder.entryList(QDir::Files);
        // Comprueba si el archivo específico está presente
        if (files.contains(eventFileName)) {
            if (eventFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // Lee el contenido del archivo
                QTextStream in(&eventFile);
                QString contenido = in.readAll();

                // Establece el contenido en el cuadro de texto
                textEdit->setPlainText(contenido);

                // Cierra el archivo
                eventFile.close();
            }
        }
    }
    else {
        QString contenido("No hay entradas para este día");
        textEdit->setPlainText(contenido);
    }



    crearEventoButton->setStyleSheet(buttonStyle);

    layout->addWidget(welcomeLabel);
    layout->addWidget(calendarWidget);
    layout->addWidget(crearEventoButton);
    layout->addWidget(textEdit);

    setCentralWidget(centralWidget);
    adjustSize();

}

void MainMenuWindow::onDateClicked(const QDate& date) {
    // Aquí puedes realizar las acciones que desees con la fecha seleccionada
    // por ejemplo, mostrarla en un mensaje o realizar alguna otra operación.
    int day = date.day();
    int month = date.month();
    int year = date.year();

    qDebug() << "Día: " << day;
    qDebug() << "Mes: " << month;
    qDebug() << "Año: " << year;
    QString eventFilePath = QDir::currentPath() + "/" + user + QString("/%1/%2").arg(year).arg(month);
    QString eventFileName = QString("%1.txt").arg(day);
    QDir folder(eventFilePath);
    QFile eventFile(eventFilePath + "/" + eventFileName);

    if (folder.exists()) {
        QStringList files = folder.entryList(QDir::Files);
        // Comprueba si el archivo específico está presente
        qDebug() << "Prueba 1";
        if (files.contains(eventFileName)) {
            if (eventFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // Lee el contenido del archivo
                QTextStream in(&eventFile);
                QString contenido = in.readAll();

                // Establece el contenido en el cuadro de texto
                textEdit->setPlainText(contenido);

                // Cierra el archivo
                eventFile.close();
            }
        }
    }
    else {
        QString contenido("No hay entradas para este día");
            textEdit->setPlainText(contenido);
    }


}
