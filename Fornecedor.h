/*
 * Fornecedor.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef FORNECEDOR_H_
#define FORNECEDOR_H_
#include "Data.h"

class Fornecedor {
protected:
	string nome, NIF, morada;
	Data data;
public:
	/** Declaracao das funcoes */
	Fornecedor();
	Fornecedor(string nome, string NIF, string morada, Data data) : nome(nome), NIF(NIF), morada(morada), data(data) {};
	Fornecedor(string nome, string NIF, string morada);
	string getNome() const;
	string getNIF() const;
	string getMorada() const;
	Data getData() const;
	void setNome(string nome);
	void setNIF(string NIF);
	void setMorada(string morada);
	void setData(Data data);
	virtual string getTipo() const = 0;
	friend ostream& operator<< (ostream& out, Fornecedor* fornecedor);
	bool operator== (Fornecedor &fornecedor) const;
	virtual ~Fornecedor();
};

class FornecedorIndividual : public Fornecedor {
protected:
	string tipo = "Individual";
public:
	/** Declaracao das funcoes */
	FornecedorIndividual(string nome, string NIF, string morada) : Fornecedor(nome,NIF,morada) {};
	FornecedorIndividual(string nome, string NIF, string morada, Data data) : Fornecedor(nome,NIF,morada, data) {};
	string getTipo() const;

};

class FornecedorEmpresa : public Fornecedor {
protected:
	string tipo = "Empresa";
public:
	/** Declaracao das funcoes */
	FornecedorEmpresa(string nome, string NIF, string morada) : Fornecedor(nome,NIF,morada) {};
	FornecedorEmpresa(string nome, string NIF, string morada, Data data) : Fornecedor(nome,NIF,morada, data) {};
	string getTipo() const;
};


#endif /* FORNECEDOR_H_ */
