#include <iostream>
#include <limits>
#include "Fase_1_GA/Access.h"
#include "Fase_1_GA/LinkedList.h"
#include "Fase_2_CS/Security.h"
#include "Fase_3_MA/ColaActividades.h"
#include "Fase_4_AS/Analista.h"

void pausar() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// FASE 1: GESTION DE ACCESOS
void ejecutarFase1() {
    std::cout << "\n=== FASE 1: GESTION DE ACCESOS (DEMO) ===\n";
    LinkedList<Access> *lAcesos = new LinkedList<Access>();

    Access a1("Pablo", 1705062400);
    Access a2("Israel", 1705062800);

    std::cout << "Insertando accesos...\n";
    lAcesos->insertAtLast(a1);
    lAcesos->insertAtLast(a2);
    lAcesos->insertAtLast(a1);

    std::cout << "\n--- Registro Actividad (Con Duplicados) ---\n";
    lAcesos->printList();

    std::cout << "\nEliminando duplicados...\n";
    lAcesos->removeDuplicates();

    std::cout << "\n--- Registro Actividad (Sin Duplicados) ---\n";
    lAcesos->printList();

    delete lAcesos;
    pausar();
}

//FASE 2: CONTROL DE SEGURIDAD
void ejecutarFase2() {
    std::cout << "\n=== FASE 2: CONTROL DE SEGURIDAD ===\n";
    Security seguridad;

    std::cout << "Nivel Inicial: " << seguridad.requierements() << "\n";

    std::cout << "Cambiando a nivel MEDIO...\n";
    seguridad.changeLevel(Nivel::MEDIO);
    std::cout << "Requisitos: " << seguridad.requierements() << "\n";

    std::cout << "Cambiando a nivel BAJO...\n";
    seguridad.changeLevel(Nivel::BAJO);
    std::cout << "Requisitos: " << seguridad.requierements() << "\n";

    pausar();
}

// --- FASE 3: MONITORIZACION (MENU INTERACTIVO) ---
void ejecutarFase3() {
    colaActividades* colaAct = new colaActividades();

    // -- Datos Pre-cargados para pruebas --
    colaAct->insertar(Actividad("Tokio", "Revisar camaras de seguridad"));
    colaAct->insertar(Actividad("Rio", "Hackear firewall del banco"));
    colaAct->insertar(Actividad("Tokio", "Descansar en el lobby"));
    // -------------------------------------

    int opcion;
    std::string nombre, descripcion;
    bool exit = false;

    limpiarBuffer();

    while (!exit) {
        std::cout << "\n======================================\n";
        std::cout << "   FASE 3: MONITORIZACION (COLA)      \n";
        std::cout << "======================================\n";
        std::cout << " 1. Supervisor: Agregar actividad\n";
        std::cout << " 2. Usuario: Ver mis actividades\n";
        std::cout << " 3. Volver al Menu Principal\n";
        std::cout << "======================================\n";
        std::cout << " Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida.\n";
            std::cin.clear();
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1:
                std::cout << "\n[Supervisor]\n";
                std::cout << "Ingrese nombre de usuario: ";
                std::cin >> nombre;
                std::cout << "Ingrese descripcion de la actividad: ";
                std::cin.ignore(); // Consumir newline del buffer anterior
                std::getline(std::cin, descripcion);
                colaAct->insertar(Actividad(nombre, descripcion));
                std::cout << ">> Actividad agregada correctamente.\n";
                break;
            case 2:
                std::cout << "\n[Usuario]\n";
                std::cout << "Ingrese su nombre de usuario: ";
                std::cin >> nombre;
                std::cout << "--- Actividades de " << nombre << " ---\n";
                colaAct->mostrarActividadesUsuario(nombre);
                std::cout << "---------------------------------\n";
                break;
            case 3:
                std::cout << "Volviendo al menu principal...\n";
                exit = true;
                break;
            default:
                std::cout << "Opcion no valida, intente nuevamente.\n";
        }
    }
    delete colaAct;
}

//FASE 4: ANALISIS DE SEGURIDAD
void ejecutarFase4() {
    std::cout << "\n=== FASE 4: ANALISIS DE SEGURIDAD ===\n";

    LinkedList<Access> *listaAccesos = new LinkedList<Access>();
    listaAccesos->insertAtLast(Access("Berlin", 1001));
    listaAccesos->insertAtLast(Access("Tokio", 1002));
    listaAccesos->insertAtLast(Access("Berlin", 1005));
    listaAccesos->insertAtLast(Access("Rio", 1006));
    listaAccesos->insertAtLast(Access("Berlin", 1010));

    Analista analista;
    std::cout << "--- Analisis de Accesos ---\n";
    std::cout << "Analizando accesos de 'Berlin'...\n";
    int accesosBerlin = analista.contarAccesos(*listaAccesos, "Berlin");
    std::cout << ">> Numero de accesos de Berlin: " << accesosBerlin << " (Esperado: 3)\n";

    std::cout << "Analizando accesos de 'Tokio'...\n";
    int accesosTokio = analista.contarAccesos(*listaAccesos, "Tokio");
    std::cout << ">> Numero de accesos de Tokio: " << accesosTokio << " (Esperado: 1)\n";

    delete listaAccesos;

    //Preparar datos para analisis de amenazas
    colaActividades *colaSospechosa = new colaActividades();
    colaSospechosa->insertar(Actividad("Nairobi", "Imprimir Dinero"));
    colaSospechosa->insertar(Actividad("Denver", "Vigilar Rehenes"));
    colaSospechosa->insertar(Actividad("Denver", "Vigilar Rehenes"));
    colaSospechosa->insertar(Actividad("Helsinki", "Curar Herido"));
    colaSospechosa->insertar(Actividad("Denver", "Vigilar Rehenes"));

    std::cout << "\n--- Analisis de Amenazas ---\n";
    analista.detectarAmenazas(*colaSospechosa);

    delete colaSospechosa;
    pausar();
}

int main() {
    int opcion;
    bool salir = false;

    while (!salir) {
        std::cout << "\n############################################\n";
        std::cout << "#  SISTEMA DE GESTION - LA CASA DE PAPEL   #\n";
        std::cout << "############################################\n";
        std::cout << " 1. Fase 1: Gestion de Accesos (Demo)\n";
        std::cout << " 2. Fase 2: Control de Seguridad (Demo)\n";
        std::cout << " 3. Fase 3: Monitorizacion (Menu Actividades)\n";
        std::cout << " 4. Fase 4: Analisis de Seguridad (Demo)\n";
        std::cout << " 0. Salir\n";
        std::cout << "############################################\n";
        std::cout << " Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida.\n";
            std::cin.clear();
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1: ejecutarFase1();
                break;
            case 2: ejecutarFase2();
                break;
            case 3: ejecutarFase3();
                break;
            case 4: ejecutarFase4();
                break;
            case 0:
                std::cout << "Cerrando el sistema...\n";
                salir = true;
                break;
            default: std::cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
