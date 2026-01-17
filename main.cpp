#include <chrono> // Para obtener el timestamp
#include <iostream>
#include <limits>
#include <string>
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

long long obtenerTimestampActual() {
    using namespace std::chrono;
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

long long pedirTimestamp(const std::string& prompt) {
    long long ts;
    while (true) {
        std::cout << prompt;
        if (std::cin >> ts) {
            return ts;
        }
        std::cout << "Entrada invalida. Intente de nuevo.\n";
        std::cin.clear();
        limpiarBuffer();
    }
}

std::string nivelToString(Nivel nivel) {
    switch (nivel) {
        case Nivel::BAJO: return "BAJO";
        case Nivel::MEDIO: return "MEDIO";
        case Nivel::ALTO: return "ALTO";
    }
    return "DESCONOCIDO";
}

void solicitarCredenciales(const Security& seguridad) {
    Nivel nivel = seguridad.currentLevel();
    std::string usuario;
    std::string contrasena;
    std::string telefono;

    std::cout << "Usuario: ";
    std::cin >> usuario;

    if (nivel == Nivel::MEDIO || nivel == Nivel::ALTO) {
        std::cout << "Contraseña: ";
        std::cin >> contrasena;
    }

    if (nivel == Nivel::ALTO) {
        std::cout << "Telefono: ";
        std::cin >> telefono;
    }

    std::cout << "Verificacion completada para nivel " << nivelToString(nivel) << ".\n";
}

// FASE 1: GESTION DE ACCESOS
void ejecutarFase1() {
    std::cout << "\nFASE 1: GESTION DE ACCESOS\n";
    LinkedList<Access> accesos;

    accesos.insertSorted(Access("Aldo", 1705062400));
    accesos.insertSorted(Access("David", 1705062800));
    accesos.insertSorted(Access("Aldo", 1705062500));
    accesos.insertSorted(Access("Aldo", 1705062500)); // Duplicado

    int opcion = -1;
    while (opcion != 0) {
        std::cout << " 1. Registrar acceso\n";
        std::cout << " 2. Buscar acceso por usuario y fecha\n";
        std::cout << " 3. Mostrar registros de acceso\n";
        std::cout << " 4. Eliminar duplicados\n";
        std::cout << " 0. Volver al menu principal\n";
        std::cout << "\nSeleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida.\n";
            std::cin.clear();
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1: {
                std::string usuario;
                std::cout << "Ingrese nombre de usuario: ";
                std::cin >> usuario;
                long long ts = obtenerTimestampActual();
                accesos.insertSorted(Access(usuario, ts));
                std::cout << "Acceso registrado para " << usuario
                          << " con timestamp " << ts << ".\n";
                break;
            }
            case 2: {
                std::string usuario;
                std::cout << "Ingrese nombre de usuario: ";
                std::cin >> usuario;
                long long ts = pedirTimestamp("Ingrese timestamp (segundos desde epoch): ");
                Access objetivo(usuario, ts);
                std::cout << "Buscando acceso... "
                          << (accesos.search(objetivo) ? "ENCONTRADO" : "NO ENCONTRADO")
                          << "\n";
                break;
            }
            case 3:
                std::cout << "\n Registros de Acceso\n";
                accesos.printList();
                break;
            case 4:
                std::cout << "Eliminando duplicados...\n";
                accesos.removeDuplicates();
                break;
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion no valida.\n";
        }
    }
    pausar();
}

// FASE 2: CONTROL DE SEGURIDAD
void ejecutarFase2() {
    std::cout << "\nFASE 2: CONTROL DE SEGURIDAD\n";
    Security seguridad;

    int opcion = -1;
    while (opcion != 0) {
        std::cout << "Nivel actual: " << nivelToString(seguridad.currentLevel()) << "\n";
        std::cout << "Requisitos: " << seguridad.requierements() << "\n";
        std::cout << " 1. Cambiar a BAJO\n";
        std::cout << " 2. Cambiar a MEDIO\n";
        std::cout << " 3. Cambiar a ALTO\n";
        std::cout << " 4. Verificar identidad\n";
        std::cout << " 0. Volver al menu principal\n";
        std::cout << "\nSeleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida.\n";
            std::cin.clear();
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1:
                seguridad.changeLevel(Nivel::BAJO);
                std::cout << "Nivel cambiado a BAJO.\n";
                break;
            case 2:
                seguridad.changeLevel(Nivel::MEDIO);
                std::cout << "Nivel cambiado a MEDIO.\n";
                break;
            case 3:
                seguridad.changeLevel(Nivel::ALTO);
                std::cout << "Nivel cambiado a ALTO.\n";
                break;
            case 4:
                solicitarCredenciales(seguridad);
                break;
            case 0:
                std::cout << "Volviendo al menu principal...\n";
                break;
            default:
                std::cout << "Opcion no valida.\n";
        }
    }

    pausar();
}

// FASE 3: MONITORIZACION
void ejecutarFase3() {
    colaActividades* colaAct = new colaActividades();

    long long baseTimeFase3 = obtenerTimestampActual();
    // Datos para pruebas
    colaAct->insertar(Actividad("Aldo", "Revisar camaras de seguridad", baseTimeFase3 - 180));
    colaAct->insertar(Actividad("David", "Hackear firewall del banco", baseTimeFase3 - 120));
    colaAct->insertar(Actividad("Aldo", "Descansar en el lobby", baseTimeFase3 - 60));

    int opcion;
    std::string nombre, descripcion;
    bool exit = false;

    limpiarBuffer();

    while (!exit) {
        std::cout << "   FASE 3: MONITORIZACION (COLA)      \n";
        std::cout << " 1. Supervisor: Agregar actividad\n";
        std::cout << " 2. Usuario: Ver mis actividades\n";
        std::cout << " 3. Volver al Menu Principal\n";
        std::cout << "\nSeleccione una opcion: ";

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
                colaAct->insertar(Actividad(nombre, descripcion, obtenerTimestampActual()));
                std::cout << " Actividad agregada correctamente.\n";
                break;
            case 2:
                std::cout << "\n[Usuario]\n";
                std::cout << "Ingrese su nombre de usuario: ";
                std::cin >> nombre;
                std::cout << "Actividades de " << nombre << " \n";
                colaAct->mostrarActividadesUsuario(nombre);
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
    std::cout << "\nFASE 4: ANALISIS DE SEGURIDAD\n";

    LinkedList<Access> *listaAccesos = new LinkedList<Access>();

    listaAccesos->insertSorted(Access("Pablo", 1001));
    listaAccesos->insertSorted(Access("Israel", 1002));
    listaAccesos->insertSorted(Access("Pablo", 1005));
    listaAccesos->insertSorted(Access("David", 1006));
    listaAccesos->insertSorted(Access("Pablo", 1010));

    Analista analista;
    std::cout << "Analisis de Accesos";
    std::cout << "Analizando accesos de 'Pablo'...";
    int accesosPablo = analista.contarAccesos(*listaAccesos, "Pablo");
    std::cout << ">> Numero de accesos de Pablo: " << accesosPablo << " (Esperado: 3)\n";

    std::cout << "Analizando accesos de 'Israel'...";
    int accesosIsrael = analista.contarAccesos(*listaAccesos, "Israel");
    std::cout << ">> Numero de accesos de Israel: " << accesosIsrael << " (Esperado: 1)\n";

    delete listaAccesos;

    colaActividades *colaSospechosa = new colaActividades();
    long long baseTimeFase4 = obtenerTimestampActual();
    colaSospechosa->insertar(Actividad("Israel", "Imprimir Dinero", baseTimeFase4 - 900));
    colaSospechosa->insertar(Actividad("Aldo", "Vigilar Rehenes", baseTimeFase4 - 200));
    colaSospechosa->insertar(Actividad("Aldo", "Vigilar Rehenes", baseTimeFase4 - 120));
    colaSospechosa->insertar(Actividad("David", "Curar Herido", baseTimeFase4 - 60));
    colaSospechosa->insertar(Actividad("Aldo", "Vigilar Rehenes", baseTimeFase4 + 400));

    std::cout << "\n";
    analista.detectarAmenazas(*colaSospechosa);

    delete colaSospechosa;
    pausar();
}

int main() {
    int opcion;
    bool salir = false;

    while (!salir) {
        std::cout << " SISTEMA DE GESTION\n";
        std::cout << " 1. Fase 1: Gestion de Accesos\n";
        std::cout << " 2. Fase 2: Control de Seguridad\n";
        std::cout << " 3. Fase 3: Monitorizacion\n";
        std::cout << " 4. Fase 4: Analisis de Seguridad\n";
        std::cout << " 0. Salir\n";
        std::cout << "\nSeleccione una opcion: ";

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
