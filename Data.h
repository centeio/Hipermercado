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
};

#endif /* DATA_H_ */
