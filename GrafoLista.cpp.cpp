#include <iostream>
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

	public:
		Grafo_t()
		{

		}

		void adicionarNo(No_t<T>* no) {
			this->nos.push_back(no);
		}

		No_t<T>* getNo(No_t<T>* no) 
		{
			No_t<T> no = NULL;
			auto it = this->nos.begin();
			for (int i = 0; i < this->nos.size(); i++) 
			{
				No_t<T> aux = *std::next(it, i);
				T valor = aux.getValor();
				if (valor == no.getValor())
				{
					no = *std::next(it, i);
					break;
				}
			}

			return no;
		}

		void adicionarAresta(double peso, No_t<T>* noInicio, No_t<T>* noFim) {
			No_t<T>* noInicioP = nullptr;
			No_t<T>* noFimP = nullptr;
			No_t<T> inicio = this->getNo(noInicio);
			No_t<T> fim = this->getNo(noFim);
			noInicioP = &inicio;
			noFimP = &fim;
			Aresta_t<T> aresta(peso, noInicioP, noFimP);
			inicio.adicionarArestaSaida(aresta);
			fim.adicionarArestaEntrada(aresta);
			this->arestas.push_back(aresta);
		}
};

int main()
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	Grafo_t<string> grafo = Grafo_t<string>();
	No_t<string> *no = new No_t<string>("1");

	grafo.adicionarNo(no);

	std::cout << grafo.getNo(no)->getValor();


}