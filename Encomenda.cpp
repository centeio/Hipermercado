/*
 * Encomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Encomenda.h"


Encomenda::Encomenda(Fornecedor* fornecedor,Produto* produto,int quantidade, float preco): fornecedor(fornecedor) {
	linhas.push_back(new LinhaEncomenda (produto,quantidade,preco));
	//data=dataactual;
	/**
	 *	@brief Adiciona encomenda com a data actual
	 *
	 * @param fornecedor Fornecedor
	 * @param quantidade Quantidade
	 * @param preco Preco
	 */
}

Encomenda::Encomenda(Fornecedor* fornecedor,Produto* produto,int quantidade, float preco, Data d):fornecedor(fornecedor),data(d){
	linhas.push_back(new LinhaEncomenda (produto,quantidade,preco));
	/**
		 *	@brief Adiciona encomenda com a data do argumento da funcao
		 *
		 * @param fornecedor Fornecedor
		 * @param quantidade Quantidade
		 * @param preco Preco
		 * @param d Data
		 */
}

Encomenda::Encomenda(Fornecedor* fornecedor, vector<LinhaEncomenda*> linhas, Data d):fornecedor(fornecedor),data(d), linhas(linhas){

}

Encomenda::~Encomenda() {
	// TODO Auto-generated destructor stub
	/**
			*	@brief Destroi a encomenda
			*
			*/
}

Fornecedor* Encomenda::getFornecedor() const{
	return fornecedor;
	/**
	*	@return Retorna o fornecedor da encomenda
	*/
}


vector<LinhaEncomenda*> Encomenda::getLinhas() const{
	return linhas;
	/**
	*	@return Retorna as linhas da encomenda
	*/
}

Data Encomenda::getData() const{
	return data;
	/**
	*	@return Retorna a data
	*/
}

void Encomenda::addLinha(Produto* produto,int quantidade,float preco){
	LinhaEncomenda l(produto,quantidade,preco);
	linhas.push_back(&l);
	/**
		*	@brief Adiciona linha de encomenda
		*
		*	@param produto Produto
		*	@param quantidade Quantidade
		*	@param preco Preco
		*/
}


ostream &operator<<(ostream& os, Encomenda* enc){

	os << "Fornecedor: " << enc->getFornecedor() << "\n \n";

	for (unsigned int i=0; i<enc->getLinhas().size();i++){
		os << "Produto: " << enc->linhas.at(i)->getProduto() << setw(30)
		<< "Quantidade: " << enc->linhas.at(i)->getQuantidade() << setw(46)
		<< "Preco: " << enc->linhas.at(i)->getPreco()<<endl;
	}
	return os;
	/** @brief Imprime no ecra os atributos da classe por overload do operator<<
	 *
	 *	@param os Objeto da iostream
	 *	@param enc Encomenda
	 *
	 *	@return Retorna ostream
	 */
}
