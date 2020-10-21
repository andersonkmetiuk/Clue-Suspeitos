#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Cartas.h"


class Baralho
{
protected:
	
	int Numero_Cartas;
	std::vector<Cartas *> colecaoCartas;
	
public:
	 Baralho();
	 ~Baralho();
	

	int getNumero_Cartas();
	void setNumero_Cartas(int a);

	std::vector<Cartas *> getcolecaoCartas();
	void setcolecaoCartas(std::vector<Cartas *> &a); 

	void Leitura();

};

