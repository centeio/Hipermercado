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

using namespace std;

template <class T>
class Encomenda {
private:
	Fornecedor* fornecedor;
	vector<LinhaEncomenda<T> > linhas;
	Data data;
public:
	Encomenda(Fornecedor* fornecedor,Produto* produto,T quantidade);
	Encomenda();
	virtual ~Encomenda();
	friend ostream &operator<<(ostream& os,const Encomenda<T>& enc);
	void addLinha(Produto* produto,T quantidade,float preco);
	Fornecedor* getFornecedor() const;
	vector<LinhaEncomenda<T> > getLinhas() const;

};

#endif /* ENCOMENDA_H_ */
