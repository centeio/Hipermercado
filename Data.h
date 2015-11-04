/*
 * Data.h
 *
 *  Created on: 29/10/2015
 *      Author: Carolina
 */

#ifndef DATA_H_
#define DATA_H_

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
	void setDia(unsigned int dia);
	void setMes(unsigned int mes);
	void setAno(unsigned int ano);
};

#endif /* DATA_H_ */
