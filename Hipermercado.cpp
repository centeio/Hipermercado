/*
 * Hipermercado.cpp
 *
 *  Created on: 10/10/2015
 *      Author: Carolina
 */
#include "Hipermercado.h"
#include <algorithm>


Hipermercado* Hipermercado::Instance = NULL;
/**
	 *	@brief Inicializacao da variavel estatica instance
	 *
	 */

Hipermercado::Hipermercado(string nome): nome(nome){
	/**
	 *	@brief Constroi o hipermercado
	 *
	 *	@param nome
	 */
}

vector<Fornecedor*> Hipermercado::getFornecedores() const{
	return fornecedores;
	/**
	 *	@return Retorna os fornecedores do hipermercado
	 */
}


vector<Produto*> Hipermercado::getProdutos() const{
	return produtos;
	/**
	 *	@return Retorna os produtos do hipermercado
	 */
}


vector<PedidoEncomenda*> Hipermercado::getPedidos() const{
	return pedidos;
	/**
	 *	@return Retorna os pedidos do hipermercado
	 */
}


vector<Encomenda*> Hipermercado::getEncomendas() const{
	return encomendas;
	/**
	 *	@return Retorna as encomendas do hipermercado
	 */
}

Data Hipermercado::getDataAtual() const { return dataatual; }

void Hipermercado::setDataAtual(unsigned int dia, unsigned int mes, unsigned int ano) {
	dataatual.setDia(dia);
	dataatual.setMes(mes);
	dataatual.setAno(ano);
}

void Hipermercado::alteraQuantProdPedido(unsigned int indicepedido, unsigned int indiceproduto, unsigned int novaqt){
	pedidos.at(indicepedido)->setQuantProduto(indiceproduto,novaqt);
	/**
	 *	@return Retorna os produtos do hipermercado
	 *
	 *	@param IndicePedido Indice do pedido
	 *	@param IndiceProduto Indice do produto
	 *	@param Novaqt Nova quantidade
	 */
}

string Hipermercado::getNome() const{
	return nome;
	/**
	 *	@return Retorna o nome do hipermercado
	 */
}

void Hipermercado::alteraNomeProdPedido(unsigned int indicepedido, unsigned int indiceproduto, string novonome){
	if(indicepedido+1>=pedidos.size())
		cout<<"Nao existe esse pedido."<<endl;
	else
		if(indiceproduto+1>=pedidos.at(indiceproduto)->getProdutos().size())
			cout<<"Nao existe esse produto nesse pedido."<<endl;
		else
			pedidos.at(indicepedido)->setProduto(indiceproduto,novonome);
	/**
	 *	@brief Altera o nome do produto de indice "indiceproduto" no pedido de indice "indicepedido"
	 *
	 *	@param indicepedido Indice do pedido
	 *	@param indiceproduto Indice do produto
	 *	@param novonome Novo Nome
	 */
}

bool of(Fornecedor* f1,Fornecedor* f2){
	if(f1->getNome() < f2->getNome())
		return true;
	else
		return false;
	/**
	 *	@return Retorna verdadeiro se o nome do fornecedor 1 for alfabeticamente anterior ao nome do fornecedor 2
	 *
	 *	@param f1 Fornecedor1
	 *	@param f2 Fornecedor2
	 */
}


void Hipermercado::ordenaFornecedores(){
	sort(fornecedores.begin(),fornecedores.end(),of);
	/**
	 *	@brief Ordena Fornecedores
	 */
}


bool op(Produto* p1,Produto* p2){
	if(p1->getNome() < p2->getNome())
		return true;
	else
		return false;
	/**
		 *	@return Retorna verdadeiro se o nome do produto 1 for alfabeticamente anterior ao nome do produto 2
		 *
		 *	@param p1 Produto1
		 *	@param p2 Produto2
		 */
}


void Hipermercado::ordenaProdutos(){
	sort(produtos.begin(),produtos.end(),op);
	/**
	 *	@brief Ordena Produtos
	 */
}


bool opd(PedidoEncomenda* p1,PedidoEncomenda* p2){
	if(p1->getData() < p2->getData())
		return true;
	else
		return false;
	/**
		 *	@return Retorna verdadeiro se a data do Pedido de Encomenda 1 for mais recente que a data do Pedido de Encomenda 2
		 *
		 *	@param p1 Pedido de Encomenda 1
		 *	@param p2 Pedido de Encomenda 2
		 */
}

void Hipermercado::ordenaPedidos(){
	sort(pedidos.begin(),pedidos.end(),opd);
	/**
	 *	@brief Ordena Pedidos
	 */
}

bool oe(Encomenda* e1, Encomenda* e2){
	if(e1->getData() < e2->getData())
		return true;
	else
		return false;
	/**
			 *	@return Retorna verdadeiro se a data da Encomenda 1 for mais recente que a  data da Encomenda 2
			 *
			 *	@param p1 Pedido de Encomenda 1
			 *	@param p2 Pedido de Encomenda 2
			 */
}

void Hipermercado::ordenaEncomendas(){
	sort(encomendas.begin(),encomendas.end(),oe);
	/**
	 *	@brief Ordena Encomendas
	 */
}


void Hipermercado::addFornecedor(Fornecedor* fornecedor){
	fornecedores.push_back(fornecedor);
	/**
	 *	@brief  Adiciona fornecedor
	 *
	 *	@param fornecedor Fornecedor
	 */
}


void Hipermercado::setNome(string novonome){
	nome=novonome;
	/**
	 *	@brief Define o novo nome do hipermercado
	 *
	 *	@param novonome Novo nome
	 */
}


void Hipermercado::eliminaFornecedor(unsigned int indice){
	delete(fornecedores.at(indice));
	fornecedores.erase(fornecedores.begin()+indice);
	/**
	 *	@brief Elimina fornecedor
	 *
	 *	@param indice Indice do fornecedor a eliminar
	 */
}


void Hipermercado::addProduto(Produto* produto){
	produtos.push_back(produto);
	/**
	 *	@brief Adiciona produto
	 *
	 *	@param produto Produto a adicionar
	 */
}


void Hipermercado::eliminaProduto(unsigned int indice){
	delete(produtos.at(indice));
	produtos.erase(produtos.begin()+indice);
	/**
	 *	@brief Elimina produto
	 *
	 *	@param indice Indice do Produto a eliminar
	 */
}

void Hipermercado::alteraNomeProduto(unsigned int indice, string novonome){
	produtos.at(indice)->setNome(novonome);
	/**
	 *	@brief Altera nome do Produto
	 *
	 *	@param indice Indice do Produto a alterar
	 *	@param novonome Novo nome
	 */
}

void Hipermercado::alteraMedidaProduto(unsigned int indice, string novamedida){
	produtos.at(indice)->setMedida(novamedida);
	/**
	 *	@brief Altera medida do Produto
	 *
	 *	@param indice Indice do Produto a alterar
	 *	@param novamedida Nova medida
	 */
}

void Hipermercado::eliminaPedido(unsigned int indice){
	delete(pedidos.at(indice));
	pedidos.erase(pedidos.begin()+indice);
	/**
	 *	@brief Elimina Pedido
	 *
	 *	@param indice Indice do pedido a eliminar
	 */
}


void Hipermercado::addPedido(PedidoEncomenda* pedido){
	pedidos.push_back(pedido);
	/**
	 *	@brief Adiciona pedido de encomenda
	 *
	 *	@param pedido Pedido de encomenda
	 */
}


void Hipermercado::addEncomenda(Encomenda* encomenda){
	encomendas.push_back(encomenda);
	/**
	 *	@brief Adiciona Encomenda
	 *
	 *	@param encomenda Encomenda
	 */
}


void Hipermercado::displayFornecedores() const{

	if(fornecedores.size() != 0) {
		cout << "Fornecedores: " << endl << setw(17) << "Tipo" << setw(15) << "Nome" << setw(15) << "NIF" << setw(15) << "Morada" << endl;

		for (unsigned int i = 0; i < fornecedores.size(); i++)
			cout << i + 1 << " - " << fornecedores.at(i) << endl;
	}
	/**
	 *	@brief display de todos Fornecedor
	 */
}


void Hipermercado::displayProdutos() const{
	if(produtos.size() != 0) {
		cout << "Produtos: " << endl << setw(15)<<"Nome"<<setw(15)<<"Medida"<<endl;
		for (unsigned int i = 0; i < produtos.size(); i++) {
			cout << i + 1 << " - " << produtos.at(i) << endl;
		}
	}
	/**
	 *	@brief display de todos os Produtos
	 */
}


void Hipermercado::displayPedidos() const{
	if(pedidos.size() != 0) {
		cout << "Pedidos: " << endl;
		for (unsigned int i = 0; i < pedidos.size(); i++)
			cout << i + 1 << " - " << pedidos.at(i) << endl;
	}
	/**
	 *	@brief display de todos os Pedidos
	 */
}

void Hipermercado::displayPedidosPorProcessar() const{
	cout << "Pedidos: "<< endl;

	for(unsigned int i=0;i<pedidos.size();i++){
		if(!pedidos.at(i)->getFinalizado())
			cout<< i+1 << " - " << pedidos.at(i) << endl;
	}
	/**
	 *	@brief display de todos pedidos por processar
	 */
}


void Hipermercado::displayPedidosProcessados() const{
	cout << "Pedidos: "<<endl;
	for(unsigned int i=0;i<pedidos.size();i++){
		if(pedidos.at(i)->getFinalizado())
			cout<< endl << i+1 << " - " << pedidos.at(i) << endl;
	}
	/**
	 *	@brief display de todos os pedidos processados
	 */
}


void Hipermercado::displayEncomendas() const{
	if(encomendas.size() != 0) {
		cout << "Encomendas: " << endl;
		for (unsigned int i = 0; i < encomendas.size(); i++) {
			cout << i + 1 << " - " << encomendas.at(i) << endl;
		}
	}
	/**
	 *	@brief display de todas as encomendas
	 */
}
/*
void Hipermercado::displayProdutosFornecedor() const {

	for(unsigned int i = 0; i < fornecedores.size(); i++) {
		fornecedores.at(i)->displayProdutosForn();
	}
	/**
	 *	@brief display de todos os produtos de todos os fornecedores
	 */
//}

void Hipermercado::processaPedido() {

	for(unsigned int i = 0; i < pedidos.size(); i++) {
		if(!pedidos.at(i)->getFinalizado()) pedidos.at(i)->processamento();
	}
	/**
	 *	@brief Processa pedido
	 */
}

void Hipermercado::atualizaTabela(){
	for(unsigned int i=0;i<fornecedores.size();i++){
		Data d=dataatual;
		d.setAno(dataatual.getAno()-1);
		if(fornecedores.at(i)->getData()<d)
			inativos.insert(fornecedores.at(i));
	}
}

void Hipermercado::removeDaTabela(Fornecedor* f){
	inativos.erase(inativos.find(f));

}

void Hipermercado::displayTabela(){
	unordered_set<Fornecedor*,hf,eqf>::iterator it = inativos.begin();
	while (it!=inativos.end()) {
		cout << *it << endl;
		it++;
	};


}
