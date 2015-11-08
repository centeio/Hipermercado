/*
 * Fornecedor.cpp
 *
 *  Creainted on: 21/10/2015
 *      Auinthor: Carolina
 */

#include "Fornecedor.h"
#include <algorithm>


Fornecedor::Fornecedor() {
	// TODO Auto-generated constructor stub
	/**
	 *	@brief Constroi o fornecedor
	 *
	 */

}


Fornecedor::~Fornecedor() {
	// TODO Auto-generated destructor stub
	/**
			*	@brief Destroi o produto
		*
			*/
}


string Fornecedor::getNome() const {
	return nome;
	/**
	 *	@return Retorna o nome do fornecedor
	 */
}


string Fornecedor::getNIF() const {
	return NIF;
	/**
	 *	@return Retorna o nif do fornecedor
	 */
}


string Fornecedor::getMorada() const {
	return morada;
	/**
	 *	@return Retorna a morada do fornecedor
	 */
}

vector<ProdFornecedor*> Fornecedor::getProdutosForn() const {
	return produtosForn;
	/**
	 *	@return Retorna os produtos do fornecedor
	 */
}


void Fornecedor::setNome(string nome) {
	this->nome = nome;
	/**
	 *	@brief Define o nome do fornecedor
	 *
	 * @param nome Nome do fornecedor
	 */
}


void Fornecedor::setNIF(string NIF) {
	this->NIF = NIF;
	/**
	 *	@brief Define o nif do fornecedor
	 *
	 * @param NIF Nif do fornecedor
	 */
}


void Fornecedor::setMorada(string morada) {
	this->morada = morada;
	/**
	 *	@brief Define a morada do fornecedor
	 *
	 * @param morada Morada do fornecedor
	 */
}

void Fornecedor::addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco) {
	produtosForn.at(indiceProduto)->addPatamar(min,max,preco);
	/**
	 *@brief Adiciona patamar
	 *
	 * @param indiceProduto Indice do Produto a adicionar novo patamar
	 * @param min Patamar minimo
	 * @param max Patamar maximo
	 * @param preco Preco do patamar
	 */
}

void Fornecedor::addProduto(Produto* produto, unsigned int stock) {

	ProdFornecedor* prodFornecedor = new ProdFornecedor(produto, stock);
	produtosForn.push_back(prodFornecedor);
	/**
	 *@brief Adiciona produto
	 *
	 * @param produto Produto a adicionar
	 * @param stock Stock do produto
	 */
}

void Fornecedor::remProduto(Produto* produto) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*(produtosForn.at(i)->getProduto()) == *produto) {
			produtosForn.erase(produtosForn.begin() + i);
		}
	}
	/**
	 *@brief Remove produto
	 *
	 * @param produto Produto a remover
	 *
	 */
}

void Fornecedor::decStock(Produto* produto,unsigned int quantidade) {

	for(unsigned int i = 0; i < produtosForn.size(); i++) {
		if(*produto == *produtosForn.at(i)->getProduto())
			produtosForn.at(i)->setStock(produtosForn.at(i)->getStock() - quantidade);
	}
	/**
	 *@brief Decrementa o stock
	 *
	 * @param produto Produto ao qual se vai decrementar o stock
	 * @param quantidade Quantidade a decrementar
	 *
	 */
}

void Fornecedor::displayProdutosForn() const {
	string resposta = "";

	cin.clear();
	cin.ignore(1000, '\n');
	cout << "Pretende que se imprima os patamares de cada produto (Y/N): " << flush;
	getline(cin,resposta);

	transform(resposta.begin(), resposta.end(), resposta.begin(), ptr_fun <int, int> (tolower));
	while(resposta != "y" && resposta != "n"){
		cerr << "Input invalido. Por favor introduza apenas Y ou N: " << flush;
		getline(cin,resposta);
		transform(resposta.begin(), resposta.end(), resposta.begin(), ptr_fun <int, int> (tolower));
	}

	if(produtosForn.size() != 0) {
		cout << "Produtos do fornecedor: " << endl << setw(16) << "Nome" << setw(15) << "Medida" << setw(15) << "Stock" << endl;

		if (resposta == "y") {
			for (unsigned int i = 0; i < produtosForn.size(); i++) {
				cout << i + 1 << produtosForn.at(i);
				produtosForn.at(i)->displayPatamares();
			}
		} else {
			for (unsigned int i = 0; i < produtosForn.size(); i++) {
				cout << i + 1 << produtosForn.at(i);
			}
		}
	}
	/**
	 *	@brief display de todos os Produtos
	 */
}

bool Fornecedor::operator== (Fornecedor &fornecedor) const {
	return this->nome == fornecedor.nome;
	/** @brief Compara a igualdade de dois fornecedor
	 *
	 *	@param &fornecedor Fornecedor
	 *
	 *	@return Retorna verdadeiro se os dois fornecedores comparados tiverem nomes iguais; caso contrario, retorna falso.
	 */
}

ostream& operator<< (ostream& out, Fornecedor* fornecedor) {

	out << setw(15) << fornecedor->getTipo() << setw(15) << fornecedor->nome << setw(15) << setw(15) << fornecedor->NIF << setw(15) << fornecedor->morada << endl;
	return out;
	/** @brief Imprime no ecra os atributos da classe por overload do operator<<
	 *
	 *	@param out Objeto da iostream
	 *	@param fornecedor Fornecedor
	 *
	 *	@return Retorna ostream
	 */
}

//FornecedorIndividual

void FornecedorIndividual::addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco) {

	if(produtosForn.at(indiceProduto)->getPatamares().size() == 1) throw DemasiadosPatamares();
	Fornecedor::addPatamar(indiceProduto,min,max,preco);
	/**
	 *@brief Adiciona patamar
	 *
	 * @param indiceProduto Indice do Produto a adicionar novo patamar
	 * @param min Patamar minimo
	 * @param max Patamar maximo
	 * @param preco Preco do patamar
	 */
}

string FornecedorIndividual::getTipo() const {
	return tipo;
	/**
	 *	@return Retorna o tipo do fornecedor
	 */
}

//FornecedorEmpresa
void FornecedorEmpresa::addPatamar(unsigned int indiceProduto, unsigned int min, unsigned int max, unsigned preco) {
	Fornecedor::addPatamar(indiceProduto,min,max,preco);
	/**
	 *@brief Adiciona patamar
	 *
	 * @param indiceProduto Indice do Produto a adicionar novo patamar
	 * @param min Patamar minimo
	 * @param max Patamar maximo
	 * @param preco Preco do patamar
	 */
}

string FornecedorEmpresa::getTipo() const {
	return tipo;
	/**
	 *	@return Retorna o tipo do fornecedor
	 */
}

