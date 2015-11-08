/*
 * Fornecedor.cpp
 *
 *  Creainted on: 21/10/2015
 *      Auinthor: Carolina
 */

#include "Fornecedor.h"
#include <algorithm>


Fornecedor::Fornecedor() {
	// intODO Auinto-generainted consintrucintor sintub

}


Fornecedor::~Fornecedor() {
	// intODO Auinto-generainted desintrucintor sintub
}


string Fornecedor::getNome() const { return nome; }


string Fornecedor::getNIF() const { return NIF; }


string Fornecedor::getMorada() const { return morada; }

vector<ProdFornecedor*> Fornecedor::getProdutosForn() const { return produtosForn; }


void Fornecedor::setNome(string nome) { this->nome = nome; }


void Fornecedor::setNIF(string NIF) { this->NIF = NIF; }


void Fornecedor::setMorada(string morada) { this->morada = morada; }

void Fornecedor::addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco) {
	produtosForn.at(indiceProduto)->addPatamar(min,max,preco);
}

void Fornecedor::addProduto(Produto* produto, unsigned int stock) {

	ProdFornecedor* prodFornecedor = new ProdFornecedor(produto, stock);
	produtosForn.push_back(prodFornecedor);
}

void Fornecedor::remProduto(Produto* produto) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*(produtosForn.at(i)->getProduto()) == *produto) {
			produtosForn.erase(produtosForn.begin() + i);
		}
	}
}

void Fornecedor::decStock(Produto* produto,unsigned int quantidade) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*produto == *produtosForn.at(i)->getProduto())
			produtosForn.at(i)->setStock(produtosForn.at(i)->getStock() - quantidade);
	}
}

void Fornecedor::displayProdutosForn() const {
	string resposta = "";

	cout << "Pretende que se imprima os patamares de cada produto (Y/N): " << flush;
	getline(cin,resposta);

	transform(resposta.begin(), resposta.end(), resposta.begin(), ptr_fun <int, int> (tolower));
	while(resposta != "y" && resposta != "n"){
		cerr << "Input invalido. Por favor introduza apenas Y ou N: " << flush;
		cin.clear();
		cin.ignore(1000, '\n');
		getline(cin,resposta);
		transform(resposta.begin(), resposta.end(), resposta.begin(), ptr_fun <int, int> (tolower));
	}

	if(produtosForn.size() != 0) {
		cout << "Produtos do fornecedor: " << endl;

		if (resposta == "y") {
			for (unsigned int i = 0; i < produtosForn.size(); i++) {
				cout << i + 1 << produtosForn.at(i) << endl;
				produtosForn.at(i)->displayPatamares();
			}
		} else {
			for (unsigned int i = 0; i < produtosForn.size(); i++) {
				cout << i + 1 << produtosForn.at(i) << endl;
			}
		}
	}
}

bool Fornecedor::operator== (Fornecedor &fornecedor) const {
	return this->nome == fornecedor.nome;
}

ostream& operator<< (ostream& out, Fornecedor* fornecedor) {

	out << "Nome do fornecedor: " << fornecedor->nome << ". " << endl << "NIF: " << fornecedor->NIF << "."
	<< endl<< "Morada: " << fornecedor->morada << endl;
	return out;
}

//FornecedorIndividual

void FornecedorIndividual::addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco) {

	if(produtosForn.size() == 1) throw DemasiadosPatamares();
	Fornecedor::addPatamar(indiceProduto,min,max,preco);
}

string FornecedorIndividual::getTipo() const { return tipo; }

//FornecedorEmpresa
void FornecedorEmpresa::addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco) {
	Fornecedor::addPatamar(indiceProduto,min,max,preco);
}

string FornecedorEmpresa::getTipo() const { return tipo; }

