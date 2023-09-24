#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include "No_t.h"
#include "Aresta_t.h"
#include "Grafo.h"


#define DEBUG
#define SANITY
// ---------------------------------------------------

#ifdef DEBUG
	#define dprint(STR) { std::cout << STR; }
	#define dprintln(STR) { std::cout << STR << std::endl; }
#else
	#define dprint(STR)
	#define dprintln(STR)
#endif

template <typename T, typename K>
class AlgoritmoOtimo {

	public:
		vector<int> melhorSolucao;
		double custoMelhorSolucao = DBL_MAX;
		No_t<T>* pontoInicial;


		//void caixeiro(Grafo_t<T, K>* grafo)
		//{
		//	No_t<T>* noAtual = grafo->nos[0];
		//	this->pontoInicial = noAtual;
		//	vector<int> nosSolucao;
		//	nosSolucao.reserve(grafo->quantidadeNosGrafo());
		//	vector<bool> noVisitado(grafo->quantidadeNosGrafo(), false);
		//	noVisitado[noAtual->getId()] = true;
		//	Grafo_t<T, K>* caminho = new Grafo_t<T, K>(grafo->quantidadeNosGrafo());
		//	nosSolucao.push_back(noAtual->getId());
		//	caixeiroProximoNo(grafo, noAtual, noVisitado, nosSolucao, 0, 1);
		//	dprintln("MELHOR CUSTO: " << this->custoMelhorSolucao);
		//	//return *melhorSolucao;

		//}

		void caixeiro(Grafo_t<T, K>* grafo)
		{
			vector<int> nosSolucao;
			nosSolucao.reserve(grafo->quantidadeNosGrafo());
			vector<bool> noVisitado(grafo->quantidadeNosGrafo(), false);
			
			for (int i = 0; i < grafo->quantidadeNosGrafo(); i++) {
				No_t<T>* noAtual = grafo->nos[i];
				this->pontoInicial = noAtual;
				noVisitado[noAtual->getId()] = true;
				nosSolucao.push_back(noAtual->getId());
				caixeiroProximoNo(grafo, noAtual, noVisitado, nosSolucao, 0, 1);
				nosSolucao.pop_back();
				noVisitado[noAtual->getId()] = false;
			}

			dprintln("MELHOR CUSTO: " << this->custoMelhorSolucao);
			//return *melhorSolucao;

		}

	void caixeiroProximoNo(Grafo_t<T, K>* grafo, No_t<T>* noAtual, vector<bool>& nosVisitados, vector<int>& nosSolucao, double custoAcumulado, int quantidadeNos) {
		if (quantidadeNos == grafo->quantidadeNosGrafo()) {
			double PesoArestaBuscar = -1.0;
			
			for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
				Aresta_t<K>* aresta = *it2;

				if (aresta->getNoFim() == this->pontoInicial) {
					PesoArestaBuscar = aresta->getPeso();
					break;
				}

			}

			assert(PesoArestaBuscar != -1.0);
			
			custoAcumulado += PesoArestaBuscar;
			imprimir(nosSolucao, custoAcumulado);
			if (custoAcumulado < custoMelhorSolucao) {
				this->melhorSolucao = nosSolucao;
				this->custoMelhorSolucao = custoAcumulado;
			}
		}
		else {
			#ifdef DEBUG
			for (int i = 0; i <= quantidadeNos; i++) {
				dprint("\t");
			}
			#endif
			dprintln("checando no inicial: " << noAtual->getId());
			for (auto it = noAtual->getArestas()->begin(); it != noAtual->getArestas()->end(); it++) {
				Aresta_t<K>* aresta = *it;
				No_t<T>* noDestino = aresta->getNoFim();

				if (nosVisitados[noDestino->getId()] == false) {
					#ifdef DEBUG
					for (int i = 0; i <= quantidadeNos; i++) {
						dprint("\t");
					}
					#endif	

					dprintln("\tchecando no inicial: " << aresta->getNoInicio()->getId() <<" e no destino: " << noDestino->getId() << " peso: " << aresta->getPeso());
					
					nosVisitados[noDestino->getId()] = true;
					nosSolucao.push_back(noDestino->getId());
					caixeiroProximoNo(grafo, noDestino, nosVisitados, nosSolucao, custoAcumulado + aresta->getPeso(), quantidadeNos + 1);

					nosVisitados[noDestino->getId()] = false;
					nosSolucao.pop_back();
				}
				
			}
		}
	}

	void imprimir(vector<int>& nosSolucao, double custo) {
		dprint(" custo: " << custo << " Nos: ");

		for (auto v: nosSolucao) {
			dprint(v << ", ");
		}

		dprintln("");
	}
};
