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
	if (hipermercadoencomendas.is_open()) {
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
	for (int i = 0; i < numprodutos; i++) {
		hipermercadoprodutos >> nome >> unidade;
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

	for (int i = 0; i < numfornecedores; i++) {
		hipermercadoFornecedores >> nome >> nif >> morada >> tipo >> numprodutos;

		if(tipo == "FornecedorIndividual") hipermercado->addFornecedor(new FornecedorIndividual(nome, nif, morada));
		else hipermercado->addFornecedor(new FornecedorEmpresa(nome,nif,morada));

		for (int j = 0; j < numprodutos; j++) {
			hipermercadoFornecedores >> nomeProduto >> medida >> stock >> numpatamares;
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

		hipermercadoencomendas >> dia >> mes >> ano >> nomeFornecedor
			>> numlinhasencomendas >> nomeProduto >> quantidade >> preco;

		Data data(dia, mes, ano);
		indiceFornecedor = procuraFornecedor(hipermercado, nomeFornecedor);
		indiceProduto = procuraProduto(hipermercado, nomeProduto);

		Encomenda* encomenda = new Encomenda(hipermercado->getFornecedores().at(indiceFornecedor),hipermercado->getProdutos().at(indiceProduto),quantidade, preco,data);
		hipermercado->addEncomenda(encomenda);
		for (int j = 0; j < numlinhasencomendas - 1; j++) {
			hipermercadoencomendas >> nomeProduto >> quantidade >> preco;
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

			hipermercadopedidosencomendas >> nomeProduto >> quantidade;
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




void opcoesmenu(Hipermercado* hipermercado);

//MENU INICIAL
void menuinicial(Hipermercado* hipermercado) {
	cout << setw(40) << "HIPERMERCADO" << endl << endl;
	cout << setw(20) << "Ecra principal: " << endl << endl;
	cout << setw(10) << "1 - Ver produtos." << endl;
	cout << setw(10) << "2 - Ver fornecedores." << endl;
	cout << setw(10) << "3 - Ver encomendas." << endl;
	cout << setw(10) << "4 - Mudar nome do Hipermercado." << endl;
	cout << setw(10) << "9 - Terminar o programa." << endl;
	opcoesmenu(hipermercado);
}

void opcaoprodutos(Hipermercado* hipermercado);
void opcaofornecedores(Hipermercado* hipermercado);
void opcaoencomendas(Hipermercado* hipermercado);
void opcaomudarnome(Hipermercado* hipermercado);

//MENU DE OPCOES
void opcoesmenu(Hipermercado* hipermercado) {
	int opcao;

	//system("cls");
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
	}else if (opcao == 4) {
		opcaomudarnome(hipermercado);
	} else {
		cout << "Terminou o programa , obrigada pela sua visita!";
	}
}

//OPCAO PRODUTOS DO MENU
void opcaoprodutos(Hipermercado* hipermercado) {
	string nomeprod, unidadesprod;
	int opcao;

	do {
		//system("cls");
		cout << setw(20) << "Produtos: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de produtos." << endl;
		cout << setw(10) << "2 - Adicionar produto." << endl;
		cout << setw(10) << "3 - Eliminar produto." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: "
			<< flush;
			cin >> opcao;
		}

		if (opcao == 1) { hipermercado->displayProdutos(); }
		else if (opcao == 2) {

			cout << "Introduza o nome do produto: " << flush;
			cin >> nomeprod;
			cout << "Introduza a medida usada para o produto: " << flush;
			cin >> unidadesprod;
			Produto *produtof = new Produto(nomeprod, unidadesprod);
			hipermercado->addProduto(produtof);
			hipermercado->ordenaProdutos();

		} else if (opcao == 3) {

			hipermercado->displayProdutos();
			cout << "Qual o nome do produto que quer eliminar: " << flush;
			cin >> nomeprod;

			unsigned int indice;
			try {
				indice = procuraProduto(hipermercado, nomeprod);
			}catch (int erro) {
				cerr << "O produto que introduziu não existe." << endl;
				opcaoprodutos(hipermercado);
			}
			hipermercado->eliminaProduto(indice);

		} else { menuinicial(hipermercado); }
	}while(opcao != 9);
}

//OPCAO FORNECEDORES DO MENU
void opcaofornecedores(Hipermercado* hipermercado) {
	string nifnovo, produtoAdicionar, unidades, novoprod, niff, moradaFornecedor, produtoaremover, nifaremover, tipo, nomeFornecedor;
	unsigned int opcao, opcao2, opcao3, stock, numprodremover, indiceFornecedor, patminimo, patmaximo, preco;

	do {
		//system("cls");
		cout << setw(20) << "Fornecedores: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de fornecedores." << endl;
		cout << setw(10) << "2 - Adicionar fornecedor." << endl;
		cout << setw(10) << "3 - Alterar fornecedor." << endl;
		cout << setw(10) << "4 - Eliminar fornecedor." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: "
					<< flush;
			cin >> opcao;
		}

		if (opcao == 1) { hipermercado->displayFornecedores(); }
		else if (opcao == 2) {

			cout << "Introduza o tipo de fornecedor (Individual ou Empresa): " << flush;
			cin >> tipo;

			transform(tipo.begin(), tipo.end(), tipo.begin(), ptr_fun <int, int> (tolower));
			while((tipo != "individual") && (tipo != "empresa")) {
				cout << "Tipo de fornecedor invalido. Por favor, introduza novamente o tipo de fornecedor (Individual ou Empresa): " << flush;
				cin >> tipo;
				transform(tipo.begin(), tipo.end(), tipo.begin(), ptr_fun <int, int> (tolower));
			}

			cout << "Introduza o nome do novo fornecedor: " << flush;
			cin >> nomeFornecedor;
			cout << "Introduza o NIFF do novo fornecedor: " << flush;
			cin >> niff;
			cout << "Introduza o morada do novo fornecedor: " << flush;
			cin >> moradaFornecedor;

			if(tipo == "individual") hipermercado->addFornecedor(new FornecedorIndividual(nomeFornecedor, niff, moradaFornecedor));
			else hipermercado->addFornecedor(new FornecedorEmpresa(nomeFornecedor, niff, moradaFornecedor));

			hipermercado->ordenaFornecedores();
		} else if (opcao == 3) {

			do {
				cout << setw(10) << "Alterar Fornecedor:" << endl;
				cout << setw(10) << "1 - Alterar nome do Fornecedor" << endl;
				cout << setw(10) << "2 - Alterar NIF do Fornecedor" << endl;
				cout << setw(10) << "3 - Alterar morada do Fornecedor" << endl;
				cout << setw(10) << "4 - Adicionar produto." << endl;
				cout << setw(10) << "5 - Adicionar patamar a um produto." << endl;
				cout << setw(10) << "8 - Voltar ao menu fornecedores" << endl;
				cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
				cin >> opcao2;

				while ((opcao2 != 1) && (opcao2 != 2) && (opcao2 != 3) && (opcao2 != 8)
					   && (opcao2 != 9)) {
					cout << setw(10) << "Opcao invalida. Volte a introduzir a opcao pretendida: " << flush;
					cin >> opcao2;
				}

				if (opcao == 1) {

					hipermercado->displayFornecedores();
					cout << setw(10) << "Introduza o indice do fornecedor que pretende alterar o nome: " << flush;
					cin >> indiceFornecedor;

					cout << setw(10) << "Introduza o novo nome: " << flush;
					cin >> nomeFornecedor;

					hipermercado->getFornecedores().at(indiceFornecedor - 1)->setNome(nomeFornecedor);
					hipermercado->ordenaFornecedores();

				} else if (opcao == 2) {

					hipermercado->displayFornecedores();
					cout << setw(10) << "Introduza o indice do fornecedor que pretende alterar o NIFF: " << flush;
					cin >> indiceFornecedor;

					cout << setw(10) << "Introduza o novo NIFF: " << flush;
					cin >> niff;
					hipermercado->getFornecedores().at(indiceFornecedor - 1)->setNIF(niff);

				} else if (opcao == 3) {

					hipermercado->displayFornecedores();
					cout << setw(10) << "Introduza o indice do fornecedor que pretende alterar a morada: " << flush;
					cin >> indiceFornecedor;

					cout << setw(10) << "Introduza a nova morada: " << flush;
					cin >> moradaFornecedor;
					hipermercado->getFornecedores().at(indiceFornecedor - 1)->setNIF(moradaFornecedor);

				} else if (opcao == 4) {

					hipermercado->displayFornecedores();
					cout << setw(10) << "Introduza o indice do fornecedor ao qual pretende adicionar produto: " << flush;
					cin >> indiceFornecedor;

					cout << "Introduza o nome do produto: " << flush;
					cin >> produtoAdicionar;
					cout << "Introduza a medida utilizada: " << flush;
					cin >> unidades;
					cout << "Introduza o stock: " << flush;
					cin >> stock;

					hipermercado->getFornecedores().at(indiceFornecedor - 1)->addProduto(new Produto(produtoAdicionar,unidades), stock);

				} else if (opcao == 5) {

					hipermercado->displayFornecedoresEmp();
					cin >> indiceFornecedor;
					unsigned int indiceReal = 0, indiceProduto;

					while(indiceFornecedor != 0) {
						tipo = typeid(hipermercado->getFornecedores().at(indiceReal)).name();
						if(tipo == "FornecedorEmpresa") {
							indiceFornecedor--;
						}
						indiceReal++;
					}

					hipermercado->getFornecedores().at(indiceReal)->displayProdutosForn();
					cout << "Introduza o indice do produto ao qual quer adicionar o patamar: " << flush;
					cin >> indiceProduto;

					cout << "Introduza o limite minimo do patamar: " << flush;
					cin >> patminimo;
					cout << "Introduza o liminte maximo do patamar: " << flush;
					cin >> patmaximo;
					cout << "Introduza o preco: " << flush;
					cin >> preco;

					hipermercado->getFornecedores().at(indiceReal)->addPatamar(indiceProduto, patminimo, patmaximo, preco);
				} else if (opcao == 8) { opcaofornecedores(hipermercado); }
				else { menuinicial(hipermercado); }
			}while((opcao2 != 8) && (opcao2 != 9));
		}
		else if (opcao == 4) {

			hipermercado->displayFornecedores();
			cout << setw(10) << "Introduza o indice do fornecedor que quer eliminar: " << flush;
			cin >> indiceFornecedor;
			hipermercado->eliminaFornecedor(indiceFornecedor - 1);

		} else { menuinicial(hipermercado); }
	}while(opcao != 9);
}

//OPCAO FORNECEDORES DO MENU
void opcaoencomendas(Hipermercado* hipermercado) {
	int opcao;
	string nomeProduto, unidades;
	unsigned int quantidade, numProdutos, numPedido;
	float preco;

	do {
		//system("cls");
		cout << setw(20) << "Encomendas: " << endl << endl;
		cout << setw(10) << "1 - Ver encomendas realizadas." << endl;
		cout << setw(10) << "2 - Ver encomendas por realizar." << endl;
		cout << setw(10) << "3 - Pedir nova encomenda." << endl;
		cout << setw(10) << "4 - Alterar encomenda (mudar o numero de produtos encomendados)." << endl;
		cout << setw(10) << "5 - Cancelar encomenda." << endl;
		cout << setw(10) << "6 - Processar pedidos." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
				&& (opcao != 5) && (opcao != 9)) {
			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: " << flush;
			cin >> opcao;
		}

		if (opcao == 1) { hipermercado->displayEncomendas(); }
		else if (opcao == 2) { hipermercado->displayPedidosProcessados(); }
		else if (opcao == 3) {

			unsigned int indiceProduto;
			vector<Produto *> produtosencomendas;
			vector<unsigned int> quantidades;

			cout << "Introduza o numero de produtos que quer encomendar: " << flush;
			cin >> numProdutos;

			for(unsigned int i = 0; i < numProdutos; i++) {
				//ADICIONAR PEDIDO DE ENCOMENDA
				cout << "Insira o nome do produto que quer encomendar: " << flush;
				cin >> nomeProduto;

				try {
					indiceProduto = procuraProduto(hipermercado, nomeProduto);
				}catch (int erro) {
					cerr << "O produto que introduziu não existe." << endl;
					opcaoencomendas(hipermercado);
				}

				cout << "Introduza a quantidade que quer encomendar deste produto: " << flush;
				cin >> quantidade;

				Produto* produto = new Produto(nomeProduto,hipermercado->getProdutos().at(indiceProduto)->getMedida());
				produtosencomendas.push_back(produto);
				quantidades.push_back(quantidade);
			}
			hipermercado->addPedido(new PedidoEncomenda(dataactual, produtosencomendas, quantidades));
			hipermercado->ordenaPedidos();

		} else if (opcao == 4) {
			//mostrar lista de pedidos por realizar
			//funcao que altera pedido encomenda;
			hipermercado->displayPedidosPorProcessar();

			cout << "Introduza o numero do pedido de encomenda que quer alterar: " << flush;
			cin >> numPedido;

			cout <<"Introduza o nome do produto do pedido de encomenda que quer alterar a sua quantidade: " << flush;
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
			hipermercado->processaPedido();
		} else { menuinicial(hipermercado); }
	} while(opcao != 9);
}

//OPCAO MUDAR NOME DO MENU
void opcaomudarnome(Hipermercado* hipermercado) {
	int opcao;
	string novonome;

	do {
		//system("cls");
		cout << setw(10) << "Insira a opcao pretendida: " << endl
				<< "1 - Mudar nome do Hipermercado. " << endl
				<< "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		while ((opcao != 1) && (opcao != 9)) {

			cout << "Opcao invalida. Volte a introduzir a opcao pretendida: " << flush;
			cin >> opcao;
		}

		if (opcao == 1) {

			cout << "Introduza o novo nome do Hipermercado: " << flush;
			cin >> novonome;
			hipermercado->setNome(novonome);

		} else if (opcao == 9) { menuinicial(hipermercado); }
	}while(opcao != 9);
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
				<< hipermercado->getProdutos().at(i)->getMedida();
	}
	hipermercadoProdutos.close();
}


void escreveFornecedores(Hipermercado* hipermercado) {
	ofstream hipermercadoFornecedores;

	hipermercadoFornecedores.open("fornecedores.txt");

	hipermercadoFornecedores << hipermercado->getFornecedores().size() << endl;

	for (unsigned int i = 0;	i < hipermercado->getFornecedores().size(); i++) {

		hipermercadoFornecedores << hipermercado->getFornecedores().at(i)->getNome() << endl
				<< hipermercado->getFornecedores().at(i)->getNIF() << endl
				<< hipermercado->getFornecedores().at(i)->getMorada() << endl
				<< typeid(hipermercado->getFornecedores().at(i)).name() << endl
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
					<< hipermercado->getPedidos().at(i)->getData().getAno() << endl
					<< (hipermercado->getPedidos().at(i)->getFinalizado()) ? (hipermercadoPedidosEncomendas << "true") : (hipermercadoPedidosEncomendas << "false") << endl
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
