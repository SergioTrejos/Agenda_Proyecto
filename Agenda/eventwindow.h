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

signals:
    void eventoCreado(const QString& nombreEvento, const QString& fecha, const QString& hora);

public slots:
    void crearEvento();

private:
    QLineEdit *nombreEventoLineEdit;
    QLineEdit *fechaLineEdit;
    QLineEdit *horaLineEdit;
    QPushButton *guardarButton;
    QPushButton* crearEventoButton;

};

#endif // EVENTWINDOW_H
