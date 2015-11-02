/*
 * Patamar.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PATAMAR_H_
#define PATAMAR_H_

template<typename T>
class Patamar {
private:
	 T min, max;
	 float preco;
public:
	Patamar();
	Patamar(T min, T max, float preco) : min(min), max(max), preco(preco) {};
	T getMinimo() const;
	T getMaximo() const;
	float getPreco() const;
	void setMinimo(T minimo);
	void setMaximo(T maximo);
	void setPreco(float preco);
	virtual ~Patamar();
};

#endif /* PATAMAR_H_ */
