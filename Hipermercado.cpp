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

string Hipermercado::getNome() const{return nome;}

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
	delete(fornecedores.at(indice));
	fornecedores.erase(fornecedores.begin()+indice);
}


void Hipermercado::addProduto(Produto* produto){
	produtos.push_back(produto);
}


void Hipermercado::eliminaProduto(unsigned int indice){
	delete(produtos.at(indice));
	produtos.erase(produtos.begin()+indice);
}

void Hipermercado::alteraNomeProduto(unsigned int indice, string novonome){
	if(indice+1>=produtos.size())
		cout<<"Nao existe esse produto."<<endl;
	else
		produtos.at(indice)->setNome(novonome);
}

void Hipermercado::alteraMedidaProduto(unsigned int indice, string novamedida){
	if(indice+1>=produtos.size())
		cout<<"Nao existe esse produto."<<endl;
	else
		produtos.at(indice)->setMedida(novamedida);
}

void Hipermercado::eliminaPedido(unsigned int indice){
	delete(pedidos.at(indice));
	pedidos.erase(pedidos.begin()+indice);
}


void Hipermercado::addPedido(PedidoEncomenda* pedido){
	pedidos.push_back(pedido);
}


void Hipermercado::addEncomenda(Encomenda* encomenda){
	encomendas.push_back(encomenda);
}


void Hipermercado::displayFornecedores() const{
	if(fornecedores.size() != 0) {
		cout << "Fornecedores: " << endl;
		for (unsigned int i = 0; i < fornecedores.size(); i++)
			cout << i + 1 << " - " << fornecedores.at(i) << endl;
	}
}


void Hipermercado::displayProdutos() const{
	if(produtos.size() != 0) {
		cout << "Produtos: " << endl << setw(15)<<"Nome"<<setw(15)<<"Medida"<<endl;
		for (unsigned int i = 0; i < produtos.size(); i++) {
			cout << i + 1 << " - " << produtos.at(i) << endl;
		}
	}
}


void Hipermercado::displayPedidos() const{
	if(pedidos.size() != 0) {
		cout << "Pedidos: " << endl;
		for (unsigned int i = 0; i < pedidos.size(); i++)
			cout << i + 1 << " - " << pedidos.at(i) << endl;
	}
}

void Hipermercado::displayFornecedoresEmp() const{
	unsigned int j=1;
	cout << "Fornecedores - Empresa: " << endl ;

	for(unsigned int i=0;i<fornecedores.size();i++){
		if(fornecedores.at(i)->getTipo() == "empresa"){
			cout << j << " - "<< fornecedores.at(i) << endl;
			j++;
		}
	}
}

void Hipermercado::displayPedidosPorProcessar() const{
	cout << "Pedidos: "<< endl;
	for(unsigned int i=0;i<pedidos.size();i++){
		if(!pedidos.at(i)->getFinalizado())
			cout<< i+1 << " - " << pedidos.at(i) << endl;
	}
}


void Hipermercado::displayPedidosProcessados() const{
	cout << "Pedidos: "<<endl;
	for(unsigned int i=0;i<pedidos.size();i++){
		if(pedidos.at(i)->getFinalizado())
			cout<< endl << i+1 << " - " << pedidos.at(i) << endl;
	}
}


void Hipermercado::displayEncomendas() const{
	if(encomendas.size() != 0) {
		cout << "Encomendas: " << endl;
		for (unsigned int i = 0; i < encomendas.size(); i++) {
			cout << i + 1 << " - " << encomendas.at(i) << endl;
		}
	}
}

void Hipermercado::processaPedido() {

	for(unsigned int i = 0; i < pedidos.size(); i++) {
		if(!pedidos.at(i)->getFinalizado()) pedidos.at(i)->processamento();
	}
}
