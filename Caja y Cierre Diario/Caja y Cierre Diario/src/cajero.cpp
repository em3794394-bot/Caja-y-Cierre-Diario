#include "cajero.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <utility>

void Cajero::mostrarMenu() {
    std::cout << "\n========== CAJA Y CIERRE DIARIO ==========\n";
    std::cout << "1. Registrar ingreso\n";
    std::cout << "2. Registrar egreso\n";
    std::cout << "3. Listar movimientos\n";
    std::cout << "4. Calcular balance\n";
    std::cout << "5. Generar cierre diario (conteo/max/min)\n";
    std::cout << "6. Estadisticas y Busqueda por ID\n";
    std::cout << "7. Guardar y salir\n";
    std::cout << "==========================================\n";
}

int Cajero::leerEntero(const std::string& msg, int min, int max) {
    int valor;
    while (true) {
        std::cout << msg;
        if (std::cin >> valor && valor >= min && valor <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cout << ">> Invalido. Entre " << min << " y " << max << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double Cajero::leerMonto(const std::string& msg) {
    double valor;
    while (true) {
        std::cout << msg;
        if (std::cin >> valor && valor > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cout << ">> Monto invalido (debe ser > 0).\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string Cajero::leerTexto(const std::string& msg) {
    std::string txt;
    while (true) {
        std::cout << msg;
        std::getline(std::cin, txt);
        if (!txt.empty()) return txt;
        std::cout << ">> El campo no puede estar vacio.\n";
    }
}

std::string Cajero::leerCategoria() {
    std::string c;
    while (true) {
        std::cout << "Categoria (max 30 caracteres): ";
        std::getline(std::cin, c);
        if (!c.empty() && c.size() <= 30) return c;
        std::cout << ">> Categoria invalida.\n";
    }
}

void Cajero::registrarMovimiento(std::vector<Movimiento>& movs, const std::string& tipo) {
    Movimiento m;
    m.id = movs.empty() ? 1 : movs.back().id + 1;
    m.tipo = tipo;
    m.categoria = leerCategoria();
    m.descripcion = leerTexto("Descripcion: ");
    m.monto = leerMonto("Monto: ");
    movs.push_back(m);
    std::cout << ">> Movimiento #" << m.id << " registrado.\n";
}

void Cajero::listarMovimientos(const std::vector<Movimiento>& movs) {
    if (movs.empty()) {
        std::cout << "\n>> No hay movimientos.\n";
        return;
    }
    std::cout << "\n================ LISTADO ================\n";
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(10) << "Tipo"
        << std::setw(15) << "Categoria"
        << std::setw(25) << "Descripcion"
        << std::setw(12) << "Monto" << "\n";
    for (const auto& m : movs) {
        std::cout << std::left << std::setw(5) << m.id
            << std::setw(10) << m.tipo
            << std::setw(15) << m.categoria
            << std::setw(25) << m.descripcion
            << std::fixed << std::setprecision(2) << std::setw(12) << m.monto << "\n";
    }
}

void Cajero::calcularBalance(const std::vector<Movimiento>& movs) {
    double ing = 0, egr = 0;
    for (const auto& m : movs) {
        if (m.tipo == "Ingreso") ing += m.monto;
        else egr += m.monto;
    }
    std::cout << "\n============ BALANCE ============\n";
    std::cout << "Total Ingresos: $" << std::fixed << std::setprecision(2) << ing << "\n";
    std::cout << "Total Egresos : $" << egr << "\n";
    std::cout << "Balance       : $" << (ing - egr) << "\n";
}

void Cajero::generarCierreDiario(const std::vector<Movimiento>& movs) {
    if (movs.empty()) { std::cout << "\n>> No hay datos para cerrar.\n"; return; }

    calcularBalance(movs);

    // Procesamiento 1: Conteo por categoria
    std::vector<std::pair<std::string, int>> conteo;
    for (const auto& m : movs) {
        bool encontrado = false;
        for (auto& c : conteo) {
            if (c.first == m.categoria) { c.second++; encontrado = true; break; }
        }
        if (!encontrado) conteo.push_back({ m.categoria, 1 });
    }

    std::cout << "\n----- Cierre por categoria -----\n";
    for (const auto& c : conteo) {
        std::cout << "  " << std::setw(20) << c.first << ": " << c.second << " mov(s)\n";
    }

    // Procesamiento 2 y 3: Maximo y Minimo
    auto itMax = std::max_element(movs.begin(), movs.end(),
        [](const Movimiento& a, const Movimiento& b) { return a.monto < b.monto; });
    auto itMin = std::min_element(movs.begin(), movs.end(),
        [](const Movimiento& a, const Movimiento& b) { return a.monto < b.monto; });

    std::cout << "\nMayor monto: #" << itMax->id << " - $" << itMax->monto << "\n";
    std::cout << "Menor monto: #" << itMin->id << " - $" << itMin->monto << "\n";
    std::cout << "\n===== CIERRE DIARIO GENERADO =====\n";
}

// Requisito: Búsqueda
int Cajero::buscarPorId(const std::vector<Movimiento>& movs, int id) {
    for (std::size_t i = 0; i < movs.size(); ++i)
        if (movs[i].id == id) return static_cast<int>(i);
    return -1;
}

void Cajero::estadisticas(const std::vector<Movimiento>& movs) {
    if (movs.empty()) { std::cout << "\n>> No hay datos.\n"; return; }

    int ingresos = 0, egresos = 0;
    double suma = 0;
    for (const auto& m : movs) {
        if (m.tipo == "Ingreso") ingresos++; else egresos++;
        suma += m.monto;
    }

    std::cout << "\n--- ESTADISTICAS ---\n";
    std::cout << "Total: " << movs.size() << " | Ingresos: " << ingresos << " | Egresos: " << egresos << "\n";
    std::cout << "Promedio de montos: $" << (suma / movs.size()) << "\n";

    int idBuscado = leerEntero("\nBuscar por ID (0 para omitir): ", 0, 999999);
    if (idBuscado != 0) {
        int idx = buscarPorId(movs, idBuscado);
        if (idx == -1) {
            std::cout << ">> ID " << idBuscado << " no encontrado.\n";
        }
        else {
            const auto& m = movs[idx];
            std::cout << ">> Encontrado: #" << m.id << " | " << m.tipo
                << " | $" << m.monto << "\n";
        }
    }
}