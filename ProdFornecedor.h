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
private:
	Produto* produto;
	unsigned int stock;
protected:
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
	virtual void addPatamar(string min, string max, string preco) = 0;
	void removePatamarIndice(int indice);
	float getPrecoStock() const;
	melhorPreco getMelhorPreco(string nome, unsigned int quantidade);
	friend ostream& operator<< (ostream& out, ProdFornecedor* prodFornecedor);
	void displayPatamares();
	virtual ~ProdFornecedor() {};
};

class ProdFornecedorUnidade : public ProdFornecedor {
public:
	ProdFornecedorUnidade(Produto* produto, unsigned int stock, vector<Patamar*> patamares);
	void addPatamar(string min, string max, string preco);
};

class ProdFornecedorEmpresa : public ProdFornecedor {
public:
	ProdFornecedorEmpresa(Produto* produto,unsigned int stock, vector<Patamar*> patamares) : ProdFornecedor(produto,stock), patamares(patamares) {};
	void addPatamar(string min, string max, string preco);
};

class DemasiadosPatamares {};

ostream& operator<< (ostream& out, ProdFornecedor* prodFornecedor) {

	out << prodFornecedor->produto << endl << "Stock: " << prodFornecedor->stock << endl;
	return out;
}

#endif /* PRODFORNECEDOR_H_ */
