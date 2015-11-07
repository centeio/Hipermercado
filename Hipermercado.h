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
#include "Fornecedor.h"
#include "Produto.h"
#include "Encomenda.h"
#include "PedidoEncomenda.h"

using namespace std;


class Hipermercado {
public:
	static Hipermercado* getInstance() {
		if(Instance == NULL) Instance = new Hipermercado("Super");
		return Instance;
	}
	vector<Fornecedor*> getFornecedores() const;
	vector<Produto*> getProdutos() const;
	vector<Encomenda*> getEncomendas() const;
	vector<PedidoEncomenda*> getPedidos() const;
	void ordenaFornecedores() const;
	void ordenaProdutos() const;
	void ordenaPedidos() const;
	void ordenaEncomendas() const;
	void displayFornecedores() const;
	void displayProdutos() const;
	void displayPedidos() const;
	void displayEncomendas() const;
	void displayPedidosPorProcessar() const;
	void displayPedidosProcessados() const;
	void addFornecedor(Fornecedor* fornecedor);
	void eliminaFornecedor(unsigned int indice);
	void addProduto(Produto* produto);
	void eliminaProduto(unsigned int indice);
	void addPedido(PedidoEncomenda* pedido);
	void eliminaPedido(unsigned int indice);
	void addEncomenda(Encomenda* encomenda);
	void setNome(string novonome);
	void alteraQuantProdPedido(unsigned int indicepedido, unsigned int indiceproduto, unsigned int novaqt);
	void alteraNomeProdPedido(unsigned int indicepedido, unsigned int indiceproduto, string novonome);
private:
	string nome;
	vector<Fornecedor*> fornecedores;
	vector<Produto*> produtos;
	vector<PedidoEncomenda*> pedidos;
	vector<Encomenda*> encomendas;
	Hipermercado(string nome);
	static Hipermercado* Instance;
};
#endif /* HIPERMERCADO_H_ */
