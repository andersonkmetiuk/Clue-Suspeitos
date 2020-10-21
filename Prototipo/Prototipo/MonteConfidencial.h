#pragma once
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "Baralho.h"
#include "Jogador.h"


class MonteConfidencial :	public Baralho //MonteConfidencial Filha de baralho
{
private: 
	std::vector<Cartas *> CartasDistribuidas;
	std::vector<Cartas *> CartasSolucao;
public:
	MonteConfidencial();
	~MonteConfidencial();
	std::vector<Cartas *> getCartasDistribuidas();
	void setCartasDistribuidas(std::vector<Cartas *> &a); 

	std::vector<Cartas *> getCartasSolucao();
	void setCartasSolucao(std::vector<Cartas *> &a); 

	void Leitura();
	void  Embaralhar();
	
	void DistribuiCartas(Jogador *a, Jogador *b);
	
};

