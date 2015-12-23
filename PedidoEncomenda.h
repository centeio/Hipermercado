/*
 * PedidoEncomenda.h
 *
 *  Created on: 21/10/2015
 *      Author: Carolina
 */

#ifndef PEDIDOENCOMENDA_H_
#define PEDIDOENCOMENDA_H_

#include "Data.h"
#include "Produto.h"
#include <vector>
#include <cmath>
#include <math.h>
#include <climits>

using namespace std;

class PedidoEncomenda {
private:
	Data data;
	bool finalizado;
	vector<string> produtos;
	vector<unsigned int> quantidade;
public:
	/** Declaracao das funcoes */
	PedidoEncomenda(Data data, vector<string> produtos, vector<unsigned int> quant);
	PedidoEncomenda(vector<string> produtos, vector<unsigned int> quant);
	PedidoEncomenda(string produto, unsigned int quant);
	PedidoEncomenda();
	virtual ~PedidoEncomenda();
	void processamento();
	Data getData() const;
	bool getFinalizado() const;
	vector<string> getProdutos() const;
	vector<unsigned int> getQuantidade() const;
	void setFinalizado(bool finalizado);
	void setProduto(unsigned int indice, string novonome);
	void setQuantProduto(unsigned int indiceProduto, unsigned int novaqt);
	void acrescenta(string produto, unsigned int quantidade);
	void eliminaProduto(string produto);
	friend ostream &operator<<(ostream& os, PedidoEncomenda* p);

	class ProdutoNaoExiste{
	private:
		string produto;
	public:
		ProdutoNaoExiste(string produto): produto(produto){
			cout<<"O produto "<<produto<<" nao existe na lista de pedidos.\n";
		};

	};

	class ProdutoNaoEstaAVenda{
	private:
		string produto;
	public:
		ProdutoNaoEstaAVenda(string produto): produto(produto){
			cout<<"O produto "<<produto<<" nao se encontra a venda em nenhum fornecedor.\n";
		};
	};

	class ProdutoParcialmenteComprado{
	private:
		string produto;
	public:
		ProdutoParcialmenteComprado(string produto): produto(produto){
					cout<<"O produto "<<produto
							<<" nao foi comprado na quantidade pretendida, devido a insuficiencia de stock nos fornecedores.\n";
				};

	};
};

#endif /* PEDIDOENCOMENDA_H_ */
