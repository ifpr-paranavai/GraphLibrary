#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include "No_t.h"
#include "Aresta_t.h"
#include "Grafo.h"
#include "AlgoritmoOtimo.h"


using namespace std;

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
Grafo_t<T, K>* CaixeiroInsercaoDoMaisDistante(Grafo_t<T, K>& grafo) {
	using Grafo = Grafo_t<T, K>;

	Grafo* resultado = new Grafo(grafo.quantidadeNosGrafo());
	No_t<T>* pontoInicial = grafo.nos[0];
	double PesoArestaBuscar = 0.0;
	std::vector<bool> noVisitado(grafo.quantidadeNosGrafo(), false);
	No_t<T>* noAtual = pontoInicial;
	auto* resultadoNoAtual = resultado->adicionarNo(noAtual->getValor());
	auto* resultadoNoInicio = resultadoNoAtual;
	noVisitado[noAtual->getId()] = true;

	dprintln("Iniciou pelo no: " << noAtual->getId());

	for (int i = 1; i < grafo.quantidadeNosGrafo(); i++) {
		list<Aresta_t<K>*>* arestas = noAtual->getArestas();
		double maiorPeso = -3.0;
		Aresta_t<K>* arestaSelecionada = nullptr;

		for (auto it2 = arestas->begin(); it2 != arestas->end(); it2++) {
			Aresta_t<K>* aresta = *it2;
			if (aresta->getNoFim()->getId() != noAtual->getId()) {
				dprintln("\tchecando no " << aresta->getNoFim()->getId() << " peso " << aresta->getPeso())
						
				if (noVisitado[aresta->getNoFim()->getId()] == false && aresta->getPeso() > maiorPeso) {
					maiorPeso = aresta->getPeso();
					arestaSelecionada = aresta;
				}
			}
		}

		No_t<T>* noSelecionado = arestaSelecionada->getNoFim();

		dprintln("proximo no: " << noSelecionado->getId())

		assert(noSelecionado != noAtual);

		auto* resultadoNoSelecionado = resultado->adicionarNo(noSelecionado->getValor());
		resultado->adicionarAresta(arestaSelecionada->getPeso(), resultadoNoAtual, resultadoNoSelecionado);

		noAtual = noSelecionado;
		resultadoNoAtual = resultadoNoSelecionado;

		noVisitado[noAtual->getId()] = true;
	}

	#ifdef SANITY
	bool sanity_caiu = false;
	#endif

	for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
		Aresta_t<K>* aresta = *it2;

		dprintln("\tchecando no " << aresta->getNoFim()->getId() << " peso " << aresta->getPeso())

		if (aresta->getNoFim() == pontoInicial) {
			#ifdef SANITY
			sanity_caiu = true;
			#endif
			PesoArestaBuscar = aresta->getPeso();
			dprintln("\tchecando ultimo no " << aresta->getNoFim()->getId() << " peso " << aresta->getPeso())
			break;
		}

	}
#ifdef SANITY
	assert(sanity_caiu);
#endif
	resultado->adicionarAresta(PesoArestaBuscar, resultadoNoAtual, resultadoNoInicio);
	return resultado;
}

template <typename T, typename K>
Grafo_t<T, K>* CaixeiroVizinhoMaisProximo(Grafo_t<T, K>& grafo) {
	using Grafo = Grafo_t<T, K>;

	Grafo* resultado = new Grafo(grafo.quantidadeNosGrafo());
	No_t<T>* pontoInicial = grafo.nos[0];
	double PesoArestaBuscar = 0.0;
	std::vector<bool> noVisitado(grafo.quantidadeNosGrafo(), false);
	No_t<T>* noAtual = pontoInicial;
	auto* resultadoNoAtual = resultado->adicionarNo(noAtual->getValor());
	auto* resultadoNoInicio = resultadoNoAtual;
	noVisitado[noAtual->getId()] = true;

	dprintln("Iniciou pelo no: " << noAtual->getId());

	for (int i = 1; i < grafo.quantidadeNosGrafo(); i++) {
		list<Aresta_t<K>*>* arestas = noAtual->getArestas();
		double maiorPeso = DBL_MAX;
		Aresta_t<K>* arestaSelecionada = nullptr;

		for (auto it2 = arestas->begin(); it2 != arestas->end(); it2++) {
			Aresta_t<K>* aresta = *it2;
			if (aresta->getNoFim()->getId() != noAtual->getId()) {
				dprintln("\tchecando no " << aresta->getNoFim()->getId() << " peso " << aresta->getPeso())

				if (noVisitado[aresta->getNoFim()->getId()] == false && aresta->getPeso() < maiorPeso) {
					maiorPeso = aresta->getPeso();
					arestaSelecionada = aresta;
				}
			}
		}

		No_t<T>* noSelecionado = arestaSelecionada->getNoFim();

		dprintln("proximo no: " << noSelecionado->getId())

		assert(noSelecionado != noAtual);

		auto* resultadoNoSelecionado = resultado->adicionarNo(noSelecionado->getValor());
		resultado->adicionarAresta(arestaSelecionada->getPeso(), resultadoNoAtual, resultadoNoSelecionado);

		noAtual = noSelecionado;
		resultadoNoAtual = resultadoNoSelecionado;

		noVisitado[noAtual->getId()] = true;
	}

	for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
		Aresta_t<K>* aresta = *it2;

		dprintln("\tchecando no " << aresta->getNoFim()->getId() << " peso " << aresta->getPeso())

		if (aresta->getNoFim() == pontoInicial) {
			PesoArestaBuscar = aresta->getPeso();
			dprintln("\tchecando ultimo no " << aresta->getNoFim()->getId() << " peso " << aresta->getPeso())
			break;
		}

	}

	resultado->adicionarAresta(PesoArestaBuscar, resultadoNoAtual, resultadoNoInicio);
	return resultado;
}

int main()
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	//// Criando um grafo
	Grafo_t<int, int>* grafo = new Grafo_t<int, int>(4);
	
	int valor_no_1 = 1;
	int valor_no_2 = 2;
	int valor_no_3 = 3;
	int valor_no_4 = 4;

	int um = 1;

	// Adicionando os nós
	No_t<int>* no1 = grafo->adicionarNo(valor_no_1);
	No_t<int>* no2 = grafo->adicionarNo(valor_no_2);
	No_t<int>* no3 = grafo->adicionarNo(valor_no_3);
	No_t<int>* no4 = grafo->adicionarNo(valor_no_4);

	// Adicionando as arestas
	grafo->adicionarAresta(10.0, no1, no2);
	grafo->adicionarAresta(15.0, no2, no1);
	grafo->adicionarAresta(20.0, no1, no3);
	grafo->adicionarAresta(25.0, no3, no1);
	grafo->adicionarAresta(12.0, no1, no4);
	grafo->adicionarAresta(18.0, no4, no1);
	grafo->adicionarAresta(22.0, no2, no3);
	grafo->adicionarAresta(8.0, no3, no2);
	grafo->adicionarAresta(13.0, no2, no4);
	grafo->adicionarAresta(17.0, no4, no2);
	grafo->adicionarAresta(2.0, no3, no4);
	grafo->adicionarAresta(1.0, no4, no3);

	//auto* grafo2 = CaixeiroInsercaoDoMaisDistante(grafo);

	AlgoritmoOtimo<int, int> algoritmo;

	algoritmo.caixeiro(grafo);

	return 0;

} 