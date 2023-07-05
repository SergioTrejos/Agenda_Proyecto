// eventwindow.h
#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>

class EventWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EventWindow(QWidget *parent = nullptr);
    ~EventWindow();
    void setup(int day, int month, int year);

signals:
    void eventoCreado(const QString& nombreEvento, const QString& day, const QString& month, const QString& year, const QString& hora);

public slots:
    void crearEvento();

private:
    QLineEdit *nombreEventoLineEdit;
    QLineEdit *dayLineEdit;
    QLineEdit *monthLineEdit;
    QLineEdit *yearLineEdit;
    QLineEdit *horaLineEdit;
    QPushButton *guardarButton;
    QPushButton* crearEventoButton;

};

#endif // EVENTWINDOW_H
