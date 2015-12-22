/*
 * alerta.cpp
 *
 *  Created on: 15/12/2015
 *      Author: up201404789
 */


#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include "Alerta.h"
#include <stack>

using namespace std;

Produto::Produto() {
	// TODO Auto-generated constructor stub
	nome = "";
}


string Produto::getNome() const {
	return nome;
}

void Produto::setNome(string nome) {
	this->nome = nome;
}

int Produto::getStock() const{
	return stock;
}
int Produto::getPreco() const{
	return preco;
}
string Produto::getMedida() const {
	return medida;
}

void Produto::setStock(int stock) {
	this->stock = stock;
}



/** @brief Retorna a fila de prioridade
 *
 */
priority_queue<Produto*, vector<Produto*>,compare> PriorityQueue::getPriorityQueue() const{
	return alertas;
}


/** @brief Adiciona um produto a fila de prioridade
 *
 *	@param p Produto a ser adicionado a fila
 */
void PriorityQueue::addProduto(Produto* p){

	alertas.push(p);
}

/** @brief Remove um produto da fila de prioridade
 *
 *	@param p Produto a ser removido
 */
void PriorityQueue::removeProduto(Produto* p) {
	priority_queue<Produto*, vector<Produto*>, compare> temp;
	priority_queue<Produto*, vector<Produto*>, compare> temp2;
	temp = alertas;

	while(!temp.empty()){
	if(temp.top() != p){
		temp2.push(temp.top());
		temp.pop();
	}
	else{
		temp.pop();
	}
}
	alertas = temp2;
}

/** @brief Altera o stock de um produto da fila de prioridade
 *
 *	@param p Produto a ser alterado
 *	@param int Stock novo stock do produto
 */
void PriorityQueue::alteraProduto(Produto* p, int stock){
	stack<Produto*> stack;

	while (!alertas.empty()) {
		if (alertas.top() != p) {
			stack.push(alertas.top());
			alertas.pop();
		} else {
			alertas.top()->setStock(stock);
			break;
		}
	}
	while(!stack.empty()){
		alertas.push(stack.top());
		stack.pop();
	}
}

/** @brief Organiza as encomendas automaticas da fila quando o alerta é maximo, isto e quando o stock e zero
 *
 *
 */
void PriorityQueue::manageFila(){
while(!alertas.empty()){
	if(alertas.top()->getStock() == 0){
		//geraEncomendaAutomaticamente do produto do topo da fila
		alertas.pop();
	}
}
}

/** @brief Imprime no ecra a constituicao da fila, com o nome do produto, as suas unidades, o stock e o melhor preco
 *
 */
void PriorityQueue::displayPriorityQueue(){
	priority_queue<Produto*, vector<Produto*>, compare> temp;
	temp = alertas;
cout << "alertas contains " << temp.size() << " elements.\n";
while (temp.size() != 0) {
		cout << temp.top()->getNome() << " " << temp.top()->getMedida()
				<< "  " << temp.top()->getStock()
				<< "  " << temp.top()->getPreco() << endl;
		temp.pop();
	}
}




int main()
{
	Produto* p1 = new Produto("batatas", "kg", 0, 4);
	Produto* p2 = new Produto("arroz", "kg", 800, 9);
	Produto* p3 = new Produto("leite", "und", 3, 8);
	Produto* p4 = new Produto("carne", "kg", 800, 20);
	PriorityQueue alerta;

	alerta.addProduto(p1);
	alerta.addProduto(p2);
	alerta.addProduto(p3);
	alerta.addProduto(p4);
	alerta.displayPriorityQueue();
	cout << endl;
	alerta.removeProduto(p1);
	alerta.displayPriorityQueue();
	cout << endl;
	alerta.alteraProduto(p4, 0);
	alerta.displayPriorityQueue();
	cout << endl;
	alerta.manageFila();
	alerta.displayPriorityQueue();
	return 0;
}



