/*
 * LinhaEncomenda.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "LinhaEncomenda.h"

template <class T>
LinhaEncomenda<T>::LinhaEncomenda(Produto* produto, T quantidade,float preco):produto(produto),quantidade(quantidade),preco(preco){


template <class T>
LinhaEncomenda<T>::~LinhaEncomenda() {
}
