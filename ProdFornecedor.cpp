/*
 * ProdFornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "ProdFornecedor.h"
#include <iterator>

//Constructor
template<class T>
ProdFornecedor<T>::ProdFornecedor() {
	// TODO Auto-generated constructor stub
	produto = NULL;
	stock = 0;

}

template<typename T>
Produto* ProdFornecedor<T>::getProduto() const { return produto; }

template<typename T>
T ProdFornecedor<T>::getStock() const { return stock; }

template<typename T>
vector<Patamar*> ProdFornecedor<T>::getPatamares() const { return patamares; }

template<typename T>
void ProdFornecedor<T>::setProduto(Produto* produto) { this->produto = produto; }

template<typename T>
void ProdFornecedor<T>::setStock(T stock) { this->stock = stock; }

template<typename T>
void ProdFornecedor<T>::setPatamares(vector<Patamar*> patamares) { this->patamares = patamares; }

template<typename T>
void ProdFornecedor<T>::addPatamar(double min, double max, double preco) {
	Patamar* patamar = new Patamar(min,max,preco);

	patamares.push_back(patamar);
}

template<typename T>
void ProdFornecedor<T>::removePatamarIndice(int indice) {

	delete(*(patamares.begin() + indice));
	patamares.erase(patamares.begin() + indice);
}

template<typename T>
void ProdFornecedor<T>::removePatamarInterator(vector<Patamar *>::iterator it) {

	delete(*it);
	patamares.erase(it);
}

template<typename T>
void ProdFornecedor<T>::displayPatamares() {

	for(vector<Patamar*>::iterator it = patamares.begin(); it != patamares.end(); it++) {
		cout << *it << endl;
	}
}

ostream& operator<<(ostream& out, Patamar* patamar) {

	out << "[" << setw(4) << patamar->getMinimo() << "," << setw(4) << patamar->getMaximo() << "] Preco: "
			<< patamar->getPreco() << "€ cada";
	return out;
}

template class ProdFornecedor<double>;
template class ProdFornecedor<int>;
