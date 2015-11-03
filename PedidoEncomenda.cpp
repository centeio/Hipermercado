/*
 * PedidoEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "PedidoEncomenda.h"
#include "Fornecedor.h"


template<class T>
PedidoEncomenda<T>::PedidoEncomenda(Data data, vector<Produto*> produtos,
		vector<unsigned int> quantidade) :
		data(data), produtos(produtos), quantidade(quantidade) {
	finalizado = false;
}

template<class T>
void PedidoEncomenda<T>::acrescenta(Produto* produto, T quantidade) {
	unsigned int i, j;
	for (i = 0; i < produtos.size(); i++) {
		if (produto->getNome() == produtos.at(i)->getNome())
			j = i;
	}

	if (j >= produtos.size())
		quantidade.at(j) += quantidade;
	else {
		produtos.push_back(produto);
		quantidade.push_back(quantidade);
	//	actualizaData();
	}
}


template<class T>
void PedidoEncomenda<T>::processamento() {
	unsigned int i, j, k;
	melhorPreco<T> melhorPreco;
	T q,qt;
	for (i = 0; i < produtos.size(); i++) {
		q=quantidade.at(i);
		while (q > 0) {
			int melhorp = INT_MAX, fornecedor;
			for (j = 0; j < Hipermercado<T>::getInstance().getFornecedores().size(); j++) {

				for (k = 0;k< Hipermercado<T>::getInstance().getFornecedores.at(j).getProdutoForn().size();k++) {
					if (Hipermercado<T>::getInstance().getFornecedores.at(j).getProdutoForn().at(k).getNome() == produtos.at(i)->getNome()){
						melhorPreco<T> = getMelhorPreco(produtos.at(i)->getNome(),q);
					if (melhorp > melhorPreco.preco) {
						melhorp = melhorPreco.preco;
						fornecedor = j;
						qt = melhorPreco.quantidade;
					}}
				}
			}


			if(j>=Hipermercado<T>::getInstance().getFornecedores().size()){
				if(q==quantidade.at(i))
					throw ProdutoNaoEstaAVenda(produtos.at(i));
				else
					throw ProdutoParcialmenteComprado(produtos.at(i));
				q=0;
			}
			else{
				bool existe=false;
				for(unsigned int enc=0;enc<Hipermercado<T>::getInstance().getEncomendas().size();enc++){
					if(Hipermercado<T>::getInstance().getEncomendas().at(enc).getFornecedor()==fornecedor)
						if(Hipermercado<T>::getInstance().getEncomendas().at(enc).getData()==data){
							Hipermercado<T>::getInstance().getEncomendas()->addLinha(produtos.at(i),qt,melhorp);
							existe=true;
						}
				}
				if(!existe)
					Hipermercado<T>::getInstance().addEncomenda(Hipermercado<T>::getInstance().getFornecedores().at(j),produtos.at(i),qt,melhorp);
				Hipermercado<T>::getInstance().getFornecedores().at(j)->decStock(produtos.at(i),quantidade.at(i));
			}


			}
		}
	}


template<class T>
void PedidoEncomenda<T>::eliminaProduto(Produto* produto) {
	unsigned int i, j;
	for (i = 0; i < produtos.size(); i++) {
		if (produto->getNome() == produtos.at(i)->getNome())
			j = i;
	}
	if (j >= produtos.size())
		throw ProdutoNaoExiste(produto);
	else {
		produtos.erase(produtos.begin() + j);
		quantidade.erase(quantidade.begin() + j);
	}
}

template<class T>
PedidoEncomenda<T>::~PedidoEncomenda() {}
