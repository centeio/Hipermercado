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
#include <sstream>
#include "Hipermercado.h"
using namespace std;

/**
 *	@brief Le os produtos do fornecedor
 *
 *	@param hipermercado Hipermercado
 *	@param &hipermercadoProdutosFornecedor Ficheiro a ler
 */
void leProdutosFornecedor(Hipermercado* hipermercado, ifstream &hipermercadoProdutosFornecedor);

/**
 *	@brief Le os produtos do hipermercado
 *	@param hipermercado Hipermercado
 *	@param &hipermercadoProdutos Ficheiro a ler
 */
void leProdutos(Hipermercado* hipermercado, ifstream &hipermercadoProdutos);

/**
 *	@brief Le os fornecedores
 *	@param hipermercado Hipermercado
 *	@param &hipermercadoFornecedores Ficheiro a ler
 */
void leFornecedores(Hipermercado* hipermercado, ifstream &hipermercadoFornecedores);

/**
 *	@brief Le as encomendas
 *	@param hipermercado Hipermercado
 *	@param &hipermercadoencomendas Ficheiro a ler
 */
void leEncomendas(Hipermercado* hipermercado, ifstream &hipermercadoencomendas);

/**
 *	@brief Le os pedidos de encomendas
 *	@param hipermercado Hipermercado
 *	@param &hipermercadopedidosencomendas Ficheiro a ler
 */
void lePedidosEncomendas(Hipermercado* hipermercado, ifstream& hipermercadopedidosencomendas);

/**
 *	@brief Le os ficheiros de texto
 *
 *	@param hipermercado Hipermercado
 */
void leFicheiros(Hipermercado* hipermercado) {

	ifstream hipermercadoProdutosFornecedor("produtosFornecedor.txt");
	if (hipermercadoProdutosFornecedor.is_open()) {
		leProdutosFornecedor(hipermercado, hipermercadoProdutosFornecedor);
		hipermercadoProdutosFornecedor.close();
		remove("produtosFornecedor.txt");
	}

	ifstream hipermercadoProdutos("produtos.txt");
	if (hipermercadoProdutos.is_open()) {
		leProdutos(hipermercado, hipermercadoProdutos);
		hipermercadoProdutos.close();
		remove("produtos.txt");
	}

	ifstream hipermercadoFornecedores("fornecedores.txt");
	if (hipermercadoFornecedores.is_open()) {
		leFornecedores(hipermercado, hipermercadoFornecedores);
		hipermercadoFornecedores.close();
		remove("fornecedores.txt");
	}

	ifstream hipermercadoEncomendas("encomendas.txt");
	if (hipermercadoEncomendas.is_open()) {
		leEncomendas(hipermercado, hipermercadoEncomendas);
		hipermercadoEncomendas.close();
		remove("encomendas.txt");
	}

	ifstream hipermercadoPedidosEncomendas("pedidosencomendas.txt");
	if (hipermercadoPedidosEncomendas.is_open()) {
		lePedidosEncomendas(hipermercado, hipermercadoPedidosEncomendas);
		hipermercadoPedidosEncomendas.close();
		remove("pedidosencomendas.txt");
	}
}

//LER PRODUTOS.TXT
void leProdutos(Hipermercado* hipermercado, ifstream &hipermercadoProdutos) {
	string nomeProduto, medida;
	float stock;
	bool cicle = true;

	while(cicle) {
		getline(hipermercadoProdutos, nomeProduto);
		if(nomeProduto != "#") {
			getline(hipermercadoProdutos, medida);
			hipermercadoProdutos >> stock;

			Produto* produto = new Produto(nomeProduto, medida, stock);
			hipermercado->addProdutoFila(produto);
			hipermercadoProdutos.clear();
			hipermercadoProdutos.ignore(1000,'\n');
		}else cicle = false;
	}
}

//LER FORNECEDORES.TXT
void leFornecedores(Hipermercado* hipermercado, ifstream &hipermercadoFornecedores) {
	string nome, NIF, morada, tipo;
	unsigned int dia, mes, ano;
	bool cicle = true;


	while(cicle) {
		getline(hipermercadoFornecedores, nome);
		if(nome != "#") {
			getline(hipermercadoFornecedores, NIF);
			getline(hipermercadoFornecedores, morada);
			hipermercadoFornecedores >> dia >> mes >> ano;
			hipermercadoFornecedores.clear();
			hipermercadoFornecedores.ignore(1000,'\n');
			getline(hipermercadoFornecedores, tipo);

			Data data(dia, mes, ano);
			if(tipo == "Individual") {
				Fornecedor* fornecedorInd = new FornecedorIndividual(nome, NIF, morada, data);
				hipermercado->addFornecedor(fornecedorInd);
			} else {
				Fornecedor* fornecedorEmp = new FornecedorEmpresa(nome, NIF, morada, data);
				hipermercado->addFornecedor(fornecedorEmp);
			}
		}else cicle = false;
	}
}

Fornecedor* procuraFornecedor(Hipermercado* hipermercado, string nome){

	for(unsigned int i = 0; i < hipermercado->getFornecedores().size(); i++ ){
		if(hipermercado->getFornecedores().at(i)->getNome() == nome)
			return hipermercado->getFornecedores().at(i);
	}
	return NULL;
}

//LER PRODUTOSFORNECEDOR.TXT
void leProdutosFornecedor(Hipermercado* hipermercado, ifstream &hipermercadoProdutosFornecedor) {
	string nomeProduto, medida, nomeFornecedor, NIF, morada, tipo;
	unsigned int min, max;
	float preco, stock;
	bool cicle = true;

	while(cicle) {
		getline(hipermercadoProdutosFornecedor, nomeProduto);
		if(nomeProduto != "#") {
			getline(hipermercadoProdutosFornecedor, medida);
			hipermercadoProdutosFornecedor >> stock;

			hipermercadoProdutosFornecedor.clear();
			hipermercadoProdutosFornecedor.ignore(1000,'\n');
			getline(hipermercadoProdutosFornecedor, nomeFornecedor);

			hipermercadoProdutosFornecedor.clear();
			hipermercadoProdutosFornecedor.ignore(1000,'\n');
			getline(hipermercadoProdutosFornecedor, tipo);
			hipermercadoProdutosFornecedor >> min >> max >> preco;

			Patamar* patamar = new Patamar(min, max, preco);
			if(tipo == "Individual") {
				Fornecedor *fornecedorInd = procuraFornecedor(hipermercado,nomeFornecedor);
				ProdutoFornecedor produto(nomeProduto, medida, stock, fornecedorInd, patamar);
				hipermercado->addProduto(produto);
			}
			else {
				Fornecedor *fornecedorEmp = procuraFornecedor(hipermercado,nomeFornecedor);
				ProdutoFornecedor produto(nomeProduto, medida, stock, fornecedorEmp, patamar);
				hipermercado->addProduto(produto);
			}
			hipermercadoProdutosFornecedor.clear();
			hipermercadoProdutosFornecedor.ignore(1000,'\n');
		}else cicle = false;
	}
}

//LER ENCOMENDAS.TXT
void leEncomendas(Hipermercado* hipermercado, ifstream &hipermercadoEncomendas) {
	string nomeFornecedor, nomeProduto;
	unsigned int dia, mes, ano, quantidade;
	float preco;
	bool firstCicle = true, secondCicle = true;
	vector<LinhaEncomenda*> linhas;

	while(firstCicle) {
		getline(hipermercadoEncomendas, nomeFornecedor);
		if(nomeFornecedor != "#") {
			while (secondCicle) {
				getline(hipermercadoEncomendas, nomeProduto);
				if (nomeProduto != "#") {
					hipermercadoEncomendas >> quantidade >> preco;
					LinhaEncomenda* linha = new LinhaEncomenda(nomeProduto, quantidade, preco);
					linhas.push_back(linha);
					hipermercadoEncomendas.clear();
					hipermercadoEncomendas.ignore(1000, '\n');
				} else secondCicle = false;
			}
			hipermercadoEncomendas >> dia >> mes >> ano;
			Data data(dia, mes, ano);
			Encomenda* encomenda = new Encomenda(procuraFornecedor(hipermercado, nomeFornecedor), linhas, data);
			hipermercado->addEncomenda(encomenda);
			hipermercadoEncomendas.clear();
			hipermercadoEncomendas.ignore(1000,'\n');
		} else firstCicle = false;
	}
}

void lePedidosEncomendas(Hipermercado* hipermercado, ifstream& hipermercadoPedidosEncomendas) {
	unsigned int dia, mes, ano, quantidade;
	string finalizado, nomeProduto;
	vector<string> produtos;
	vector<unsigned int> quantidades;
	bool outerCicle = true, innerCicle = true;

	while(outerCicle) {
		hipermercadoPedidosEncomendas >> dia;
		if(dia != 0) {
			hipermercadoPedidosEncomendas >> mes >> ano >> finalizado;
			while(innerCicle) {
				hipermercadoPedidosEncomendas.clear();
				hipermercadoPedidosEncomendas.ignore(1000,'\n');
				getline(hipermercadoPedidosEncomendas, nomeProduto);
				if(nomeProduto != "#") {
					hipermercadoPedidosEncomendas >> quantidade;
					produtos.push_back(nomeProduto);
					quantidades.push_back(quantidade);
				}else innerCicle = false;
			}
			PedidoEncomenda* pedido = new PedidoEncomenda(Data(dia,mes,ano), produtos, quantidades);
			if(finalizado == "true") pedido->setFinalizado(true);
			else pedido->setFinalizado(false);
			hipermercado->addPedido(pedido);
		}else outerCicle = false;
	}
}


void opcaoprodutos(Hipermercado* hipermercado);
void opcaofornecedores(Hipermercado* hipermercado);
void opcaoencomendas(Hipermercado* hipermercado);

//MENU INICIAL
void menuinicial(Hipermercado* hipermercado) {
	string noveNomeHipermercado,opcaoString;
	int opcao;

	do {
		//system("cls");
		cout << setw(40) << "HIPERMERCADO" << " " << hipermercado->getNome() << endl << endl;
		cout << setw(20) << "Ecra principal: " << endl << endl;
		cout << setw(10) << "1 - Menu produtos." << endl;
		cout << setw(10) << "2 - Menu fornecedores." << endl;
		cout << setw(10) << "3 - Menu encomendas." << endl;
		cout << setw(10) << "4 - Mudar nome do Hipermercado." << endl;
		cout << setw(10) << "9 - Terminar o programa." << endl;

		do {
			cout << "Introduza a opcao pretendida: " << flush;
			getline(cin, opcaoString);
			stringstream ss(opcaoString);
			ss >> opcao;

			if ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) && (opcao != 9))
				cout << "Opcao invalida." << flush;
		}while ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) && (opcao != 9));

		if (opcao == 1) {
			opcaoprodutos(hipermercado);
		} else if (opcao == 2) {
			opcaofornecedores(hipermercado);
		} else if (opcao == 3) {
			opcaoencomendas(hipermercado);
		} else if (opcao == 4) {
			cout << "Introduza o novo nome do hipermercado: " << flush;
			getline(cin,noveNomeHipermercado);
			hipermercado->setNome(noveNomeHipermercado);
		} else {
			cout << "Terminou o programa, obrigados pela sua visita!";
		}
	}while(opcao != 9);
}

bool operator==(const ProdutoFornecedor produto1, const ProdutoFornecedor produto2) {
	return produto1.getNome() == produto2.getNome();
}

//OPCAO PRODUTOS DO MENU
void opcaoprodutos(Hipermercado* hipermercado) {
	string medida, nomeProduto, nomeFornecedor, NIF, morada,opcaoString, answer;
	float stock, preco;
	unsigned int opcao, min, max;

	do {
		//system("cls");
		cout << setw(20) << "Menu Produtos: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de produtos." << endl;
		cout << setw(10) << "2 - Adicionar produto." << endl;
		cout << setw(10) << "3 - Alterar nome de um produto." << endl;
		cout << setw(10) << "4 - Alterar medida usada para um produto." << endl;
		cout << setw(10) << "5 - Alterar stock do produto." << endl;
		cout << setw(10) << "6 - Alterar fornecedor do produto." << endl;
		cout << setw(10) << "7 - Eliminar produto." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;


		do {
			cout << "Introduza a opcao pretendida: " << flush;
			getline(cin, opcaoString);
			stringstream ss(opcaoString);
			ss >> opcao;

			if ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) &&
					(opcao != 5) && (opcao != 6) && (opcao != 7) && (opcao != 9))
				cout << "Opcao invalida." << flush;
		} while ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) &&
				(opcao != 5) && (opcao != 6) && (opcao != 7) && (opcao != 9));


		if (opcao == 1) {
			//hipermercado->displayProdutos();
			hipermercado->displayPriorityQueue();
			//system("pause");
		}
		else if (opcao == 2) {
			cout << "Introduza o nome do produto: " << flush;
			getline(cin,nomeProduto);
			cout << "Introduza a medida usada para o produto: " << flush;
			getline(cin,medida);
			do {
				cout << "Introduza o stock inicial do produto: " << flush;
				getline(cin, opcaoString);
				stringstream ss(opcaoString);
				ss >> stock;
				if (stock == 0)	cout << "Tem de introduzir um valor valido." << flush;

			} while (stock == 0);
			cout << "Introduza o nome do Fornecedor desse produto: " << flush;
			getline(cin, nomeFornecedor);
			Fornecedor* fornecedor = procuraFornecedor(hipermercado, nomeFornecedor);
			if(fornecedor == NULL) {
				cout << "Esse fornecedor nao faz parte dos fornecedores do " << hipermercado->getNome() << "."
						<< endl << "Pretende adiciona-lo como novo fornecedor(Y/N): " << flush;
				getline(cin, answer);
				transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
				while (answer != "n" && answer != "y") {
					cout << "Por favor introduza Y para sim e N para nao. " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
				}
				if (answer == "n") {
					cout << endl << "Nao e possivel adicionar um produto sem um fornecedor." << endl << endl;
					return;
				} else {
					do {
						cout << "Introduza o tipo de fornecedor: " << endl << "1. Individual;" << endl << "2. Empresa: " << flush;
						getline(cin, opcaoString);
						stringstream ss(opcaoString);
						ss >> opcao;
						if (opcao == 0 && (opcao != 1) && (opcao != 2))	cout << "Opcao invalida." << flush;

					} while (opcao == 0 && (opcao != 1) && (opcao != 2));
					if (opcao == 1) {
						cout << "Introduza o NIF do fornecedor: " << flush;
						getline(cin, NIF);
						cout << "Introduza a morada do fornecedor: " << flush;
						getline(cin, morada);

						FornecedorIndividual *fornecedorInd = new FornecedorIndividual(nomeFornecedor, NIF, morada);
						hipermercado->addFornecedor(fornecedorInd);
						do {
							cout << "E necessario introduzir o patamar para este produto." << endl <<
										"Introduza o limite inferior: " << flush;
							getline(cin, opcaoString);
							stringstream ss(opcaoString);
							ss >> min;
							if (min == 0)
								cout << "Tem de introduzir um valor valido." << flush;
						} while (min == 0);
						do {
							cout <<"Introduza o limite superior: " << flush;
							getline(cin, opcaoString);
							stringstream ss(opcaoString);
							ss >> max;
							if (max == 0)
								cout << "Tem de introduzir um valor valido."
										<< flush;
						} while (max == 0);
						do {
							cout << "Introduza o limite inferior: " << flush;
							getline(cin, opcaoString);
							stringstream ss(opcaoString);
							ss >> preco;
							if (preco == 0)
								cout << "Tem de introduzir um valor valido." << flush;

						} while (preco == 0);

						Patamar *patamarInd = new Patamar(min, max, preco);
						ProdutoFornecedor produto(nomeProduto, medida, stock, fornecedorInd, patamarInd);
						hipermercado->addProduto(produto);
					}
					else {
						cout << "Introduza o NIF do fornecedor: " << flush;
						getline(cin, NIF);
						cout << "Introduza a morada do fornecedor: " << flush;
						getline(cin, morada);

						FornecedorEmpresa* fornecedorEmp = new FornecedorEmpresa(nomeFornecedor, NIF, morada);
						hipermercado->addFornecedor(fornecedorEmp);

						do {
							cout << "E necessario introduzir o patamar para este produto."
									<< endl << "Introduza o limite inferior: "
									<< flush;
							getline(cin, opcaoString);
							stringstream ss(opcaoString);
							ss >> min;
							if (min == 0)
								cout << "Tem de introduzir um valor valido." << flush;
						} while (min == 0);

						do {
							cout << "Introduza o limite superior: " << flush;
							getline(cin, opcaoString);
							stringstream ss(opcaoString);
							ss >> max;
							if (max == 0)
								cout << "Tem de introduzir um valor valido."
										<< flush;
						} while (max == 0);

						do {
							cout << "Introduza o preco: " << flush;
							getline(cin, opcaoString);
							stringstream ss(opcaoString);
							ss >> preco;
							if (preco == 0)
								cout << "Tem de introduzir um valor valido."
										<< flush;

						} while (preco == 0);

						Patamar* patamarEmp = new Patamar(min, max, preco);
						ProdutoFornecedor produto(nomeProduto, medida, stock, fornecedorEmp, patamarEmp);
						hipermercado->addProduto(produto);
					}
				}
			} else {
				do {
					cout << "Introduza o limite inferior: " << flush;
					getline(cin, opcaoString);
					stringstream ss(opcaoString);
					ss >> min;
					if (min == 0)
						cout << "Tem de introduzir um valor valido." << flush;
				} while (min == 0);

				do {
					cout << "Introduza o limite superior: " << flush;
					getline(cin, opcaoString);
					stringstream ss(opcaoString);
					ss >> max;
					if (max == 0)
						cout << "Tem de introduzir um valor valido." << flush;
				} while (max == 0);

				do {
					cout << "Introduza o preco: " << flush;
					getline(cin, opcaoString);
					stringstream ss(opcaoString);
					ss >> preco;
					if (preco == 0)
						cout << "Tem de introduzir um valor valido." << flush;

				} while (preco == 0);

				Patamar* patamar = new Patamar(min,max,preco);
				ProdutoFornecedor produto(nomeProduto, medida, stock, fornecedor, patamar);
				hipermercado->addProduto(produto);
			}
		} else if (opcao == 3) {
			string novoNome;

			do {
				answer = "n";
				cout << "Introduza o nome do produto que pretende alterar: " << flush;
				getline(cin, nomeProduto);

				ProdutoFornecedor temp(nomeProduto, "", 0, NULL, NULL);
				BST<ProdutoFornecedor> temporary = hipermercado->getProdutos();

				if (temporary.find(temp) == Hipermercado::ITEM_NOT_FOUND) {
					cout << "O produto que pretende alterar nao existe. Prentende introduziu outro nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				}
			} while (answer == "y");
			cout << "Introduza o novo nome do produto: " << flush;
			getline(cin, novoNome);
			hipermercado->alteraNomeProduto(nomeProduto, novoNome);
		} else if (opcao == 4) {
			string novaMedida;

			do {
				answer = "n";
				cout << "Introduza o nome do produto que pretende alterar: " << flush;
				getline(cin, nomeProduto);

				ProdutoFornecedor temp(nomeProduto,"",0,NULL,NULL);
				BST<ProdutoFornecedor> temporary = hipermercado->getProdutos();

				if (temporary.find(temp) == Hipermercado::ITEM_NOT_FOUND) {
					cout << "O produto que pretende alterar nao existe. Prentende introduziu outro nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				}
			}while(answer == "y");

			cout << "Introduza a nova medida: " << flush;
			getline(cin, novaMedida);
			hipermercado->alteraMedidaProduto(nomeProduto, novaMedida);

		} else if (opcao == 5) {
			float novoStock;

			do {
				answer = "n";
				cout << "Introduza o nome do produto que pretende alterar: " << flush;
				getline(cin, nomeProduto);

				ProdutoFornecedor temp(nomeProduto,"",0,NULL,NULL);
				BST<ProdutoFornecedor> temporary = hipermercado->getProdutos();

				if (temporary.find(temp) == Hipermercado::ITEM_NOT_FOUND) {
					cout << "O produto que pretende alterar nao existe. Prentende introduziu outro nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				}
			}while(answer == "y");
			cout << "Introduza o novo stock: " << flush;
			cin >> novoStock;
			Produto* produto = new Produto(nomeProduto,"",0);
			hipermercado->alteraProdutoFila(produto, stock);

		} else if (opcao == 6) {
			/*cin.clear();
			cin.ignore(1000,'\n');

			cout << "Introduza o nome do produto que pretende alterar: " << flush;
			getline(cin,nomeProduto);
			cout << "Introduza o novo fornecedor: " << flush;
			getline(cin, nomeFornecedor);

			Fornecedor* fornecedor = procuraFornecedor(hipermercado, nomeFornecedor);
			if(fornecedor == NULL) {
				cout << "Esse fornecedor nÃ£o faz parte dos fornecedores do " << hipermercado->getNome() << "."
				<< endl << "Pretende adiciona-lo como novo fornecedor(Y/N): " << flush;
				cin >> answer;
				while (tolower(answer) != 'n' && tolower(answer) != 'y') {
					cout << "Por favor introduza Y para sim e N para nao. " << flush;
					cin >> answer;
				}
				if (answer == 'n') {
					cout << "Nao e possivel ter um produto sem um fornecedor." << endl;
					return;
				} else {
					cout << "Introduza o tipo de fornecedor: " << endl << "1. Individual;" << endl << "2. Empresa: " <<
					flush;
					cin >> opcao;
					while (opcao != 1 && opcao != 2) {
						cout << "Opcao invalida. Por favor reintroduza o opcao valido ou 0 para sair: " << flush;
						cin >> opcao;
					}
					if (opcao == 0) return;
					else if (opcao == 1) {
						cout << "Introduza o NIF do fornecedor: " << flush;
						cin.clear();
						cin.ignore(1000, '\n');
						getline(cin, NIF);
						cout << "Introduza a morada do fornecedor: " << flush;
						getline(cin, morada);

						FornecedorIndividual *fornecedorInd = new FornecedorIndividual(nomeFornecedor, NIF, morada);
						hipermercado->addFornecedor(fornecedorInd);
						hipermercado->alteraFornecedorProduto(nomeProduto, fornecedorInd);
					}
					else {
						cout << "Introduza o NIF do fornecedor: " << flush;
						cin.clear();
						cin.ignore(1000, '\n');
						getline(cin, NIF);
						cout << "Introduza a morada do fornecedor: " << flush;
						getline(cin, morada);

						FornecedorEmpresa *fornecedorEmp = new FornecedorEmpresa(nomeFornecedor, NIF, morada);
						hipermercado->addFornecedor(fornecedorEmp);
						hipermercado->alteraFornecedorProduto(nomeProduto, fornecedorEmp);

					}
				}
			} else {
				hipermercado->alteraFornecedorProduto(nomeProduto, fornecedor);
			}*/
		} else if(opcao == 7) {
			do {
				answer = "n";
				cout << "Introduza o nome do produto que pretende eliminar: " << flush;
				getline(cin, nomeProduto);

				ProdutoFornecedor temp(nomeProduto,"",0,NULL,NULL);
				BST<ProdutoFornecedor> temporary = hipermercado->getProdutos();

				if (temporary.find(temp) == Hipermercado::ITEM_NOT_FOUND) {
					cout << "O produto que pretende alterar nao existe. Prentende introduziu outro nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				}
			}while(answer == "y");
			ProdutoFornecedor temp(nomeProduto,"",0,NULL,NULL);
			hipermercado->eliminaProduto(hipermercado->getProdutos().find(temp));
		}
		else { return; }
	}while(opcao != 9);
}

void alteraFornecedor(Hipermercado* hipermercado);

//OPCAO FORNECEDORES DO MENU

/**
 *	@brief Opcao do menu relativamente aos fornecedores
 */
void opcaofornecedores(Hipermercado* hipermercado) {
	string nomeFornecedor, morada, tipo, NIF, opcaoString;
	unsigned int opcao;

	do {
		//system("cls");
		cout << setw(20) << "Menu Fornecedores: " << endl << endl;
		cout << setw(10) << "1 - Ver lista de fornecedores." << endl;
		cout << setw(10) << "2 - Ver lista de fornecedores inativos." << endl;
		cout << setw(10) << "3 - Adicionar fornecedor." << endl;
		cout << setw(10) << "4 - Alterar fornecedor." << endl;
		cout << setw(10) << "5 - Eliminar fornecedor." << endl;
		cout << setw(10) << "9 - Voltar ao menu inicial." << endl;
		cin >> opcao;

		do {
			cout << "Introduza a opcao pretendida: " << flush;
			getline(cin, opcaoString);
			stringstream ss(opcaoString);
			ss >> opcao;

			if ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) &&
				(opcao != 5) && (opcao != 9))
				cout << "Opcao invalida." << flush;
		} while ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4) &&
				(opcao != 5) && (opcao != 9));

		if (opcao == 1) {
			hipermercado->displayFornecedores();
			//system("pause");
		}
		else if(opcao == 2) {
			hipermercado->displayTabela();
			//system("pause");
		} else if (opcao == 3) {
			cout << "Introduza o nome do novo fornecedor: " << flush;
			getline(cin, nomeFornecedor);
			cout << "Introduza o NIF do novo fornecedor: " << flush;
			getline(cin, NIF);
			cout << "Introduza a morada do novo fornecedor: " << flush;
			getline(cin, morada);

			do {
				cout << "Introduza o tipo de fornecedor: " << endl << "1. Individual;" << endl << "2. Empresa: " << flush;
				getline(cin, opcaoString);
				stringstream ss(opcaoString);
				ss >> opcao;
				if (opcao == 0 && (opcao != 1) && (opcao != 2))	cout << "Opcao invalida." << flush;

			} while (opcao == 0 && (opcao != 1) && (opcao != 2));
			if (opcao == 1) {
				FornecedorIndividual *fornecedorInd = new FornecedorIndividual(nomeFornecedor, NIF, morada);
				hipermercado->addFornecedor(fornecedorInd);
			}
			else {
				FornecedorEmpresa *fornecedorEmp = new FornecedorEmpresa(nomeFornecedor, NIF, morada);
				hipermercado->addFornecedor(fornecedorEmp);
			}
		} else if(opcao == 4) {
			alteraFornecedor(hipermercado);
		}
		else if (opcao == 5) {
			/*
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
			 */
		} else { return; }
	}while(opcao != 9);
}

/**
 *	@brief Altera um fornecedor
 *
 *	@param hipermercado Hipermercado
 */
void alteraFornecedor(Hipermercado* hipermercado) {
	unsigned int opcao;
	string nomeFornecedor, NIF, morada, produtoAdicionar, opcaoString, answer;

	do {
		cout << setw(10) << "Menu Alterar Fornecedor:" << endl;
		cout << setw(10) << "1 - Alterar nome do Fornecedor" << endl;
		cout << setw(10) << "2 - Alterar NIF do Fornecedor" << endl;
		cout << setw(10) << "3 - Alterar morada do Fornecedor" << endl;
		cout << setw(10) << "9 - Voltar ao menu fornecedores" << endl;

		do {
			cout << "Introduza a opcao pretendida: " << flush;
			getline(cin, opcaoString);
			stringstream ss(opcaoString);
			ss >> opcao;

			if ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 9))
				cout << "Opcao invalida." << flush;

		} while ((opcao == 0) && (opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 9));

		if (opcao == 1) {
			do {
				answer = "n";
				cout << "Introduza o nome do fornecedor que pretende alterar: " << flush;
				getline(cin, nomeFornecedor);
				Fornecedor* fornecedor = procuraFornecedor(hipermercado, nomeFornecedor);

				if (fornecedor == NULL) {
					cout << "O fornecedor que introduziu nao existe. Prentende reintroduzir o nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				} else {
					cout << "Introduza o novo nome do fornecedor: " << flush;
					getline(cin, nomeFornecedor);
					fornecedor->setNome(nomeFornecedor);
				}
			}while(answer == "y");

		} else if (opcao == 2) {
			answer = 'n';
			do {
				answer = "n";
				cout << "Introduza o nome do fornecedor que pretende alterar: " << flush;
				getline(cin, nomeFornecedor);
				Fornecedor* fornecedor = procuraFornecedor(hipermercado, nomeFornecedor);

				if (fornecedor == NULL) {
					cout << "O fornecedor que introduziu nao existe. Prentende reintroduzir o nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				} else {
					cout << "Introduza o novo NIF do fornecedor: " << flush;
					getline(cin, NIF);
					fornecedor->setNIF(NIF);
				}
			}while(answer == "y");

		} else if (opcao == 3) {
			do {
				answer = "n";
				cout << "Introduza o nome do fornecedor que pretende alterar: " << flush;
				getline(cin, nomeFornecedor);
				Fornecedor* fornecedor = procuraFornecedor(hipermercado, nomeFornecedor);

				if (fornecedor == NULL) {
					cout << "O fornecedor que introduziu nao existe. Prentende reintroduzir o nome(Y/N): " << flush;
					getline(cin, answer);
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					while (answer != "n" && answer != "y") {
						cout << "Por favor introduza Y para sim e N para nao. " << flush;
						getline(cin, answer);
						transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					}
					if (answer == "n")	return;
				} else {
					cout << "Introduza a nova morada do fornecedor: " << flush;
					getline(cin, morada);
					fornecedor->setMorada(morada);
				}
			}while(answer == "y");

		} else { return; }
	}while(opcao != 9);
}

//OPCAO FORNECEDORES DO MENU
/**
 *	@brief Opcao do menu do hipermercado relativa as encomendas
 *
 *	@param hipermercado Hipermercado
 */
void opcaoencomendas(Hipermercado* hipermercado) {
	int opcao;
	string nomeProduto, unidades;
	unsigned int quantidade, numProdutos, numPedido;
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


			//	string nomeProduto;
			vector<string> produtosencomendas;
			vector<unsigned int> quantidades;

			do
			{
				//ADICIONAR PEDIDO DE ENCOMENDA

				cout << "Para terminar carregue 0. Insira o nome do produto que quer encomendar: " << flush;
				getline(cin, nomeProduto);
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Para terminar carregue 0. Insira o nome do produto que quer encomendar: " << flush;
				getline(cin, nomeProduto);
				ProdutoFornecedor temp(nomeProduto,"",0,NULL,NULL);
				if (hipermercado->getProdutos().find(temp) == Hipermercado::ITEM_NOT_FOUND)
					cout << "O produto que pretende alterar nao existe." << flush;
				else{
					cout << "Introduza a quantidade que quer encomendar deste produto: " << flush;
				//	getline(cin,quantidade);
					cin>>quantidade;
					produtosencomendas.push_back(nomeProduto);
					quantidades.push_back(quantidade); //TODO convert to int
					}

			}while(nomeProduto!="0");
				if(produtosencomendas.size()!=0)
					hipermercado->addPedido(new PedidoEncomenda(hipermercado->getDataAtual(), produtosencomendas, quantidades));
				opcaoencomendas(hipermercado);

			cin.clear();
			cin.ignore(1000,'\n');		} else if (opcao == 4) {
			//mostrar lista de pedidos por realizar
			//funcao que altera pedido encomenda;
			hipermercado->displayPedidosPorProcessar();

			cout << "Introduza o indice do pedido de encomenda que quer alterar: " << flush;
			cin >> numPedido;

			cout <<"Introduza o indice do produto do pedido de encomenda que quer alterar a sua quantidade: " << flush;
			cin >> nomeProduto;

			cout << "Qual a nova quantidade de produto do pedido de encomenda: " << flush;;
			cin >> quantidade;
			//esta funÃ§Ã£o nÃ£o existe
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

/**
 *	@brief Escreve os produtos do fornecedor no ficheiro de texto, isto é atualiza a informacao antes de fechar o programa
 *
 *	@param hipermercado Hipermercado
 */
void escreveProdutosFornecedor(Hipermercado* hipermercado);

/**
 *	@brief Escreve os produtos no ficheiro de texto, isto é atualiza a informacao antes de fechar o programa
 *
 *	@param hipermercado Hipermercado
 */
void escreveProdutos(Hipermercado* hipermercado);

/**
 *	@brief Escreve os fornecedores no ficheiro de texto, isto é atualiza a informacao antes de fechar o programa
 *
 *	@param hipermercado Hipermercado
 */
void escreveFornecedores(Hipermercado* hipermercado);

/**
 *	@brief Escreve as encomendas no ficheiro de texto, isto é atualiza a informacao antes de fechar o programa
 *
 *	@param hipermercado Hipermercado
 */
void escreveEncomendas(Hipermercado* hipermercado);

/**
 *	@brief Escreve os pedidos de encomendas no ficheiro de texto, isto é atualiza a informacao antes de fechar o programa
 *
 *	@param hipermercado Hipermercado
 */
void escrevePedidosEncomendas(Hipermercado* hipermercado);

/**
 *	@brief Escreve em todos os ficheiros de texto , atualizando a informacao antes de fechar o programa
 *
 *	@param hipermercado Hipermercado
 */
void escreveFicheiros(Hipermercado* hipermercado) {


	escreveProdutosFornecedor(hipermercado);
	escreveProdutos(hipermercado);
	escreveFornecedores(hipermercado);
	escreveEncomendas(hipermercado);
	escrevePedidosEncomendas(hipermercado);
}

void escreveProdutos(Hipermercado* hipermercado) {
	ofstream hipermercadoProdutos;

	hipermercadoProdutos.open("produtos.txt");
	while(!hipermercado->getPriorityQueue().empty()) {
		hipermercadoProdutos << hipermercado->getPriorityQueue().top()->getNome() << endl << hipermercado->getPriorityQueue().top()->getMedida()
						<< endl << hipermercado->getPriorityQueue().top()->getStock() << endl;
		hipermercado->getPriorityQueue().pop();
	}
	hipermercadoProdutos << "#";
	hipermercadoProdutos.close();
}

void escreveProdutosFornecedor(Hipermercado* hipermercado) {
	ofstream hipermercadoProdutosFornecedor;
	BST<ProdutoFornecedor> temp = hipermercado->getProdutos();
	BSTItrIn<ProdutoFornecedor> it(temp);

	hipermercadoProdutosFornecedor.open("produtosFornecedor.txt");

	while(!it.isAtEnd()) {
		hipermercadoProdutosFornecedor << it.retrieve().getNome() << endl << it.retrieve().getMedida()
						<< endl << it.retrieve().getStock() << endl << it.retrieve().getFornecedor()->getNome()
						<< endl << it.retrieve().getPatamar()->getMinimo() << endl << it.retrieve().getPatamar()->getMaximo()
						<< endl << it.retrieve().getPatamar()->getPreco() << endl;
		it.advance();
	}
	hipermercadoProdutosFornecedor << "#";
	hipermercadoProdutosFornecedor.close();
}


void escreveFornecedores(Hipermercado* hipermercado) {
	ofstream hipermercadoFornecedores;

	hipermercadoFornecedores.open("fornecedores.txt");

	for (unsigned int i = 0; i < hipermercado->getFornecedores().size(); i++) {
		hipermercadoFornecedores << hipermercado->getFornecedores().at(i)->getNome() << endl
				<< hipermercado->getFornecedores().at(i)->getNIF() << endl << hipermercado->getFornecedores().at(i)->getMorada()
				<< endl << hipermercado->getFornecedores().at(i)->getData().getDia() << endl << hipermercado->getFornecedores().at(i)->getData().getMes()
				<< endl << hipermercado->getFornecedores().at(i)->getData().getAno() << endl << hipermercado->getFornecedores().at(i)->getTipo() << endl;
	}
	hipermercadoFornecedores << "#";
	hipermercadoFornecedores.close();
}

void escreveEncomendas(Hipermercado* hipermercado) {
	ofstream hipermercadoEncomendas;

	hipermercadoEncomendas.open("encomendas.txt");

	for (unsigned int i = 0; i < hipermercado->getEncomendas().size(); i++) {
		hipermercadoEncomendas << hipermercado->getEncomendas().at(i)->getFornecedor()->getNome() << endl;

		for (unsigned int j = 0; j < hipermercado->getEncomendas().at(i)->getLinhas().size(); j++) {
			hipermercadoEncomendas << hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getProduto() << endl
					<< hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getQuantidade() << endl
					<< hipermercado->getEncomendas().at(i)->getLinhas().at(j)->getPreco() << endl;
		}
		hipermercadoEncomendas << "#" << endl;
		hipermercadoEncomendas << hipermercado->getEncomendas().at(i)->getData().getDia() << endl
				<< hipermercado->getEncomendas().at(i)->getData().getMes() << endl << hipermercado->getEncomendas().at(i)->getData().getAno() << endl;
	}
	hipermercadoEncomendas << "#";
	hipermercadoEncomendas.close();
}

void escrevePedidosEncomendas(Hipermercado* hipermercado) {
	ofstream hipermercadoPedidosEncomendas;

	hipermercadoPedidosEncomendas.open("pedidosencomendas.txt");

	for(unsigned int i = 0; i < hipermercado->getPedidos().size(); i++) {
		hipermercadoPedidosEncomendas << hipermercado->getPedidos().at(i)->getData().getDia() << endl
				<< hipermercado->getPedidos().at(i)->getData().getMes() << endl
				<< hipermercado->getPedidos().at(i)->getData().getAno() << endl;
		if(hipermercado->getPedidos().at(i)->getFinalizado()) (hipermercadoPedidosEncomendas << "true");
		else (hipermercadoPedidosEncomendas << "false");

		for(unsigned int j = 0; j < hipermercado->getPedidos().at(i)->getProdutos().size(); j++) {
			hipermercadoPedidosEncomendas << hipermercado->getPedidos().at(i)->getProdutos().at(j) << endl
					<< hipermercado->getPedidos().at(i)->getQuantidade().at(j) << endl;
		}
		hipermercadoPedidosEncomendas << "#" << endl;
	}
	hipermercadoPedidosEncomendas << "0" << endl;
}


/**
 *	@brief Main do programa
 *
 **/
int main() {
	Hipermercado* hipermercado = Hipermercado::getInstance();

	//inicializando a data
	time_t now = time(0);
	tm *date = localtime(&now);
	hipermercado->setDataAtual(date->tm_mday, 1 + date->tm_mon, 1900 + date->tm_year);

	leFicheiros(hipermercado);
	menuinicial(hipermercado);
	escreveFicheiros(hipermercado);


	return 0;
}
