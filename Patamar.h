/*
 * Patamar.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PATAMAR_H_
#define PATAMAR_H_

class Patamar {
private:
	double min, max, preco;
public:
	Patamar();
	Patamar(double min, double max, double preco) : min(min), max(max), preco(preco) {};
	double getMinimo() const;
	double getMaximo() const;
	double getPreco() const;
	void setMinimo(double minimo);
	void setMaximo(double maximo);
	void setPreco(double preco);
	virtual ~Patamar();
};

#endif /* PATAMAR_H_ */
