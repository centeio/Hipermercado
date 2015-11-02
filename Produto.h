/*
 * Produto.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PRODUTO_H_
#define PRODUTO_H_
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


class Produto {
private:
	string nome;
public:
	Produto();
	Produto(string nome) : nome(nome) {};
	string getNome() const;
	void setNome(string nome);
	virtual ~Produto();
};

#endif /* PRODUTO_H_ */

class ProdutoUnidade: public Produto {
public:
	ProdutoUnidade();
	ProdutoUnidade(string nome) : Produto(nome) {};

};

class ProdutoMedida: public Produto {
private:
	string medida;
public:
	ProdutoMedida();
	ProdutoMedida(string nome, string medida) : Produto(nome) , medida(medida) {};
	string getMedida() const;
	void setMedida(string medida);
};
