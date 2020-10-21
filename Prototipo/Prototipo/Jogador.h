#pragma once
#include <string>
#include "Cartas.h"
#include "Baralho.h"
class Jogador
{
	private:
	std::string Nome;	
	Cartas Resposta,R_Aux;
	std::vector<Cartas *> Pergunta;
	std::vector<Cartas *> Palpite;
	Baralho Mao_evidencia, Mao_arquivo;
	std::vector<Cartas *> Evidencias_Oponente;
	
	

public:
	Jogador();
	~Jogador();

Baralho getMao_evidencia();
void setMao_evidencia(Baralho a);

Baralho getMao_arquivo();
void setMao_arquivo(Baralho a);

std::string getNome();
void setNome(std::string a);


std::vector<Cartas *>  getPergunta(); 
void addPergunta(Cartas  *a , Cartas* b );

std::vector<Cartas *>  getEvidencias_Oponente(); 
void addEvidencias_Oponente(Cartas  *evidencias_oponente);
void IniciaEvidencias_Oponente();

Cartas *Busca_Carta(int pos_carta);


Cartas getResposta();
void addResposta(std::vector<Cartas *> &Perg);

Cartas getR_Aux();
void setR_Aux(Cartas *a);


std::vector<Cartas *> getPalpite();
void addPalpite(Cartas *a, Cartas *b, Cartas *c);
void Quero_addPalpite();
void Quero_addPergunta();



void ImprimeRespOponente(Cartas *resp);
void Imprime_Cartas();

void Imprime_Evidencias();
void Imprime_Descarte();


};

