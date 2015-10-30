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

//Produto Unidade

//Produto Medida

string ProdutoMedida::getMedida() const { return medida; }

void ProdutoMedida::setMedida(string medida) { this->medida = medida; }
