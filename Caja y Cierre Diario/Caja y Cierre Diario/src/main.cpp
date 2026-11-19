// 

#include <iostream>
#include <vector>
#include "cajero.h"
#include "repositorio.h"

int main() {
    std::vector<Movimiento> movimientos;
    Repositorio::cargar(movimientos);

    int opcion = 0;
    do {
        Cajero::mostrarMenu();
        opcion = Cajero::leerEntero("Opcion: ", 1, 7);

        switch (opcion) {
        case 1: Cajero::registrarMovimiento(movimientos, "Ingreso"); break;
        case 2: Cajero::registrarMovimiento(movimientos, "Egreso");  break;
        case 3: Cajero::listarMovimientos(movimientos); break;
        case 4: Cajero::calcularBalance(movimientos); break;
        case 5: Cajero::generarCierreDiario(movimientos); break;
        case 6: Cajero::estadisticas(movimientos); break;
        case 7:
            Repositorio::guardar(movimientos);
            std::cout << "Saliendo...\n";
            break;
        }
    } while (opcion != 7);

    return 0;
}