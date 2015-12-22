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

PedidoEncomenda::PedidoEncomenda(Produto* produto, unsigned int quant): data(Hipermercado::getInstance()->getDataAtual()){
	finalizado=false;
	produtos.push_back(produto);
	quantidade.push_back(quant);

}

PedidoEncomenda::PedidoEncomenda(vector<Produto*> produtos, vector<unsigned int> quantidade) :
						data(Hipermercado::getInstance()->getDataAtual()), produtos(produtos), quantidade(quantidade) {
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



void PedidoEncomenda::processamento() {
	Hipermercado* hipermercado = Hipermercado::getInstance();
	vector<Encomenda*> encomendas;
	stack<ProdutoFornecedor> prods;

	for(unsigned int i=0;i<produtos.size();i++)
	{
		unsigned int q=quantidade.at(i);

		while(q>0)
		{
			if(hipermercado->existeProduto(produtos.at(i)->getNome()) != NULL)
			{

				ProdutoFornecedor p = hipermercado->existeProduto(produtos.at(i)->getNome())->element;

				if(q>=p.getPatamar()->getMinimo()&&q<=p.getPatamar()->getMaximo())
				{

					Fornecedor* f = p.getFornecedor();
					if(q<p.getStock())
					{
						hipermercado->existeProduto(produtos.at(i)->getNome())->element.setStock(p.getStock()-q);
						q=0;
					}
					else
					{
						if(q==p.getStock())
							q=0;
						else
							q-=p.getStock();
						hipermercado->eliminaProduto(p);
					}
					bool existe=false;
					for(unsigned int j=0;j<encomendas.size();j++)
					{
						if(encomendas.at(j)->getFornecedor()==f)
						{
							encomendas.at(j)->addLinha(p.getNome(),quantidade.at(i)-q,p.getPatamar()->getPreco());
							existe=true;
						}
					}
					if(!existe)
					{
						Encomenda* enc= new Encomenda(f,p.getNome(),quantidade.at(i)-q,p.getPatamar()->getPreco());
						encomendas.push_back(enc);
					}

				}
				else
				{
					prods.push(p);
					hipermercado->eliminaProduto(p);
				}
			}
			else
			{
				if(q!=quantidade.at(i))
					throw ProdutoParcialmenteComprado(produtos.at(i));
				else
					throw ProdutoNaoEstaAVenda(produtos.at(i));

				PedidoEncomenda* pedido = new PedidoEncomenda(produtos.at(i),q);
				hipermercado->addPedido(pedido);
				q=0;
			}

		}

		hipermercado->alteraProdutoFila(produtos.at(i),produtos.at(i)->getStock()+quantidade.at(i)-q);
	}

	for(unsigned int k=0;k<encomendas.size();k++)
	{
		hipermercado->addEncomenda(encomendas.at(k));
	}
	while(!prods.empty())
	{
		hipermercado->addProduto(prods.top());
		prods.pop();
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
