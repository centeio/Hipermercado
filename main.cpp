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
		Hipermercado<int>::getInstance()->getProdutos()->addProduto(produtof);
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
		Hipermercado<int>::getInstance()->addFornecedor(nome, nif, morada);
		for (int j = 0; j < numprodutos; j++) {
			hipermercadofornecedores >> numproduto >> produtos >> medida
					>> stock >> numpatamares >> patminimo >> patmaximo >> preco;
			Produto* produtof = new Produto(produtos, medida);
			vector<Patamar*> patamares;
			Patamar* patamar = new Patamar(patminimo, patmaximo, preco);
			patamares.push_back(patamar);
			Hipermercado<int>::getInstance()->getFornecedores.at(
					Hipermercado<int>::getInstance()->getFornecedores.size()
							- 1)->addProduto(produtof, stock, patamares);
			for (int k = 0; k < numpatamares - 1; k++) {
				hipermercadofornecedores >> patminimo >> patmaximo >> preco;
				Hipermercado<int>::getInstance()->fornecedores.at(
						Hipermercado<int>::getInstance()->fornecedores.size()
								- 1).getProdutos.at(
						Hipermercado<int>::getInstance()->fornecedores.at(
								Hipermercado<int>::getInstance()->fornecedores.size()
										- 1).getProdutos.size() - 1).addPatamar(
						patminimo, patmaximo, preco);
			}
		}
	}
}

//LER ENCOMENDAS.TXT
void leEncomendas(ifstream hipermercadoencomendas) {
	string fornecedor, produto, quantidade, preco, dia, mes, ano, medida;
	int numencomendas, numprodutos;
	hipermercadoencomendas >> numencomendas;
	for (int i = 0; i < numencomendas; i++) {
		hipermercadoencomendas >> dia >> mes >> ano >> fornecedor
				>> numprodutos;
		Data dataactual(dia, mes, ano);
		Encomenda* encomendaf = new Encomenda(fornecedor, produto, quantidade);
		Hipermercado<int>::getInstance()->addEncomenda(encomendaf);
		for (int j = 0; j < numprodutos; j++) {
			hipermercadoencomendas >> produto >> medida >> quantidade >> preco;
			Produto* produtof = new Produto(produto, medida);
			Hipermercado<int>::getInstance()->getEncomendas.at(
					Hipermercado<int>::getInstance()->getEncomendas.size() - 1)->addLinhaEncomenda(
					produtof, quantidade, preco);
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
		Hipermercado<int>::getInstance()->getProdutos()->addProduto(produtof);
	} else if (opcao == 3) {
		cout << "Qual o numero do produto que quer eliminar ? ";
		int numprodeliminar;
		cin >> numprodeliminar;
		Hipermercado<int>::getInstance()->getProdutos()->eliminaProduto(
				Hipermercado<int>::getInstance()->getProdutos()[numprodeliminar]);
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
		//funcao que mostra lista de fornecedores;
	} else if (opcao == 2) {
		cout << "Qual o nome , nif e morada do novo fornecedor? ";
		cin >> nomef >> niff >> moradaf;
		Fornecedor* fornecedorn = new Fornecedor(nomef, niff, moradaf);
		Hipermercado<int>::getInstance()->addFornecedor(fornecedorn);
	} else if (opcao == 3) {
		cout << setw(10) << "Introduza a opção pretendida pf" << endl;
		cout << setw(10) << "1 - Alterar nome do Fornecedor" << endl;
		cout << setw(10) << "2 - Alterar morada do Fornecedor" << endl;
		cout << setw(10) << "3 - Alterar NIF do Fornecedor" << endl;
		cout << setw(10) << "4 - Alterar produtos do Fornecedor" << endl;
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
			cout << setw(10)
					<< "Introduza o numero do fornecedor actual e o novo nome do fornecedor pf"
					<< endl;
			int numfornecedor1;
			cin >> numfornecedor1;
			cin >> nomenovo;
			//PROCURA INDICE DO FORNECEDOR DO NOME ANTIGO E ALTERA
			Hipermercado<int>::getInstance()->getFornecedores()[numfornecedor1]->setNome(
					nomenovo);
		} else if (opcao == 2) {
			cout << setw(10)
					<< "Introduza numero do fornecedor que quer alterar e a nova morada do fornecedor pf"
					<< endl;
			int numfornecedor2;
			cin >> numfornecedor2;
			cin >> moradanova;
			Hipermercado<int>::getInstance()->getFornecedores()[numfornecedor2]->setMorada(
					moradanova);
		} else if (opcao == 3) {
			cout << setw(10)
					<< "Introduza numero do fornecedor que quer alterar e o novo nif do fornecedor pf"
					<< endl;
			int numfornecedor3;
			cin >> numfornecedor3;
			cin >> nifnovo;
			Hipermercado<int>::getInstance()->getFornecedores()[numfornecedor3]->setNIF(
					nifnovo);
		} else if (opcao == 4) {
			Hipermercado<int>::getInstance()->getFornecedores()[1]->displayProdutosForn();
			cout << setw(10) << "Introduza a opção pretendida pf" << endl;
			cout << setw(10) << "1 - Adiciona produto" << endl;
			cout << setw(10) << "2 - Altera produto" << endl;
			cout << setw(10) << "3 - Remove produto" << endl;
			cout << setw(10) << "9 - Voltar ao menu inicial" << endl;
			cin >> opcao3;
			while ((opcao3 != 1) && (opcao3 != 2) && (opcao3 != 3)
					&& (opcao != 9)) {
				cout << setw(10)
						<< "Opção inválida, volte a introduzir a opção pretendida pf"
						<< endl;
				cin >> opcao3;
			}
			if (opcao == 1) {
				cout << setw(10)
						<< "Introduza o nome do produto e o tipo de medida( unidades/kgs/lts/...)que quer adicionar pf"
						<< endl;
				cin >> produtoaadicionar;
				cin >> unidades;
				cin >> stock;
				Produto* produton = new Produto(produtoaadicionar, unidades);
				//Hipermercado<int>::getInstance()->addProduto(produton, stock, ?? );
			} else if (opcao == 2) {
				cout << setw(10)
						<< "Introduza o novo nome do produto a alterar pf"
						<< endl;
				cin >> novoprod;
				//FUNCAO QUE ADICIONA PRODUTO AO FORNECEDOR
			} else if (opcao == 9) {
				menuinicial();
			} else {
				cout << setw(10)
						<< "Introduza o numero do produto que quer remover pf"
						<< endl;
				cin >> numprodremover;
				//ciclo que procura na funcao
				//FUNCAO QUE ELIMINA PRODUTO DO FORNECEDOR
				Hipermercado<int>::getInstance()->remProduto(
						Hipermercado<int>::getInstance()->getProdutos()[numprodremover]);
			}
		}
	} else if (opcao == 4) {
		cout << setw(10)
				<< "Introduza o numero do fornecedor que quer eliminar pf"
				<< endl;
		int numforremover;
		cin >> numforremover;
		//Hipermercado<int>::getInstance()->removeFornecedor(Hipermercado<int>::getInstance()->getFornecedores()[numforremover]);
	} else {
		menuinicial();
	}
}

//OPCAO FORNECEDORES DO MENU
void opcaoencomendas() {
	int opcao;
	string nomeproduto, unidades;
	int quantidade, preco;
	cout << setw(20) << "Encomendas: " << endl << endl;
	cout << setw(10) << "Introduza a opção pretendida pf" << endl << endl;
	cout << setw(10) << "1 - Ver encomendas realizadas" << endl;
	cout << setw(10) << "2 - Ver encomendas por realizar" << endl;
	cout << setw(10) << "3 - Pedir nova encomenda" << endl;
	cout << setw(10) << "4 - Alterar encomenda" << endl;
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
//funcao que mostra a lista de encomendas realizadas;
	} else if (opcao == 2) {
//funcao que mostra a lista de encomendas por realizar;
	} else if (opcao == 3) {
		//vector<Produto*> produtos;
		//vector<T> quantidade;
		int num, qnt;
		cout << "Insira o número do produto que quer encomendar pf";
		cin >> num;
		cout << "Qual a quantidade que quer encomendar deste produto?";
		cin >> qnt;
		while (num != 'f') {
			cout << "Insira o número do produto que quer encomendar pf";
			cin >> num;
			//produtos.push_back(num);
			cout << "Qual a quantidade que quer encomendar deste produto?";
			cin >> qnt;
			//quantidade.pus_back(qnt);
		}

		Produto* produtof = new Produto(nomeproduto, unidades);
//ADICIONAR PEDIDO DE ENCOMENDA
	} else if (opcao == 4) {
		cout << "Introduza a opção pretendida pf" << endl;
		cout << "1- Mudar o numero de produtos encomendados" << endl;
//funcao que altera pedido encomenda;
	} else if (opcao == 5) {
		cout << "Qual o numero do pedido de encomenda que quer eliminar?";
		int numprodeliminar;
		cin >> numprodeliminar;
//funcao que elimina pedido encomenda;
		Hipermercado<int>::getInstance()->getPedidos()->eliminaProduto(
				Hipermercado<int>::getInstance()->getPedidos()[numprodeliminar]);
	} else {
		menuinicial();
	}

}

//OPCAO MUDAR NOME DO MENU
void opcaomudarnome() {
	string novonome;
	cout << setw(10)
			<< "Qual o novo nome do Hipermercado? (se quiser voltar ao menu inicial insira o nº9)"
			<< endl;
	cin >> novonome;
	if (novonome == "9") {
		menuinicial();
	}
	Hipermercado<int>::getInstance()->setNomeHipermercado(novonome);
	//funcao para mudar o nome do hipermercado
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
				<< Hipermercado<int>::getInstance()->getPedidos()[i]->getData()
				<< endl
				<< Hipermercado<int>::getInstance()->getPedidos()[i]->getFornecedor()
				<< endl;
		for (int j = 0;
				j
						< Hipermercado<int>::getInstance()->getPedidos()[i]->getProdutos().size();
				j++) {
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

	menuinicial();
	leFicheiros();
	escreveFicheiros();
	return 0;
}
