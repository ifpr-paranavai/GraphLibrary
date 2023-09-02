#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include "No_t.h"
#include "Aresta_t.h"

template <typename T, typename K>
class Grafo_t {
public:
	using Aresta = Aresta_t<K>;
	using No = No_t<T>;
private:


public:
	//list< Aresta* > arestas;
	vector< No* > nos;
	Grafo_t(int qtdeNos)
	{
		this->nos.reserve(qtdeNos);
	}

	int quantidadeNosGrafo() {
		return this->nos.size();
	}

	No_t<T>* adicionarNo(T& valor) {
		if (this->nos.size() == this->nos.capacity()) {
			throw std::runtime_error("Alocação maior do que reservada");
		}
		No_t<T>* no = new No_t<T>(valor, this->nos.size());
		this->nos.push_back(no);
		return no;
	}

	void removerNo(No_t<T>* noRemover) {
		this->nos.erase(noRemover->getId());
	}

	No_t<T>* getNo(std::function<bool(No_t<T>&)> funcao) {
		for (auto it = nos.begin(); it != nos.end(); ++it) {
			if (funcao(*it)) {
				return &(*it);
			}
		}
		return nullptr;
	}

	void adicionarAresta(double peso, No_t<T>* noInicio, No_t<T>* noFim) {
		Aresta_t<K>* aresta = new Aresta_t<K>(peso, noInicio, noFim);
		noInicio->adicionarAresta(aresta);
		Aresta_t<K>* arestaInvertida = new Aresta_t<K>(peso, noFim, noInicio);
		noFim->adicionarAresta(aresta);
	}

	void removerAresta(Aresta_t<K>* aresta) {
		No_t<T>* noInicio = aresta->getNoInicio()->removerAresta(aresta);
		No_t<T>* noFim = aresta->getNoFim()->removerAresta(aresta);
	}

	bool verificarGrafoCompleto(Grafo_t<T, K>* grafo) {
		int numNos = this->nos.size();
		char** matrizAdj = new char* [numNos];
		for (int i = 0; i < numNos; i++) {
			matrizAdj[i] = new char[numNos];
			for (int j = 0; j < numNos; j++) {
				matrizAdj[i][j] = 'N';
			}
		}

		for (auto it = this->nos.begin(); it != this->nos.end(); it++) {
			No_t<T>* noAtual = *it;
			list< Aresta_t<T>* > listaArestasNoAtual = noAtual->getArestas();
			for (auto it2 = listaArestasNoAtual.begin(); it2 != listaArestasNoAtual.end(); it2++) {
				Aresta_t<K>* arestaAtual = *it2;
				No_t<T>* noFim = arestaAtual->getNoFim();
				matrizAdj[noAtual->getId()][noFim->getId()] = 'S';
			}
		}

		for (int i = 0; i < numNos; i++) {
			for (int j = 0; j < numNos; j++) {
				if (matrizAdj[i][j] != 'S' && i != j) {
					return false;
				}
			}
		}

		return true;
	}
};