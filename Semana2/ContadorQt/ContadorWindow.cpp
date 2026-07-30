#include "ContadorWindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ContadorWindow::ContadorWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Ejemplo Qt - Contador");

    etiquetaContador = new QLabel("Contador: 0", this);
    etiquetaContador->setAlignment(Qt::AlignCenter);

    auto *botonSumar = new QPushButton("Sumar", this);
    auto *botonReiniciar = new QPushButton("Reiniciar", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(etiquetaContador);
    layout->addWidget(botonSumar);
    layout->addWidget(botonReiniciar);

    connect(botonSumar, &QPushButton::clicked, this, &ContadorWindow::incrementar);
    connect(botonReiniciar, &QPushButton::clicked, this, &ContadorWindow::reiniciar);
}

void ContadorWindow::incrementar() {
    contador++;
    etiquetaContador->setText(QString("Contador: %1").arg(contador));
}

void ContadorWindow::reiniciar() {
    contador = 0;
    etiquetaContador->setText("Contador: 0");
}
