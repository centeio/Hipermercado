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
#include "Hipermercado.h"
#include "Data.h"
using namespace std;

static Data dataactual;

//LER FICHEIROS DE TEXTO
//LER PRODUTOS.TXT
void leProdutos(ifstream hipermercadoprodutos) {
	string nome, unidade;
	int numprodutos;
	hipermercadoprodutos >> numprodutos;
	for (int i = 0; i < numprodutos; i++) {
		hipermercadoprodutos >> nome >> unidade;
		Produto* produtof = new Produto(nome, unidade);
		Hipermercado<int>::getInstance()->addProduto(produtof);
	}
}

//LER FORNECEDORES.TXT
void leFornecedores(ifstream hipermercadofornecedores) {
	string nome, nif, morada, tipo, produtos, patminimo, patmaximo, preco,
			stock, medida;
	int numfornecedores, numprodutos, numpatamares, numproduto;
	hipermercadofornecedores >> numfornecedores;
	for (int i = 0; i < numfornecedores; i++) {
		hipermercadofornecedores >> nome >> nif >> morada >> tipo
				>> numprodutos;
		Hipermercado<int>::getInstance()->addFornecedor(new Fornecedor<int>(nome, nif, morada));
		for (int j = 0; j < numprodutos; j++) {
			hipermercadofornecedores >> numproduto >> produtos >> medida
					>> stock >> numpatamares >> patminimo >> patmaximo >> preco;
			vector<Patamar<int>*> patamares;
			patamares.push_back(new Patamar<int>(patminimo, patmaximo, preco));
			Hipermercado<int>::getInstance()->getFornecedores().at(Hipermercado<int>::getInstance()->getFornecedores().size()
							- 1)->addProduto(new Produto(produtos, medida),stock,patamares);
			for (int k = 0; k < numpatamares - 1; k++) {
				hipermercadofornecedores >> patminimo >> patmaximo >> preco;
				Hipermercado<int>::getInstance()->getFornecedores().at(
						Hipermercado<int>::getInstance()->getFornecedores().size()
								- 1)->getProdutosForn().at(
						Hipermercado<int>::getInstance()->getFornecedores().at(
								Hipermercado<int>::getInstance()->getFornecedores().size()
										- 1)->getProdutosForn().size() - 1)->addPatamar(
						patminimo, patmaximo, preco);
			}
		}
	}
}

int procurafornecedor(string nome){
	for(int i = 0; i < Hipermercado<int>::getInstance()->getFornecedores().size(); i++ ){
		if(Hipermercado<int>::getInstance()->getFornecedores()[i]->getNome() == nome)
			return i ;
	}
}

int procuraproduto(string nome){
	for(int i = 0; i < Hipermercado<int>::getInstance()->getProdutos().size(); i++ ){
		if(Hipermercado<int>::getInstance()->getProdutos()[i]->getNome() == nome)
					return i ;
	}
}

//LER ENCOMENDAS.TXT
void leEncomendas(ifstream hipermercadoencomendas) {
	string fornecedor, produto, quantidade, dia, mes, ano, medida;
	float preco;
	int numencomendas, numlinhasencomendas;

	hipermercadoencomendas >> numencomendas;
	for (int i = 0; i < numencomendas; i++) {
		hipermercadoencomendas >> dia >> mes >> ano >> fornecedor
				>> numlinhasencomendas >> produto >> quantidade >> preco;
		Data data(dia, mes, ano);
		int indicef, indicep;
		indicef = procurafornecedor(fornecedor);
		indicep = procuraproduto(produto);
		Hipermercado<int>::getInstance()->addEncomenda(Hipermercado::getInstance()->getFornecedores()[indicef],
				Hipermercado::getInstance()->getProdutos()[indicep], quantidade, preco);
		for (int j = 0; j < numlinhasencomendas - 1; j++) {
			hipermercadoencomendas >> produto >> medida >> quantidade >> preco;
			Hipermercado<int>::getInstance()->getEncomendas().at(
					Hipermercado<int>::getInstance()->getEncomendas().size() - 1)->addLinha(
							 new Produto(produto, medida), quantidade, preco);
		}
	}
}

void leFicheiros() {
	ifstream hipermercadoprodutos("produtos.txt");
	if (hipermercadoprodutos) {
		leProdutos(hipermercadoprodutos);
	} else {
		ofstream hipermercadoprodutos;
		hipermercadoprodutos.open("produtos.txt");
	}
	ifstream hipermercadofornecedores("fornecedores.txt");
	if (hipermercadofornecedores) {
		leFornecedores(hipermercadofornecedores);
	} else {
		ofstream hipermercado;
		hipermercado.open("fornecedores.txt");
		hipermercado.close();
	}
	ifstream hipermercadoencomendas("encomendas.txt");
	if (hipermercadoencomendas) {
		leEncomendas(hipermercadoencomendas);
	} else {
		ofstream hipermercado;
		hipermercado.open("encomendas.txt");
		hipermercado.close();
	}
}

//MENU INICIAL
void menuinicial() {
	cout << setw(40) << "HIPERMERCADOS" << endl << endl;
	cout << setw(20) << "Ecra principal: " << endl << endl;
	cout << setw(10) << "1 -  Ver produtos" << endl;
	cout << setw(10) << "2 -  Ver fornecedores" << endl;
	cout << setw(10) << "3 -  Ver encomendas" << endl;
	cout << setw(10) << "4 - Mudar nome do Hipermercado" << endl;
	opcoesmenu();
}

//OPCAO PRODUTOS DO MENU
void opcaoprodutos() {
	string nomeprod, unidadesprod, nomeprodeliminar;
	int opcao;
	cout << setw(20) << "Produtos: " << endl << endl;
	cout << setw(10) << "1 - Ver lista de produtos" << endl;
	cout << setw(10) << "2 - Adicionar produto" << endl;
	cout << setw(10) << "3 - Eliminar produto" << endl;
	cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 9)) {
		cout << "Opção inválida, volte a introduzir a opção pretendida pf"
				<< endl;
		cin >> opcao;
	}
	if (opcao == 1) {
		Hipermercado<int>::getInstance()->displayProdutos();
	} else if (opcao == 2) {
		cout << "Qual o nome e a medida do novo produto?" << endl;
		cin >> nomeprod;
		cin >> unidadesprod;
		Produto* produtof = new Produto(nomeprod, unidadesprod);
		Hipermercado<int>::getInstance()->addProduto(produtof);
	} else if (opcao == 3) {
		Hipermercado<int>::getInstance()->displayProdutos();
		cout << "Qual o numero do produto que quer eliminar ? ";
		int numprodeliminar;
		cin >> numprodeliminar;
		Hipermercado<int>::getInstance()->eliminaProduto(numprodeliminar);

	} else {
		menuinicial();
	}
}

//OPCAO FORNECEDORES DO MENU
void opcaofornecedores() {
	string nomenovo, moradanova, nifnovo, produtoaadicionar, unidades, novoprod,
			nomef, niff, moradaf, produtoaremover, nifaremover;

	int opcao, opcao2, opcao3, stock, numprodremover;

	cout << setw(20) << "Fornecedores: " << endl << endl;
	cout << setw(10) << "1 - Ver lista de fornecedores" << endl;
	cout << setw(10) << "2 - Adicionar fornecedor" << endl;
	cout << setw(10) << "3 - Alterar fornecedor" << endl;
	cout << setw(10) << "4 - Eliminar fornecedor" << endl;
	cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 9)) {
		cout << "Opção inválida, volte a introduzir a opção pretendida pf"
				<< endl;
		cin >> opcao;
	}
	if (opcao == 1) {
		Hipermercado<int>::getInstance()->displayFornecedores();
	} else if (opcao == 2) {
		cout << "Qual o nome , nif e morada do novo fornecedor? ";
		cin >> nomef >> niff >> moradaf;
		Hipermercado<int>::getInstance()->addFornecedor(new Fornecedor<int>(nomef, niff, moradaf));
	} else if (opcao == 3) {
		cout << setw(10) << "Introduza a opção pretendida pf" << endl;
		cout << setw(10) << "1 - Alterar nome do Fornecedor" << endl;
		cout << setw(10) << "2 - Alterar morada do Fornecedor" << endl;
		cout << setw(10) << "3 - Alterar NIF do Fornecedor" << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
		cin >> opcao2;

		while ((opcao2 != 1) && (opcao2 != 2) && (opcao2 != 3) && (opcao2 != 4)
				&& (opcao != 9)) {
			cout << setw(10)
					<< "Opção inválida, volte a introduzir a opção pretendida pf"
					<< endl;
			cin >> opcao2;
		}
		if (opcao == 1) {
			Hipermercado<int>::getInstance()->displayFornecedores();
			cout << setw(10)
					<< "Introduza o numero do fornecedor actual e o novo nome do fornecedor pf"
					<< endl;
			int numfornecedor1;
			cin >> numfornecedor1;
			cin >> nomenovo;
			Hipermercado<int>::getInstance()->getFornecedores()[numfornecedor1]->setNome(
					nomenovo);
		} else if (opcao == 2) {
			Hipermercado<int>::getInstance()->displayFornecedores();
			cout << setw(10)
					<< "Introduza numero do fornecedor que quer alterar e a nova morada do fornecedor pf"
					<< endl;
			int numfornecedor2;
			cin >> numfornecedor2;
			cin >> moradanova;
			Hipermercado<int>::getInstance()->getFornecedores()[numfornecedor2]->setMorada(
					moradanova);
		} else if (opcao == 3) {
			Hipermercado<int>::getInstance()->displayFornecedores();
			cout << setw(10)
					<< "Introduza numero do fornecedor que quer alterar e o novo nif do fornecedor pf"
					<< endl;
			int numfornecedor3;
			cin >> numfornecedor3;
			cin >> nifnovo;
			Hipermercado<int>::getInstance()->getFornecedores()[numfornecedor3]->setNIF(
					nifnovo);
	} else if (opcao == 4) {
		cout << setw(10)
				<< "Introduza o numero do fornecedor que quer eliminar pf"
				<< endl;
		int numforremover;
		cin >> numforremover;
		Hipermercado<int>::getInstance()->eliminaFornecedor(numforremover);
	} else {
		menuinicial();
	}
}
}

//OPCAO FORNECEDORES DO MENU
void opcaoencomendas() {
	int opcao;
	string nomeproduto, unidades;
	int quantidade, preco;
	cout << setw(20) << "Encomendas: " << endl << endl;
	cout << setw(10) << "Introduza a opção pretendida pf" << endl << endl;
	cout << setw(10) << "1 - Ver pedidos de encomendas realizadas" << endl;
	cout << setw(10) << "2 - Ver pedidos de encomendas por realizar" << endl;
	cout << setw(10) << "3 - Pedir nova encomenda" << endl;
	cout << setw(10) << "4 - Alterar encomenda (mudar o numero de produtos encomendados)" << endl;
	cout << setw(10) << "5 - Cancelar encomenda" << endl;
	cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 5) && (opcao != 9)) {
		cout << "Opção inválida, volte a introduzir a opção pretendida pf"
				<< endl;
		cin >> opcao;
	}
	if (opcao == 1) {
		Hipermercado<int>::getInstance()->displayPedidos();
	} else if (opcao == 2) {
		Hipermercado<int>::getInstance()->displayPedidosPorProcessar();
	} else if (opcao == 3) {
		vector<Produto*> produtos;
		vector<int> quantidade;
		int num, qnt;
		cout << "Insira o número do produto que quer encomendar pf";
		cin >> num;
		cout << "Qual a quantidade que quer encomendar deste produto?(Quando terminar de pedir encomendas insira f pf )";
		cin >> qnt;
		while (num != 'f') {
			//ADICIONAR PEDIDO DE ENCOMENDA
			vector<Produto *> produtosencomendas;
			vector <int> quantidades;
			cout << "Insira o número do produto que quer encomendar pf";
			cin >> num;
			cout << "Qual a quantidade que quer encomendar deste produto?";
			cin >> qnt;
			Produto* produtof = new Produto(Hipermercado<int>::getInstance()->getProdutos()[num]->getNome(),
					Hipermercado<int>::getInstance()->getProdutos()[num]->getMedida());
			produtosencomendas.push_back(produtof);
			quantidades.push_back(qnt);
			Hipermercado<int>::getInstance()->addPedido(new PedidoEncomenda<int>(dataactual, produtosencomendas, quantidades));
			}

	} else if (opcao == 4) {
		//mostrar lista de pedidos por realizar
		//funcao que altera pedido encomenda;
		Hipermercado<int>::getInstance()->displayPedidosPorProcessar();
		cout << "Qual o numero do pedido de encomenda que quer alterar?" << endl;
		int numalt;
		cin >> numalt;
		cout <<"Qual o produto do pedido de encomenda que quer alterar a sua quantidade?" << endl;
		string numproduto;
		cin >> numproduto;
		cout << "Qual a nova quantidade de produto do pedido de encomenda? " << endl;
		int novaquantidade;
		cin >> novaquantidade;
		Hipermercado<int>::getInstance()->alteraPedidos(numalt,numproduto,novaquantidade);

	} else if (opcao == 5) {
		//funcao que elimina pedido encomenda;
		Hipermercado<int>::getInstance()->displayPedidosPorProcessar();
		cout << "Qual o numero do pedido de encomenda que quer eliminar?";
		unsigned int numprodeliminar;
		cin >> numprodeliminar;
		Hipermercado<int>::getInstance()->eliminaProduto(numprodeliminar);
	} else {
		menuinicial();
	}

}

//OPCAO MUDAR NOME DO MENU
void opcaomudarnome() {
	int opcao;
	string novonome;
	cout << setw(10) << "Insira a opção pretendida pf" << endl
			<< "1 - Mudar nome do Hipermercado " << endl
			<< "9 - Voltar ao mene inicial" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 9)) {
		cout << "Opção inválida, volte a introduzir a opção pretendida pf"
				<< endl;
		cin >> opcao;
	}
	if (opcao == 1) {
		Hipermercado<int>::getInstance()->setNome(novonome);
	} else if (opcao == 9) {
		menuinicial();
	}
}

//MENU DE OPCOES
void opcoesmenu() {
	int opcao;
	cout << "Introduza a opção pretendida pf" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)) {
		cout << "Opção inválida, volte a introduzir a opção pretendida pf"
				<< endl;
		cin >> opcao;
	}
	if (opcao == 1) {
		opcaoprodutos();
	} else if (opcao == 2) {
		opcaofornecedores();
	} else if (opcao == 3) {
		opcaoencomendas();
	} else if (opcao == 4) {
		opcaomudarnome();
	};
}

void escreveProdutos(ifstream hipermercadoprodutos) {
	hipermercadoprodutos.close();
	remove("produtos.txt");
	ofstream hipermercado;
	hipermercado.open("produtos.txt");
	hipermercado << Hipermercado<int>::getInstance()->getProdutos().size()
			<< endl;
	for (int i = 0; i < Hipermercado<int>::getInstance()->getProdutos().size();
			i++) {
		hipermercado
				<< Hipermercado<int>::getInstance()->getProdutos()[i]->getNome()
				<< endl
				<< Hipermercado<int>::getInstance()->getProdutos()[i]->getMedida();
	}
	hipermercado.close();
}


void escreveFornecedores(ifstream hipermercadofornecedores) {
	hipermercadofornecedores.close();
	remove("fornecedores.txt");
	ofstream hipermercado;
	hipermercado.open("fornecedores.txt");
	hipermercado << Hipermercado<int>::getInstance()->getFornecedores().size()
			<< endl;
	for (int i = 0;
			i < Hipermercado<int>::getInstance()->getFornecedores().size();
			i++) {
		hipermercado
				<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getNome()
				<< endl
				<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getNIF()
				<< endl
				<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getMorada()
				<< endl
				<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn().size()
				<< endl;
		for (int j = 0;
				j
						< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn().size();
				j++) {
			hipermercado
					<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn()[j]->getProduto()->getNome()
					<< endl
					<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn()[j]->getProduto()->getMedida()
					<< endl
					<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn()[j]->getStock()
					<< endl;
			for (int l = 0;
					l
							< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn()[j]->getPatamares().size();
					l++) {
				hipermercado
						<< Hipermercado<int>::getInstance()->getFornecedores()[i]->getProdutosForn()[j]->getPatamares()[l]
						<< endl;
			}
		}
	}
	hipermercado.close();
}

void escreveEncomendas(ifstream hipermercadoencomendas) {
	remove("encomendas.txt");
	ofstream hipermercado;
	hipermercado.open("encomendas.txt");
	hipermercado << Hipermercado<int>::getInstance()->getPedidos().size()
			<< endl;
	for (int i = 0; i < Hipermercado<int>::getInstance()->getPedidos().size();
			i++) {
		hipermercado
				<< Hipermercado<int>::getInstance()->getPedidos()[i]->getData();
		<< endl << Hipermercado<int>::getInstance()->getPedidos()[i]->getFornecedor()
		<< endl;
		for (int j = 0; j
						< Hipermercado<int>::getInstance()->getPedidos()[i]->getProdutos().size();
				j++
			) {
				hipermercado
				<< Hipermercado<int>::getInstance()->getPedidos()[i]->getProdutos()[j]->getNome()
				<< endl
				<< Hipermercado<int>::getInstance()->getPedidos()[i]->getProdutos()[j]->getMedida()
				<< endl
				<< Hipermercado<int>::getInstance()->getPedidos()[i]->getQuantidade()[j]
				<< endl;

			}
		}
		hipermercado.close();
	}

void escreveFicheiros() {
	ifstream hipermercadoprodutos("produtos.txt");
	escreveProdutos(hipermercadoprodutos);
	ifstream hipermercadofornecedores("fornecedores.txt");
	escreveFornecedores(hipermercadofornecedores);
	ifstream hipermercadoencomendas("encomendas.txt");
	escreveEncomendas(hipermercadoencomendas);
}


int main() {
	leFicheiros();
	menuinicial();
	escreveFicheiros();
	return 0;
}
