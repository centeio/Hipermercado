/*
 * Encomenda.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef ENCOMENDA_H_
#define ENCOMENDA_H_
#include "Fornecedor.h"
#include "LinhaEncomenda.h"
#include "Data.h"

using namespace std;




class Encomenda {
protected:
	Fornecedor* fornecedor;
	vector<LinhaEncomenda* > linhas;
	Data data;
public:
	/** Declaracao das funcoes */
	Encomenda(Fornecedor* fornecedor,string produto, int quantidade, float preco);
	Encomenda(Fornecedor* fornecedor,string produto, int quantidade, float preco, Data d);
	Encomenda(Fornecedor* fornecedor, vector<LinhaEncomenda*> linhas, Data d);
	Encomenda();
	virtual ~Encomenda();
	friend ostream &operator<<(ostream& os, Encomenda* enc);
	void addLinha(string produto, int quantidade, float preco);
	Fornecedor* getFornecedor() const;
	vector<LinhaEncomenda*> getLinhas() const;
	Data getData() const;
};

#endif /* ENCOMENDA_H_ */
