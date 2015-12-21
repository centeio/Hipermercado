/*
 * Data.cpp
 *
 *  Created on: 29/10/2015
 *      Author: Carolina
 */

#include "Data.h"



Data::Data(){};

Data::Data(unsigned int dia, unsigned int mes, unsigned int ano): dia(dia), mes(mes), ano(ano) {
	/**
	 *	@brief Cria a data
	 */
}

bool Data::operator<(Data d2){
	if(ano==d2.ano)
		if(mes==d2.mes)
			if(dia==d2.dia)
				return false;
			else
				if(dia>d2.dia)
					return false;
				else
					return true;
		else
			if(mes>d2.mes)
				return false;
			else
				return true;
	else
		if(ano>d2.ano)
			return false;
		else
			return true;
	/**
	 	 *
		 *
		 *	@param d2 Data
		 *
		 *	@return Retorna verdadeiro se a data a ser comparada e mais antiga
		 */
}

void Data::setDia(unsigned int novodia){
	dia=novodia;
	/**
	*	@brief Define o dia
	*
	* @param novodia Novo dia
	*/
}

void Data::setMes(unsigned int novomes){
	mes=novomes;
	/**
	*	@brief Define o mes
	*
	* @param novomes Novo mes
	*/
}

void Data::setAno(unsigned int novoano){
	ano=novoano;
	/**
	*	@brief Define o ano
	*
	* @param novoano Novo ano
	*/
}

bool Data::operator==(Data d2){
	if(dia==d2.dia && mes==d2.mes && ano==d2.ano)
		return true;
	return false;
	/**
			*
			*	@param d2 Data
			*
			*	@return Retorna verdadeiro se as duas datas comparadas sao iguais; caso contrario, retorna falso.
			*/
}

ostream &operator<<(ostream& os,const Data& d){
	os<<d.dia<<"-"<<d.mes<<"-"<<d.ano;
	return os;
	/**
				*
				* @brief Imprime no ecra os atributos da classe por overload do operator<<
				*	@param os Objeto da iostream
				*	@param d Data
				*
				*	@return Retorna ostream
				*/
}

Data::~Data() {
	// TODO Auto-generated destructor stub
	/**
			*	@brief Destroi a data
			*
			*/
}

/*bool Data::maisDeUmAno(){
	if(ano+1<dataactual.ano)
		return true;
	else
		if(ano+1==dataactual.ano)
			if(mes==dataactual.mes)
				if(dia<=dataactual.dia)
					return true;
				else
					return false;
			else if(mes<dataactual.mes)
				return true;
			else
				return false;
		else
			return false;


}*/
