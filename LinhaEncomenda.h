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
	Produto* produto;
	T quantidade;
	float preco;
public:
	LinhaEncomenda(Produto* produto, int quantidade, float preco);
	LinhaEncomenda();
	virtual ~LinhaEncomenda();
	Produto* getProduto() const;
	unsigned int getQuantidade() const;
	float getPreco() const;
};

#endif /* LINHAENCOMENDA_H_ */
