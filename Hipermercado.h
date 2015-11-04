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

template <class T>
class Hipermercado {
public:
	static Hipermercado* getInstance() {
		if(Instance == NULL) Instance = new Hipermercado("Super");
		return Instance;
	}
	vector<Fornecedor<T>*> getFornecedores() const;
	vector<Produto*> getProdutos() const;
	vector<PedidoEncomenda<T>*> getPedidos() const;
	vector<Encomenda<T>*> getEncomendas() const;
	void displayFornecedores() const;
	void displayProdutos() const;
	void displayPedidos() const;
	void displayEncomendas() const;
//	void displayEncomendasOrdenadas() const;
	void displayPedidosPorProcessar() const;
	void displayPedidosProcessados() const;
	void addFornecedor(Fornecedor<T>* fornecedor);
	void eliminaFornecedor(unsigned int indice);
	void addProduto(Produto* produto);
	void eliminaProduto(unsigned int indice);
	void addPedido(PedidoEncomenda<T>* pedido);
	void eliminaPedido(unsigned int indice);
	void addEncomenda(Fornecedor<T>* fornecedor,Produto* produto,T quantidade);
	void setNome(string novonome);
private:
	string nome;
	vector<Fornecedor<T>*> fornecedores;
	vector<Produto*> produtos;
	vector<PedidoEncomenda<T>*> pedidos;
	vector<Encomenda<T>*> encomendas;
	static Hipermercado<T>* Instance = NULL;
	void addEncomenda(Fornecedor<T>* fornecedor,Produto* produto,T quantidade);
	//setNomeHipermercad ??? CAROL?
};
#endif /* HIPERMERCADO_H_ */
