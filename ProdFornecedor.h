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

template<typename T>
struct melhorPreco{
	T quantidade;
	float preco;
};


template<typename T>
class ProdFornecedor {
private:
	Produto* produto;
	T stock;
	vector<Patamar<T>*> patamares;

public:
	ProdFornecedor();
	ProdFornecedor(Produto* produto, T stock) : produto(produto), stock(stock) {};
	ProdFornecedor(Produto* produto, T stock, vector<Patamar<T>*> patamares) :
		produto(produto), stock(stock), patamares(patamares) {};
	Produto* getProduto() const;
	T getStock() const;
	vector<Patamar<T>*> getPatamares() const;
	void setProduto(Produto* produto);
	void setStock(T stock);
	void setPatamares(vector<Patamar<T>*> patamares);
	void addPatamar(string min, string max, string preco);
	void removePatamarIndice(int indice);
	float getPrecoStock() const;
	melhorPreco<T> getMelhorPreco(string nome, T quantidade);
	void displayPatamares();
	~ProdFornecedor() {};
};

#endif /* PRODFORNECEDOR_H_ */
