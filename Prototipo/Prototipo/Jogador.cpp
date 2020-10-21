#include "Jogador.h"


Jogador::Jogador()
{
}


Jogador::~Jogador()
{
}

std::string Jogador::getNome(){return Nome;}
void Jogador::setNome(std::string a){Nome=a;}

std::vector<Cartas *> Jogador::getPergunta(){return Pergunta;}

Cartas *Jogador::Busca_Carta(int pos_carta)
{
	std::vector<Cartas *> aux;
	aux = Mao_arquivo.getcolecaoCartas();

	return aux[pos_carta];
}

void Jogador::addPergunta(Cartas  *a , Cartas *b )
{
	//limpa o vetor para evitar que as perguntas se repitam
	if( !Pergunta.empty() )
		Pergunta.clear();
	a->setCor("Evidencia");
	b->setCor("Evidencia");
	Pergunta.push_back(a);
	Pergunta.push_back(b);

}




Cartas Jogador::getResposta(){return Resposta;}

/*RECEBE COMO PARÂMETRO UMA PERGUNTA, QUE NO CASO É A DO OPONENTE E COMPARA COM SUAS CARTAS
PARA VER SE ALGUMA É IGUAL */

void Jogador::addResposta(std::vector<Cartas *> &Perg)
{
	int n=0,j,i,m;
	std::vector<Cartas *> aux, Resp;
	aux = Mao_evidencia.getcolecaoCartas();
	m = Mao_evidencia.getNumero_Cartas();
	Cartas c1_aux, c2_aux;

	//LOOP QUE COMPARA PERGUNTA E TIRA UMA RESPOSTA
	for(i=0; i<2; i++) //testa as 2 perguntas
	{
		for(j=0;j<m ; j++) //compara as perguntas com o vetor de evidencia
		{
			if( (Perg[i])->getNome() == (aux[j])->getNome())
			{
				Resp.push_back(aux[j]);
				n++;
			}
		}
	}
	//imprime a pergunta
	std::cout<<"A pergunta foi: " <<(Perg[0])->getNome()<< " e " << (Perg[1])->getNome() << std::endl;
	//DEPOIS DE ACHAR A RESPOSTA ATRIBUIMOS O VALOR
	//NENHUMA CARTA IGUAL 
	if(n==0)
	{
		Cartas *c = new Cartas("NULL", "NULL","Evidencia");
		std::cout<< "Voce nao tem nenhuma das cartas que foram perguntadas!" <<std::endl<<std::endl;
		Resposta = *c;
		
	}		
	// 1 CARTA CORRESPONDENTE
	else if (n==1) 
	{
		c1_aux.setNome((Resp[n-1])->getNome());
		c1_aux.setTipo((Resp[n-1])->getTipo());
		c1_aux.setCor((Resp[n-1])->getCor());
		Cartas *c = new Cartas( c1_aux.getNome(), c1_aux.getTipo(), c1_aux.getCor() );
		std::cout << "Voce tem a carta: " << c1_aux.getNome()<<std::endl<<std::endl;
		Resposta = *c;
		
	}
	// 2 CARTAS CORRESPONDENTES
	else
	{
		c1_aux.setNome((Resp[n-2])->getNome());
		c1_aux.setTipo((Resp[n-2])->getTipo());
		c1_aux.setCor((Resp[n-2])->getCor());

		c2_aux.setNome((Resp[n-1])->getNome());
		c2_aux.setTipo((Resp[n-1])->getTipo());
		c2_aux.setCor((Resp[n-1])->getCor());

		int k;
		std::cout << "Voce tem as cartas:\n1) "<< c1_aux.getNome() <<std::endl;
		std::cout<<"2) "<< c2_aux.getNome() <<std::endl;
		std::cout<<"Qual deseja mostrar? Escolha o numero correspondente: "<<std::endl;

		std::cin>>k;

		while(k !=1 && k !=2)
		{
			std::cout<< "Digite numero 1 ou 2 !!!"<<std::endl;
			std::cin>>k;
		}
		if(k==1)
		{
			Cartas *c = new Cartas(c1_aux.getNome(),c1_aux.getTipo(),c1_aux.getCor());
			Resposta = *c;
			std::cout<<"Voce resolveu mostrar: "<<c1_aux.getNome()<<std::endl;
		}

		else 
		{
			Cartas *c = new Cartas(c2_aux.getNome(),c2_aux.getTipo(),c2_aux.getCor());
			Resposta = *c;
			std::cout<<"Voce resolveu mostrar: "<<c2_aux.getNome()<<std::endl;
		}

		std::cout<<std::endl;
	}
}


Baralho Jogador::getMao_evidencia(){return Mao_evidencia;}
void Jogador::setMao_evidencia(Baralho a){ Mao_evidencia = a;}

Baralho Jogador::getMao_arquivo() {return Mao_arquivo;}
void Jogador::setMao_arquivo(Baralho a){Mao_arquivo = a;}



void Jogador::ImprimeRespOponente(Cartas *resp)
{
	std::string a;
	if(resp->getNome() == "NULL")
		std::cout<<"Seu oponente nao tinha nenhuma das cartas perguntadas!"<<std::endl;
	else
	{
		std::cout<<"Seu oponente tem a seguinte carta: " << resp->getNome() <<std::endl;
		std::cout<<"\nDeseja anotar essa carta no monte de cartas descobertas? "<<std::endl;
		std::cout<<"\nSe SIM , digite 'S' ou 's' (ou digite qualquer letra pra sair) "<<std::endl;
		std::cin>>a;
		if(a=="S" || a=="s")
		{
			setR_Aux(resp);
			addEvidencias_Oponente(&R_Aux);
		}
	}

	std::cout<<std::endl;


}

std::vector<Cartas *> Jogador::getPalpite(){return Palpite;}

void Jogador::addPalpite(Cartas *a, Cartas *b, Cartas *c) 
{
	Palpite.push_back(a);
	Palpite.push_back(b);
	Palpite.push_back(c);
}

void Jogador::Quero_addPalpite()
{



	int x;
	Cartas *c_suspeito,*c_arma,*c_local;
	std::vector<Cartas *> aux;
	aux = Mao_arquivo.getcolecaoCartas();

	Imprime_Evidencias();
	Imprime_Descarte();
	Imprime_Cartas();
	//ESCOLHA DO SUSPEITO
	std::cout<<std::endl<<std::endl;
	std::cout<<"Escolha um suspeito (Digite um numero de 1 a 6): "<<std::endl;
	std::cin>>x;
	std::cout<<std::endl;
	while (x<1 || x>6)
	{
		std::cout<<"Digite um numero de 1 a 6!!!"<<std::endl;
		std::cin>>x;
	}

	c_suspeito = aux [x-1];

	// ESCOLHA DA ARMA
	std::cout<<std::endl<<std::endl;
	std::cout<<"Escolha uma Arma (Digite um numero de 7 a 10): "<<std::endl;
	std::cin>>x;
	std::cout<<std::endl;
	while (x<7 || x>10)
	{
		std::cout<<"Digite um numero de 7 a 10!!!"<<std::endl;
		std::cin>>x;
	}

	c_arma = aux [x-1];

	//ESCOLHA DO LOCAL

	std::cout<<std::endl<<std::endl;
	std::cout<<"Escolha um Local (Digite um numero de 11 a 15): "<<std::endl;
	std::cin>>x;
	std::cout<<std::endl;
	while (x<11 || x>15)
	{
		std::cout<<"Digite um numero de 11 a 15!!!"<<std::endl;
		std::cin>>x;
	}

	c_local = aux [x-1];

	//ATRIBUI OS VALORES AO PALPITE
	addPalpite(c_suspeito, c_arma, c_local);
}

void Jogador::Imprime_Cartas()
{
	int m,i;
	std::vector<Cartas *> aux;
	aux = Mao_arquivo.getcolecaoCartas();
	m = Mao_arquivo.getNumero_Cartas();

	std::cout<<"\nCartas para perguntar:"<<std::endl;
	for( i = 0 ; i< m ; i++)
	{
		if(i==0)
			std::cout<<"Suspeito:"<<std::endl;
		else if(i==6)
			std::cout<<"Arma:"<<std::endl;
		else if (i==10)
			std::cout<<"Local:"<<std::endl;

		std::cout<<""<<i+1<<")"<< aux[i]->getNome()<<std::endl;
	}
}

void Jogador::Quero_addPergunta()
{
	int c1,c2;
	Cartas *carta1,*carta2;


	Imprime_Evidencias();
	Imprime_Descarte();
	Imprime_Cartas();

	std::cout<<"Escolha 2 cartas diferentes:"<<std::endl;


	std::cout<<std::endl;
	std::cout<<"Carta 1):"<<std::endl;
	std::cin>>c1;

	while(c1<=0 || c1>15)
	{
		std::cout<<"Escolha um numero de 1 a 15!\nCarta 1):"<<std::endl;
		std::cin>>c1;
	}

	std::cout<<std::endl;
	std::cout<<"Carta 2):"<<std::endl;
	std::cin>>c2;

	while(c2<=0 || c2>15 || c2==c1)
	{
		std::cout<<"Escolha um numero de 1 a 15 e diferente do primeiro!\nCarta 1):"<<std::endl;
		std::cin>>c2;
	}
	c1--;
	c2--;
	//Busca a carta correspondente
	carta1 = Busca_Carta(c1);
	carta2 = Busca_Carta(c2);
	//add as cartas à pergunta
	addPergunta(carta1 , carta2 );
	std::cout<<std::endl;
	std::cout<<"PRESSIONE QUALQUER BOTAO PARA PASSAR A VEZ PARA O PROXIMO JOGADOR"<<std::endl;
	std::cout<<std::endl;
	system("pause");
	system("cls");

}

std::vector<Cartas *>  Jogador::getEvidencias_Oponente(){return  Evidencias_Oponente;}

void Jogador::addEvidencias_Oponente(Cartas  *evidencias_oponente)
{
	int i,m,temp=0;
	m=Evidencias_Oponente.size();
	
	//EVITA QUE AS EVIDENCIAS DESCOBERTAS SEJAM IMPRESSAS DUPLICADAS
	//CASO A PERGUNTA SEJA FEITA MAIS Q UMA VEZ
	for(i=0;i<m;i++)
	{
		if(Evidencias_Oponente[i] == evidencias_oponente)
		{
			temp++;
			break;
		}
	}

	if(temp==0)
		Evidencias_Oponente.push_back(evidencias_oponente);
}

void Jogador::Imprime_Evidencias()
{
	int i,m;
	std::vector<Cartas *> aux;
	aux = Mao_evidencia.getcolecaoCartas();
	m= Mao_evidencia.getNumero_Cartas();

	std::cout<<"\nSuas cartas de Evidencia:"<<std::endl;
	for( i=0; i<m;i++)
		std::cout<< (aux[i])->getNome() <<std::endl;

}

void Jogador::Imprime_Descarte()
{

	int i,m;
	std::vector<Cartas *> aux;
	m=Evidencias_Oponente.size();
	aux = Evidencias_Oponente;

	std::cout<<"\nCartas descobertas\n(que nao se encontram no monte confidencial/monte solucao):"<<std::endl;
	for( i=0; i<m;i++)
		std::cout<< (aux[i])->getNome() <<std::endl;
}

void Jogador::IniciaEvidencias_Oponente()
{
	Evidencias_Oponente = Mao_evidencia.getcolecaoCartas();
}

Cartas Jogador::getR_Aux(){return R_Aux;}
void Jogador::setR_Aux(Cartas *a){ R_Aux = *a;}