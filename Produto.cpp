/*
 * Produto.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Produto.h"
#include <iomanip>

//Produto
Produto::Produto() {
	// TODO Auto-generated constructor stub
	nome = "";
	/**
		*	@brief Constroi produto
		*
		*/

}

Produto::~Produto() {
	// TODO Auto-generated destructor stub
	/**
		*	@brief Destroi o produto
		*
		*/
}

string Produto::getNome() const {
	return nome;
	/**
	*	@return Retorna o nome do produto
	*/
}

void Produto::setNome(string nome) {
	this->nome = nome;
	/**
	*	@brief Define o nome do produto
	*
	* @param nome Nome do produto
	*/
}

string Produto::getMedida() const {
	return medida;
	/**
	*	@return Retorna a medida do produto
	*
	*/
}

void Produto::setMedida(string medida) {
	this->medida = medida;
	/**
	*	@brief Define a medida do produto
	*
	* @param medida Medida do produto
	*/
}

bool Produto::operator== (Produto &produto) {
	return (nome == produto.getNome());
	/** @brief Compara a igualdade de dois produtos
	*
			*	@param &produto Produto
	*
	*	@return Retorna verdadeiro se os dois produtos comparados tiverem nomes iguais; caso contrario, retorna falso.
																												 */
}


ostream& operator<< (ostream& out, Produto* produto) {

	out << setw(15) << produto->nome << setw(15) << produto->medida << endl;
	return out;
	/** @brief Imprime no ecra os atributos da classe por overload do operator<<
			*
			*	@param out Objeto da iostream
			*	@param produto Produto
			*
			*	@return Retorna ostream
			*/
}
