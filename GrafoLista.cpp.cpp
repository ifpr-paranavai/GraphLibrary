#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include "No_t.h"
#include "Aresta_t.h"

using namespace std;

#define DEBUG

// ---------------------------------------------------

#ifdef DEBUG
	#define dprint(STR) { std::cout << STR; }
	#define dprintln(STR) { std::cout << STR << std::endl; }
#else
	#define dprint(STR)
	#define dprintln(STR)
#endif


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
			No_t<T> *no = new No_t<T>(valor, this->nos.size());
			this->nos.push_back(no);
			return no;
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
			Aresta_t<K> *aresta = new Aresta_t<K>(peso, noInicio, noFim);
			noInicio->adicionarAresta(aresta);
			Aresta_t<K>* arestaInvertida = new Aresta_t<K>(peso, noFim, noInicio);
			noFim->adicionarAresta(aresta);
			//this->arestas.push_back(aresta);
			//return aresta;
		}

		bool verificarGrafoCompleto(Grafo_t<T, K>* grafo) {
			int numNos = this->nos.size();
			char **matrizAdj = new char*[numNos];
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

		#if 0
		Grafo_t<T, K>* BranchAndBound(Grafo_t<T, K>& grafo) {
			double melhorCaminho = DBL_MAX;

			Grafo_t<T, K>* resultado = new Grafo_t<T, K>(grafo.quantidadeNosGrafo());
			No_t<T>* pontoInicial = grafo.nos[0];
			std::vector<bool> noVisitado(grafo.quantidadeNosGrafo(), false);
			No_t<T>* noAtual = pontoInicial;
			double PesoArestaBuscar;
			double custoAtual = DBL_MAX;

			
			for (int i = 1; i < grafo.quantidadeNosGrafo(); i++) {
				list<Aresta_t<K>*>* arestas = noAtual->getArestas();
				if (resultado->quantidadeNosGrafo() == grafo.quantidadeNosGrafo() - 1) {
					// precisa adicionar a última aresta que liga o o último nó ao primeiro nó
					for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
						Aresta_t<K>* aresta = *it2;

						if (aresta->getNoFim() == pontoInicial) {
							PesoArestaBuscar = aresta->getPeso();
						}
						resultado->adicionarAresta(PesoArestaBuscar, noAtual, pontoInicial);
						// precisa fazer calcular o custo, exemplo:
						// custoAtual = calcularCusto(resultado)
						if (custoAtual < melhorCaminho) {
							melhorCaminho = custoAtual;
						}
					}

					if (custoAtual < melhorCaminho) {
						melhorCaminho = custoAtual;
					}
					return;
				}
			}
			
			for (int i = 0; i < grafo.quantidadeNosGrafo(); i++) {
				noAtual = grafo.nos[i];
				if (!noVisitado[noAtual->getId()]) {
					resultado->adicionarNo(grafo.nos[i]);
					noVisitado[noAtual->getId()] = true;
					//calcular limite superior

					//se o limite superior < melhorCaminho 
					//BranchAndBound(Grafo_t<T, K>& grafo) 

				}
			}

			return resultado;

		}
		#endif



		#if 0
		Grafo_t<T, K>* CaixeiroVizinhoMaisProximo(Grafo_t<T, K>& grafo) {
			using Grafo = Grafo_t<T, K>;

			Grafo_t<T, K>* resultado = new Grafo_t<T, K>(grafo.quantidadeNosGrafo());
			Grafo::No* pontoInicial = grafo.nos[0];
			double PesoArestaBuscar = 0.0;
			std::vector<bool> noVisitado(grafo.quantidadeNosGrafo(), false);
			No_t<T>* noAtual = pontoInicial;
			auto* resultadoNoAtual = resultado->adicionarNo(noAtual->getValor());
			auto* resultadoNoInicio = resultadoNoAtual;
			noVisitado[noAtual->getId()] = true;

			for (int i = 1; i < grafo.quantidadeNosGrafo(); i++) {
				list<Aresta_t<K>*>* arestas = noAtual->getArestas();
				double maiorPeso = DBL_MAX;
				Aresta_t<K>* arestaSelecionada = nullptr;

				for (auto it2 = arestas->begin(); it2 != arestas->end(); it2++) {
					Aresta_t<K>* aresta = *it2;

					if (noVisitado[aresta->getNoFim()->getId()] == false && aresta->getPeso() < maiorPeso) {
						maiorPeso = aresta->getPeso();
						arestaSelecionada = aresta;
					}

				}

				No_t<T>* noSelecionado = arestaSelecionada->getNoFim();
				auto* resultadoNoSelecionado = resultado->adicionarNo(noSelecionado->getValor());
				resultado->adicionarAresta(arestaSelecionada->getPeso(), resultadoNoAtual, resultadoNoSelecionado);

				noAtual = noSelecionado;
				resultadoNoAtual = resultadoNoSelecionado;

				noVisitado[noAtual->getId()] = true;
			}


			for (auto it2 = noAtual->getArestas()->begin(); it2 != noAtual->getArestas()->end(); it2++) {
				Aresta_t<K>* aresta = *it2;

				if (aresta->getNoFim() == pontoInicial) {
					PesoArestaBuscar = aresta->getPeso();
				}

			}

			resultado->adicionarAresta(PesoArestaBuscar, resultadoNoAtual, resultadoNoInicio);

			return resultado;
		}
		#endif
};


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
	Grafo_t<int, int> grafo(4);

	int valor_no_1 = 1;
	int valor_no_2 = 2;
	int valor_no_3 = 3;
	int valor_no_4 = 4;

	int um = 1;

	// Adicionando os nós
	No_t<int>* no1 = grafo.adicionarNo(valor_no_1);
	No_t<int>* no2 = grafo.adicionarNo(valor_no_2);
	No_t<int>* no3 = grafo.adicionarNo(valor_no_3);
	No_t<int>* no4 = grafo.adicionarNo(valor_no_4);

	// Adicionando as arestas
	grafo.adicionarAresta(10.0, no1, no2);
	grafo.adicionarAresta(15.0, no2, no1);
	grafo.adicionarAresta(20.0, no1, no3);
	grafo.adicionarAresta(25.0, no3, no1);
	grafo.adicionarAresta(12.0, no1, no4);
	grafo.adicionarAresta(18.0, no4, no1);
	grafo.adicionarAresta(22.0, no2, no3);
	grafo.adicionarAresta(8.0, no3, no2);
	grafo.adicionarAresta(13.0, no2, no4);
	grafo.adicionarAresta(17.0, no4, no2);
	grafo.adicionarAresta(2.0, no3, no4);
	grafo.adicionarAresta(1.0, no4, no3);

	auto* grafo2 = CaixeiroInsercaoDoMaisDistante<int, int>(grafo);

	return 0;

} 