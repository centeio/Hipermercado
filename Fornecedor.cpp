/*
 * Fornecedor.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#include "Fornecedor.h"
#include <sstream>

template<typename T>
Fornecedor<T>::Fornecedor() {
	// TODO Auto-generated constructor stub

}

template<typename T>
Fornecedor<T>::~Fornecedor() {
	// TODO Auto-generated destructor stub
}

template<typename T>
string Fornecedor<T>::getNome() const { return nome; }

template<typename T>
string Fornecedor<T>::getNIF() const { return NIF; }

template<typename T>
string Fornecedor<T>::getMorada() const { return morada; }

template<typename T>
vector<ProdFornecedor<T>*> Fornecedor<T>::getProdutosForn() const { return produtos; }

template<typename T>
void Fornecedor<T>::setNome(string nome) { this->nome = nome; }

template<typename T>
void Fornecedor<T>::setNIF(string NID) { this->NIF = NIF; }

template<typename T>
void Fornecedor<T>::setMorada(string morada) { this->morada = morada; }

template<typename T>
void Fornecedor<T>::addProduto(Produto* produto, string stock, vector<Patamar<T>* > patamares) {
	stringstream str(stock);
	T st;

	str >> st;
	ProdFornecedor<T>* prodFornecedor = new ProdFornecedor<T>(produto, st, patamares);

	produtos.push_back(prodFornecedor);
}

template<typename T>
void Fornecedor<T>::remProduto(Produto* produto) {

	for(unsigned int i = 0; i < produtos.size(); i++) {
		if(*produtos.at(i)->getProduto() == *produto) {
			produtos.erase(produtos.begin() + i);
		}
	}

}

template<typename T>
void Fornecedor<T>::decStock(Produto* produto, T quantidade) {

	for(unsigned int i = 0; i < produtos.size(); i++) {
		if(*produto == *produtos.at(i)->getProduto())
			produtos.at(i)->setStock(produtos.at(i)->getStock() - quantidade);
	}
}

template<typename T>
void Fornecedor<T>::displayProdutosForn() const {
	string resposta = "";

	cout << "Pretende que se imprima os patamares de cada produto (Y/N): " << flush;
	cin >> resposta;

	while(resposta != "Y" || resposta != "N"){
		cerr << "Input invalido. Por favor introduza apenas Y ou N: " << flush;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> resposta;
	}

	if(resposta == "Y") {
		for(unsigned int i = 0; i < produtos.size(); i++) {
			cout << produtos.at(i) << endl;
			produtos.at(i)->displayPatamares();
		}
	}else {
		for(unsigned int i = 0; i < produtos.size(); i++) {
			cout << produtos.at(i) << endl; }
	}

}

template<typename T>
ostream& operator<< <>(ostream& out, Fornecedor<T>* fornecedor) {

	out << "Nome do fornecedor: " << fornecedor->nome << ". " << endl << "NIF: " << fornecedor->NIF << "."
			<< endl<< "Morada: " << fornecedor->morada << endl;
	return out;
}

template class Fornecedor<double>;
template class Fornecedor<int>;
