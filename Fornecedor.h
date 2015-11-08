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
	vector<ProdFornecedor*> produtosForn;
public:
	Fornecedor();
	Fornecedor(string nome, string NIF, string morada) : nome(nome), NIF(NIF), morada(morada) {};
	string getNome() const;
	string getNIF() const;
	string getMorada() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setMorada(string morada);
	vector<ProdFornecedor*> getProdutosForn() const;
	virtual void addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco);
	virtual string getTipo() const = 0;
	void addProduto(Produto* produto, unsigned int stock);
	void remProduto(Produto* produto);
	void decStock(Produto* produto,unsigned int quantidade);
	friend ostream& operator<< (ostream& out, Fornecedor* fornecedor);
	bool operator== (Fornecedor &fornecedor) const;
	void displayProdutosForn() const;
	virtual ~Fornecedor();
};

class FornecedorIndividual : public Fornecedor {
protected:
	string tipo = "individual";
public:
	FornecedorIndividual(string nome, string NIF, string morada) : Fornecedor(nome,NIF,morada) {};
	void addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco);
	string getTipo() const;

};

class FornecedorEmpresa : public Fornecedor {
protected:
	string tipo = "empresa";
public:
	FornecedorEmpresa(string nome, string NIF, string morada) : Fornecedor(nome,NIF,morada) {};
	void addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco);
	string getTipo() const;
};

class DemasiadosPatamares{};


#endif /* FORNECEDOR_H_ */
