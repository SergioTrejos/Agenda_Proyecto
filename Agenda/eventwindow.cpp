// eventwindow.cpp
#include "eventwindow.h"
#include "qboxlayout.h"
#include <QObject>

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QLabel>

EventWindow::EventWindow(QWidget *parent) :
    QDialog(parent)
{

}

EventWindow::~EventWindow()
{
}

void EventWindow::crearEvento()
{
    QString nombreEvento = nombreEventoLineEdit->text();
    QString day = dayLineEdit->text();
    QString month = monthLineEdit->text();
    QString year = yearLineEdit->text();
    QString hora = horaLineEdit->text();


    emit eventoCreado(nombreEvento, day, month, year, hora);

    close();
}

void EventWindow::setup(int day, int month, int year)
{
  //  QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(50, 50, 50, 50); // Establecer márgenes


    QLabel *welcomeLabel = new QLabel("Ingrese los siguientes datos: ", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px;");

    setWindowTitle("Añadir Evento");

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

    nombreEventoLineEdit = new QLineEdit(this);
    nombreEventoLineEdit->setGeometry(50, 30, 200, 30);
    nombreEventoLineEdit->setPlaceholderText("Nombre del evento");

    dayLineEdit = new QLineEdit(this);
    dayLineEdit->setGeometry(50, 70, 200, 30);
    QString placeholderText = QString("Dia: %1").arg(day);
    dayLineEdit->setPlaceholderText(placeholderText);

    monthLineEdit = new QLineEdit(this);
    monthLineEdit->setGeometry(50, 70, 200, 30);
    placeholderText = QString("Mes: %1").arg(month);
    monthLineEdit->setPlaceholderText(placeholderText);

    yearLineEdit = new QLineEdit(this);
    yearLineEdit->setGeometry(50, 70, 200, 30);
    placeholderText = QString("Año: %1").arg(year);
    yearLineEdit->setPlaceholderText(placeholderText);

    horaLineEdit = new QLineEdit(this);
    horaLineEdit->setGeometry(50, 110, 200, 30);
    horaLineEdit->setPlaceholderText("Hora (HH:MM)");

    guardarButton = new QPushButton("Guardar", this);
    guardarButton->setGeometry(50, 150, 200, 30);

    connect(guardarButton, &QPushButton::clicked, this, &EventWindow::crearEvento);



    layout->addWidget(welcomeLabel);
    layout->addWidget(nombreEventoLineEdit);
    layout->addWidget(dayLineEdit);
    layout->addWidget(monthLineEdit);
    layout->addWidget(yearLineEdit);
    layout->addWidget(horaLineEdit);
    layout->addWidget(guardarButton);

    this->setLayout(layout);

 //   setCentralWidget(centralWidget);
  //  adjustSize();
}
