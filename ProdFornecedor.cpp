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
