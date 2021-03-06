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


class Hipermercado {
protected:
	string nome;
	vector<Fornecedor*> fornecedores;
	vector<PedidoEncomenda*> pedidos;
	vector<Encomenda*> encomendas;
	Hipermercado(string nome);
	static Hipermercado* Instance;
	unordered_set<Fornecedor*, hf, eqf> inativos;
	Data dataatual;
	BST<ProdutoFornecedor> produtos;
	struct compare{
		bool operator() (const Produto* produto1, const Produto* produto2) {
			if (produto1->getStock() == produto2->getStock()) {
				ProdutoFornecedor temp1(produto1->getNome(),"",0, NULL, NULL), temp2(produto2->getNome(),"",0, NULL, NULL);
				return (getInstance()->produtos.find(temp1).getPatamar()->getPreco() >
					getInstance()->produtos.find(temp2).getPatamar()->getPreco());
			}
			return (produto1->getStock() > produto2->getStock());
		}
	};

	priority_queue<Produto*, vector<Produto*>, compare> alertas;

public:
	/** Declaracao das funcoes */
	static Hipermercado* getInstance() {
		if(Instance == NULL) Instance = new Hipermercado("Super");
		return Instance;
	}
	static ProdutoFornecedor ITEM_NOT_FOUND;
	vector<Fornecedor*> getFornecedores() const;
	BST<ProdutoFornecedor> getProdutos();
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
	void eliminaFornecedor(Fornecedor* fornecedor);
	void addProduto(ProdutoFornecedor produto);
	void eliminaProduto(ProdutoFornecedor produto);
	void alteraNomeProduto(string produto, string novonome);
	void alteraMedidaProduto(string produto, string novamedida);
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
	void addProdutoFila(Produto* p);
	void removeProdutoFila(Produto* p);
	void alteraProdutoFila(Produto* p, int stock);
	void manageFila();
	bool existeFila(Produto* produto);
	priority_queue<Produto*, vector<Produto*>, compare>& getPriorityQueue() {return alertas;};

	friend class PedidoEncomenda;

};
#endif /* HIPERMERCADO_H_ */

