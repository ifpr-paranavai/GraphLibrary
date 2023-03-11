#include <iostream>
#include <list>
#include <algorithm>
#include "Aresta_t.h"

using namespace std;

template <typename T>
class No_t {

private:
	T valor;
	list<Aresta_t<T>> arestasEntrada = list<Aresta_t<T>>();
	list<Aresta_t<T>> arestasSaida = list<Aresta_t<T>>();

public:
	No_t(T valor)
	{
		this->valor = valor;
	}

	void setValor(T valor)
	{
		this->valor = valor;
	}

	T getValor()
	{
		return this->valor;
	}

	void adicionarArestaEntrada(Aresta_t<T> aresta)
	{
		this->arestasEntrada.push_back(aresta);
	}

	void adicionarArestaSaida(Aresta_t<T> aresta)
	{
		this->arestasSaida.push_back(aresta);
	}

};