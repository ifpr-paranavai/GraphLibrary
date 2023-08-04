#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include "No_t.h"

template <typename T>
class Aresta_t {

	private:
		double peso;
		No_t<T> *noInicio;
		No_t<T> *noFim;
		T valor;

	public:
		Aresta_t(double peso, No_t<T> *noInicio, No_t<T> *noFim, T& valor)
		{
			this->peso = peso;
			this->noInicio = noInicio;
			this->noFim = noFim;
			this->valor = valor;
		}

		No_t<T>* getNoInicio() {
			return this->noInicio;
		}

		No_t<T>* getNoFim() {
			return this->noFim;
		}

		double getPeso() {
			return this->peso;
		}
};
