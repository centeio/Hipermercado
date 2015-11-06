/*
 * Patamar.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PATAMAR_H_
#define PATAMAR_H_

using namespace std;
#include <iomanip>


class Patamar {
protected:
	 unsigned int min, max;
	 float preco;
public:
	Patamar();
	Patamar(unsigned int min, unsigned int max, float preco) : min(min), max(max), preco(preco) {};
	unsigned int getMinimo() const;
	unsigned int getMaximo() const;
	float getPreco() const;
	void setMinimo(unsigned int minimo);
	void setMaximo(unsigned int maximo);
	void setPreco(float preco);
	friend std::ostream& operator<< (std::ostream& out, Patamar* patamar);
	virtual ~Patamar();
};

#endif /* PATAMAR_H_ */
