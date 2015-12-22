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
#include "BST.h"

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

/** @brief Struct compare que organiza a fila de prioridade
 *
 */

class Hipermercado {
public:
	/** Declaracao das funcoes */
	static Hipermercado* getInstance() {
		if(Instance == NULL) Instance = new Hipermercado("Super");
		return Instance;
	}

	vector<Fornecedor*> getFornecedores() const;
	BST<ProdutoFornecedor> getProdutos() const;
	vector<Encomenda*> getEncomendas() const;
	vector<PedidoEncomenda*> getPedidos() const;
	string getNome() const;
	Data getDataAtual() const;
	void setDataAtual(unsigned int dia, unsigned int mes, unsigned int ano);
	void ordenaFornecedores();
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
	void addProduto(ProdutoFornecedor produto);
	void eliminaProduto(ProdutoFornecedor produto);
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

	void displayPriorityQueue();
	//organiza na fila prioritaria
	void addProduto(Produto* p);
	void removeProduto(Produto* p);
	void alteraProduto(Produto* p, int stock);
	void manageFila();
	priority_queue<Produto*, vector<Produto*>, compare> getPriorityQueue() const;

	BinaryNode<ProdutoFornecedor> * existeProduto(string nome);

private:
	string nome;
	vector<Fornecedor*> fornecedores;
	vector<PedidoEncomenda*> pedidos;
	vector<Encomenda*> encomendas;
	Hipermercado(string nome);
	static Hipermercado* Instance;
	unordered_set<Fornecedor*, hf, eqf> inativos;
	Data dataatual;
	BST<ProdutoFornecedor> produtos;
	BinaryNode<ProdutoFornecedor> * existe(string nome, BinaryNode<ProdutoFornecedor> *t);

	struct compare{
		bool operator() (const Produto* a, const Produto* b) {
			//se o stock de dois produtos for igual o produto com maior alerta e o com menor preco
			if (a->getStock() == b->getStock()) {
				//return (melhorPreco(a)>melhorPreco(b));//preco pelo qual pode ser adquirido
				return getInstance()->existeProduto(a->getNome())->element.getPatamar()->getPreco() > getInstance()->existeProduto(b->getNome())->element.getPatamar()->getPreco();
			}
			//o maior alerta e o do produto com menor stock
			return (a->getStock() > b->getStock());
		}
	};

	priority_queue<Produto*, vector<Produto*>, compare> alertas;


};
#endif /* HIPERMERCADO_H_ */

