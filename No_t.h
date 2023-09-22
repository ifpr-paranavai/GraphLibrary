#ifndef __HEADER_NO_H__
#define __HEADER_NO_H__ 

#include <iostream>
#include <list>
#include <algorithm>


template <typename T>
class Aresta_t;

using namespace std;


template <typename T>
class No_t {

	private:
		int id;
		T valor;
		list<Aresta_t<T>*> arestas;

	public:
		No_t(const T& valor, const int id)
		{
			this->id = id;
			this->valor = valor;
		}

		void setValor(const T& valor)
		{
			this->valor = valor;
		}

		T& getValor()
		{
			return this->valor;
		}

		int getId() 
		{
			return this->id;
		}

		void adicionarAresta(Aresta_t<T>* aresta)
		{
			assert(aresta->getNoInicio() == this);
			assert(aresta->getNoFim() != this);
			this->arestas.push_back(aresta);
		}

		list<Aresta_t<T>*>* getArestas() {
			return &this->arestas;
		}

		void removerAresta(Aresta_t<T>* aresta) {
			auto it = std::find(this->arestas.begin(), this->arestas.end(), aresta);
			assert(it != this->arestas.end());
			this->arestas.erase(it);
		}

};
#include "Aresta_t.h"
#endif