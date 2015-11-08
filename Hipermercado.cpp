/*
 * Hipermercado.cpp
 *
 *  Created on: 10/10/2015
 *      Author: Carolina
 */
#include "Hipermercado.h"
#include <algorithm>

Hipermercado* Hipermercado::Instance = NULL;

Hipermercado::Hipermercado(string nome): nome(nome){}

vector<Fornecedor*> Hipermercado::getFornecedores() const{return fornecedores;}


vector<Produto*> Hipermercado::getProdutos() const{return produtos;}


vector<PedidoEncomenda*> Hipermercado::getPedidos() const{return pedidos;}


vector<Encomenda*> Hipermercado::getEncomendas() const{return encomendas;}

void Hipermercado::alteraQuantProdPedido(unsigned int indicepedido, unsigned int indiceproduto, unsigned int novaqt){
	pedidos.at(indicepedido)->setQuantProduto(indiceproduto,novaqt);
}


void Hipermercado::alteraNomeProdPedido(unsigned int indicepedido, unsigned int indiceproduto, string novonome){
	if(indicepedido+1>=pedidos.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		if(indiceproduto+1>=pedidos.at(indiceproduto)->getProdutos().size())
			cout<<"Nao existe esse produto nesse pedido."<<endl;
		else
			pedidos.at(indicepedido)->setProduto(indiceproduto,novonome);
}

bool of(Fornecedor* f1,Fornecedor* f2){
	if(f1->getNome() < f2->getNome())
		return true;
	else
		return false;
}


void Hipermercado::ordenaFornecedores(){
	sort(fornecedores.begin(),fornecedores.end(),of);
}


bool op(Produto* p1,Produto* p2){
	if(p1->getNome() < p2->getNome())
		return true;
	else
		return false;
}


void Hipermercado::ordenaProdutos(){
	sort(produtos.begin(),produtos.end(),op);
}


bool opd(PedidoEncomenda* p1,PedidoEncomenda* p2){
	if(p1->getData() < p2->getData())
		return true;
	else
		return false;
}

void Hipermercado::ordenaPedidos(){
	sort(pedidos.begin(),pedidos.end(),opd);
}

bool oe(Encomenda* e1, Encomenda* e2){
	if(e1->getData() < e2->getData())
		return true;
	else
		return false;
}

void Hipermercado::ordenaEncomendas(){
	sort(encomendas.begin(),encomendas.end(),oe);
}


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


void Hipermercado::addEncomenda(Encomenda* encomenda){
	encomendas.push_back(encomenda);
}


void Hipermercado::displayFornecedores() const{
	for(unsigned int i=0;i<fornecedores.size();i++)
		cout <<"Fornecedores " << endl << i+1 << " - " <<fornecedores.at(i)<<endl;

}


void Hipermercado::displayProdutos() const{
	for(unsigned int i=0;i<produtos.size();i++){
		cout <<"Produtos: " << endl << i+1 << " - " << produtos.at(i)<<endl;
	}
}


void Hipermercado::displayPedidos() const{
	for(unsigned int i=0;i<pedidos.size();i++)
		cout << "Pedidos: " << endl << i+1 << " - " << pedidos.at(i)<<endl;

}


void Hipermercado::displayPedidosPorProcessar() const{

	for(unsigned int i=0;i<pedidos.size();i++){
		if(!pedidos.at(i)->getFinalizado())
		cout << "Pedidos: "<< endl << i+1 << " - " << pedidos.at(i) << endl;
	}
}


void Hipermercado::displayPedidosProcessados() const{

	for(unsigned int i=0;i<pedidos.size();i++){
		if(pedidos.at(i)->getFinalizado())
			cout << "Pedidos: "<< endl << i+1 << " - " << pedidos.at(i) << endl;
	}
}


void Hipermercado::displayEncomendas() const{

	for(unsigned int i=0;i<encomendas.size();i++){
		cout << "Encomendas: " << endl << i+1 << " - " << encomendas.at(i) << endl;
	}
}



