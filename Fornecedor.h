/*
 * Fornecedor.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef FORNECEDOR_H_
#define FORNECEDOR_H_
#include "ProdFornecedor.h"

template<typename T>
class Fornecedor {
private:
	string nome, NIF, morada;
	vector<ProdFornecedor<T>*> produtos;
public:
	Fornecedor();
	Fornecedor(string nome, string NIF, string morada) : nome(nome), NIF(NIF), morada(morada) {};
	string getNome() const;
	string getNIF() const;
	string getMorada() const;
	void addProduto(Produto* produto, T stock, vector<Patamar<T>* > patamares);
	void decStock(Produto* produto, T quantidade);
	virtual ~Fornecedor();
};



#endif /* FORNECEDOR_H_ */
