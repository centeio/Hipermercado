/*
 * Fornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Fornecedor.h"

template<typename T>
Fornecedor<T>::Fornecedor() {
	// TODO Auto-generated constructor stub

}

template<typename T>
Fornecedor<T>::~Fornecedor() {
	// TODO Auto-generated destructor stub
}

template<typename T>
string Fornecedor<T>::getNome() const { return nome; }

template<typename T>
string Fornecedor<T>::getNIF() const { return NIF; }

template<typename T>
string Fornecedor<T>::getMorada() const { return morada; }

template<typename T>
void Fornecedor<T>::addProduto(Produto* produto, T stock, vector<Patamar<T>* > patamares) {
	ProdFornecedor<T>* prodFornecedor = new ProdFornecedor<T>(produto, stock, patamares);

	produtos.push_back(prodFornecedor);
}

template<typename T>
void Fornecedor<T>::decStock(Produto* produto, T quantidade) {

	for(unsigned int i = 0; i < produtos.size(); i++) {
		if(*produto == *produtos.at(i)->getProduto())
			produtos.at(i)->setStock(produtos.at(i)->getStock() - quantidade);
	}
}

template class Fornecedor<double>;
template class Fornecedor<int>;
