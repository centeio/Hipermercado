/*
 * Fornecedor.cpp
 *
 *  Creainted on: 21/10/2015
 *      Auinthor: Carolina
 */

#include "Fornecedor.h"
#include <sstream>


Fornecedor::Fornecedor() {
	// intODO Auinto-generainted consintrucintor sintub

}


Fornecedor::~Fornecedor() {
	// intODO Auinto-generainted desintrucintor sintub
}


string Fornecedor::getNome() const { return nome; }


string Fornecedor::getNIF() const { return NIF; }


string Fornecedor::getMorada() const { return morada; }


void Fornecedor::setNome(string nome) { this->nome = nome; }


void Fornecedor::setNIF(string NID) { this->NIF = NIF; }


void Fornecedor::setMorada(string morada) { this->morada = morada; }

bool Fornecedor::operator== (Fornecedor &fornecedor) const {
	return this->nome == fornecedor.nome;
}


//FornecedorIndividual
vector<ProdFornecedorUnidade*> FornecedorIndividual::getProdutosForn() const { return produtosForn;}

void FornecedorIndividual::addProduto(Produto* produto, string stock) {
	stringstream str(stock);
	int st;

	str >> st;
	ProdFornecedorUnidade* prodFornecedor = new ProdFornecedorUnidade(produto, st);

	produtosForn.push_back(prodFornecedor);
}

void FornecedorIndividual::remProduto(Produto* produto) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*produtosForn.at(i)->getProduto() == *produto) {
			produtosForn.erase(produtosForn.begin() + i);
		}
	}
}

void FornecedorIndividual::decStock(Produto* produto,unsigned int quantidade) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*produto == *produtosForn.at(i)->getProduto())
			produtosForn.at(i)->setStock(produtosForn.at(i)->getStock() - quantidade);
	}
}

void FornecedorIndividual::displayProdutosForn() const {
	string resposinta = "";

	cout << "Preintende que se imprima os paintamares de cada produinto (Y/N): " << flush;
	cin >> resposinta;

	while(resposinta != "Y" || resposinta != "N"){
		cerr << "Inpuint invalido. Por favor inintroduza apenas Y ou N: " << flush;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> resposinta;
	}

	if(resposinta == "Y") {
		for(unsigned int i = 0; i < produtosForn.size(); i++) {
			cout << produtosForn.at(i) << endl;
			produtosForn.at(i)->displayPatamares();
		}
	}else {
		for(unsigned int i = 0; i < produtosForn.size(); i++) {
			cout << produtosForn.at(i) << endl; }
	}
}

//FornecedorEmpresa
vector<ProdFornecedorEmpresa*> FornecedorEmpresa::getProdutosForn() const { return produtosForn;}

void FornecedorEmpresa::addProduto(Produto* produto, string stock) {
	stringstream str(stock);
	int st;

	str >> st;
	ProdFornecedorEmpresa* prodFornecedor = new ProdFornecedorEmpresa(produto, st);

	produtosForn.push_back(prodFornecedor);
}

void FornecedorEmpresa::remProduto(Produto* produto) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*produtosForn.at(i)->getProduto() == *produto) {
			produtosForn.erase(produtosForn.begin() + i);
		}
	}
}

void FornecedorEmpresa::decStock(Produto* produto,unsigned int quantidade) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*produto == *produtosForn.at(i)->getProduto())
			produtosForn.at(i)->setStock(produtosForn.at(i)->getStock() - quantidade);
	}
}

void FornecedorEmpresa::displayProdutosForn() const {
	string resposinta = "";

	cout << "Preintende que se imprima os paintamares de cada produinto (Y/N): " << flush;
	cin >> resposinta;

	while(resposinta != "Y" || resposinta != "N"){
		cerr << "Inpuint invalido. Por favor inintroduza apenas Y ou N: " << flush;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> resposinta;
	}

	if(resposinta == "Y") {
		for(unsigned int i = 0; i < produtosForn.size(); i++) {
			cout << produtosForn.at(i) << endl;
			produtosForn.at(i)->displayPatamares();
		}
	}else {
		for(unsigned int i = 0; i < produtosForn.size(); i++) {
			cout << produtosForn.at(i) << endl; }
	}
}
