#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <stdlib.h>
#include <time.h>
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

	dprintln("Iniciou pelo no: " << noAtual->getValor());

	for (int i = 1; i < grafo.quantidadeNosGrafo(); i++) {
		list<Aresta_t<K>*>* arestas = noAtual->getArestas();
		double maiorPeso = -1.0;
		Aresta_t<K>* arestaSelecionada = nullptr;

		for (auto it2 = arestas->begin(); it2 != arestas->end(); it2++) {
			Aresta_t<K>* aresta = *it2;
			if (aresta->getNoFim()->getId() != noAtual->getId()) {
				dprintln("\tchecando no " << aresta->getNoFim()->getValor() << " peso " << aresta->getPeso())

				if (noVisitado[aresta->getNoFim()->getId()] == false && aresta->getPeso() > maiorPeso) {
					maiorPeso = aresta->getPeso();
					arestaSelecionada = aresta;
				}
			}
		}

		No_t<T>* noSelecionado = arestaSelecionada->getNoFim();

		dprintln("proximo no: " << noSelecionado->getValor())

			assert(noSelecionado != noAtual);

		auto* resultadoNoSelecionado = resultado->adicionarNo(noSelecionado->getValor());
		resultado->adicionarAresta(arestaSelecionada->getPeso(), resultadoNoAtual, resultadoNoSelecionado);

		noAtual = noSelecionado;
		resultadoNoAtual = resultadoNoSelecionado;

		noVisitado[noAtual->getId()] = true;
	}

	for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
		Aresta_t<K>* aresta = *it2;

		dprintln("\tchecando no " << aresta->getNoFim()->getValor() << " peso " << aresta->getPeso())

			if (aresta->getNoFim() == pontoInicial) {
				PesoArestaBuscar = aresta->getPeso();
				dprintln("\tchecando ultimo no " << aresta->getNoFim()->getValor() << " peso " << aresta->getPeso())
					break;
			}

	}

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

	dprintln("Iniciou pelo no: " << noAtual->getValor());

	for (int i = 1; i < grafo.quantidadeNosGrafo(); i++) {
		list<Aresta_t<K>*>* arestas = noAtual->getArestas();
		double maiorPeso = DBL_MAX;
		Aresta_t<K>* arestaSelecionada = nullptr;

		for (auto it2 = arestas->begin(); it2 != arestas->end(); it2++) {
			Aresta_t<K>* aresta = *it2;
			if (aresta->getNoFim()->getId() != noAtual->getId()) {
				dprintln("\tchecando no " << aresta->getNoFim()->getValor() << " peso " << aresta->getPeso())

				if (noVisitado[aresta->getNoFim()->getId()] == false && aresta->getPeso() < maiorPeso) {
					maiorPeso = aresta->getPeso();
					arestaSelecionada = aresta;
				}
			}
		}

		No_t<T>* noSelecionado = arestaSelecionada->getNoFim();

		dprintln("proximo no: " << noSelecionado->getValor())

		assert(noSelecionado != noAtual);

		auto* resultadoNoSelecionado = resultado->adicionarNo(noSelecionado->getValor());
		resultado->adicionarAresta(arestaSelecionada->getPeso(), resultadoNoAtual, resultadoNoSelecionado);

		noAtual = noSelecionado;
		resultadoNoAtual = resultadoNoSelecionado;

		noVisitado[noAtual->getId()] = true;
	}

	for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
		Aresta_t<K>* aresta = *it2;

		dprintln("\tchecando no " << aresta->getNoFim()->getValor() << " peso " << aresta->getPeso())

		if (aresta->getNoFim() == pontoInicial) {
			PesoArestaBuscar = aresta->getPeso();
			dprintln("\tchecando ultimo no " << aresta->getNoFim()->getValor() << " peso " << aresta->getPeso())
			break;
		}

	}

	resultado->adicionarAresta(PesoArestaBuscar, resultadoNoAtual, resultadoNoInicio);

	return resultado;
}

template <typename T, typename K>
void imprimirGrafo_(Grafo_t<T, K>* grafo, vector<bool>& nosVisitados, No_t<T>* noAtual, double& custoAcumulado, No_t<T>** ultimoNo) {
	assert(noAtual->getArestas()->size() == 2);
	for (auto* aresta: *noAtual->getArestas()) {
		No_t<T>* noDestino = aresta->getNoFim();
		if (nosVisitados[noDestino->getId()] == false) {
			nosVisitados[noDestino->getId()] = true;
			dprint(" " << noDestino->getValor());
			*ultimoNo = noDestino;
			custoAcumulado += aresta->getPeso();
			imprimirGrafo_(grafo, nosVisitados, noDestino, custoAcumulado, ultimoNo);
		}
	}

}

template <typename T, typename K>
void imprimirGrafo(Grafo_t<T, K>* grafo) {
	vector<bool> nosVisitados(grafo->quantidadeNosGrafo(), false);
	No_t<T>* noInicial = grafo->nos[0];
	No_t<T>* ultimoNo = nullptr;
	double custoAcumulado = 0;
	nosVisitados[noInicial->getId()] = true;
	dprint(" " << noInicial->getValor());
	imprimirGrafo_(grafo, nosVisitados, noInicial, custoAcumulado, &ultimoNo);
	dprintln("[" << ultimoNo->getValor() << "]");
	assert(ultimoNo->getArestas()->size() == 2);
	for (auto* aresta: *ultimoNo->getArestas()) {
		if (aresta->getNoFim() == noInicial) {
			custoAcumulado += aresta->getPeso();
			break;
		}
	}
	dprintln("    custo acumulado: " << custoAcumulado);
}

template <typename T, typename K>
Grafo_t<T, K>* gerarGrafoInteirosAleatorio(int numeroNos) {
	
	std::srand(std::time(0));

	double lower_bound = 0;
	double upper_bound = 100;

	Grafo_t<T, K>* grafo = new Grafo_t<T, K>(numeroNos);
	No_t<T>* noAnterior = nullptr;

	for (int i = 0; i < numeroNos; i++) {
		int valorAleatorio = i;
		grafo->adicionarNo(valorAleatorio);
	}

	vector<bool> noVisitado(grafo->quantidadeNosGrafo(), false);
	for (int i = 0; i < numeroNos-1; i++) {
		No_t<T>* noInicial = grafo->nos[i];

		for (int j = 1; j < numeroNos; j++) {
			int random_integer = std::rand();
			double random_double = lower_bound + (upper_bound - lower_bound) * (static_cast<double>(random_integer) / RAND_MAX);
			double pesoAleatorio = random_double;
			No_t<T>* noFinal = grafo->nos[j];
			Aresta_t<T>* aresta = new Aresta_t<T>(pesoAleatorio, noInicial, noFinal);

			if (!(noVisitado[noFinal->getId()]) && (noFinal != noAnterior && noFinal != noInicial)) {
				grafo->adicionarAresta(pesoAleatorio, noInicial, noFinal);
			}
		}
		noVisitado[noInicial->getId()] = true;
		//noAnterior = noInicial;
	}

	return grafo;

}


int main()
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	////// Criando um grafo
	//Grafo_t<int, int>* grafo = new Grafo_t<int, int>(5);

	//// Adicionando os nós
	//No_t<int>* no1 = grafo->adicionarNo(1);
	//No_t<int>* no2 = grafo->adicionarNo(2);
	//No_t<int>* no3 = grafo->adicionarNo(3);
	//No_t<int>* no4 = grafo->adicionarNo(4);
	//No_t<int>* no5 = grafo->adicionarNo(5);


	//// Adicionando as arestas
	//grafo->adicionarAresta(1.0, no1, no2);
	//grafo->adicionarAresta(20.0, no1, no3);
	//grafo->adicionarAresta(6.0, no1, no4);
	//grafo->adicionarAresta(15.0, no1, no5);
	//grafo->adicionarAresta(10.0, no2, no3);
	//grafo->adicionarAresta(7.0, no2, no4);
	//grafo->adicionarAresta(35.0, no2, no5);
	//grafo->adicionarAresta(30.0, no3, no4);
	//grafo->adicionarAresta(20.0, no3, no5);
	//grafo->adicionarAresta(10.0, no4, no5);

	//Grafo_t<int, int>* grafoVizinhoMaisProximo = CaixeiroVizinhoMaisProximo(*grafo);

	//dprint("Grafo vizinho mais próximo: ");
	//imprimirGrafo(grafoVizinhoMaisProximo);

	//Grafo_t<int, int>* grafoVizinhoMaisDistante = CaixeiroInsercaoDoMaisDistante(*grafo);
	//
	//dprint("Grafo vizinho mais distante: ");
	//imprimirGrafo(grafoVizinhoMaisDistante);

	//AlgoritmoOtimo<int, int> algoritmo;

	//Grafo_t<int, int> grafo1 = Grafo_t<int, int>(grafo->quantidadeNosGrafo());
	//algoritmo.caixeiro(grafo);

	Grafo_t<int, int>* grafoAleatorio = gerarGrafoInteirosAleatorio<int, int>(10);
	
	Grafo_t<int, int>* grafoVizinhoMaisDistanteAleatorio = CaixeiroInsercaoDoMaisDistante(*grafoAleatorio);

	return 0;

} 