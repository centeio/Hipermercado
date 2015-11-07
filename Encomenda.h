/*
 * Encomenda.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef ENCOMENDA_H_
#define ENCOMENDA_H_
#include <iostream>
#include <vector>
#include "Fornecedor.h"
#include "LinhaEncomenda.h"
#include "Data.h"

using namespace std;


class Encomenda {
private:
	Fornecedor* fornecedor;
	vector<LinhaEncomenda* > linhas;
	Data data;
public:
	Encomenda(Fornecedor* fornecedor,Produto* produto, int quantidade, float preco);
	Encomenda(Fornecedor* fornecedor,Produto* produto, int quantidade, float preco, Data d);
	Encomenda();
	virtual ~Encomenda();
	friend ostream &operator<<(ostream& os,const Encomenda& enc);
	void addLinha(Produto* produto, int quantidade, float preco);
	Fornecedor* getFornecedor() const;
	vector<LinhaEncomenda*> getLinhas() const;
	Data getData() const;
};

#endif /* ENCOMENDA_H_ */
