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

using namespace std;

template <class T>
class PedidoEncomenda {
private:
	Data data;
	bool finalizado;
	vector<Produto*> produtos;
	vector<T> quantidade;
public:
	PedidoEncomenda(Data data, vector<Produto*> produtos, vector<unsigned int> quant);
	virtual ~PedidoEncomenda();
	void processamento();
	Data getData() const;
	bool getFinalizado();
	vector<Produto*> getProdutos() const;
	vector<unsigned int> getQuantidade() const;
	void acrescenta(Produto* produto, T quantidade);
	void eliminaProduto(Produto* produto);
	class ProdutoNaoExiste{
	private:
		Produto* produto;
	public:
		ProdutoNaoExiste(Produto* produto): produto(produto){
			cout<<"O produto "<<produto->getNome()<<" não existe na lista de pedidos.\n";
		};

	};
	class ProdutoNaoEstaAVenda{
	private:
		Produto* produto;
	public:
		ProdutoNaoEstaAVenda(Produto* produto): produto(produto){
			cout<<"O produto "<<produto->getNome()<<" não se encontra à venda em nenhum fornecedor.\n";
		};
	};
	class ProdutoParcialmenteComprado{
	private:
		Produto* produto;
	public:
		ProdutoParcialmenteComprado(Produto* produto): produto(produto){
					cout<<"O produto "<<produto->getNome()
							<<" não foi comprado na quantidade pretendida, devido a insuficiência de stock nos fornecedores.\n";
				};

	};
};

#endif /* PEDIDOENCOMENDA_H_ */
