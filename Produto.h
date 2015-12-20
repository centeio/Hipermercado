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
#include "Fornecedor.h"
#include "Patamar.h"
using namespace std;


class Produto {
protected:
	string nome, medida;
	float stock;
public:
	/** Declaracao das funcoes */
	Produto();
	Produto(string nome, string medida, float stock) : nome(nome), medida(medida), stock(stock) {};
	string getNome() const;
	void setNome(string nome);
	string getMedida() const;
	void setMedida(string medida);
	float getStock() const;
	void setStock();
	bool operator==(Produto &produto);
	friend ostream& operator<< (ostream& out, Produto* produto);
	virtual ~Produto();
};

class ProdutoFornecedor : public Produto {
protected:
	Fornecedor* fornecedor;
	vector<Patamar*> patamares;
public:
	ProdutoFornecedor(string nome, string medida,float stock) : Produto(nome, medida, stock){};
	Fornecedor* getFornecedor() const;
	void setFornecedor(Fornecedor* fornecedor);
	vector<Patamar*> getPatamares() const;
	void addPatamar();

};

#endif /* PRODUTO_H_ */
