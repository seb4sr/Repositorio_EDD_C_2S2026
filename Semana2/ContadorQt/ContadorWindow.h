#pragma once

#include <QWidget>

class QLabel;
class QPushButton;

class ContadorWindow : public QWidget {
    Q_OBJECT

public:
    explicit ContadorWindow(QWidget *parent = nullptr);

private slots:
    void incrementar();
    void reiniciar();

private:
    QLabel *etiquetaContador;
    int contador = 0;
};
