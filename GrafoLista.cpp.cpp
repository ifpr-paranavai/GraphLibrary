#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include "No_t.h"
#include "Aresta_t.h"

using namespace std;

template <typename T, typename K>
class Grafo_t {

	private:
		list< Aresta_t<K>* > arestas;
		vector< No_t<T>* > nos;

	public:
		Grafo_t(int qtdeNos)
		{
			this->nos.reserve(qtdeNos);
		}

		No_t<T>* adicionarNo(T& valor) { 
			No_t<T> *no = new No_t<T>(valor);
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

		Aresta_t<K>* adicionarAresta(double peso, No_t<T>* noInicio, No_t<T>* noFim, T& valor) {
			Aresta_t<K> *aresta = new Aresta_t<K>(peso, noInicio, noFim, valor);
			noInicio->adicionarAresta(aresta);
			this->arestas.push_back(aresta);
			return aresta;
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
		
		double calcularDistancia(No_t<T>* no1, No_t<T>* no2) {
			return 0.0;
		}

		void InsercaoDoMaisDistante() {
			if (nos.empty()) {
				cout << "O grafo está vazio." << endl;
				return;
			}

			No_t<T>* pontoInicial = nos[0];
			No_t<T>* pontoMaisDistante = nullptr;
			double maiorDistancia = 0.0;

			for (auto it = nos.begin(); it != nos.end(); it++) {
				No_t<T>* noAtual = *it;
				if (noAtual != pontoInicial) {
					list<Aresta_t<K>*> arestas = pontoInicial->getArestas();

					for (auto it2 = arestas.begin(); it2 != arestas.end(); it2++) {
						Aresta_t<K>* aresta = *it2;
						No_t<T>* noDestino = aresta->getNoFim();

						if (noDestino == noAtual) {
							double pesoAresta = aresta->getPeso();
							if (pesoAresta > maiorDistancia) {
								maiorDistancia = pesoAresta;
								pontoMaisDistante = noAtual;
							}
							break;
						}
					}
				}
			}

			if (pontoMaisDistante != nullptr) {
				// Adiciona o ponto mais distante ao grafo
				adicionarNo(pontoMaisDistante->getValor());
				adicionarAresta(maiorDistancia, pontoInicial, pontoMaisDistante, pontoMaisDistante->getValor());
			}
		}

		void VizinhoMaisProximo(Grafo_t<T, K> grafo, No_t<T> ponto_inicial) {
			int i = 0;
			if (nos.empty()) {
				cout << "O grafo está vazio." << endl;
				return;
			}

			vector<bool> visitados(nos.size(), false);
			int numNosVisitados = 0;

			visitados[ponto_inicial->getId()] = true;
			numNosVisitados++;

			while (numNosVisitados < nos.size()) {
				int menorPeso = numeric_limits<int>::max();
				int indiceMenorPeso = -1;

				for (int i = 0; i < nos.size(); i++) {
					if (visitados[i]) {
						No_t<T>* noAtual = nos[i];
						list<Aresta_t<K>*> arestas = noAtual->getArestas();

						for (auto it = arestas.begin(); it != arestas.end(); it++) {
							Aresta_t<K>* aresta = *it;
							No_t<T>* noDestino = aresta->getNoFim();

							if (!visitados[noDestino->getId()]) {
								if (aresta->getPeso() < menorPeso) {
									menorPeso = aresta->getPeso();
									indiceMenorPeso = noDestino->getId();
									cout << indiceMenorPeso;
								}
							}
						}
					}
				}

				visitados[indiceMenorPeso] = true;
				numNosVisitados++;
			}
		}

};


int main()
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	// Criando um grafo
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
	grafo.adicionarAresta(10.0, no1, no2, um);
	grafo.adicionarAresta(15.0, no2, no1, um);
	grafo.adicionarAresta(20.0, no1, no3, um);
	grafo.adicionarAresta(25.0, no3, no1, um);
	grafo.adicionarAresta(12.0, no1, no4, um);
	grafo.adicionarAresta(18.0, no4, no1, um);
	grafo.adicionarAresta(22.0, no2, no3, um);
	grafo.adicionarAresta(8.0, no3, no2, um);
	grafo.adicionarAresta(13.0, no2, no4, um);
	grafo.adicionarAresta(17.0, no4, no2, um);
	grafo.adicionarAresta(2.0, no3, no4, um);
	grafo.adicionarAresta(1.0, no4, no3, um);

	return 0;

} 