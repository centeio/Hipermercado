/*
 * ProdFornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "ProdFornecedor.h"
#include <iterator>
#include <climits>

//Constructor
template<typename T>
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
vector<Patamar<T>*> ProdFornecedor<T>::getPatamares() const { return patamares; }

template<typename T>
void ProdFornecedor<T>::setProduto(Produto* produto) { this->produto = produto; }

template<typename T>
void ProdFornecedor<T>::setStock(T stock) { this->stock = stock; }

template<typename T>
void ProdFornecedor<T>::setPatamares(vector<Patamar<T>*> patamares) { this->patamares = patamares; }

template<typename T>
void ProdFornecedor<T>::addPatamar(T min, T max, float preco) {
	Patamar<T>* patamar = new Patamar<T>(min,max,preco);

	patamares.push_back(patamar);
}

template<typename T>
void ProdFornecedor<T>::removePatamarIndice(int indice) {

	delete(*(patamares.begin() + indice));
	patamares.erase(patamares.begin() + indice);
}


template<typename T>
void ProdFornecedor<T>::displayPatamares() {

	for(unsigned int i = 0; i < patamares.size(); i++) {
		cout << patamares.at(i) << endl;
	}
}

template<typename T>
float ProdFornecedor<T>::getPrecoStock() const {

	for(unsigned int i = 0; i < patamares.size(); i++) {
		if(stock > patamares.at(i)->getMinimo() && stock < patamares.at(i)->getMaximo()) {
			return patamares.at(i)->getPreco();
		}
	}
	return -1;
}


template<typename T>
melhorPreco<T> ProdFornecedor<T>::getMelhorPreco(string nome, T quantidade) {
	melhorPreco<T> melhorpreco;

	for(unsigned int i = 0; i < patamares.size(); i++) {
		if(quantidade > patamares.at(i)->getMinimo() && quantidade < patamares.at(i)->getMaximo()) {
			melhorpreco.quantidade = quantidade;
			melhorpreco.preco = patamares.at(i)->getPreco();
			return melhorpreco;
		}
	}
	melhorpreco.quantidade = stock;
	melhorpreco.preco = getPrecoStock();
	return melhorpreco;
}

template<typename T>
ostream& operator<<(ostream& out, Patamar<T>* patamar) {

	out << "[" << setw(4) << patamar->getMinimo() << "," << setw(4) << patamar->getMaximo() << "] Preco: "
			<< patamar->getPreco() << "€ cada";
	return out;
}

template class ProdFornecedor<double>;
template class ProdFornecedor<int>;
