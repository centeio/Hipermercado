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
protected:
	string nome, NIF, morada;
public:
	Fornecedor();
	virtual Fornecedor(string nome, string NIF, string morada) : nome(nome), NIF(NIF), morada(morada) {};
	string getNome() const;
	string getNIF() const;
	string getMorada() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setMorada(string morada);
	virtual vector<ProdFornecedorUnidade*> getProdutosForn() const = 0;
	virtual vector<ProdFornecedorEmpresa*> getProdutosForn() const = 0;
	virtual void addProduto(Produto* produto, string stock) = 0;
	virtual void remProduto(Produto* produto) = 0;
	virtual void decStock(Produto* produto,unsigned int quantidade) = 0;
	friend ostream& operator<< (ostream& out, Fornecedor* fornecedor);
	bool operator== (Fornecedor &fornecedor) const;
	virtual void displayProdutosForn() const = 0;
	virtual ~Fornecedor();
};

class FornecedorIndividual : public Fornecedor {
protected:
	vector<ProdFornecedorUnidade*> produtosForn;
public:
	FornecedorIndividual(string nome, string NIF, string morada) : Fornecedor(nome,NIF,morada) {};
	vector<ProdFornecedorUnidade*> getProdutosForn() const;
	void addProduto(Produto* produto, string stock);
	void remProduto(Produto* produto);
	void decStock(Produto* produto,unsigned int quantidade);
	void displayProdutosForn() const;
};

class FornecedorEmpresa : public Fornecedor {
protected:
	vector<ProdFornecedorEmpresa*> produtosForn;
public:
	FornecedorEmpresa(string nome, string NIF, string morada) : Fornecedor(nome,NIF,morada) {};
	vector<ProdFornecedorEmpresa*> getProdutosForn() const;
	void addProduto(Produto* produto, string stock);
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
