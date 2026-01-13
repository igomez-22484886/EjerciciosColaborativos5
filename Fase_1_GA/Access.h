//
// Created by ppiqu on 12/01/2026.
//

#ifndef EJERCICIOSCOLABORATIVOS5_ACCESOS_H
#define EJERCICIOSCOLABORATIVOS5_ACCESOS_H
#include <string>
#include <iostream>

struct Access {
	std::string usuario;
	long long ts;

	Access() : usuario(""), ts(0) {};

	Access(std::string usuario, long long ts) {
		this->usuario = usuario;
		this->ts = ts;
	}

	std::string getUsuario() const {
		return usuario;
	}

	long long getTs() const {
		return ts;
	}

	std::string toString() const {
		return "Usuario: " + usuario + " | Timestamp: " + std::to_string(ts);
	}
	// Operador para comparar y que pueda encontrar el duplicado
	bool operator==(const Access& otro) const {
		return (this->usuario == otro.usuario && this->ts == otro.ts);
	}
};
#endif //EJERCICIOSCOLABORATIVOS5_ACCESOS_H
