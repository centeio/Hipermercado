/*
 * Data.cpp
 *
 *  Created on: 29/10/2015
 *      Author: Carolina
 */

#include "Data.h"

Data::Data(){};

Data::Data(unsigned int dia, unsigned int mes, unsigned int ano): dia(dia), mes(mes), ano(ano) {}

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
}

void Data::setDia(unsigned int dia){dia(dia);}

void Data::setMes(unsigned int mes){mes(mes);}

void Data::setAno(unsigned int ano){ano(ano);}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

