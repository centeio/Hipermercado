/*
 * Produto.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */


#include <climits>
#include "Produto.h"
#include "Exceptions.h"

//Produto

/**
 *	@brief Constroi produto
 *
 */
Produto::Produto() {
	// TODO Auto-generated constructor stub
	nome = "";
	medida = "";
	stock = 0;
}


/**
 *	@brief Destroi o produto
 *
 */
Produto::~Produto() {
	// TODO Auto-generated destructor stub

}


/**
 *	@return Retorna o nome do produto
 */
string Produto::getNome() const { return nome; }


/**
 *	@brief Define o nome do produto
 *
 * @param nome Nome do produto
 */
void Produto::setNome(string nome) { this->nome = nome; }


/**
 *	@return Retorna a medida do produto
 *
 */
string Produto::getMedida() const {	return medida; }


/**
 *	@brief Define a medida do produto
 *
 * @param medida Medida do produto
 */
void Produto::setMedida(string medida) { this->medida = medida; }

float Produto::getStock() const { return stock; }


void Produto::setStock(float stock) { this->stock = stock; }


/**
 * @brief Compara a igualdade de dois produtos
 *
 *	@param &produto Produto
 *
 *	@return Retorna verdadeiro se os dois produtos comparados tiverem nomes iguais; caso contrario, retorna falso.
 */
bool Produto::operator== (Produto &produto) { return (nome == produto.getNome()); }


/** @brief Imprime no ecra os atributos da classe por overload do operator<<
 *
 *	@param out Objeto da iostream
 *	@param produto Produto
 *
 *	@return Retorna ostream
 */
ostream& operator<< (ostream& out, Produto* produto) {

	out << setw(15) << produto->nome << setw(15) << produto->medida << endl;
	return out;

}


//ProdutoFornecedor

/*void ProdutoFornecedor::addPatamar() {
	float preco;
	unsigned int min, max;

	if(fornecedor->getTipo() == "Individual") {
		if(patamares.size() == 0) {
			cout << "Introduza o preco: " << flush;
			cin >> preco;
			Patamar* pat = new Patamar(0, UINT_MAX, preco);
			patamares.push_back(pat);
		}else throw DemasiadosPatamares();
	} else {
		cout << "Introduza o patamar minimo: " << flush;
		cin >> min;
		cout << "Introduza o patamar maximo: " << flush;
		cin >> max;
		cout << "Introduza o preco: " << flush;
		cin >> preco;
		Patamar* pat = new Patamar(min, max, preco);
		patamares.push_back(pat);
	}
}*/

Fornecedor* ProdutoFornecedor::getFornecedor() const { return fornecedor; }

Patamar* ProdutoFornecedor::getPatamar() const { return patamar; }

void ProdutoFornecedor::setFornecedor(Fornecedor *fornecedor) { this->fornecedor = fornecedor; }

bool ProdutoFornecedor::operator < (ProdutoFornecedor produto) const {

	if(nome < produto.getNome()) return true;
	else if(nome == produto.getNome()) {
		if(patamar->getPreco() <= produto.getPatamar()->getPreco()) return true;
	}

	return false;
}


ostream& operator<< (ostream& out, ProdutoFornecedor produto) {

	out << produto.getNome() << " " << produto.getMedida() << " " << produto.getStock() << " " << produto.getPatamar()->getPreco() << endl;
	return out;
}
