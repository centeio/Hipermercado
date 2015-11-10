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
#include <cctype>
#include <algorithm>
#include <ctime>
#include "Hipermercado.h"
using namespace std;

void leProdutos(Hipermercado* hipermercado, ifstream &hipermercadoprodutos);
void leFornecedores(Hipermercado* hipermercado, ifstream &hipermercadoFornecedores);
void leEncomendas(Hipermercado* hipermercado, ifstream &hipermercadoencomendas);
void lePedidosEncomendas(Hipermercado* hipermercado, ifstream& hipermercadopedidosencomendas);

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

	ifstream hipermercadopedidosencomendas("pedidosencomendas.txt");
	if (hipermercadopedidosencomendas.is_open()) {
		lePedidosEncomendas(hipermercado, hipermercadopedidosencomendas);
		hipermercadopedidosencomendas.close();
		remove("pedidosencomendas.txt");
	}


}

//LER PRODUTOS.TXT
void leProdutos(Hipermercado* hipermercado, ifstream &hipermercadoprodutos) {
	string nome, unidade;
	int numprodutos;

	hipermercadoprodutos >> numprodutos;
	hipermercadoprodutos.clear();
	hipermercadoprodutos.ignore(1000,'\n');
	for (int i = 0; i < numprodutos; i++) {
		getline(hipermercadoprodutos,nome);
		getline(hipermercadoprodutos, unidade);
		Produto* produto = new Produto(nome, unidade);
		hipermercado->addProduto(produto);
	}
}

//LER FORNECEDORES.TXT
void leFornecedores(Hipermercado* hipermercado, ifstream &hipermercadoFornecedores) {
	string nome, nif, morada, tipo, nomeProduto, medida;
	unsigned int stock, patminimo, patmaximo;
	float preco;
	int numfornecedores, numprodutos, numpatamares;

	hipermercadoFornecedores >> numfornecedores;
	hipermercadoFornecedores.clear();
	hipermercadoFornecedores.ignore(1000,'\n');
	for (int i = 0; i < numfornecedores; i++) {
		getline(hipermercadoFornecedores, nome);
		getline(hipermercadoFornecedores, nif);
		getline(hipermercadoFornecedores, morada);
		getline(hipermercadoFornecedores, tipo);
		hipermercadoFornecedores >> numprodutos;

		if(tipo == "Individual") hipermercado->addFornecedor(new FornecedorIndividual(nome, nif, morada));
		else hipermercado->addFornecedor(new FornecedorEmpresa(nome,nif,morada));

		for (int j = 0; j < numprodutos; j++) {
			hipermercadoFornecedores.clear();
			hipermercadoFornecedores.ignore(1000,'\n');
			getline(hipermercadoFornecedores, nomeProduto);
			getline(hipermercadoFornecedores, medida);
			hipermercadoFornecedores >> stock >> numpatamares;
			hipermercado->getFornecedores().at(i)->addProduto(new Produto(nomeProduto, medida),stock);

			for (int k = 0; k < numpatamares ; k++) {
				hipermercadoFornecedores >> patminimo >> patmaximo >> preco;
				hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->addPatamar(patminimo, patmaximo, preco);
			}
		}
	}
}


unsigned int procuraFornecedor(Hipermercado* hipermercado, string nome){

	for(unsigned int i = 0; i < hipermercado->getFornecedores().size(); i++ ){
		if(hipermercado->getFornecedores().at(i)->getNome() == nome)
			return i ;
	}
	throw -1;
}

unsigned int procuraProduto(Hipermercado* hipermercado, string nome){

	for(unsigned int i = 0; i < hipermercado->getProdutos().size(); i++ ){
		if(hipermercado->getProdutos().at(i)->getNome() == nome)
					return i ;
	}
	throw -1;
}

//LER ENCOMENDAS.TXT
void leEncomendas(Hipermercado* hipermercado, ifstream &hipermercadoencomendas) {
	string nomeFornecedor, nomeProduto;
	unsigned int dia, mes, ano;
	float preco;
	int numencomendas, numlinhasencomendas, indiceFornecedor, indiceProduto, quantidade;

	hipermercadoencomendas >> numencomendas;
	for (int i = 0; i < numencomendas; i++) {

		hipermercadoencomendas >> dia >> mes >> ano;
		hipermercadoencomendas.clear();
		hipermercadoencomendas.ignore(1000,'\n');
		getline(hipermercadoencomendas,nomeFornecedor);
		hipermercadoencomendas >> numlinhasencomendas;
		hipermercadoencomendas.clear();
		hipermercadoencomendas.ignore(1000,'\n');
		getline(hipermercadoencomendas,nomeProduto);
		hipermercadoencomendas >> quantidade >> preco;

		Data data(dia, mes, ano);
		indiceFornecedor = procuraFornecedor(hipermercado, nomeFornecedor);
		indiceProduto = procuraProduto(hipermercado, nomeProduto);

		Encomenda* encomenda = new Encomenda(hipermercado->getFornecedores().at(indiceFornecedor),hipermercado->getProdutos().at(indiceProduto),quantidade, preco,data);
		hipermercado->addEncomenda(encomenda);
		for (int j = 0; j < numlinhasencomendas - 1; j++) {
			hipermercadoencomendas.clear();
			hipermercadoencomendas.ignore(1000,'\n');
			getline(hipermercadoencomendas,nomeProduto);
			hipermercadoencomendas >> quantidade >> preco;
			hipermercado->getEncomendas().at(i)->addLinha(hipermercado->getProdutos().at(indiceProduto), quantidade, preco);
		}
	}
}

void lePedidosEncomendas(Hipermercado* hipermercado, ifstream& hipermercadopedidosencomendas) {
	unsigned int numPedidos, dia, mes, ano, numProdutos, quantidade, indiceProduto;
	string finalizado, nomeProduto;
	vector<Produto*> produtos;
	vector<unsigned int> quantidades;

	hipermercadopedidosencomendas >> numPedidos;
	for(unsigned int i = 0; i < numPedidos; i++) {

		hipermercadopedidosencomendas >> dia >> mes >> ano >> finalizado >> numProdutos;
		Data data(dia,mes,ano);

		for(unsigned int j = 0; j < numProdutos; j++) {

			hipermercadopedidosencomendas.clear();
			hipermercadopedidosencomendas.ignore(1000,'\n');
			getline(hipermercadopedidosencomendas, nomeProduto);
			hipermercadopedidosencomendas >> quantidade;
			indiceProduto = procuraProduto(hipermercado, nomeProduto);
			produtos.push_back(hipermercado->getProdutos().at(indiceProduto));
			quantidades.push_back(quantidade);
		}

		PedidoEncomenda* pedido = new PedidoEncomenda(data, produtos, quantidades);
		hipermercado->addPedido(pedido);

		if(finalizado == "true") hipermercado->getPedidos().at(hipermercado->getPedidos().size() - 1)->setFinalizado(true);
		else hipermercado->getPedidos().at(hipermercado->getPedidos().size() - 1)->setFinalizado(false);
	}
}




void opcaoprodutos(Hipermercado* hipermercado);
void opcaofornecedores(Hipermercado* hipermercado);
void opcaoencomendas(Hipermercado* hipermercado);
void opcaomudarnome(Hipermercado* hipermercado);

//MENU INICIAL
void menuinicial(Hipermercado* hipermercado) {
	unsigned int opcao;
	string noveNomeHipermercado;

	do {
		//system("cls");
		cout << setw(40) << "HIPERMERCADO" << " " << hipermercado->getNome() << endl << endl;
		cout << setw(20) << "Ecra principal: " << endl << endl;
		cout << setw(10) << "1 - Menu produtos." << endl;
		cout << setw(10) << "2 - Menu fornecedores." << endl;
		cout << setw(10) << "3 - Menu encomendas." << endl;
		cout << setw(10) << "4 - Mudar nome do Hipermercado." << endl;
		cout << setw(10) << "9 - Terminar o programa." << endl;

		cout << "Introduza a opcao pretendida: " << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) && (opcao != 5) && (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: "
			<< flush;
			cin >> opcao;
		}

		if (opcao == 1) {
			opcaoprodutos(hipermercado);
		} else if (opcao == 2) {
			opcaofornecedores(hipermercado);
		} else if (opcao == 3) {
			opcaoencomendas(hipermercado);
		} else if (opcao == 4) {
			cout << "Introduza o novo nome do hipermercado: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin,noveNomeHipermercado);
			hipermercado->setNome(noveNomeHipermercado);
		} else {
			cout << "Terminou o programa, obrigados pela sua visita!";
		}
	}while(opcao != 9);
}

//OPCAO PRODUTOS DO MENU
void opcaoprodutos(Hipermercado* hipermercado) {
	string unidadesprod, nomeProd;
	unsigned int opcao, indiceProduto;

	do {
		//system("cls");
		cout << setw(20) << "Menu Produtos: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de produtos." << endl;
		cout << setw(10) << "2 - Ver lista de produtos ordenados." << endl;
		cout << setw(10) << "3 - Adicionar produto." << endl;
		cout << setw(10) << "4 - Alterar nome de um produto." << endl;
		cout << setw(10) << "5 - Alterar medida usada para um produto." << endl;
		cout << setw(10) << "6 - Eliminar produto." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) && (opcao != 5) && (opcao != 6) && (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: "
			<< flush;
			cin >> opcao;
		}

		if (opcao == 1) {
			hipermercado->displayProdutos();
			//system("pause");
		} else if (opcao == 2) {
			hipermercado->ordenaProdutos();
			hipermercado->displayProdutos();
			//system("pause");
		}
		else if (opcao == 3) {

			cout << "Introduza o nome do produto: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin,nomeProd);
			cout << "Introduza a medida usada para o produto: " << flush;
			getline(cin,unidadesprod);

			Produto *produtof = new Produto(nomeProd, unidadesprod);
			hipermercado->addProduto(produtof);

		} else if (opcao == 4) {

			hipermercado->displayProdutos();
			cout << "Qual o indice do produto que quer alterar: " << flush;
			cin >> indiceProduto;

			while((indiceProduto <= 0) || (indiceProduto > hipermercado->getProdutos().size())) {
				if(indiceProduto == 0) opcaoprodutos(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceProduto;
			}

			cout << "Introduza o novo nome: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, nomeProd);

			hipermercado->alteraNomeProduto(indiceProduto - 1, nomeProd);
		} else if (opcao == 5) {

			hipermercado->displayProdutos();
			cout << "Qual o indice do produto que quer alterar: " << flush;
			cin >> indiceProduto;

			while((indiceProduto <= 0) || (indiceProduto > hipermercado->getProdutos().size())) {
				if(indiceProduto == 0) opcaoprodutos(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceProduto;
			}

			cout << "Introduza a nova medida: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, unidadesprod);

			hipermercado->alteraMedidaProduto(indiceProduto - 1, unidadesprod);
		} else if (opcao == 6) {

			hipermercado->displayProdutos();
			cout << "Qual o indice do produto que quer eliminar: " << flush;
			cin >> indiceProduto;

			while((indiceProduto <= 0) || (indiceProduto > hipermercado->getProdutos().size())) {
				if(indiceProduto == 0) opcaoprodutos(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceProduto;
			}
			hipermercado->eliminaProduto(indiceProduto - 1);

		} else { return; }
	}while(opcao != 9);
}

void alteraFornecedor(Hipermercado* hipermercado);

//OPCAO FORNECEDORES DO MENU
void opcaofornecedores(Hipermercado* hipermercado) {
	string nomeFornecedor, nif, moradaFornecedor, tipo;
	unsigned int opcao, indiceFornecedor;

	do {
		//system("cls");
		cout << setw(20) << "Menu Fornecedores: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de fornecedores." << endl;
		cout << setw(10) << "2 - Ver lista de fornecedores ordenados." << endl;
		cout << setw(10) << "3 - Ver lista de produtos de um fornecedor." << endl;
		cout << setw(10) << "4 - Ver lista de produtos de todos os fornecedores." << endl;
		cout << setw(10) << "5 - Adicionar fornecedor." << endl;
		cout << setw(10) << "6 - Alterar fornecedor." << endl;
		cout << setw(10) << "7 - Eliminar fornecedor." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) && (opcao != 5) && (opcao != 6) && (opcao != 7)
			&& (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: " << flush;
			cin >> opcao;
		}

		if (opcao == 1) {
			hipermercado->displayFornecedores();
			//system("pause");
			}
		else if(opcao == 2) {
			hipermercado->ordenaFornecedores();
			hipermercado->displayFornecedores();
			//system("pause");
		} else if (opcao == 3) {
			hipermercado->displayFornecedores();

			cout << setw(10) << "Introduza o indice do fornecedor: " << flush;
			cin >> indiceFornecedor;

			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) opcaofornecedores(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			hipermercado->getFornecedores().at(indiceFornecedor - 1)->displayProdutosForn();
		} else if(opcao == 4) {
			hipermercado->displayProdutosFornecedor();
		}
		else if (opcao == 5) {

			cout << "Introduza o tipo de fornecedor (Individual ou Empresa): " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, tipo);

			transform(tipo.begin(), tipo.end(), tipo.begin(), ptr_fun <int, int> (tolower));
			while((tipo != "individual") && (tipo != "empresa")) {
				cout << "Tipo de fornecedor invalido. Por favor, introduza novamente o tipo de fornecedor (Individual ou Empresa): " << flush;
				getline(cin, tipo);
				transform(tipo.begin(), tipo.end(), tipo.begin(), ptr_fun <int, int> (tolower));
			}

			cout << "Introduza o nome do novo fornecedor: " << flush;
			getline(cin, nomeFornecedor);
			cout << "Introduza o NIF do novo fornecedor: " << flush;
			getline(cin, nif);
			cout << "Introduza o morada do novo fornecedor: " << flush;
			getline(cin, moradaFornecedor);

			if(tipo == "individual") hipermercado->addFornecedor(new FornecedorIndividual(nomeFornecedor, nif, moradaFornecedor));
			else hipermercado->addFornecedor(new FornecedorEmpresa(nomeFornecedor, nif, moradaFornecedor));

		} else if (opcao == 6) {
			alteraFornecedor(hipermercado);
		}
		else if (opcao == 7) {

			hipermercado->displayFornecedores();
			cout << setw(10) << "Introduza o indice do fornecedor que quer eliminar: " << flush;
			cin >> indiceFornecedor;

			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) opcaofornecedores(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			hipermercado->eliminaFornecedor(indiceFornecedor - 1);

		} else { return; }
	}while(opcao != 9);
}

void alteraFornecedor(Hipermercado* hipermercado) {
	unsigned int opcao2, indiceFornecedor, stock, patminimo, patmaximo;
	string nomeFornecedor, nif, unidades, moradaFornecedor, produtoAdicionar, tipo;
	float preco;

	do {
		cout << setw(10) << "Menu Alterar Fornecedor:" << endl;
		cout << setw(10) << "1 - Alterar nome do Fornecedor" << endl;
		cout << setw(10) << "2 - Alterar NIF do Fornecedor" << endl;
		cout << setw(10) << "3 - Alterar morada do Fornecedor" << endl;
		cout << setw(10) << "4 - Adicionar produto." << endl;
		cout << setw(10) << "5 - Adicionar patamar a um produto." << endl;
		cout << setw(10) << "9 - Voltar ao menu fornecedores" << endl;
		cin >> opcao2;

		while ((opcao2 != 1) && (opcao2 != 2) && (opcao2 != 3) && (opcao2 != 4) && (opcao2 != 5)
			   && (opcao2 != 9)) {
			cout << setw(10) << "Opcao invalida. Volte a introduzir a opcao pretendida: " << flush;
			cin >> opcao2;
		}

		if (opcao2 == 1) {

			hipermercado->displayFornecedores();
			cout << setw(10) << "Introduza o indice do fornecedor que pretende alterar o nome: " << flush;
			cin >> indiceFornecedor;

			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) alteraFornecedor(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			cout << setw(10) << "Introduza o novo nome: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, nomeFornecedor);

			hipermercado->getFornecedores().at(indiceFornecedor - 1)->setNome(nomeFornecedor);

		} else if (opcao2 == 2) {

			hipermercado->displayFornecedores();
			cout << setw(10) << "Introduza o indice do fornecedor que pretende alterar o NIFF: " << flush;
			cin >> indiceFornecedor;

			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) alteraFornecedor(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			cout << setw(10) << "Introduza o novo NIFF: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, nif);
			hipermercado->getFornecedores().at(indiceFornecedor - 1)->setNIF(nif);

		} else if (opcao2 == 3) {

			hipermercado->displayFornecedores();
			cout << setw(10) << "Introduza o indice do fornecedor que pretende alterar a morada: " << flush;
			cin >> indiceFornecedor;

			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) alteraFornecedor(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			cout << setw(10) << "Introduza a nova morada: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, moradaFornecedor);
			hipermercado->getFornecedores().at(indiceFornecedor - 1)->setMorada(moradaFornecedor);

		} else if (opcao2 == 4) {

			hipermercado->displayFornecedores();
			cout << setw(10) << "Introduza o indice do fornecedor ao qual pretende adicionar produto: " << flush;
			cin >> indiceFornecedor;

			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) alteraFornecedor(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			cout << "Introduza o nome do produto: " << flush;
			cin.clear();
			cin.ignore(1000,'\n');
			getline(cin, produtoAdicionar);
			cout << "Introduza a medida utilizada: " << flush;
			getline(cin, unidades);
			cout << "Introduza o stock: " << flush;
			cin >> stock;

			hipermercado->getFornecedores().at(indiceFornecedor - 1)->addProduto(new Produto(produtoAdicionar,unidades), stock);

		} else if (opcao2 == 5) {
			unsigned int indiceProduto;

			hipermercado->displayFornecedores();
			cout << "Introduza o indice do fornecedor: " << flush;
			cin >> indiceFornecedor;
			while((indiceFornecedor <= 0) || (indiceFornecedor > hipermercado->getFornecedores().size())) {
				if(indiceFornecedor == 0) alteraFornecedor(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceFornecedor;
			}

			hipermercado->getFornecedores().at(indiceFornecedor - 1)->displayProdutosForn();
			cout << "Introduza o indice do produto ao qual quer adicionar o patamar: " << flush;
			cin >> indiceProduto;

			while((indiceProduto <= 0) || (indiceProduto > hipermercado->getFornecedores().at(indiceFornecedor - 1)->getProdutosForn().size())) {
				if(indiceFornecedor == 0) alteraFornecedor(hipermercado);
				cerr << "Indice invalido. Por favor, introduza um indice valido ou 0 para sair: " << flush;
				cin >> indiceProduto;
			}

			cout << "Introduza o limite minimo do patamar: " << flush;
			cin >> patminimo;
			cout << "Introduza o limite maximo do patamar: " << flush;
			cin >> patmaximo;
			cout << "Introduza o preco: " << flush;
			cin >> preco;

			try {
				hipermercado->getFornecedores().at(indiceFornecedor - 1)->addPatamar(indiceProduto - 1, patminimo, patmaximo, preco);
			}catch(DemasiadosPatamares& p) {
				cerr << "Não e possivel adicionar mais do que um patamar a um fornecedor individual." << endl;
				alteraFornecedor(hipermercado);
			}
		} else { return; }
	}while((opcao2 != 9));
}

//OPCAO FORNECEDORES DO MENU
void opcaoencomendas(Hipermercado* hipermercado) {
	int opcao;
	string nomeProduto, unidades;
	unsigned int quantidade, numProdutos, numPedido, numProduto;
	float preco;
	bool b;

	do {
		//system("cls");
		cout << setw(20) << "Encomendas: " << endl << endl;
		cout << setw(10) << "1 - Ver encomendas realizadas." << endl;
		cout << setw(10) << "2 - Ver encomendas por realizar." << endl;
		cout << setw(10) << "3 - Pedir nova encomenda." << endl;
		cout << setw(10) << "4 - Alterar encomenda." << endl;
		cout << setw(10) << "5 - Cancelar encomenda." << endl;
		cout << setw(10) << "6 - Processar pedidos." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			   && (opcao != 5) && (opcao != 6) && (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: " << flush;
			cin >> opcao;
		}

		if (opcao == 1) {
			hipermercado->displayEncomendas();
			//system("pause");
			}
		else if (opcao == 2) {
			hipermercado->displayPedidosPorProcessar();
			//system("pause");
			}
		else if (opcao == 3) {

			unsigned int indiceProduto;
			vector<Produto *> produtosencomendas;
			vector<unsigned int> quantidades;

			do
			{
				//ADICIONAR PEDIDO DE ENCOMENDA
				b=true;
				hipermercado->displayProdutos();
				cout << "Para terminar carregue 0. Insira o indice do produto que quer encomendar: " << flush;
				cin >> indiceProduto;

				if(indiceProduto>0 && indiceProduto<=hipermercado->getProdutos().size()){
					cout << "Introduza a quantidade que quer encomendar deste produto: " << flush;
					cin >> quantidade;
					produtosencomendas.push_back(hipermercado->getProdutos().at(indiceProduto-1));
					quantidades.push_back(quantidade);
				}
				else
				if(indiceProduto==0){
					if(produtosencomendas.size()!=0)
						hipermercado->addPedido(new PedidoEncomenda(dataactual, produtosencomendas, quantidades));
					opcaoencomendas(hipermercado);
					b=false;}
				else{
					//system("cls");
					cout<<"O produto que introduziu não existe." << endl;
				}
				cin.clear();
				cin.ignore(1000,'\n');
			}while(b==true);

		} else if (opcao == 4) {
			//mostrar lista de pedidos por realizar
			//funcao que altera pedido encomenda;
			hipermercado->displayPedidosPorProcessar();

			cout << "Introduza o indice do pedido de encomenda que quer alterar: " << flush;
			cin >> numPedido;

			cout <<"Introduza o indice do produto do pedido de encomenda que quer alterar a sua quantidade: " << flush;
			cin >> nomeProduto;

			cout << "Qual a nova quantidade de produto do pedido de encomenda: " << flush;;
			cin >> quantidade;
			//esta função não existe
			//hipermercado->alteraPedidos(numPedido,nomeProduto,quantidade);

		} else if (opcao == 5) {
			//funcao que elimina pedido encomenda;
			hipermercado->displayPedidosPorProcessar();

			cout << "Introduza o numero do pedido de encomenda que quer eliminar: " << flush;
			cin >> numPedido;
			hipermercado->eliminaPedido(numPedido-1);

		}else if (opcao == 6) {
			try {hipermercado->processaPedido();}
			catch(PedidoEncomenda::ProdutoNaoEstaAVenda& p1){
				opcaoencomendas(hipermercado);
			}
			catch(PedidoEncomenda::ProdutoParcialmenteComprado& p2){
				opcaoencomendas(hipermercado);
			}		} else { return; }
	} while(opcao != 9);
}

void escreveProdutos(Hipermercado* hipermercado);
void escreveFornecedores(Hipermercado* hipermercado);
void escreveEncomendas(Hipermercado* hipermercado);
void escrevePedidosEncomendas(Hipermercado* hipermercado);

void escreveFicheiros(Hipermercado* hipermercado) {


	escreveProdutos(hipermercado);
	escreveFornecedores(hipermercado);
	escreveEncomendas(hipermercado);
	escrevePedidosEncomendas(hipermercado);
}

void escreveProdutos(Hipermercado* hipermercado) {
	ofstream hipermercadoProdutos;

	hipermercadoProdutos.open("produtos.txt");
	hipermercadoProdutos << hipermercado->getProdutos().size() << endl;

	for (unsigned int i = 0; i < hipermercado->getProdutos().size();i++) {
		hipermercadoProdutos << hipermercado->getProdutos().at(i)->getNome() << endl
				<< hipermercado->getProdutos().at(i)->getMedida() << endl;
	}
	hipermercadoProdutos.close();
}


void escreveFornecedores(Hipermercado* hipermercado) {
	ofstream hipermercadoFornecedores;

	hipermercadoFornecedores.open("fornecedores.txt");

	hipermercadoFornecedores << hipermercado->getFornecedores().size() << endl;

	for (unsigned int i = 0; i < hipermercado->getFornecedores().size(); i++) {

		hipermercadoFornecedores << hipermercado->getFornecedores().at(i)->getNome() << endl
				<< hipermercado->getFornecedores().at(i)->getNIF() << endl
				<< hipermercado->getFornecedores().at(i)->getMorada() << endl
				<< hipermercado->getFornecedores().at(i)->getTipo() << endl
				<< hipermercado->getFornecedores().at(i)->getProdutosForn().size() << endl;

		for (unsigned int j = 0;	j < hipermercado->getFornecedores().at(i)->getProdutosForn().size();j++) {

			hipermercadoFornecedores << hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getProduto()->getNome() << endl
					<< hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getProduto()->getMedida() << endl
					<< hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getStock() << endl
					<<  hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().size() << endl;

			for (unsigned int k = 0;k < hipermercado->getFornecedores().at(i)->getProdutosForn().at(j)->getPatamares().size(); k++) {

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

	hipermercadoEncomendas << hipermercado->getEncomendas().size() << endl;

	for (unsigned int i = 0; i < hipermercado->getEncomendas().size(); i++) {

		hipermercadoEncomendas << hipermercado->getEncomendas().at(i)->getData().getDia() << endl
				<< hipermercado->getEncomendas().at(i)->getData().getMes() << endl
				<< hipermercado->getEncomendas().at(i)->getData().getAno() << endl
				<< hipermercado->getEncomendas().at(i)->getFornecedor()->getNome() << endl
				<< hipermercado->getEncomendas().at(i)->getLinhas().size() << endl;

		for (unsigned int j = 0; j < hipermercado->getEncomendas().at(i)->getLinhas().size(); j++) {

			hipermercadoEncomendas << hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getProduto()->getNome() << endl
					<< hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getProduto()->getMedida() << endl
					<< hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getQuantidade() << endl
					<< hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getPreco() << endl;
		}
	}
	hipermercadoEncomendas.close();
}

void escrevePedidosEncomendas(Hipermercado* hipermercado) {
	ofstream hipermercadoPedidosEncomendas;

	hipermercadoPedidosEncomendas.open("pedidosencomendas.txt");

	hipermercadoPedidosEncomendas << hipermercado->getPedidos().size() << endl;

	for(unsigned int i = 0; i < hipermercado->getPedidos().size(); i++) {

		hipermercadoPedidosEncomendas << hipermercado->getPedidos().at(i)->getData().getDia() << endl
					<< hipermercado->getPedidos().at(i)->getData().getMes() << endl
					<< hipermercado->getPedidos().at(i)->getData().getAno() << endl;
		if(hipermercado->getPedidos().at(i)->getFinalizado()) (hipermercadoPedidosEncomendas << "true");
		else (hipermercadoPedidosEncomendas << "false");
		hipermercadoPedidosEncomendas << endl
					<< hipermercado->getPedidos().at(i)->getProdutos().size() << endl;

		for(unsigned int j = 0; j < hipermercado->getPedidos().at(i)->getProdutos().size(); j++) {

			hipermercadoPedidosEncomendas << hipermercado->getPedidos().at(i)->getProdutos().at(j)->getNome() << endl
					<< hipermercado->getPedidos().at(i)->getQuantidade().at(j) << endl;
		}
	}

}

int main() {
	Hipermercado* hipermercado = Hipermercado::getInstance();

	//inicializando a data
	time_t now = time(0);
	tm *date = localtime(&now);
	dataactual.setDia(date->tm_mday);
	dataactual.setMes(1 + date->tm_mon);
	dataactual.setAno(1900 + date->tm_year);

	leFicheiros(hipermercado);
	menuinicial(hipermercado);
	escreveFicheiros(hipermercado);
	return 0;
}
