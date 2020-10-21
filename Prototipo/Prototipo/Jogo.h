#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Baralho.h"
#include "Cartas.h"
#include "MonteConfidencial.h"
#include "Jogo.h"
#include "Jogador.h"


class Jogo
{
private:

	

public:
	Jogo();
	~Jogo();
	
void IniciaJogo();
void Loop();

void menu();
void instrucoes();

void Processar_Palpite(Jogador player1, Jogador player2, MonteConfidencial Monte);
bool Validar_Palpite(std::vector<Cartas *> &a, std::vector<Cartas *> &solucao);
void Tela_Padrao(int a);

};

