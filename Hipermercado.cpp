/*
 * Hipermercado.cpp
 *
 *  Created on: 10/10/2015
 *      Author: Carolina
 */
#include "Hipermercado.h"
#include <algorithm>

/**
 *	@brief Inicializacao da variavel estatica instance
 *
 */
Hipermercado* Hipermercado::Instance = NULL;

ProdutoFornecedor Hipermercado::ITEM_NOT_FOUND = ProdutoFornecedor("","",1000, NULL, NULL);

Hipermercado::Hipermercado(string nome): nome(nome), produtos(ITEM_NOT_FOUND){
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


BST<ProdutoFornecedor> Hipermercado::getProdutos() const{
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

/**
 *	@brief Adiciona produto
 *
 *	@param produto Produto a adicionar
 */
void Hipermercado::addProduto(ProdutoFornecedor produto){
	produtos.insert(produto);
	Produto* produtoFila = new Produto(produto.getNome(), produto.getMedida(), produto.getStock());
	addProdutoFila(produtoFila);
}

/**
 *
 * 	@brief Elimina produto
 *
 *	@param indice Indice do Produto a eliminar
 */
void Hipermercado::eliminaProduto(ProdutoFornecedor produto){
	ProdutoFornecedor produtoFornecedor = produtos.find(produto);

	while(produtoFornecedor != ITEM_NOT_FOUND) {
		produtos.remove(produto);
		produtoFornecedor = produtos.find(produto);
	}
	Produto* produtoFila = new Produto(produto.getNome(), produto.getMedida(), produto.getStock());
	removeProdutoFila(produtoFila);
}

/**
*	@brief Altera nome do Produto
*
*	@param indice Indice do Produto a alterar
*	@param novonome Novo nome
*/
void Hipermercado::alteraNomeProduto(string nome, string novonome){
	BinaryNode<ProdutoFornecedor>* node = existeProduto(nome);

	while(node != NULL) {
		ProdutoFornecedor produto = node->element;
		produtos.remove(produto);
		produto.setNome(novonome);
		produtos.insert(produto);
		node = existeProduto(nome);
	}
}

/**
*	@brief Altera medida do Produto
*
*	@param indice Indice do Produto a alterar
*	@param novamedida Nova medida
*/
void Hipermercado::alteraMedidaProduto(string nome, string novamedida){
	BinaryNode<ProdutoFornecedor>* node = existeProduto(nome);

	while(node != NULL) {
		ProdutoFornecedor produto = node->element;
		produtos.remove(produto);
		produto.setMedida(novamedida);
		produtos.insert(produto);
		node = existeProduto(nome);
	}
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


void Hipermercado::displayProdutos() const {
	produtos.printTree();
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

BinaryNode<ProdutoFornecedor> * Hipermercado::existeProduto(string nome){
	existe(nome, produtos.root);
}


BinaryNode<ProdutoFornecedor> * Hipermercado::existe(string nome,  BinaryNode<ProdutoFornecedor> *t){

	if( t == NULL )
		return NULL;
	else if( nome < t->element.getNome() )
		return existe( nome, t->left );
	else if( t->element.getNome() < nome )
		return existe( nome, t->right );
	else
		return t;    // Match
}

/** @brief Retorna a fila de prioridade
 *
 */
/*priority_queue<Produto*, vector<Produto*>,compare> Hipermercado::getPriorityQueue() const{
	return alertas;
}*/

/** @brief Adiciona um produto a fila de prioridade
 *
 *	@param p Produto a ser adicionado a fila
 */
void Hipermercado::addProdutoFila(Produto* p){

	alertas.push(p);
}

/** @brief Remove um produto da fila de prioridade
 *
 *	@param p Produto a ser removido
 */
void Hipermercado::removeProdutoFila(Produto* p) {
	priority_queue<Produto*, vector<Produto*>, compare> temp;
	priority_queue<Produto*, vector<Produto*>, compare> temp2;
	temp = alertas;

	while(!temp.empty()){
		if((*temp.top()) != *p){
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
void Hipermercado::alteraProdutoFila(Produto* p, int stock){
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

/** @brief Organiza as encomendas automaticas da fila quando o alerta � maximo, isto e quando o stock e zero
 *
 *
 */
void Hipermercado::manageFila(){
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
void Hipermercado::displayPriorityQueue(){
	priority_queue<Produto*, vector<Produto*>, compare> temp;
	temp = alertas;
	cout << "alertas contains " << temp.size() << " elements.\n";
	while (temp.size() != 0) {
		cout << temp.top()->getNome() << " " << temp.top()->getMedida()
		<< "  " << temp.top()->getStock() << endl;
		temp.pop();
	}
}