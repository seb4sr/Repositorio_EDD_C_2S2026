#include <iostream>
#include "httplib.h"

int main() {
    httplib::Server servidor;

    servidor.set_default_headers({
        {"Access-Control-Allow-Origin", "*"}
    });

    servidor.Get("/api/saludo", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Peticion recibida: GET /api/saludo" << std::endl;
        res.set_content("{\"mensaje\": \"Hola desde el backend en C++\"}", "application/json");
    });

    const char* host = "0.0.0.0";
    const int puerto = 8080;

    std::cout << "Servidor escuchando en http://localhost:" << puerto << std::endl;

    if (!servidor.listen(host, puerto)) {
        std::cerr << "No se pudo iniciar el servidor (puerto ocupado?)" << std::endl;
        return 1;
    }

    return 0;
}
