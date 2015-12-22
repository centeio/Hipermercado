/*
 * LinhaEncomenda.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef LINHAENCOMENDA_H_
#define LINHAENCOMENDA_H_
#include "Produto.h"

class LinhaEncomenda {
private:
	string produto;
	unsigned int quantidade;
	float preco;
public:
	/** Declaracao das funcoes */
	LinhaEncomenda(string produto, unsigned int quantidade, float preco);
	LinhaEncomenda();
	virtual ~LinhaEncomenda();
	string getProduto() const;
	unsigned int getQuantidade() const;
	float getPreco() const;
};

#endif /* LINHAENCOMENDA_H_ */
