/*
 * PedidoEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "PedidoEncomenda.h"
#include "ProdFornecedor.h"
#include "Hipermercado.h"
#include <climits>



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
		actualizaData();
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
			for (j = 0; j < Hipermercado::getInstance().getFornecedores().size(); j++) {

				for (k = 0;k< Hipermercado::getInstance().getFornecedores.at(j).getProdutoForn().size();k++) {
					if (Hipermercado::getInstance().getFornecedores.at(j).getProdutoForn().at(k).getNome() == produtos.getNome()){
						melhorPreco<T> = getMelhorPreco(produtos.at(i)->getNome(),q);
					if (melhorp > melhorPreco.preco) {
						melhorp = melhorPreco.preco;
						fornecedor = j;
						qt = melhorPreco.quantidade;
					}}
				}
			}


			if(j>=Hipermercado::getInstance().getFornecedores().size()){
				if(q==quantidade.at(i))
					throw ProdutoNaoEstaAVenda(produtos.at(i));
				else
					throw ProdutoParcialmenteComprado(produtos.at(i));
				q=0;
			}
			else{
				bool existe=false;
				for(unsigned int enc=0;enc<Hipermercado::getInstance().getEncomendas().size();enc++){
					if(Hipermercado::getInstance().getEncomendas().at(enc).getFornecedor()==fornecedor)
						if(Hipermercado::getInstance().getEncomendas().at(enc).getData()==data){
							Hipermercado::getInstance().getEncomendas()->addLinha(produtos.at(i),qt,melhorp);
							existe=true;
						}
				}
				if(!existe)
					Hipermercado::getInstance().addEncomenda(Hipermercado::getInstance().getFornecedores().at(j),produtos.at(i),qt,melhorp);
				Hipermercado::getInstance().getFornecedores().at(j)->decStock(produtos.at(i),quantidade.at(i));
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
PedidoEncomenda<T>::~PedidoEncomenda() {
// TODO Auto-generated destructor stub
}

