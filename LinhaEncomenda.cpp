/*
 * LinhaEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "LinhaEncomenda.h"

/**
 *	@brief Cria a linha de encomenda
 *
 */
LinhaEncomenda::LinhaEncomenda(string produto, unsigned int quantidade,
		float preco) :
		produto(produto), quantidade(quantidade), preco(preco) {
	/**
	 *	@brief Constroi a linha de encomenda
	 *
	 *	@param produto Produto da linha de encomenda
	 *	@param quantidade Quantidade da linha de encomenda
	 *	@param preco Preco da linha de encomenda
	 */
}

/**
 *	@brief Elimina a linha de encomenda
 *
 */
LinhaEncomenda::~LinhaEncomenda() {
	/**
	 *	@brief Destroi a linha de encomenda
	 *
	 */
}

/**
 *	@return Retorna o produto da linha de encomenda
 */
string LinhaEncomenda::getProduto() const {
	return produto;
}

/**
 *	@return Retorna a quantidade da linha de encomenda
 */
unsigned int LinhaEncomenda::getQuantidade() const {
	return quantidade;
}

/**
 *	@return Retorna o preco
 */
float LinhaEncomenda::getPreco() const {
	return preco;

}
