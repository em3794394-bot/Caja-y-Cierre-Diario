#pragma once
#include <vector>
#include <string>

struct Movimiento {
    int         id;
    std::string tipo;        // "Ingreso" o "Egreso"
    std::string categoria;
    std::string descripcion;
    double      monto;
};

class Repositorio {
public:
    static const std::string ARCHIVO;

    // Carga los datos desde el archivo CSV al vector
    static void cargar(std::vector<Movimiento>& movs);

    // Guarda el vector en el archivo CSV
    static void guardar(const std::vector<Movimiento>& movs);
};