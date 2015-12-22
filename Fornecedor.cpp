/*
 * Fornecedor.cpp
 *
 *  Creainted on: 21/10/2015
 *      Auinthor: Carolina
 */

#include "Fornecedor.h"
#include <algorithm>
#include <iomanip>

/**
 *	@brief Constroi o fornecedor
 *
 */
Fornecedor::Fornecedor() {
	// TODO Auto-generated constructor stub
	nome = "";
	NIF = "";
	morada = "";
	data.setDia(0);
	data.setMes(0);
	data.setAno(0);
}

Fornecedor::Fornecedor(string nome, string NIF, string morada) : nome(nome), NIF(NIF), morada(morada) {
	Data data(0,0,0);
	this->data = data;
}


/**
 *	@brief Destroi o produto
 *
 */
Fornecedor::~Fornecedor() {
	// TODO Auto-generated destructor stub
}

/**
 *	@return Retorna o nome do fornecedor
 */
string Fornecedor::getNome() const {
	return nome;
}

/**
 *	@return Retorna o nif do fornecedor
 */
string Fornecedor::getNIF() const {
	return NIF;
}

/**
 *	@return Retorna a morada do fornecedor
 */
string Fornecedor::getMorada() const {
	return morada;
}

Data Fornecedor::getData() const {
	return data;
}

/**
 *	@brief Define o nome do fornecedor
 *
 * @param nome Nome do fornecedor
 */
void Fornecedor::setNome(string nome) {
	this->nome = nome;
}

/**
 *	@brief Define o nif do fornecedor
 *
 * @param NIF Nif do fornecedor
 */
void Fornecedor::setNIF(string NIF) {
	this->NIF = NIF;
}

/**
 *	@brief Define a morada do fornecedor
 *
 * @param morada Morada do fornecedor
 */
void Fornecedor::setMorada(string morada) {
	this->morada = morada;
}

void Fornecedor::setData(Data data) {
	this->data = data;
}

/** @brief Compara a igualdade de dois fornecedor
 *
 *	@param &fornecedor Fornecedor
 *
 *	@return Retorna verdadeiro se os dois fornecedores comparados tiverem nomes iguais; caso contrario, retorna falso.
 */
bool Fornecedor::operator==(Fornecedor &fornecedor) const {
	return this->nome == fornecedor.nome;
}

/** @brief Imprime no ecra os atributos da classe por overload do operator<<
 *
 *	@param out Objeto da iostream
 *	@param fornecedor Fornecedor
 *
 *	@return Retorna ostream
 */
ostream& operator<<(ostream& out, Fornecedor* fornecedor) {

	out << setw(15) << fornecedor->getTipo() << setw(15) << fornecedor->nome
			<< setw(15) << setw(15) << fornecedor->NIF << setw(15)
			<< fornecedor->morada << endl;
	return out;
}

//FornecedorIndividual
/**
 *	@return Retorna o tipo do Fornecedor
 */
string FornecedorIndividual::getTipo() const {
	return tipo;
}

//FornecedorEmpresa
/**
 *	@return Retorna o tipo do Fornecedor
 */
string FornecedorEmpresa::getTipo() const {
	return tipo;
}

