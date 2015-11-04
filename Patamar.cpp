/*
 * Patamar.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Patamar.h"
#include <iostream>
#include <iomanip>
using namespace std;


Patamar::Patamar() {
	// TODO Auto-generated constructor stub
	min = 0;
	max = 0;
	preco = 0;

}


Patamar::~Patamar() {
	// TODO Auto-generated destructor stub
}


int Patamar::getMinimo() const { return min; }


int Patamar::getMaximo() const { return max; }


float Patamar::getPreco() const { return preco; }


void Patamar::setMinimo(int minimo) { this->min = minimo; }


void Patamar::setMaximo(int maximo) { this->max = maximo;}


void Patamar::setPreco(float preco) { this->preco = preco; }




