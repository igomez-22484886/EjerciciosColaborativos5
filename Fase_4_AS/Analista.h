//
// Created by igomez on 1/13/26.
//

#ifndef EJERCICIOSCOLABORATIVOS5_ANALISTA_H
#define EJERCICIOSCOLABORATIVOS5_ANALISTA_H

#include "../Fase_1_GA/LinkedList.h"
#include "../Fase_1_GA/Access.h"
#include "../Fase_3_MA/ColaActividades.h"
#include <string>
#include <iostream>

class Analista {
public:
    //Recorrer lista de accesos y contar accesos por usuario
    int contarAccesos(const LinkedList<Access>& lista, const std::string& usuario) {
        return contarAccesosRec(lista.head, usuario);
    }

    //Buscar actividades repetidas
    void detectarAmenazas(const colaActividades& cola) {
        std::cout << "--- Informe de Analisis de Amenazas ---\n";
        bool amenazasEncontradas = false;
        detectarAmenazasRec(cola.frente, amenazasEncontradas);
        if (!amenazasEncontradas) {
            std::cout << "No se detectaron patrones sospechosos.\n";
        }
        std::cout << "---------------------------------------\n";
    }

private:
    int contarAccesosRec(LinkedList<Access>::Node* nodo, const std::string& usuario) {
        if (nodo == nullptr) {
            return 0;
        }
        int count = (nodo->data.getUsuario() == usuario) ? 1 : 0;
        return count + contarAccesosRec(nodo->next, usuario);
    }

    void detectarAmenazasRec(colaActividades::nodoCola* nodo, bool& amenazasEncontradas) {
        if (nodo == nullptr || nodo->siguiente == nullptr) {
            return;
        }

        if (nodo->elemento.usuario == nodo->siguiente->elemento.usuario &&
            nodo->elemento.descripcion == nodo->siguiente->elemento.descripcion) {
            
            std::cout << "[ALERTA] Actividad sospechosa detectada:\n";
            std::cout << "  Usuario: " << nodo->elemento.usuario << "\n";
            std::cout << "  Actividad repetida: " << nodo->elemento.descripcion << "\n";
            amenazasEncontradas = true;
        }

        detectarAmenazasRec(nodo->siguiente, amenazasEncontradas);
    }
};

#endif //EJERCICIOSCOLABORATIVOS5_ANALISTA_H
