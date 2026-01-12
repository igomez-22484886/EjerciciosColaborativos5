#include <iostream>
#include "Fase_1_GA/accesos.h"
#include "Fase_1_GA/gestion_accesos.h"

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

    return 0;
}