/*
 * Encomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Encomenda.h"
#include <iomanip>

template <class T>
Encomenda<T>::Encomenda(Fornecedor<T>* fornecedor,Produto* produto,T quantidade, float preco): fornecedor(fornecedor) {
	linhas.push_back(new LinhaEncomenda<T> (produto,quantidade,preco));
	data=dataactual;
}

template <class T>
Encomenda<T>::Encomenda(Fornecedor<T>* fornecedor,Produto* produto,T quantidade, float preco, Data d):fornecedor(fornecedor),data(d){
	linhas.push_back(new LinhaEncomenda<T> (produto,quantidade,preco));
}


template <class T>
Encomenda<T>::~Encomenda() {
	// TODO Auto-generated destructor stub
}
template <class T>
Fornecedor<T>* Encomenda<T>::getFornecedor() const{return fornecedor;}

template <class T>
vector<LinhaEncomenda<T> > Encomenda<T>::getLinhas() const{return linhas;}

template <class T>
void Encomenda<T>::addLinha(Produto* produto,T quantidade,float preco){
	LinhaEncomenda<T> l(produto,quantidade,preco);
	linhas.push_back(l);
}

template <class T>
ostream &operator<<(ostream& os, const Encomenda<T>& enc){
	os<<"Fornecedor: "<<enc.getFornecedor()<<"\n \n";
	for (unsigned int i=0; i<enc.getLinhas().size();i++){
		os<<"Produto: "<<enc.getLinhas().at(i).getProduto()<<setw(30)
				<<"Quantidade: "<<enc.getLinhas().at(i).getQuantidade()<<setw(46)
				<<"Preco: "<<enc.getLinhas().at(i).getPreco()<<endl;
	}
	return os;
}
