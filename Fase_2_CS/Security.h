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
        niveles.push(Nivel::BAJO);
        niveles.push(Nivel::MEDIO);
        niveles.push(Nivel::ALTO);
    }

    void changeLevel(Nivel nuevo) {
        replace(niveles, nuevo);
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
    void replace(stack<Nivel> &s, Nivel nuevo) {
        if (s.empty()) {
            s.push(nuevo);
            return;
        }
        Nivel top = s.top();
        s.pop();
        if (s.empty()) {
            s.push(nuevo);
        }else {
            replace(s, nuevo);
            s.push(nuevo);
        }

    }

};

#endif //EJERCICIOSCOLABORATIVOS5_SECURITY_H