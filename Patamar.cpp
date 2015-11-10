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
	/**
			*	@brief Constroi patamar
			*
			*/

}


Patamar::~Patamar() {
	// TODO Auto-generated destructor stub
	/**
			*	@brief Destroi patamar
			*
			*/
}


unsigned int Patamar::getMinimo() const {
	return min;
	/**
	*	@return Retorna o minimo do patamar
	*/
}


unsigned int Patamar::getMaximo() const {
	return max;
	/**
	*	@return Retorna o maximo do patamar
	*/
}


float Patamar::getPreco() const {
	return preco;
	/**
	*	@return Retorna o preco do patamar
	*/
}


void Patamar::setMinimo(unsigned int minimo) {
	this->min = minimo;
	/**
	*	@brief Define o minimo do patamar
	*
	*   @param minimo Minimo
	*/
}


void Patamar::setMaximo(unsigned int maximo) {
	this->max = maximo;
	/**
	*	@brief Define o maximo do patamar
	*
	*	@param maximo Maximo
	*/
}


void Patamar::setPreco(float preco) {
	this->preco = preco;
	/**
	*	@brief Define o preco do Patamar
	*
	* @param Preco Preco
	*/
}

ostream& operator<<(ostream& out, Patamar* patamar) {

	out << "[" << setw(4) << patamar->min << "," << setw(4) << patamar->max << "] Preco: "
	<< patamar->preco << "€ cada";
	return out;
	/** @brief Imprime no ecra os atributos da classe por overload do operator<<
					*
					*	@param Out Objeto da iostream
					*	@param Patamar Patamar
					*
					*	@return Retorna ostream
					*/
}


