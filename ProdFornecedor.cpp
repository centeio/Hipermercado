/*
 * ProdFornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "ProdFornecedor.h"
#include <iterator>
#include <climits>
#include <sstream>

//Constructor

ProdFornecedor::ProdFornecedor() {
	// TODO Auto-generated constructor stub
	produto = NULL;
	stock = 0;

}


Produto* ProdFornecedor::getProduto() const { return produto; }


unsigned int ProdFornecedor::getStock() const { return stock; }


vector<Patamar*> ProdFornecedor::getPatamares() const { return patamares; }


void ProdFornecedor::setProduto(Produto* produto) { this->produto = produto; }


void ProdFornecedor::setStock(unsigned int stock) { this->stock = stock; }


void ProdFornecedor::setPatamares(vector<Patamar*> patamares) { this->patamares = patamares; }


void ProdFornecedor::addPatamar(string min, string max, string preco) {
	int minimo,maximo;
	float prec;
	stringstream str(min);

	str >> minimo; str.clear();
	str << max;	str >> maximo; str.clear();
	str << preco; str >> prec; str.clear();

	Patamar* patamar = new Patamar(minimo,maximo,prec);

	patamares.push_back(patamar);
}


void ProdFornecedor::removePatamarIndice(int indice) {

	delete(*(patamares.begin() + indice));
	patamares.erase(patamares.begin() + indice);
}



void ProdFornecedor::displayPatamares() {

	for(unsigned int i = 0; i < patamares.size(); i++) {
		cout << patamares.at(i) << endl;
	}
}


float ProdFornecedor::getPrecoStock() const {

	for(unsigned int i = 0; i < patamares.size(); i++) {
		if(stock > patamares.at(i)->getMinimo() && stock < patamares.at(i)->getMaximo()) {
			return patamares.at(i)->getPreco();
		}
	}
	return -1;
}



melhorPreco ProdFornecedor::getMelhorPreco(string nome,unsigned int quantidade) {
	melhorPreco melhorpreco;

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


//ProdForncedorUnidade
ProdFornecedorUnidade::ProdFornecedorUnidade(Produto* produto,unsigned int stock, vector<Patamar*> patamares) : ProdFornecedor(produto,stock) {

	if (patamares.size() > 1) throw DemasiadosPatamares();
	this->patamares = patamares;
}

void ProdFornecedorUnidade::addPatamar(string min, string max, string preco) {
	int minimo,maximo;
	float prec;
	stringstream str(min);

	if(patamares.size() > 1) throw DemasiadosPatamares();

	str >> minimo; str.clear();
	str << max;	str >> maximo; str.clear();
	str << preco; str >> prec; str.clear();

	Patamar* patamar = new Patamar(minimo,maximo,prec);
	patamares.push_back(patamar);
}

//ProdFornecedorEmpresa
void ProdFornecedorEmpresa::addPatamar(string min, string max, string preco) {
	int minimo,maximo;
	float prec;
	stringstream str(min);

	str >> minimo; str.clear();
	str << max;	str >> maximo; str.clear();
	str << preco; str >> prec; str.clear();

	Patamar* patamar = new Patamar(minimo,maximo,prec);
	patamares.push_back(patamar);
}



