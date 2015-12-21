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
	Patamar* patamar;
public:
	ProdutoFornecedor(string nome, string medida,float stock, Fornecedor* fornecedor, Patamar* patamar) : Produto(nome, medida, stock), fornecedor(fornecedor), patamar(patamar){};
	Fornecedor* getFornecedor() const;
	void setFornecedor(Fornecedor* fornecedor);
	Patamar* getPatamar() const;
	void addPatamar();
	bool operator < (ProdutoFornecedor produto) const;
	friend ostream& operator<< (ostream& out, ProdutoFornecedor produto);
};

#endif /* PRODUTO_H_ */
