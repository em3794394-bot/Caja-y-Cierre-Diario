#include "repositorio.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

const std::string Repositorio::ARCHIVO = "movimientos.csv";

void Repositorio::cargar(std::vector<Movimiento>& movs) {
    std::ifstream archivo(ARCHIVO);
    if (!archivo.is_open()) return;

    std::string linea;
    std::getline(archivo, linea); // cabecera
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string campo;
        Movimiento m;

        std::getline(ss, campo, ','); m.id = std::stoi(campo);
        std::getline(ss, campo, ','); m.tipo = campo;
        std::getline(ss, campo, ','); m.categoria = campo;
        std::getline(ss, campo, ','); m.descripcion = campo;
        std::getline(ss, campo, ','); m.monto = std::stod(campo);

        movs.push_back(m);
    }
    archivo.close();
    std::cout << "[INFO] " << movs.size() << " movimientos cargados.\n";
}

void Repositorio::guardar(const std::vector<Movimiento>& movs) {
    std::ofstream archivo(ARCHIVO);
    archivo << "id,tipo,categoria,descripcion,monto\n";
    for (const auto& m : movs) {
        archivo << m.id << "," << m.tipo << "," << m.categoria << ","
            << m.descripcion << "," << std::fixed << std::setprecision(2) << m.monto << "\n";
    }
    archivo.close();
    std::cout << "[INFO] " << movs.size() << " movimientos guardados.\n";
}