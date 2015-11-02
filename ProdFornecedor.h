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

class ProdFornecedor {
private:
	Produto* produto;
	double stock;
	vector<Patamar*> patamares;
public:
	ProdFornecedor();
	ProdFornecedor(Produto* produto, double stock) : produto(produto), stock(stock) {};
	ProdFornecedor(Produto* produto, double stock, vector<Patamar*> patamares) :
		produto(produto), stock(stock), patamares(patamares) {};
	Produto* getProduto() const;
	double getStock() const;
	vector<Patamar*> getPatamares() const;
	void setProduto(Produto* produto);
	void setStock(double stock);
	void setPatamares(vector<Patamar*> patamares);
	void addPatamar(double min, double max, double preco);
	void removePatamarIndice(int indice);
	void removePatamarInterator(vector<Patamar *>::iterator it);
	void displayPatamares() const;
	virtual ~ProdFornecedor();
};

#endif /* PRODFORNECEDOR_H_ */
