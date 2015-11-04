/*
 * Encomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Encomenda.h"
#include <iomanip>


Encomenda::Encomenda(Fornecedor* fornecedor,Produto* produto,int quantidade, float preco): fornecedor(fornecedor) {
	linhas.push_back(new LinhaEncomenda (produto,quantidade,preco));
	data=dataactual;
}


Encomenda::Encomenda(Fornecedor* fornecedor,Produto* produto,int quantidade, float preco, Data d):fornecedor(fornecedor),data(d){
	linhas.push_back(new LinhaEncomenda (produto,quantidade,preco));
}



Encomenda::~Encomenda() {
	// TODO Auto-generated destructor stub
}

Fornecedor* Encomenda::getFornecedor() const{return fornecedor;}


vector<LinhaEncomenda > Encomenda::getLinhas() const{return linhas;}


void Encomenda::addLinha(Produto* produto,T quantidade,float preco){
	LinhaEncomenda l(produto,quantidade,preco);
	linhas.push_back(l);
}


ostream &operator<<(ostream& os, const Encomenda& enc){
	os<<"Fornecedor: "<<enc.getFornecedor()<<"\n \n";
	for (unsigned int i=0; i<enc.getLinhas().size();i++){
		os<<"Produto: "<<enc.getLinhas().at(i).getProduto()<<setw(30)
				<<"Quantidade: "<<enc.getLinhas().at(i).getQuantidade()<<setw(46)
				<<"Preco: "<<enc.getLinhas().at(i).getPreco()<<endl;
	}
	return os;
}
