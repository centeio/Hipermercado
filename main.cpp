/*

 * main.cpp
 *
 *  Created on: 02/11/2015
 *      Author: Ariana
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include "Hipermercado.h"
#include "Data.h"
using namespace std;

static Data dataactual;

void leProdutos(Hipermercado* hipermercado, ifstream hipermercadoprodutos);
void leFornecedores(Hipermercado* hipermercado, ifstream hipermercadoFornecedores);
void leEncomendas(Hipermercado* hipermercado, ifstream hipermercadoencomendas);

//LER FICHEIROS DE TEXTO
void leFicheiros(Hipermercado* hipermercado) {

	ifstream hipermercadoprodutos("produtos.txt");
	if (hipermercadoprodutos.is_open()) {
		leProdutos(hipermercado, hipermercadoprodutos);
		hipermercadoprodutos.close();
		remove("produtos.txt");
	}

	ifstream hipermercadofornecedores("fornecedores.txt");
	if (hipermercadofornecedores.is_open()) {
		leFornecedores(hipermercado, hipermercadofornecedores);
		hipermercadofornecedores.close();
		remove("fornecedores.txt");
	}

	ifstream hipermercadoencomendas("encomendas.txt");
	if (hipermercadoencomendas.is_open()) {
		leEncomendas(hipermercado, hipermercadoencomendas);
		hipermercadoencomendas.close();
		remove("encomendas.txt");
	}
}

//LER PRODUTOS.TXT
void leProdutos(Hipermercado* hipermercado, ifstream &hipermercadoprodutos) {
	string nome, unidade;
	int numprodutos;

	hipermercadoprodutos >> numprodutos;
	for (int i = 0; i < numprodutos; i++) {
		hipermercadoprodutos >> nome >> unidade;
		Produto* produto = new Produto(nome, unidade);
		hipermercado->addProduto(produto);
	}
}

//LER FORNECEDORES.TXT
void leFornecedores(Hipermercado* hipermercado, ifstream &hipermercadoFornecedores) {
	string nome, nif, morada, tipo, produto, medida;
	unsigned int stock, patminimo, patmaximo;
	float preco;
	int numfornecedores, numprodutos, numpatamares;

	hipermercadoFornecedores >> numfornecedores;

	for (int i = 0; i < numfornecedores; i++) {
		hipermercadoFornecedores >> nome >> nif >> morada >> tipo >> numprodutos;

		if(tipo == "individual") hipermercado->addFornecedor(new FornecedorIndividual(nome, nif, morada));
		else hipermercado->addFornecedor(new FornecedorEmpresa(nome,nif,morada));

		for (int j = 0; j < numprodutos; j++) {
			hipermercadoFornecedores >> produto >> medida >> stock >> numpatamares;
			hipermercado->getFornecedores().at(i)->addProduto(new Produto(produto, medida),stock);

			for (int k = 0; k < numpatamares ; k++) {
				hipermercadoFornecedores >> patminimo >> patmaximo >> preco;
				hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->addPatamar(patminimo, patmaximo, preco);
			}
		}
	}
}


unsigned int procuraFornecedor(Hipermercado* hipermercado, string nome){

	for(int i = 0; i < hipermercado->getFornecedores().size(); i++ ){
		if(hipermercado->getFornecedores().at(i)->getNome() == nome)
			return i ;
	}
}

unsigned int procuraProduto(Hipermercado* hipermercado, string nome){

	for(int i = 0; i < hipermercado->getProdutos().size(); i++ ){
		if(hipermercado->getProdutos().at(i)->getNome() == nome)
					return i ;
	}
}

//LER ENCOMENDAS.TXT
void leEncomendas(Hipermercado* hipermercado, ifstream &hipermercadoencomendas) {
	string fornecedor, produto, medida;
	unsigned int dia, mes, ano;
	float preco;
	int numencomendas, numlinhasencomendas, indiceFornecedor, indiceProduto, quantidade;

	hipermercadoencomendas >> numencomendas;
	for (int i = 0; i < numencomendas; i++) {

		hipermercadoencomendas >> dia >> mes >> ano >> fornecedor
			>> numlinhasencomendas >> produto >> quantidade >> preco;

		Data data(dia, mes, ano);
		indiceFornecedor = procuraFornecedor(hipermercado, fornecedor);
		indiceProduto = procuraProduto(hipermercado, produto);

		Encomenda* encomenda = new Encomenda(hipermercado->getFornecedores().at(indiceFornecedor),hipermercado->getProdutos().at(indiceProduto),quantidade, preco,data);
		hipermercado->addEncomenda(encomenda);
		for (int j = 0; j < numlinhasencomendas - 1; j++) {
			hipermercadoencomendas >> produto >> medida >> quantidade >> preco;
			hipermercado->getEncomendas().at(i)->addLinha(new Produto(produto, medida), quantidade, preco);
			//Mistério! Não faço ideia porque não reconhece o addLinha
		}
	}
}
void opcoesmenu(Hipermercado* hipermercado);

//MENU INICIAL
void menuinicial(Hipermercado* hipermercado) {
	cout << setw(40) << "HIPERMERCADO" << endl << endl;
	cout << setw(20) << "Ecra principal: " << endl << endl;
	cout << setw(10) << "1 - Ver produtos" << endl;
	cout << setw(10) << "2 - Ver fornecedores" << endl;
	cout << setw(10) << "3 - Ver encomendas" << endl;
	cout << setw(10) << "4 - Mudar nome do Hipermercado" << endl;
	cout << setw(10) << "9 - Terminar o programa" << endl;
	opcoesmenu(hipermercado);
}

void opcaoprodutos(Hipermercado* hipermercado);
void opcaofornecedores(Hipermercado* hipermercado);
void opcaoencomendas(Hipermercado* hipermercado);
void opcaomudarnome(Hipermercado* hipermercado);

//MENU DE OPCOES
void opcoesmenu(Hipermercado* hipermercado) {
	int opcao;

	cout << "Introduza a opcao pretendida: " << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)) {
		cout << "Opcao invalida, volte a introduzir a opcao pretendida: "
				<< endl;
		cin >> opcao;
	}

	if (opcao == 1) {
		opcaoprodutos(hipermercado);
	} else if (opcao == 2) {
		opcaofornecedores(hipermercado);
	} else if (opcao == 3) {
		opcaoencomendas(hipermercado);
	} else if (opcao == 4) {
		opcaomudarnome(hipermercado);
	} else {
		cout << "Terminou o programa , obrigada pela sua visita!";
	}
}

//OPCAO PRODUTOS DO MENU
void opcaoprodutos(Hipermercado* hipermercado) {
	string nomeprod, unidadesprod, nomeprodeliminar;
	int opcao, numprodeliminar;

	cout << setw(20) << "Produtos: " << endl << endl;
	cout << setw(10) << "1 - Ver lista de produtos" << endl;
	cout << setw(10) << "2 - Adicionar produto" << endl;
	cout << setw(10) << "3 - Eliminar produto" << endl;
	cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
	cin >> opcao;

	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 9)) {
		cout << "Opcao invalida, volte a introduzir a opcao pretendida: "
				<< endl;
		cin >> opcao;
	}

	if (opcao == 1) {
		hipermercado->displayProdutos();
	} else if (opcao == 2) {
		cout << "Qual o nome e a medida do novo produto?" << endl;
		cin >> nomeprod;
		cin >> unidadesprod;
		Produto* produtof = new Produto(nomeprod, unidadesprod);
		hipermercado->addProduto(produtof);
	} else if (opcao == 3) {
		hipermercado->displayProdutos();
		cout << "Qual o numero do produto que quer eliminar ? ";
		cin >> numprodeliminar;
		hipermercado->eliminaProduto(numprodeliminar);
	} else {
		menuinicial(hipermercado);
	}
}

//OPCAO FORNECEDORES DO MENU
void opcaofornecedores(Hipermercado* hipermercado) {
	string nomenovo, moradanova, nifnovo, produtoaadicionar, unidades, novoprod,
			nomef, niff, moradaf, produtoaremover, nifaremover;
	int opcao, opcao2, opcao3, stock, numprodremover;

	do {
		cout << setw(20) << "Fornecedores: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de fornecedores" << endl;
		cout << setw(10) << "2 - Adicionar fornecedor" << endl;
		cout << setw(10) << "3 - Alterar fornecedor" << endl;
		cout << setw(10) << "4 - Eliminar fornecedor" << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 9)) {
			cout << "Opcao invalida, volte a introduzir a opcao pretendida pf"
					<< endl;
			cin >> opcao;
		}

		if (opcao == 1) { hipermercado->displayFornecedores(); }
		else if (opcao == 2) {
			cout << "Qual o nome , nif e morada do novo fornecedor? ";
			cin >> nomef >> niff >> moradaf;
			hipermercado->addFornecedor(new Fornecedor(nomef, niff, moradaf));
		} else if (opcao == 3) {
			cout << setw(10) << "Introduza a opcao pretendida pf" << endl;
			cout << setw(10) << "1 - Alterar nome do Fornecedor" << endl;
			cout << setw(10) << "2 - Alterar morada do Fornecedor" << endl;
			cout << setw(10) << "3 - Alterar NIF do Fornecedor" << endl;
			cout << setw(10) << "8 - Voltar ao menu fornecedores" << endl;
			cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
			cin >> opcao2;

			while ((opcao2 != 1) && (opcao2 != 2) && (opcao2 != 3) && (opcao2 != 4)
					&& (opcao != 9)) {
				cout << setw(10)
							<< "Opcao invalida, volte a introduzir a opcao pretendida: "
							<< endl;
				cin >> opcao2;
			}

			if (opcao == 1) {

				hipermercado->displayFornecedores();
				cout << setw(10)
							<< "Introduza o numero do fornecedor actual e o novo nome do fornecedor: "
						<< endl;
				int numfornecedor1;
				cin >> numfornecedor1;
				cin >> nomenovo;
				hipermercado->getFornecedores().at(numfornecedor1)->setNome(nomenovo);

			} else if (opcao == 2) {

				hipermercado->displayFornecedores();
				cout << setw(10)
							<< "Introduza numero do fornecedor que quer alterar e a nova morada do fornecedor: "
					<< endl;
				int numfornecedor2;
				cin >> numfornecedor2;
				cin >> moradanova;
				hipermercado->getFornecedores()[numfornecedor2]->setMorada(moradanova);

			} else if (opcao == 3) {

				hipermercado->displayFornecedores();
				cout << setw(10)
							<< "Introduza numero do fornecedor que quer alterar e o novo nif do fornecedor: "
						<< endl;
				int numfornecedor3;
				cin >> numfornecedor3;
				cin >> nifnovo;
				hipermercado->getFornecedores()[numfornecedor3]->setNIF(nifnovo);

			} else if (opcao == 8) { opcaofornecedores(hipermercado); }
			else { menuinicial(hipermercado); }
		}
		else if (opcao == 4) {

			cout << setw(10)
					<< "Introduza o numero do fornecedor que quer eliminar: "
					<< endl;
			int numforremover;
			cin >> numforremover;
			hipermercado->eliminaFornecedor(numforremover);
		} else { menuinicial(hipermercado); }
	}while(opcao != 9);
}

//OPCAO FORNECEDORES DO MENU
void opcaoencomendas(Hipermercado* hipermercado) {
	int opcao;
	string nomeproduto, unidades;
	int quantidade, preco;

	do {
		cout << setw(20) << "Encomendas: " << endl << endl;
		cout << setw(10) << "Introduza a opcao pretendida: " << endl << endl;
		//o que queres dizer com realizadas? Pedidos feitos e processados ou só pedidos feitos?
		cout << setw(10) << "1 - Ver pedidos de encomendas realizadas" << endl;
		cout << setw(10) << "2 - Ver pedidos de encomendas por realizar" << endl;
		cout << setw(10) << "3 - Pedir nova encomenda" << endl;
		cout << setw(10) << "4 - Alterar encomenda (mudar o numero de produtos encomendados)" << endl;
		cout << setw(10) << "5 - Cancelar encomenda" << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
				&& (opcao != 5) && (opcao != 9)) {
			cout << "Opcao invalida, volte a introduzir a opcao pretendida pf"
					<< endl;
			cin >> opcao;
		}

		if (opcao == 1) { hipermercado->displayPedidos(); }
		else if (opcao == 2) { hipermercado->displayPedidosPorProcessar(); }
		else if (opcao == 3) {

			string nomeProduto;
			unsigned int indiceProduto;
			int num, qnt;
			vector<Produto *> produtosencomendas;
			vector<int> quantidades;

			cout << "Insira o numero de produtos que quer encomendar: ";
			cin >> num;
			for(int i = 0; i < num; i++) {
				//ADICIONAR PEDIDO DE ENCOMENDA
				cout << "Insira o nome do produto que quer encomendar: ";
				cin >> nomeProduto;
				//criar excepção caso o nome introduzido para o produto não exista
				indiceProduto = procuraProduto(hipermercado, nomeProduto);

				cout << "Qual a quantidade que quer encomendar deste produto?";
				cin >> qnt;

				Produto* produto = new Produto(nomeProduto,
						hipermercado->getProdutos().at(indiceProduto)->getMedida());
				produtosencomendas.push_back(produto);
				quantidades.push_back(qnt);
			}
			hipermercado->addPedido(new PedidoEncomenda(dataactual, produtosencomendas, quantidades));

		} else if (opcao == 4) {
			//mostrar lista de pedidos por realizar
			//funcao que altera pedido encomenda;
			hipermercado->displayPedidosPorProcessar();

			cout << "Qual o numero do pedido de encomenda que quer alterar?" << endl;
			int numalt;
			cin >> numalt;

			cout <<"Qual o produto do pedido de encomenda que quer alterar a sua quantidade?" << endl;
			string nomeproduto;
			cin >> nomeproduto;

			cout << "Qual a nova quantidade de produto do pedido de encomenda? " << endl;
			int novaquantidade;
			cin >> novaquantidade;
			//esta função não existe
			//hipermercado->alteraPedidos(numalt,nomeproduto,novaquantidade);

		} else if (opcao == 5) {
			//funcao que elimina pedido encomenda;
			hipermercado->displayPedidosPorProcessar();

			cout << "Qual o numero do pedido de encomenda que quer eliminar?";
			unsigned int numprodeliminar;
			cin >> numprodeliminar;
			hipermercado->eliminaPedido(numprodeliminar);
		} else { menuinicial(hipermercado); }
	} while(opcao != 9);
}

//OPCAO MUDAR NOME DO MENU
void opcaomudarnome(Hipermercado* hipermercado) {
	int opcao;
	string novonome;

	do {
		cout << setw(10) << "Insira a opcao pretendida: " << endl
				<< "1 - Mudar nome do Hipermercado " << endl
				<< "9 - Voltar ao menu inicial" << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 9)) {
			cout << "Opcao invalida, volte a introduzir a opcao pretendida: "
				<< endl;
			cin >> opcao;
		}

		if (opcao == 1) {
			hipermercado->setNome(novonome);
		} else if (opcao == 9) { menuinicial(hipermercado); }
	}while(opcao != 9);
}

void escreveProdutos(Hipermercado* hipermercado);
void escreveFornecedores(Hipermercado* hipermercado);
void escreveEncomendas(Hipermercado* hipermercado);

void escreveFicheiros(Hipermercado* hipermercado) {


	escreveProdutos(hipermercado);
	escreveFornecedores(hipermercado);
	escreveEncomendas(hipermercado);
}

void escreveProdutos(Hipermercado* hipermercado) {
	ofstream hipermercadoProdutos;

	hipermercadoProdutos.open("produtos.txt");
	hipermercadoProdutos << hipermercado->getProdutos().size() << endl;
	for (int i = 0; i < hipermercado->getProdutos().size();i++) {
		hipermercadoProdutos << hipermercado->getProdutos()[i]->getNome() << endl
				<< hipermercado->getProdutos()[i]->getMedida();
	}
	hipermercadoProdutos.close();
}


void escreveFornecedores(Hipermercado* hipermercado) {
	ofstream hipermercadoFornecedores;

	hipermercadoFornecedores.open("fornecedores.txt");

	hipermercadoFornecedores << hipermercado->getFornecedores().size() << endl;

	for (int i = 0;	i < hipermercado->getFornecedores().size(); i++) {
		hipermercadoFornecedores << hipermercado->getFornecedores()[i]->getNome() << endl
				<< hipermercado->getFornecedores().at(i)->getNIF() << endl
				<< hipermercado->getFornecedores().at(i)->getMorada() << endl
				<< hipermercado->getFornecedores().at(i)->getProdutosForn().size() << endl;

		for (int j = 0;	j < hipermercado->getFornecedores().at(i)->getProdutosForn().size();j++) {
			hipermercadoFornecedores << hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getProduto()->getNome() << endl
					<< hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getProduto()->getMedida() << endl
					<< hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getStock() << endl
					<<  hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().size() << endl;

			for (int k = 0;k < hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().size(); k++) {
				hipermercadoFornecedores << hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().at(k)->getMinimo() << " "
						<< hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().at(k)->getMaximo() << " "
						<<hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().at(k)->getPreco() << endl;
			}
		}
	}
	hipermercadoFornecedores.close();
}

void escreveEncomendas(Hipermercado* hipermercado) {
	ofstream hipermercadoEncomendas;

	hipermercadoEncomendas.open("encomendas.txt");

	hipermercadoEncomendas << hipermercado->getPedidos().size() << endl;

	for (int i = 0; i < hipermercado->getPedidos().size(); i++) {
		hipermercadoEncomendas << hipermercado->getPedidos().at(i)->getData() << endl
				<< hipermercado->getPedidos().at(i)->getFornecedor() << endl;
		for (int j = 0; j < hipermercado->getPedidos().at(i)->getProdutos().size(); j++) {
			hipermercadoEncomendas << hipermercado->getPedidos().at(i)->getProdutos().at(j)->getNome() << endl
			<< hipermercado->getPedidos().at(i)->getProdutos().at(j)->getMedida() << endl
			<< hipermercado->getPedidos().at(i)->getQuantidade().at(j) << endl;
		}
	}
	hipermercadoEncomendas.close();
}


int main() {
	Hipermercado* hipermercado = Hipermercado::getInstance();

	leFicheiros(hipermercado);
	menuinicial(hipermercado);
	escreveFicheiros(hipermercado);
	return 0;
}
