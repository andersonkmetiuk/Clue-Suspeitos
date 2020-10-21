#include "Baralho.h"

Baralho::Baralho()
{
	
	
}

Baralho::~Baralho()
{
}

int Baralho::getNumero_Cartas(){return Numero_Cartas;}
void Baralho::setNumero_Cartas(int a){Numero_Cartas=a;}

std::vector<Cartas *> Baralho::getcolecaoCartas(){return colecaoCartas;}
void Baralho::setcolecaoCartas(std::vector<Cartas *> &a){colecaoCartas = a;}
void Baralho::Leitura()
{
	bool nomeRecuperado = false;
	bool tipoRecuperado = false;
	std::string nome_aux, tipo_aux;
	std::ifstream arquivo( "DefinicaoCartas.txt");
	std::string valor;
	int n_cartas=0;
	while (!arquivo.eof())
	{
		while(getline(arquivo,valor,';'))
		{
			if (!tipoRecuperado) //verifica se o tipo foi encontrado e atribuido à variável
			{
				tipo_aux = valor;
				tipoRecuperado = true;
			}
			else //verifica se o nome foi encontrado e atribuido à variável
			{
				nome_aux = valor;
				nomeRecuperado = true;
			}			

			if (tipoRecuperado && nomeRecuperado) //quando os 2 atributos foram recuperados do txt
			{
				Cartas *carta_aux = new Cartas(nome_aux,tipo_aux); //cria um objeto auxiliar para armazenar os valores
				colecaoCartas.push_back(carta_aux); //joga os valores do objeto auxiliar no vector de cartas
				nomeRecuperado = false;
				tipoRecuperado = false;
				n_cartas++;
			}
		}
		

	}
	Baralho::setNumero_Cartas(n_cartas);
	arquivo.close(); //fecha o arquivo
}