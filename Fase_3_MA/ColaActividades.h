//
// Created by dnovo on 13/01/2026.
//

#ifndef EJERCICIOSCOLABORATIVOS5_COLAACTIVIDADES_H
#define EJERCICIOSCOLABORATIVOS5_COLAACTIVIDADES_H

#include <iostream>
#include <string>
using namespace std;

class Analista;

// Dato que se almacena en la cola
struct Actividad {
    string usuario;
    string descripcion;

    Actividad(string u = "", string d = "") {
        usuario = u;
        descripcion = d;
    }
};

class colaActividades {
    friend class Analista;
protected:
    class nodoCola {
    public:
        Actividad elemento;
        nodoCola* siguiente;

        nodoCola(Actividad a) {
            elemento = a;
            siguiente = NULL;
        }
    };
    nodoCola* frente;
    nodoCola* final;

    //Recorrido recursivo
    void mostrarRecursivo(nodoCola* nodo, string usuario) {
        if (nodo == nullptr) return;

        if (nodo->elemento.usuario == usuario) {
            cout << "- " << nodo->elemento.descripcion << endl;
        }

        mostrarRecursivo(nodo->siguiente, usuario);
    }

    void insertarRecursivo(nodoCola* nodo, nodoCola* nuevo) {
        if (nodo->siguiente == NULL) {
            nodo->siguiente = nuevo;
        } else {
            insertarRecursivo(nodo->siguiente, nuevo);
        }
    }

public:
    colaActividades() {
        frente = final = NULL;
    }

    //Insertar
    void insertar(Actividad a) {
        nodoCola* nuevo = new nodoCola(a);

        if (colaVacia()) {
            frente = final = nuevo;
        } else {
            insertarRecursivo(frente, nuevo);
            final = nuevo;
        }
    }

    //Mostrar actividades de un usuario
    void mostrarActividadesUsuario(string usuario) {
        mostrarRecursivo(frente, usuario);
    }

    bool colaVacia() const {
        return frente == NULL;
    }
};

#endif //EJERCICIOSCOLABORATIVOS5_COLAACTIVIDADES_H