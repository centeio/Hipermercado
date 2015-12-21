/*
 * Hipermercado.h
 *
 *  Created on: 10/10/2015
 *      Author: Carolina
 */

#ifndef HIPERMERCADO_H_
#define HIPERMERCADO_H_

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "Encomenda.h"
#include "PedidoEncomenda.h"
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

struct eqf {
	bool operator() (Fornecedor* f1,  Fornecedor* f2) const
	{
		return (*f1)==(*f2);
	}
};

struct hf
{
	int operator() (const Fornecedor* f1) const
	{
		string s1=(*f1).getNome();
		int v = 0;
		for ( unsigned int i=0; i< s1.size(); i++ )
			v = 37*v + s1[i];
		return v;
	}
};


class Hipermercado {
public:
	/** Declaracao das funcoes */
	static Hipermercado* getInstance() {
		if(Instance == NULL) Instance = new Hipermercado("Super");
		return Instance;
	}

	vector<Fornecedor*> getFornecedores() const;
	vector<Produto*> getProdutos() const;
	vector<Encomenda*> getEncomendas() const;
	vector<PedidoEncomenda*> getPedidos() const;
	string getNome() const;
	Data getDataAtual() const;
	void setDataAtual(unsigned int dia, unsigned int mes, unsigned int ano);
	void ordenaFornecedores();
	void ordenaProdutos();
	void ordenaPedidos();
	void ordenaEncomendas();
	void displayFornecedores() const;
	void displayProdutos() const;
	void displayPedidos() const;
	void displayEncomendas() const;
	void displayPedidosPorProcessar() const;
	void displayPedidosProcessados() const;
	void displayProdutosFornecedor() const;
	void processaPedido();
	void addFornecedor(Fornecedor* fornecedor);
	void eliminaFornecedor(unsigned int indice);
	void addProduto(Produto* produto);
	void eliminaProduto(unsigned int indice);
	void alteraNomeProduto(unsigned int indice, string novonome);
	void alteraMedidaProduto(unsigned int indice, string novamedida);
	void addPedido(PedidoEncomenda* pedido);
	void eliminaPedido(unsigned int indice);
	void addEncomenda(Encomenda* encomenda);
	void setNome(string novonome);
	void alteraQuantProdPedido(unsigned int indicepedido, unsigned int indiceproduto, unsigned int novaqt);
	void alteraNomeProdPedido(unsigned int indicepedido, unsigned int indiceproduto, string novonome);
	void atualizaTabela();
	void removeDaTabela(Fornecedor* f);
	void displayTabela();

private:
	string nome;
	vector<Fornecedor*> fornecedores;
	vector<Produto*> produtos;
	vector<PedidoEncomenda*> pedidos;
	vector<Encomenda*> encomendas;
	Hipermercado(string nome);
	static Hipermercado* Instance;
	unordered_set<Fornecedor*, hf, eqf> inativos;
	Data dataatual;

};
#endif /* HIPERMERCADO_H_ */
