// eventwindow.cpp
#include "eventwindow.h"
#include "qboxlayout.h"
#include <QObject>

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

EventWindow::EventWindow(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Crear Evento");

    nombreEventoLineEdit = new QLineEdit(this);
    nombreEventoLineEdit->setGeometry(50, 30, 200, 30);
    nombreEventoLineEdit->setPlaceholderText("Nombre del evento");

    fechaLineEdit = new QLineEdit(this);
    fechaLineEdit->setGeometry(50, 70, 200, 30);
    fechaLineEdit->setPlaceholderText("Fecha (YYYY-MM-DD)");

    horaLineEdit = new QLineEdit(this);
    horaLineEdit->setGeometry(50, 110, 200, 30);
    horaLineEdit->setPlaceholderText("Hora (HH:MM)");

    guardarButton = new QPushButton("Guardar", this);
    guardarButton->setGeometry(50, 150, 200, 30);

    connect(guardarButton, &QPushButton::clicked, this, &EventWindow::crearEvento);


}

EventWindow::~EventWindow()
{
}

void EventWindow::crearEvento()
{
    QString nombreEvento = nombreEventoLineEdit->text();
    QString fecha = fechaLineEdit->text();
    QString hora = horaLineEdit->text();


    emit eventoCreado(nombreEvento, fecha, hora);

    close();
}
