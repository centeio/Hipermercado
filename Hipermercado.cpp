/*
 * Hipermercado.cpp
 *
 *  Created on: 10/10/2015
 *      Author: Carolina
 */
#include "Hipermercado.h"

// TODO STATIC DATA


vector<Fornecedor*> Hipermercado::getFornecedores() const{return fornecedores;}


vector<Produto*> Hipermercado::getProdutos() const{return produtos;}


vector<PedidoEncomenda*> Hipermercado::getPedidos() const{return pedidos;}


vector<Encomenda*> Hipermercado::getEncomendas() const{return encomendas;}


bool of(Fornecedor* f1,Fornecedor f2){
	if(f1->getNome()<f2->getNome())
		return true;
	else
		return false;
}


void Hipermercado::ordenaFornecedores() const{}


bool op(Produto* p1,Produto* p2){
	if(p1->getNome()<p2->getNome())
		return true;
	else
		return false;
}


bool opd(PedidoEncomenda* p1,PedidoEncomenda* p2){
	if(p1->getData()<p2->getNome())
		return true;
	else
		return false;
}


void Hipermercado::ordenaProdutos() const{}


void Hipermercado::ordenaPedidos() const{}



void Hipermercado::ordenaEncomendas() const{}


void Hipermercado::addFornecedor(Fornecedor* fornecedor){
	fornecedores.push_back(fornecedor);
}


void Hipermercado::setNome(string novonome){
	nome=novonome;
}


void Hipermercado::eliminaFornecedor(unsigned int indice){
	if(indice+1>=fornecedores.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		fornecedores.erase(fornecedores.begin()+indice);
}


void Hipermercado::addProduto(Produto* produto){
	produtos.push_back(produto);
}


void Hipermercado::eliminaProduto(unsigned int indice){
	if(indice+1>=produtos.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		produtos.erase(produtos.begin()+indice);
}


void Hipermercado::eliminaPedido(unsigned int indice){
	if(indice+1>=pedidos.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		pedidos.erase(pedidos.begin()+indice);
}


void Hipermercado::addPedido(PedidoEncomenda* pedido){
	pedidos.push_back(pedido);
}


void Hipermercado::addEncomenda(Fornecedor* fornecedor,Produto* produto,T quantidade){
	Encomenda enc(fornecedor,produto,quantidade);
	encomendas.push_back(enc);
}


void Hipermercado::displayFornecedores() const{
	for(unsigned int i=0;i<fornecedores.size();i++)
		cout <<"FORNECEDOR "<< i << endl <<fornecedores.at(i)<<endl;

}


void Hipermercado::displayProdutos() const{
	for(unsigned int i=0;i<produtos.size();i++){
		cout <<"PRODUTO "<< i << endl <<produtos.at(i)<<endl;
	}
}


void Hipermercado::displayPedidos() const{
	for(unsigned int i=0;i<pedidos.size();i++)
		cout << "PEDIDO "<<i<<endl<< pedidos.at(i)<<endl;

}


void Hipermercado::displayPedidosPorProcessar() const{
	for(unsigned int i=0;i<pedidos.size();i++){
		if(!pedidos.at(i)->getFinalizado())
		cout << "PEDIDO "<<i<<endl<< pedidos.at(i)<<endl;
	}
}


void Hipermercado::displayPedidosProcessados() const{
	for(unsigned int i=0;i<pedidos.size();i++){
		if(pedidos.at(i)->getFinalizado())
		cout << "PEDIDO "<<i<<endl<< pedidos.at(i)<<endl;
	}
}


void Hipermercado::displayEncomendas() const{
	for(unsigned int i=0;i<encomendas.size();i++){
		cout << encomendas.at(i);
	}
}



