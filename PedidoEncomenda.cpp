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
	/**
		 *	@brief Construtor do Pedido de Encomenda
		 *
		 *	@param produtos Produtos do pedido de encomenda
		 *	@param quantidade Quantidade da encomenda
		 */
}


Data PedidoEncomenda::getData() const{
	return data;
	/**
	*	@return Retorna a data
	*/
}


bool PedidoEncomenda::getFinalizado() const{
	return finalizado;
	/**
	*	@return Retorna Verdadeiro se o pedido de encomenda estiver finalizado, caso contrario retorna falso
	*/
}


vector<Produto*> PedidoEncomenda::getProdutos() const{
	return produtos;
	/**
	*	@return Retorna os produtos do pedido de encomenda
	*/
}


vector<unsigned int> PedidoEncomenda::getQuantidade() const{
	return quantidade;
	/**
	*	@return Retorna as quantidades do produtos do pedido de encomenda
	*/
}

void PedidoEncomenda::setFinalizado(bool finalizado) {
	this->finalizado = finalizado;
	/**
	*	@brief Define o se o pedido de encomenda esta finalizado ou nao
	*
	* @param finalizado Finalizado
	*/
}


void PedidoEncomenda::setQuantProduto(unsigned int indiceProduto, unsigned int novaqt){
	if(indiceProduto<produtos.size())
		quantidade.at(indiceProduto)=novaqt;
	/**
		*	@brief Define a quantidade do produto do pedido de encomenda
		*
		* @param indiceProduto Indice do Produto
		* @param novaqt Nova quantidade
		*/
}


void PedidoEncomenda::setProduto(unsigned int indice, string novonome){
	if(indice<produtos.size())
		produtos.at(indice)->setNome(novonome);
	/**
		*	@brief Define o novo nome do produto do pedido de encomenda
		*
		* @param indice Indice do Produto
		* @param novonome Novo nome
		*/
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
	/**
			*	@brief Acrescenta um pedido de encomenda
			*
			* @param produto Produto a acrescentar
			* @param qt Quantidade
			*/
}
}



void PedidoEncomenda::processamento() {
	unsigned int i, j, k, q, qt;

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
	/**
				*	@brief Processa o pedido de encomenda
				*/
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
	/**
				*	@brief Elimina um produto de um pedido de encomenda
				*
				* @param produto Produto a eliminar
				*/
}

ostream &operator<<(ostream& os,PedidoEncomenda* p){

	os << "Data " << p->getData() << "\n \n";
	if(p->getFinalizado()) os << "Finalizado" << endl;
	os << "Produto: " << setw(15) << "Quantidade:" << endl;
	for (unsigned int i=0; i<p->getProdutos().size();i++){
		os << p->getProdutos().at(i)->getNome() << setw(15) << p->getQuantidade().at(i) << endl;
	}
	return os;
	/** @brief Imprime no ecra os atributos da classe por overload do operator<<
				*
				*	@param os Objeto da iostream
				*	@param p Pedido de Encomenda
				*
				*	@return Retorna ostream
				*/
}


PedidoEncomenda::~PedidoEncomenda() {
	/** @brief Destrutor do Pedido de Encomenda
	*/
}
