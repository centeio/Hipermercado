/*
 * Produto.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Produto.h"

//Produto
Produto::Produto() {
	// TODO Auto-generated constructor stub
	nome = "";

}

Produto::~Produto() {
	// TODO Auto-generated destructor stub
}

string Produto::getNome() const { return nome; }

void Produto::setNome(string nome) { this->nome = nome; }

string Produto::getMedida() const { return medida; }

void Produto::setMedida(string medida) { this->medida = medida; }

bool Produto::operator== (Produto &produto) {
	return (nome == produto.getNome());
}
