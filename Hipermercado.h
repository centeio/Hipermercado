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
	};
	vector<Fornecedor<T>*> getFornecedores() const;
	vector<Produto*> getProdutos() const;
	vector<PedidoEncomenda<T>*> getPedidos() const;
	vector<Encomenda<T>*> getEncomendas() const;
private:
	string nome;
	vector<Fornecedor<T>*> fornecedores;
	vector<Produto*> produtos;
	vector<PedidoEncomenda<T>*> pedidos;
	vector<Encomenda<T>*> encomendas;
	static Hipermercado<T>* Instance = NULL;
	void addEncomenda(Fornecedor<T>* fornecedor,Produto<T>* produto,T quantidade);
};
#endif /* HIPERMERCADO_H_ */
