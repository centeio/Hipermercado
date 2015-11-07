/*
 * Data.h
 *
 *  Created on: 29/10/2015
 *      Author: Carolina
 */

#ifndef DATA_H_
#define DATA_H_

#include <iostream>


using namespace std;

class Data {
private:
	unsigned int dia;
	unsigned int mes;
	unsigned int ano;
public:
	Data();
	Data(unsigned int dia, unsigned int mes, unsigned int ano);
	virtual ~Data();
	bool operator<(Data d2);
	unsigned int getDia() const{return dia;};
	unsigned int getMes() const{return mes;};
	unsigned int getAno() const{return ano;};
	void setDia(unsigned int novodia);
	void setMes(unsigned int novomes);
	void setAno(unsigned int novoano);
	bool operator==(Data d2);
	friend ostream &operator<<(ostream& os,const Data& d);
};

#endif /* DATA_H_ */
