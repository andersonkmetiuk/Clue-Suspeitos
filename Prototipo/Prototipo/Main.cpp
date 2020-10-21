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

using namespace std;



int main()
{
	
	Jogo play;
	
	play.IniciaJogo();

	system("pause");
	return 0;
}
