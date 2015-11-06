/*
 * Produto.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PRODUTO_H_
#define PRODUTO_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Produto {
protected:
	string nome;
	string medida;
public:
	Produto();
	Produto(string nome, string medida) : nome(nome), medida(medida) {};
	string getNome() const;
	void setNome(string nome);
	string getMedida() const;
	void setMedida(string medida);
	bool operator==(Produto &produto);
	friend ostream& operator<< (ostream& out, Produto* produto);
	virtual ~Produto();
};

#endif /* PRODUTO_H_ */
