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
		Grafo_t<T, K>* melhorSolucao;
		double custoMelhorSolucao = DBL_MAX;
		No_t<T>* pontoInicial;


		Grafo_t<T, K> caixeiro(Grafo_t<T, K>* grafo)
		{
			// utilizar um vetor de inteiros com os ids dos nós do grafo, somente após a finalização que tiver a melhor solução montar o grafo
			No_t<T>* noAtual = grafo->nos[0];
			pontoInicial = noAtual;
			vector<int> nosSolucao(grafo->quantidadeNosGrafo());
			vector<bool> noVisitado(grafo->quantidadeNosGrafo(), false);
			noVisitado[noAtual->getId()] = true;
			Grafo_t<T, K>* caminho = new Grafo_t<T, K>(grafo->quantidadeNosGrafo());
			nosSolucao[0] = noAtual->getId();
			//caminho->adicionarNo(noAtual->getValor());
			caixeiroProximoNo(grafo, noAtual, noVisitado, nosSolucao,caminho, 0, 1);
			return *melhorSolucao;

		}

	void caixeiroProximoNo(Grafo_t<T, K>* grafo, No_t<T>* noAtual, vector<bool>& nosVisitados, vector<int>& nosSolucao, Grafo_t<T, K>* caminho, double custoAcumulado, int quantidadeNos) {
		if (quantidadeNos == grafo->quantidadeNosGrafo()) {
			double PesoArestaBuscar = 0.0;
			for (int i = 0; i < nosSolucao.size(); i++) {				
				if (nosSolucao[i] == grafo->nos[i]->getId()) {
					caminho->adicionarNo(grafo->nos[i]->getValor());
				}
			}
			dprintln(caminho->quantidadeNosGrafo())
		/*	for (auto it = caminho->nos->begin(); it != caminho->nos->end(); it++) {
				No_t<T>* no = *it;
				for (auto it2 = no->getArestas()->begin(); it2 != no->getArestas()->end(); it2++) {
					int i = 0;
					Aresta_t<K>* aresta = *it2;
					if (i+1 < nosSolucao.size()) {
						if (aresta->getNoInicio()->getId() == nosSolucao[i] && aresta->getNoFim()->getId() == nosSolucao[i + 1]) {
							caminho->adicionarAresta(aresta->getPeso(), aresta->getNoInicio(), aresta->getNoFim());
						}
					}
					i++;
				}
			}*/

			for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
				Aresta_t<K>* aresta = *it2;

				if (aresta->getNoFim() == pontoInicial) {
					PesoArestaBuscar = aresta->getPeso();
					break;
				}

			}
			caminho->adicionarAresta(PesoArestaBuscar, noAtual, pontoInicial);
			if (custoAcumulado < custoMelhorSolucao) {
				melhorSolucao = caminho;
				custoMelhorSolucao = custoAcumulado;
			}
		}
		else {
			for (auto it = noAtual->getArestas()->begin(); it != noAtual->getArestas()->end(); it++) {
				int i = 1;
				Aresta_t<K>* aresta = *it;
				if (aresta->getNoFim()->getId() != noAtual->getId()) {
					No_t<T>* noDestino = aresta->getNoFim();

					if (nosVisitados[noDestino->getId()] == false) {
						nosVisitados[noDestino->getId()] = true;
						nosSolucao[i] = (noDestino->getId());
						i++;
						caixeiroProximoNo(grafo, noDestino, nosVisitados, nosSolucao, caminho, custoAcumulado, quantidadeNos + 1);

						nosVisitados[noDestino->getId()] = false;
						nosSolucao.pop_back();
					}

				}
			}
		}
	}
};
