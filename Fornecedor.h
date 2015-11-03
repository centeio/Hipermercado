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
	vector<ProdFornecedor<T>*> getProdutosForn() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setMorada(string morada);
	void addProduto(Produto* produto, string stock, vector<Patamar<T>* > patamares);
	void remProduto(Produto* produto);
	void decStock(Produto* produto, T quantidade);
	friend ostream& operator<< <>(ostream& out, Fornecedor<T>* fornecedor);
	void displayProdutosForn() const;
	virtual ~Fornecedor();
};


#endif /* FORNECEDOR_H_ */
