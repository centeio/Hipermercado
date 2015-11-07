/*
 * LinhaEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "LinhaEncomenda.h"


LinhaEncomenda::LinhaEncomenda(Produto* produto, unsigned int quantidade,float preco):produto(produto),quantidade(quantidade),preco(preco){
}

LinhaEncomenda::~LinhaEncomenda() {}

Produto* LinhaEncomenda::getProduto() const { return produto; }

unsigned int LinhaEncomenda::getQuantidade() const {return quantidade; }

float LinhaEncomenda::getPreco() const { return preco; }
