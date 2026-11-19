#pragma once
#include <vector>
#include <string>
#include "repositorio.h"

class Cajero {
public:
    static void mostrarMenu();

    // Validaciones
    static int leerEntero(const std::string& msg, int min, int max);
    static double leerMonto(const std::string& msg);
    static std::string leerTexto(const std::string& msg);
    static std::string leerCategoria();

    // Operaciones
    static void registrarMovimiento(std::vector<Movimiento>& movs, const std::string& tipo);
    static void listarMovimientos(const std::vector<Movimiento>& movs);
    static void calcularBalance(const std::vector<Movimiento>& movs);
    static void generarCierreDiario(const std::vector<Movimiento>& movs);
    static void estadisticas(const std::vector<Movimiento>& movs);

    // Búsqueda (Requisito)
    static int buscarPorId(const std::vector<Movimiento>& movs, int id);
};