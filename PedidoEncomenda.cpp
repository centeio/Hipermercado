/*
 * PedidoEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "PedidoEncomenda.h"
#include "Hipermercado.h"


/**
	 *	@brief Construtor do Pedido de Encomenda
	 *
	 *	@param produtos Produtos do pedido de encomenda
	 *	@param quantidade Quantidade da encomenda
	 */
PedidoEncomenda::PedidoEncomenda(Data data, vector<string> produtos, vector<unsigned int> quantidade) :
data(data), produtos(produtos), quantidade(quantidade) {
	finalizado = false;
}

/**
	 *	@brief Construtor do Pedido de Encomenda
	 *
	 *	@param produtos Produtos do pedido de encomenda
	 *	@param quantidade Quantidade da encomenda
	 */
PedidoEncomenda::PedidoEncomenda(string produto, unsigned int quant): data(Hipermercado::getInstance()->getDataAtual()){
	finalizado=false;
	produtos.push_back(produto);
	quantidade.push_back(quant);

}

/**
	 *	@brief Construtor do Pedido de Encomenda
	 *
	 *	@param produtos Produtos do pedido de encomenda
	 *	@param quantidade Quantidade da encomenda
	 */
PedidoEncomenda::PedidoEncomenda(vector<string> produtos, vector<unsigned int> quantidade) :
						data(Hipermercado::getInstance()->getDataAtual()), produtos(produtos), quantidade(quantidade) {
	finalizado = false;
}

/**
	 *	@return Retorna a data
	 */
Data PedidoEncomenda::getData() const{
	return data;
}


/**
	 *	@return Retorna Verdadeiro se o pedido de encomenda estiver finalizado, caso contrario retorna falso
	 */
bool PedidoEncomenda::getFinalizado() const{
	return finalizado;
}

/**
	 *	@return Retorna os produtos do pedido de encomenda
	 */
vector<string> PedidoEncomenda::getProdutos() const{
	return produtos;

}

/**
	 *	@return Retorna as quantidades do produtos do pedido de encomenda
	 */
vector<unsigned int> PedidoEncomenda::getQuantidade() const{
	return quantidade;
}

/**
	 *	@brief Define o se o pedido de encomenda esta finalizado ou nao
	 *
	 * @param finalizado Finalizado
	 */
void PedidoEncomenda::setFinalizado(bool finalizado) {
	this->finalizado = finalizado;
}

/**
	 *	@brief Define a quantidade do produto do pedido de encomenda
	 *
	 * @param indiceProduto Indice do Produto
	 * @param novaqt Nova quantidade
	 */
void PedidoEncomenda::setQuantProduto(unsigned int indiceProduto, unsigned int novaqt){
	if(indiceProduto<produtos.size())
		quantidade.at(indiceProduto)=novaqt;
}

/**
	 *	@brief Define o novo nome do produto do pedido de encomenda
	 *
	 * @param indice Indice do Produto
	 * @param novonome Novo nome
	 */
void PedidoEncomenda::setProduto(unsigned int indice, string novonome){
	if(indice<produtos.size())
		produtos.at(indice)=novonome;
}

/**
	 *	@brief Acrescenta um pedido de encomenda
	 *
	 * @param produto Produto a acrescentar
	 * @param qt Quantidade
	 */
void PedidoEncomenda::acrescenta(string produto, unsigned int qt) {
	unsigned int i, j;
	for (i = 0; i < produtos.size(); i++) {
		if (produto == produtos.at(i))
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



/**
	 *	@return Retorna Verdadeiro se nome do produto 1 for diferente do nome do produto 2
	 *
	 *	@param produto1 Produto1
	 *	@param produto2 Produto2
	 */
bool operator!=(const ProdutoFornecedor produto1, const ProdutoFornecedor produto2) {
	return produto1.getNome() != produto2.getNome();
}

/**
	 *	@brief Processa o pedido de encomenda
	 */
void PedidoEncomenda::processamento() {
	Hipermercado* hipermercado = Hipermercado::getInstance();
	vector<Encomenda*> encomendas;
	stack<ProdutoFornecedor> prods;

	for(unsigned int i=0;i<produtos.size();i++)
	{
		unsigned int q=quantidade.at(i);

		while(q>0)
		{
			ProdutoFornecedor temp(produtos.at(i),"",0,NULL,NULL);
			if(hipermercado->getProdutos().find(temp) != Hipermercado::ITEM_NOT_FOUND)
			{
				ProdutoFornecedor p = hipermercado->getProdutos().find(temp);

				if(q>=p.getPatamar()->getMinimo()&&q<=p.getPatamar()->getMaximo())
				{

					Fornecedor* f = p.getFornecedor();
					if(q<p.getStock())
					{
						hipermercado->produtos.remove(p);
						p.setStock(p.getStock()-q);
						hipermercado->produtos.insert(p);
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

//TODO		hipermercado->alteraProdutoFila(produtos.at(i),produtos.at(i)->getStock()+quantidade.at(i)-q);
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
}

/**
	 *	@brief Elimina um produto de um pedido de encomenda
	 *
	 * @param produto Produto a eliminar
	 */
void PedidoEncomenda::eliminaProduto(string produto) {
	unsigned int i, j;
	for (i = 0; i < produtos.size(); i++) {
		if (produto == produtos.at(i))
			j = i;
	}
	if (j >= produtos.size())
		throw ProdutoNaoExiste(produto);
	else {
		produtos.erase(produtos.begin() + j);
		quantidade.erase(quantidade.begin() + j);
	}
}

/** @brief Imprime no ecra os atributos da classe por overload do operator<<
	 *
	 *	@param os Objeto da iostream
	 *	@param p Pedido de Encomenda
	 *
	 *	@return Retorna ostream
	 */
ostream &operator<<(ostream& os,PedidoEncomenda* p){

	os << "Data " << p->getData() << "\n \n";
	if(p->getFinalizado()) os << "Finalizado" << endl;
	os << "Produto: " << setw(15) << "Quantidade:" << endl;
	for (unsigned int i=0; i<p->getProdutos().size();i++){
		os << p->getProdutos().at(i) << setw(15) << p->getQuantidade().at(i) << endl;
	}
	return os;
}

/** @brief Destrutor do Pedido de Encomenda
	 */
PedidoEncomenda::~PedidoEncomenda() {

}
