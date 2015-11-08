/*
 * PedidoEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "PedidoEncomenda.h"
#include "Hipermercado.h"


PedidoEncomenda::PedidoEncomenda(Data data, vector<Produto*> produtos, vector<unsigned int> quantidade) :
		data(data), produtos(produtos), quantidade(quantidade) {
	finalizado = false;
}


Data PedidoEncomenda::getData() const{return data;}


bool PedidoEncomenda::getFinalizado() const{return finalizado;}


vector<Produto*> PedidoEncomenda::getProdutos() const{return produtos;}


vector<unsigned int> PedidoEncomenda::getQuantidade() const{return quantidade;}


void PedidoEncomenda::setQuantProduto(unsigned int indiceProduto, unsigned int novaqt){
	if(indiceProduto<produtos.size())
		quantidade.at(indiceProduto)=novaqt;
}


void PedidoEncomenda::setProduto(unsigned int indice, string novonome){
	if(indice<produtos.size())
		produtos.at(indice)->setNome(novonome);
}


void PedidoEncomenda::acrescenta(Produto* produto, unsigned int qt) {
	unsigned int i, j;
	for (i = 0; i < produtos.size(); i++) {
		if (produto->getNome() == produtos.at(i)->getNome())
			j = i;
	}

	if (j >= produtos.size())
		quantidade.at(j) += qt;
	else {
		produtos.push_back(produto);
		quantidade.push_back(qt);
	//	actualizaData();
	}
}



void PedidoEncomenda::processamento() {
	unsigned int i, j, k;
	int q,qt;
	for (i = 0; i < produtos.size(); i++) {
		q=quantidade.at(i);
		while (q > 0) {
			int melhorp = INT_MAX, fornecedor;
			for (j = 0; j < Hipermercado::getInstance()->getFornecedores().size(); j++) {

				for (k = 0;k< Hipermercado::getInstance()->getFornecedores().at(j)->getProdutosForn().size();k++) {
					if (Hipermercado::getInstance()->getFornecedores().at(j)->getProdutosForn().at(k)->getProduto()->getNome() == produtos.at(i)->getNome()){
						melhorPreco melhorpreco = Hipermercado::getInstance()->getFornecedores().at(j)->getProdutosForn().at(k)->getMelhorPreco(produtos.at(i)->getNome(),q);
					if (melhorp > melhorpreco.preco) {
						melhorp = melhorpreco.preco;
						fornecedor = j;
						qt = melhorpreco.quantidade;
					}}
				}
			}


			if(j>=Hipermercado::getInstance()->getFornecedores().size()){
				if(q==quantidade.at(i))
					throw ProdutoNaoEstaAVenda(produtos.at(i));
				else
					throw ProdutoParcialmenteComprado(produtos.at(i));
				q=0;

			}
			else{
				bool existe=false;
				for(unsigned int enc=0;enc<Hipermercado::getInstance()->getEncomendas().size();enc++){
					if(Hipermercado::getInstance()->getEncomendas().at(enc)->getFornecedor()==Hipermercado::getInstance()->getFornecedores().at(fornecedor))
						if(Hipermercado::getInstance()->getEncomendas().at(enc)->getData()==data){
							Hipermercado::getInstance()->getEncomendas().at(enc)->addLinha(produtos.at(i),qt,melhorp);
							existe=true;
						}
				}
				if(!existe)
					Hipermercado::getInstance()->addEncomenda(new Encomenda(Hipermercado::getInstance()->getFornecedores().at(j),produtos.at(i),qt,melhorp));
				Hipermercado::getInstance()->getFornecedores().at(j)->decStock(produtos.at(i),quantidade.at(i));
			}


			}
		}
	finalizado=true;
}



void PedidoEncomenda::eliminaProduto(Produto* produto) {
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


ostream &operator<<(ostream& os,const PedidoEncomenda& p){
	os<<"Data "<<p.getData()<<"\n \n";
	if(p.getFinalizado())
		os<<"Finalizado"<<endl;
	os<<"Produto: "<<setw(15)<<"Quantidade:"<<endl;
	for (unsigned int i=0; i<p.getProdutos().size();i++){
		os<<p.getProdutos().at(i)<<setw(15)<<p.getQuantidade().at(i)<<endl;
	}
	return os;
}


PedidoEncomenda::~PedidoEncomenda() {}
