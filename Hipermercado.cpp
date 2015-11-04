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
void Hipermercado<T>::addFornecedor(Fornecedor<T>* fornecedor){
	fornecedores.push_back(fornecedor);
}

template <class T>
void Hipermercado<T>::eliminaFornecedor(unsigned int indice){
	if(indice+1>=fornecedores.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		fornecedores.erase(fornecedores.begin()+indice);
}

template <class T>
void Hipermercado<T>::addProduto(Produto* produto){
	produtos.push_back(produto);
}

template <class T>
void Hipermercado<T>::eliminaProduto(unsigned int indice){
	if(indice+1>=produtos.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		produtos.erase(produtos.begin()+indice);
}

template <class T>
void Hipermercado<T>::eliminaPedido(unsigned int indice){
	if(indice+1>=pedidos.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		pedidos.erase(pedidos.begin()+indice);
}

template <class T>
void Hipermercado<T>::addPedido(PedidoEncomenda<T>* pedido){
	pedidos.push_back(pedido);
}

template <class T>
void Hipermercado<T>::addEncomenda(Fornecedor<T>* fornecedor,Produto* produto,T quantidade){
	Encomenda<T> enc(fornecedor,produto,quantidade);
	encomendas.push_back(enc);
}

template <class T>
void Hipermercado<T>::displayFornecedores() const{
	for(unsigned int i=0;i<fornecedores.size();i++){
		cout << fornecedores.at(i);
	}
}

template <class T>
void Hipermercado<T>::displayProdutos() const{
	for(unsigned int i=0;i<produtos.size();i++){
		cout << produtos.at(i);
	}
}

template <class T>
void Hipermercado<T>::displayPedidos() const{
	for(unsigned int i=0;i<pedidos.size();i++){
		cout << "PEDIDO "<<i<<endl;
		cout << pedidos.at(i)<<endl;
	}
}

template <class T>
void Hipermercado<T>::displayPedidosPorProcessar() const{
	for(unsigned int i=0;i<pedidos.size();i++){
		if(!pedidos.at(i)->getFinalizado())
		cout << pedidos.at(i);
	}
}

template <class T>
void Hipermercado<T>::displayPedidosProcessados() const{
	for(unsigned int i=0;i<pedidos.size();i++){
		if(pedidos.at(i)->getFinalizado())
		cout << pedidos.at(i);
	}
}

template <class T>
void Hipermercado<T>::displayEncomendas() const{
	for(unsigned int i=0;i<encomendas.size();i++){
		cout << encomendas.at(i);
	}
}



