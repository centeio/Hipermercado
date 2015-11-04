/*
 * Fornecedor.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef FORNECEDOR_H_
#define FORNECEDOR_H_
#include "ProdFornecedor.h"


class Fornecedor {
private:
	string nome, NIF, morada;
public:
	Fornecedor();
	Fornecedor(string nome, string NIF, string morada) : nome(nome), NIF(NIF), morada(morada) {};
	string getNome() const;
	string getNIF() const;
	string getMorada() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setMorada(string morada);
	virtual void addProduto(Produto* produto, string stock, vector<Patamar* > patamares) = 0;
	virtual void remProduto(Produto* produto) = 0;
	virtual void decStock(Produto* produto,unsigned int quantidade) = 0;
	friend ostream& operator<< (ostream& out, Fornecedor* fornecedor);
	virtual void displayProdutosForn() const = 0;
	virtual ~Fornecedor();
};

class FornecedorUnidade : public Fornecedor {
private:
	vector<ProdFornecedorUnidade*> produtosForn;
public:
	vector<ProdFornecedorUnidade*> getProdutosForn() const;
	void addProduto(Produto* produto, string stock, vector<Patamar* > patamares);
	void remProduto(Produto* produto);
	void decStock(Produto* produto,unsigned int quantidade);
	void displayProdutosForn() const;
};

class FornecedorEmpresa : public Fornecedor {
private:
	vector<ProdFornecedorEmpresa*> produtosForn;
public:
	vector<ProdFornecedorEmpresa*> getProdutosForn() const;
	void addProduto(Produto* produto, string stock, vector<Patamar* > patamares);
	void remProduto(Produto* produto);
	void decStock(Produto* produto,unsigned int quantidade);
	void displayProdutosForn() const;
};

ostream& operator<< (ostream& out, Fornecedor* fornecedor) {

	out << "Nome do fornecedor: " << fornecedor->nome << ". " << endl << "NIF: " << fornecedor->NIF << "."
			<< endl<< "Morada: " << fornecedor->morada << endl;
	return out;
}


#endif /* FORNECEDOR_H_ */
