/*
 * ProdFornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "ProdFornecedor.h"
#include <climits>
#include <sstream>

//Constructor

ProdFornecedor::ProdFornecedor() {
	// TODO Auto-generated constructor stub
	produto = NULL;
	stock = 0;
	/**
		 *	@brief Construtor do Produto do Fornecedor
		 */

}

Produto* ProdFornecedor::getProduto() const {
	return produto;
	/**
	*	@return Retorna o nome do produto do fornecedor
	*/
}


unsigned int ProdFornecedor::getStock() const {
	return stock;
	/**
	*	@return Retorna o stock do produto do fornecedor
	*
	*/
}


vector<Patamar*> ProdFornecedor::getPatamares() const {
	return patamares;
	/**
	*	@return Retorna os patamares do produto do fornecedor
	*
	*/
}


void ProdFornecedor::setProduto(Produto* produto) {
	this->produto = produto;
	/**
	*	@brief Define o produto do fornecedor
	*
	*@param produto Produto do fornecedor
	*/
}


void ProdFornecedor::setStock(unsigned int stock) {
	this->stock = stock;
	/**
	*	@brief Define o stock do produto do fornecedor
	*
	*@param stock Stock do produto
	*/
}


void ProdFornecedor::setPatamares(vector<Patamar*> patamares) {
	this->patamares = patamares;
	/**
	*	@brief Define os patamares do produto do fornecedor
	*
	*@param patamares Patamares do produto
	*/
}


void ProdFornecedor::addPatamar(unsigned int min, unsigned int max, unsigned int preco) {

	Patamar* patamar = new Patamar(min,max,preco);
	patamares.push_back(patamar);
	/**
		*	@brief Adiciona um patamar a um produto do fornecedor
		*
		*@param min Valor minimo do patamar
		*@param max Valor maximo do patamar
		*@param preco Preco do patamar
		*
		*/
}


void ProdFornecedor::removePatamarIndice(int indice) {

	delete(*(patamares.begin() + indice));
	patamares.erase(patamares.begin() + indice);
	/**
			*	@brief Remove um patamar a um produto do fornecedor
			*
			*@param indice Indice do patamar a ser removido
			*
			*/
}

void ProdFornecedor::displayPatamares() {

	for(unsigned int i = 0; i < patamares.size(); i++) {
		cout << patamares.at(i) << endl;
	}
	/**
					*	@brief Mostra todos os patamares do produto
					*
					*/
}


float ProdFornecedor::getPrecoStock() const {

	for(unsigned int i = 0; i < patamares.size(); i++) {
		if(stock > patamares.at(i)->getMinimo() && stock < patamares.at(i)->getMaximo()) {
			return patamares.at(i)->getPreco();
		}
	}
	return -1;
	/**
		*	@return Retorna o preço para a quantidade igual ao stock
		*
		*/
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
	/**
				*	@brief Retorna o melhor preco
				*
				*@param nome Nome do Produto
				*@param quantidade Quantidade
				*
				*@return Melhor preco
				*/

}

ostream& operator<< (ostream& out, ProdFornecedor* prodFornecedor) {

	out << prodFornecedor->produto << setw(15) << prodFornecedor->stock << endl;
	return out;
	/** @brief Imprime no ecra os atributos da classe por overload do operator<<
				*
				*	@param out Objeto da iostream
				*	@param produto Produto
				*
				*	@return Retorna ostream
				*/
}
