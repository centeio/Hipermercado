/*
 * Alerta.h
 *
 *  Created on: 15/12/2015
 *      Author: up201404789
 */

#ifndef ALERTA_H_
#define ALERTA_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;



class Produto {
protected:
	string nome;
	string medida;
	int stock;
	int preco;
public:
	/** Declaracao das funcoes */
	Produto();
	Produto(string nome, string medida, int stock, int preco) :
			nome(nome), medida(medida), stock(stock), preco(preco) {};
	string getNome() const;
	int getStock() const;
	int getPreco() const;
	void setNome(string nome);
	string getMedida() const;
	void setStock(int stock);
//	bool operator==(Produto &produto);
//	friend ostream& operator<< (ostream& out, Produto* produto);
//	virtual ~Produto();
};

/** @brief Struct compare que organiza a fila de prioridade
 *
 */
struct compare{
	bool operator() (const Produto* a, const Produto* b) {
	//se o stock de dois produtos for igual o produto com maior alerta é o com menor preco
	if (a->getStock() == b->getStock()) {
		//return (melhorPreco(a)>melhorPreco(b));//preco pelo qual pode ser adquirido
		return a->getPreco() > b->getPreco();
	}
//
//	//o maior alerta é o do produto com menor stock
	return (a->getStock() > b->getStock());
}
};

class PriorityQueue {
	priority_queue<Produto*, vector<Produto*>, compare> alertas;
public:
	/** Declaracao das funcoes */
	PriorityQueue() {
	}
	;
	PriorityQueue(priority_queue<Produto*, vector<Produto*>, compare> alertas) :
			alertas(alertas) {
	}
	;
	priority_queue<Produto*, vector<Produto*>, compare> getPriorityQueue() const;
	void displayPriorityQueue();
	//organiza na fila prioritaria
	void addProduto(Produto* p);
	void removeProduto(Produto* p);
	void alteraProduto(Produto* p, int stock);
	void manageFila();
};

#endif /* ALERTA_H_ */
