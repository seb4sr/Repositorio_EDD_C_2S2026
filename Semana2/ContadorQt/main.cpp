#include "ContadorWindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ContadorWindow ventana;
    ventana.show();

    return app.exec();
}
