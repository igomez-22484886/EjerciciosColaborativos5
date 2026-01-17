//
// Created by Aldo on 12/01/26.
//

#ifndef EJERCICIOSCOLABORATIVOS5_SECURITY_H
#define EJERCICIOSCOLABORATIVOS5_SECURITY_H

#include <stack>
#include <string>

using namespace std;
enum class Nivel {
    BAJO, MEDIO, ALTO
};

class Security {
public:
    Security() {
        restart();
    }

    void restart() {
        while (!niveles.empty()) niveles.pop();
        niveles.push(Nivel::ALTO);
        niveles.push(Nivel::MEDIO);
        niveles.push(Nivel::BAJO);
    }

    void changeLevel(Nivel nuevo) {
        moveToTop(niveles, nuevo);
    }

    Nivel currentLevel() const {
        return niveles.empty() ? Nivel::BAJO : niveles.top();
    }

    string requierements() const {
        if (niveles.empty()) return "No hay niveles";
        switch (niveles.top()) {
            case Nivel::BAJO: return "Pedir usuario";
            case Nivel::MEDIO: return "Pedir usuario y contraseña";
            case Nivel::ALTO:  return "Pedir usuario, contraseña y teléfono";
        }
        return "";
    }

private:
    stack<Nivel> niveles;

    // funcion para mover un nivel especifico a la cima
    void moveToTop(stack<Nivel> &s, Nivel target) {
        if (s.empty()) return;
        if (s.top() == target) return; // ya esta arriba

        extract(s, target);
        s.push(target);
    }

    void extract(stack<Nivel> &s, Nivel target) {
        if (s.empty()) return;

        Nivel top = s.top();
        s.pop();

        if (top == target) {
            // no hacemos nada
        } else {
            extract(s, target);
            s.push(top);
        }
    }

};

#endif //EJERCICIOSCOLABORATIVOS5_SECURITY_H
