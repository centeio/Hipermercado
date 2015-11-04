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
private:
	 int min, max;
	 float preco;
public:
	Patamar();
	Patamar(int min, int max, float preco) : min(min), max(max), preco(preco) {};
	int getMinimo() const;
	int getMaximo() const;
	float getPreco() const;
	void setMinimo(int minimo);
	void setMaximo(int maximo);
	void setPreco(float preco);
	friend std::ostream& operator<< (std::ostream& out, Patamar* patamar);
	virtual ~Patamar();
};

ostream& operator<<(ostream& out, Patamar* patamar) {

	out << "[" << setw(4) << patamar->min << "," << setw(4) << patamar->max << "] Preco: "
			<< patamar->preco << "€ cada";
	return out;
}
#endif /* PATAMAR_H_ */
