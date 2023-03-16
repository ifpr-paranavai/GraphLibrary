#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include "No_t.h"
#include "Aresta_t.h"

using namespace std;

template <typename T>
class Grafo_t {

	private:
		list< Aresta_t<T>* > arestas;
		list< No_t<T>* > nos;
		vector< list< No_t<T>* > > listaAdjacencia;


	public:
		Grafo_t()
		{

		}

		No_t<T>* adicionarNo(T& valor) { 
			No_t<T> *no = new No_t<T>(valor);
			this->nos.push_back(no);
			adicionarNaListaAdjacencia(no);
			return no;
		}

		// Passar uma função lambda como parametro
		No_t<T>* getNo(std::function<bool(No_t<T>&)> funcao) {
			for (auto it = nos.begin(); it != nos.end(); ++it) {
				if (funcao(*it)) {
					return &(*it);
				}
			}
			return nullptr;
		}

		void adicionarNaListaAdjacencia(No_t<T>* no) {
			listaAdjacencia.push_back(list<No_t<T>*>());
		}

		Aresta_t<T>* adicionarAresta(double peso, No_t<T>* noInicio, No_t<T>* noFim, T& valor) {
			Aresta_t<T> *aresta = new Aresta_t<T>(peso, noInicio, noFim, valor);
			listaAdjacencia[noInicio].push_back(noFim);
			listaAdjacencia[noFim].push_back(noInicio);
			this->arestas.push_back(aresta);
			return aresta;
		}

		void imprimirListaAdjacencia() {
			for (int i = 0; i < listaAdjacencia.size(); i++) {
				cout << "Nó " << i << ": ";
				for (No_t<T>* no : listaAdjacencia[i]) {
					cout << no->getValor() << " ";
				}
				cout << endl;
			}
		}
};

int main()
{
	setlocale(LC_ALL, "pt_BR.UTF-8");
	Grafo_t<string> grafo;

	string a = "A";
	string b = "B";
	string c = "C";

	string ab = "A-B";
	string ac = "A-C";
	string bc = "B-C";

	No_t<string>* no1 = grafo.adicionarNo(a);
	No_t<string>* no2 = grafo.adicionarNo(b);
	No_t<string>* no3 = grafo.adicionarNo(c);

	grafo.adicionarAresta(1.0, no1, no2, ab);
	grafo.adicionarAresta(2.0, no1, no3, ac);
	grafo.adicionarAresta(3.0, no2, no3, bc);

	grafo.imprimirListaAdjacencia();

}