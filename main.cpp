#include <iostream>
#include "Fase_1_GA/accesos.h"
#include "Fase_1_GA/gestion_accesos.h"
#include "Fase_2_CS/Security.h"
#include "Fase_3_MA/ColaActividades.h"

int main() {
    LinkedList<Acceso> *lAcesos = new LinkedList<Acceso>();

    Acceso a1("pablo", 1705062400);
    Acceso a2("israel", 1705062800);

    lAcesos->insertAtLast(a1);
    lAcesos->insertAtLast(a2);
    lAcesos->insertAtLast(a1); //

    std::cout << "--- Registro Actividad ---" << std::endl;
    lAcesos->printList();
    lAcesos->removeDuplicates();
    // Ahora quito los duplicados
    std::cout << "\n---  Registro Actividad ---" << std::endl;
    lAcesos->printList();
    // Limpio la memoria
    delete lAcesos;
    lAcesos = nullptr;


    //Seguridad
    Security seguridad;
    std::cout << seguridad.requierements() << "\n"; // ALTO por defecto

    seguridad.changeLevel(Nivel::MEDIO);
    std::cout << seguridad.requierements() << "\n"; // ahora MEDIO

    seguridad.changeLevel(Nivel::BAJO);
    std::cout << seguridad.requierements() << "\n"; // ahora BAJO

    //Cola de Actividades
    colaActividades* colaAct = new colaActividades();

    int opcion;
    std::string perfil, nombre, descripcion;
    bool exit = false;
    while (exit == false) {
        std::cout << "\n--- Menu Cola de Actividades ---\n";
        std::cout << "1. Supervisor: agregar actividad\n";
        std::cout << "2. Usuario: ver mis actividades\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        switch (opcion) {
            case 1:
                std::cout << "Ingrese nombre de usuario para la actividad: ";
                std::cin >> nombre;
                std::cout << "Ingrese descripcion de la actividad: ";
                std::cin >> descripcion;
                colaAct -> insertar(Actividad(nombre, descripcion));
                std::cout << "Actividad agregada correctamente.\n";
                break;
            case 2:
                std::cout << "Ingrese su nombre de usuario: ";
                std::cin >> nombre;
                std::cout << "--- Actividades de " << nombre << " ---\n";
                colaAct -> mostrarActividadesUsuario(nombre);
                break;
            case 3:
                std::cout << "Saliendo del menu de actividades...\n";
                exit = true;
                break;
            default:
                std::cout << "Opcion no valida, intente nuevamente.\n";
        }
    }
    // Liberar memoria
    delete colaAct;
    colaAct = nullptr;

    return 0;
}