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

template<typename T>
Patamar<T>::Patamar() {
	// TODO Auto-generated constructor stub
	min = 0;
	max = 0;
	preco = 0;

}

template<typename T>
Patamar<T>::~Patamar() {
	// TODO Auto-generated destructor stub
}

template<typename T>
T Patamar<T>::getMinimo() const { return min; }

template<typename T>
T Patamar<T>::getMaximo() const { return max; }

template<typename T>
float Patamar<T>::getPreco() const { return preco; }

template<typename T>
void Patamar<T>::setMinimo(T minimo) { this->min = minimo; }

template<typename T>
void Patamar<T>::setMaximo(T maximo) { this->max = maximo;}

template<typename T>
void Patamar<T>::setPreco(float preco) { this->preco = preco; }

template class Patamar<double>;
template class Patamar<int>;
