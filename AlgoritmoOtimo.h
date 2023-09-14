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

template <typename T, typename K>
class AlgoritmoOtimo {

	public:
		Grafo_t<T, K>* melhorSolucao;
		double custoMelhorSolucao = DBL_MAX;
		No_t<T>* pontoInicial;


		Grafo_t<T, K> caixeiro(Grafo_t<T, K>* grafo)
		{
			No_t<T>* noAtual = grafo->nos[0];
			pontoInicial = noAtual;
			vector<bool> noVisitado(grafo->quantidadeNosGrafo(), false);
			noVisitado[noAtual->getId()] = true;
			Grafo_t<T, K>* caminho = new Grafo_t<T, K>(grafo->quantidadeNosGrafo());
			caminho->adicionarNo(noAtual->getValor());
			caixeiroProximoNo(grafo, noAtual, noVisitado, caminho, 0, 1);
			return *melhorSolucao;

		}

	void caixeiroProximoNo(Grafo_t<T, K>* grafo, No_t<T>* noAtual, vector<bool>& nosVisitados, Grafo_t<T, K>* caminho, double custoAcumulado, int quantidadeNos) {
		if (quantidadeNos == grafo->quantidadeNosGrafo()) {
			double PesoArestaBuscar = 0.0;
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
				Aresta_t<K>* aresta = *it;
				if (aresta->getNoFim()->getId() != noAtual->getId()) {
					No_t<T>* noDestino = aresta->getNoFim();

					if (nosVisitados[noDestino->getId()] == false) {
						nosVisitados[noDestino->getId()] = true;
						caminho->adicionarNo(noDestino->getValor());
						caminho->adicionarAresta(aresta->getPeso(), aresta->getNoInicio(), aresta->getNoFim());
						caixeiroProximoNo(grafo, noDestino, nosVisitados, caminho, custoAcumulado, quantidadeNos + 1);

						caminho->removerAresta(aresta);
						caminho->removerNo(noDestino);
						nosVisitados[noDestino->getId()] = false;
					}

				}
			}
		}
	}
};
