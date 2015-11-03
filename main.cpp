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
using namespace std;

static Data dataatual;

//menu inicial
int menuinicial() {
	cout << setw(40) << "HIPERMERCADOS" << endl << endl;
	cout << setw(20) << "Ecra principal: " << endl << endl;
	cout << setw(10) << "1 -  Ver produtos" << endl;
	cout << setw(10) << "2 -  Ver fornecedores" << endl;
	cout << setw(10) << "3 -  Ver encomendas" << endl;
	cout << setw(10) << "4 - Mudar nome do Hipermercado" << endl;
	return 0;
}

//diferentes opcoes
void opcaoprodutos() {
	int opcao;
	cout << setw(20) << "Produtos: " << endl << endl;
	cout << setw(10) << "1 - Ver lista de produtos" << endl;
	cout << setw(10) << "2 - Adicionar produto" << endl;
	cout << setw(10) << "3 - Alterar produto" << endl;
	cout << setw(10) << "4 - Eliminar produto" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)) {
			cout << "Opção inválida, volte a introduzir a opção pretendida pf"
					<< endl;
			cin >> opcao;
		}
		if (opcao == 1) {
			//funcao que mostra a lista de produtos;
		} else if (opcao == 2) {
			//funcao que adiciona produto;
		} else if (opcao == 3) {
			//funcao que altera produto;
		} else if (opcao == 4) {
			//funcao que elimina produto;
		};
}
void opcaofornecedores() {
	int opcao;
	cout << setw(20) << "Fornecedores: " << endl << endl;
	cout << setw(10) << "1 - Ver lista de fornecedores" << endl;
	cout << setw(10) << "2 - Adicionar fornecedor" << endl;
	cout << setw(10) << "3 - Alterar fornecedor" << endl;
	cout << setw(10) << "4 - Eliminar fornecedor" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)) {
			cout << "Opção inválida, volte a introduzir a opção pretendida pf"
					<< endl;
			cin >> opcao;
		}
		if (opcao == 1) {
			//funcao que mostra lista de fornecedores;
		} else if (opcao == 2) {
			//funcao que adiciona fornecedor;
		} else if (opcao == 3) {
			//funcao que altera fornecedor;
		} else if (opcao == 4) {
			//funcao que elimina fornecedor;
		};
}
void opcaoencomendas() {
	int opcao;
	cout << setw(20) << "Encomendas: " << endl << endl;
	cout << setw(10) << "Introduza a opção pretendida pf" << endl << endl;
	cout << setw(10) << "1 - Ver encomendas realizadas" << endl;
	cout << setw(10) << "2 - Ver encomendas por realizar" << endl;
	cout << setw(10) << "3 - Realizar nova encomenda" << endl;
	cout << setw(10) << "4 - Alterar encomenda" << endl;
	cout << setw(10) << "5 - Eliminar encomenda" << endl;
	cin >> opcao;
	while ((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4)
			&& (opcao != 5)) {
		cout << "Opção inválida, volte a introduzir a opção pretendida pf"
				<< endl;
		cin >> opcao;
	}
	if (opcao == 1) {
		//funcao que mostra a lista de encomendas realizadas;
	} else if (opcao == 2) {
		//funcao que mostra a lista de encomendas por realizar;
	} else if (opcao == 3) {
		//funcao que realiza nova encomenda;
	} else if (opcao == 4) {
		//funcao que altera encomenda;
	} else if (opcao == 5) {
		//funcao que elimina encomenda;
	}
}

void opcaomudarnome() {
	string novonome;
	cout << setw(10) << "Qual o novo nome do Hipermercado?" << endl;
	cin >> novonome;
	//funcao para mudar o nome do hipermercado
}

//menu de opcoes
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

void leProdutos(ifstream hipermercadoprodutos) {
	string nome, unidade;
	int numprodutos;
	hipermercadoprdutos >> numprodutos;
	for (int i = 0; i < numprodutos; i++) {
		hipermercado >> nome >> unidade;
		Produto* produtof = new Produto(nome, unidade);
		//Hipermercado::getInstance()->addProduto(produtof)
	}
}

void leFornecedores() {
	string nome, nif, morada, tipo, produtos, patminimo, patmaximo, preco,
			stock, medida;
	int numfornecedores, numprodutos, numpatamares;
	ifstream hipermercado("fornecedores.txt");
	hipermercado >> numfornecedores;
	for (int i = 0; i < numfornecedores; i++) {
		hipermercado >> nome >> nif >> morada >> tipo >> numprodutos;
		//Hipermercado::getInstance()->addFornecedor(nome, nif, morada);
		for (int j = 0; j < numprodutos; j++) {
			hipermercado >> produtos >> medida >> stock >> numpatamares
					>> patminimo >> patmaximo >> preco;
			Produto* produtof = new Produto(produtos, medida);
			//vector<Patamar*> patamares;
			//Patamar* patamar = new Patamar(patminimo, patmaximo, preco);
			//patamares.push_back(patamar);
			//Hipermercado::getInstance()->getFornecedores.at(Hipermercado::getInstance()->getFornecedores.size() -1)->addProduto(
			//produtof,stock,patamares)
			for (int k = 0; k < numpatamares - 1; k++) {
				hipermercado >> patminimo >> patmaximo >> preco;
				//Hipermercado::getInstance()->fornecedores.at(Hipermercado::getInstance()->fornecedores.size() - 1).getProdutos.at(
				//Hipermercado::getInstance()->fornecedores.at(Hipermercado::getInstance()->fornecedores.size() - 1).getProdutos.size() -1). addPatamar(
				//patminimo, patmaximo, preco);
			}
		}
	}
}

void leEncomendas() {
	ifstream hipermercado("encomendas.txt");
	string fornecedor, produto, quantidade, preco, dia, mes,ano, medida;
	int numencomendas, numprodutos;
	hipermercado >> numencomendas;
	for (int i = 0; i < numencomendas; i++) {
		hipermercado >> dia >> mes >> ano >> fornecedor >> numprodutos;
		Data dataatual(dia, mes, ano);
		Encomenda* encomendaf = new Encomenda(fornecedor, produto, quantidade);
		//Hipermercado::getInstance()->addEncomenda(encomendaf);
		for (int j = 0; j < numprodutos; j++) {
			hipermercado >> produto >> medida >> quantidade >> preco;
			Produto* produtof = new Produto(produto, medida);
			//Hipermercado::getInstance()->getEncomendas.at(Hipermercado::getInstance()->getEncomendas.size()-1)->addLinhaEncomenda(
			//produtof, quantidade,preco);
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
		//escreve no hipermercado o que for necessario
	}
	ifstream hipermercadof("fornecedores.txt");
	if (hipermercadof) {
		leFornecedores();
	} else {
		ofstream hipermercado;
		hipermercado.open("fornecedores.txt");
		//escreve no hipermercado o que for necessario
		hipermercado.close();
	}
	ifstream hipermercadoe("encomendas.txt");
	if (hipermercado) {
		leEncomendas();
	} else {
		ofstream hipermercado;
		hipermercado.open("encomendas.txt");
		//escreve no hipermercado o que for necessario
		hipermercado.close();
	}
}

void escreveProdutos(){
	ifstream hipermercado;
	hipermercado.close();
	//remove("produtos.txt");
	//ofstream hipermercado;
//	hipermercado.open("produtos.txt");
//	hipermercado << "Novos produtos";
//	hipermercado.close();
}
void escreveFornecedores(){
	ifstream hipermercado;
//	remove("fornecedores.txt");
	//ofstream hipermercado;
//	hipermercado.open("fornecedores.txt");
//	hipermercado << "Novos Fornecedores";
//	hipermercado.close();
}

void escreveEncomendas(){
	ifstream hipermercado;
	//remove("encomendas.txt");
	//ofstream hipermercado;
//	hipermercado.open("encomendas.txt");
//	hipermercado << "Novas Encomandas";
//	hipermercado.close();
}

void escreveFicheiros(){
	escreveProdutos();
	escreveFornecedores();
	escreveEncomendas();
}
int main() {

	menuinicial();
	opcoesmenu();
	leFicheiros();
	escreveFicheiros();
	return 0;
}
