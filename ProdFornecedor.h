/*
 * ProdFornecedor.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PRODFORNECEDOR_H_
#define PRODFORNECEDOR_H_
#include "Produto.h"
#include "Patamar.h"


struct melhorPreco{
	unsigned int quantidade;
	float preco;
};

class ProdFornecedor {
protected:
	Produto* produto;
	unsigned int stock;
	vector<Patamar*> patamares;

public:
	ProdFornecedor();
	ProdFornecedor(Produto* produto, unsigned int stock) : produto(produto), stock(stock) {};
	Produto* getProduto() const;
	unsigned int getStock() const;
	vector<Patamar*> getPatamares() const;
	void setProduto(Produto* produto);
	void setStock(unsigned int stock);
	void setPatamares(vector<Patamar*> patamares);
	void addPatamar(unsigned int min, unsigned int max, unsigned int preco);
	void removePatamarIndice(int indice);
	float getPrecoStock() const;
	melhorPreco getMelhorPreco(string nome, unsigned int quantidade);
	friend ostream& operator<< (ostream& out, ProdFornecedor* prodFornecedor);
	void displayPatamares();
	~ProdFornecedor() {};
};

#endif /* PRODFORNECEDOR_H_ */
