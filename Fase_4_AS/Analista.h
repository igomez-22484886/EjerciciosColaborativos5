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
    int contarAccesos(const LinkedList<Access>& lista, const std::string& usuario) {
        return contarAccesosRec(lista.head, usuario);
    }

    void detectarAmenazas(const colaActividades& cola, long long ventanaSegundos = 300) {
        std::cout << " Informe de Analisis de Amenazas (ventana: "
                  << ventanaSegundos << "s) \n";
        bool amenazasEncontradas = false;
        detectarAmenazasRec(cola.frente, ventanaSegundos, amenazasEncontradas);
        if (!amenazasEncontradas) {
            std::cout << "No se detectaron patrones sospechosos.\n";
        }
    }

private:
    int contarAccesosRec(LinkedList<Access>::Node* nodo, const std::string& usuario) {
        if (nodo == nullptr) {
            return 0;
        }
        int count = (nodo->data.getUsuario() == usuario) ? 1 : 0;
        return count + contarAccesosRec(nodo->next, usuario);
    }

    void detectarAmenazasRec(colaActividades::nodoCola* nodo, long long ventanaSegundos,
                             bool& amenazasEncontradas) {
        if (nodo == nullptr) {
            return;
        }

        buscarRepeticionRec(nodo, nodo->siguiente, ventanaSegundos, amenazasEncontradas);
        detectarAmenazasRec(nodo->siguiente, ventanaSegundos, amenazasEncontradas);
    }

    void buscarRepeticionRec(colaActividades::nodoCola* base, colaActividades::nodoCola* actual,
                             long long ventanaSegundos, bool& amenazasEncontradas) {
        if (actual == nullptr) {
            return;
        }

        long long diff = actual->elemento.ts - base->elemento.ts;
        long long absDiff = diff < 0 ? -diff : diff;

        if (diff >= 0 && diff > ventanaSegundos) {
            return;
        }

        if (absDiff <= ventanaSegundos &&
            base->elemento.usuario == actual->elemento.usuario &&
            base->elemento.descripcion == actual->elemento.descripcion) {
            std::cout << "[ALERTA] Actividad sospechosa detectada:\n";
            std::cout << "  Usuario: " << base->elemento.usuario << "\n";
            std::cout << "  Actividad repetida: " << base->elemento.descripcion << "\n";
            std::cout << "  Timestamps: " << base->elemento.ts << " y "
                      << actual->elemento.ts << " (diferencia: " << absDiff
                      << "s)\n";
            amenazasEncontradas = true;
        }

        buscarRepeticionRec(base, actual->siguiente, ventanaSegundos, amenazasEncontradas);
    }
};

#endif //EJERCICIOSCOLABORATIVOS5_ANALISTA_H
