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
			char matrizAdj[numNos][numNos];
			for (int i = 0; i < numNos; i++) {
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

			std::copy(matrizAdj.begin(), matrizAdj.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << std::endl;

			for (int i = 0; i < numNos; i++) {
				for (int j = 0; j < numNos; j++) {
					if (i != j) {
						continue;
					}
					else if (matrizAdj[i][j] != 'S') {
						return false;
					}
				}
			}

			return true;
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
	grafo.adicionarAresta(1, no1, no2, um);
	grafo.adicionarAresta(1, no2, no1, um);
	grafo.adicionarAresta(1, no1, no3, um);
	grafo.adicionarAresta(1, no3, no1, um);
	grafo.adicionarAresta(1, no1, no4, um);
	grafo.adicionarAresta(1, no4, no1, um);
	grafo.adicionarAresta(1, no2, no3, um);
	grafo.adicionarAresta(1, no3, no2, um);
	grafo.adicionarAresta(1, no2, no4, um);
	grafo.adicionarAresta(1, no4, no2, um);
	grafo.adicionarAresta(1, no3, no4, um);
	grafo.adicionarAresta(1, no4, no3, um);



	// Verificando se o grafo é completo
	if (grafo.verificarGrafoCompleto(&grafo)) {
		cout << "O grafo e completo!" << endl;
	}
	else {
		cout << "O grafo nao e completo!" << endl;
	}

	return 0;

}