/*
 * Patamar.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Patamar.h"

Patamar::Patamar() {
	// TODO Auto-generated constructor stub
	min = 0;
	max = 0;
	preco = 0;

}

Patamar::~Patamar() {
	// TODO Auto-generated destructor stub
}

double Patamar::getMinimo() const { return min; }

double Patamar::getMaximo() const { return max; }

double Patamar::getPreco() const { return preco; }

void Patamar::setMinimo(double minimo) { this->min = minimo; }

void Patamar::setMaximo(double maximo) { this->max = maximo;}

void Patamar::setPreco(double preco) { this->preco = preco; }
