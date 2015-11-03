/*
 * Hipermercado.cpp
 *
 *  Created on: 10/10/2015
 *      Author: Carolina
 */
#include "Hipermercado.h"

// TODO STATIC DATA

template <class T>
vector<Fornecedor<T>*> Hipermercado<T>::getFornecedores() const{return fornecedores;}

template <class T>
vector<Produto*> Hipermercado<T>::getProdutos() const{return produtos;}

template <class T>
vector<PedidoEncomenda<T>*> Hipermercado<T>::getPedidos() const{return pedidos;}

template <class T>
vector<Encomenda<T>*> Hipermercado<T>::getEncomendas() const{return encomendas;}

template <class T>
void Hipermercado<T>::addEncomenda(Fornecedor<T>* fornecedor,Produto* produto,T quantidade){
	Encomenda<T> enc(fornecedor,produto,quantidade);
	encomendas.push_back(enc);
}



