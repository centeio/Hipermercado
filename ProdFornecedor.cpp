/*
 * ProdFornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "ProdFornecedor.h"

//Constructor
ProdFornecedor::ProdFornecedor() {
	// TODO Auto-generated constructor stub
	produto = NULL;
	stock = 0;

}

ProdFornecedor::~ProdFornecedor() {
	// TODO Auto-generated destructor stub
}

Produto* ProdFornecedor::getProduto() const { return produto; }

double ProdFornecedor::getStock() const { return stock; }

vector<Patamar*> ProdFornecedor::getPatamares() const { return patamares; }

void ProdFornecedor::setProduto(Produto* produto) { this->produto = produto; }

void ProdFornecedor::setStock(double stock) { this->stock = stock; }

void ProdFornecedor::setPatamares(vector<Patamar*> patamares) { this->patamares = patamares; }

void ProdFornecedor::addPatamar(double min, double max, double preco) {
	Patamar* patamar = new Patamar(min,max,preco);

	patamares.push_back(patamar);
}

void ProdFornecedor::removePatamarIndice(int indice) {

	delete(*(patamares.begin() + indice));
	patamares.erase(patamares.begin() + indice);
}

void ProdFornecedor::removePatamarInterator(vector<Patamar *>::iterator it) {

	delete(*it);
	patamares.erase(it);
}

void ProdFornecedor::displayPatamares() const {


	for(unsigned int i = 0; i < patamares.size(); i++) {
		cout << "[" << setw(4) << patamares.at(i)->getMinimo() << "," << setw(4) << patamares.at(i)->getMaximo()
				<< "] Preco: " << patamares.at(i)->getPreco() << "€ cada" << endl;
	}
}
