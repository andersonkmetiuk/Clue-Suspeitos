#include "Jogo.h"


Jogo::Jogo(void)
{
}


Jogo::~Jogo(void)
{
}




void Jogo::menu()
{
	int menu;
	std::cout <<"\t\t\t***CLUE SUSPEITOS***\n\n";
	std::cout << "Digite o numero correspondente a opcao selecionada\n1. Jogar\n2. Instrucoes\n3. Sair\n\n";
	std::cin >> menu;

	while(menu <= 0 || menu >= 4)
	{
		std::cout<<"Digite um numero valido!!!"<<std::endl;
		std::cin >> menu;
	}
	switch(menu)
	{
	case 1:
		system("cls");
		Loop();
		break;
	case 2:
		instrucoes();
		break;
	case 3:			
		system("cls");
		std::cout<<"FIM"<<std::endl;
		break;

	}		

}

void Jogo::instrucoes()
{
	std::cout << "\nVoce precisa descobrir os detalhes de um assassinato!\n";
	std::cout << "Em cada jogo eh sorteado  uma carta de suspeito, uma arma e um\nlugar, que sao a resposta do enigma.\nOs jogadores recebem as cartas restantes ";
	std::cout << "e sabem que elas nao estao incluidas \nno assassinato.\n";
	std::cout << "Os jogadores fazem perguntas um pro outro ate \num deles arriscar dar um palpite.\n";
	std::cout << "Cuidado! Se voce dar um palpite e errar, voce perde!\n\n";
	system("pause");
	system("cls");
	menu();
} 


bool Jogo::Validar_Palpite(std::vector<Cartas *> &a, std::vector<Cartas *> &solucao)
{
	int i, j,temp=0;


	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if((solucao[i])->getNome()==(a[i])->getNome())
			{
				temp++;
				break;
			}
		}
	}
	if(temp==3)
		return true;
	else
		return false;

}
void Jogo::Processar_Palpite(Jogador player1, Jogador player2, MonteConfidencial Monte)
{
	player1.Quero_addPalpite();
	if( Validar_Palpite( player1.getPalpite() , Monte.getCartasSolucao() ) )
	{
		system("cls");
		std::cout<<"\t\t\tVOCE GANHOU!!!\n\n"<<std::endl;


	}
	else
	{
		system("cls");
		std::cout<<"\t\t\tVOCE ERROU!!!\n\n"<<std::endl;
		std::cout<<"\t\t\tDEIXE O PROXIMO JOGADOR TENTAR\n\n"<<std::endl;
		std::cout<<"\n\n***PROXIMO JOGADOR: APERTE ALGUMA TECLA PARA CONTINUAR!!!***\n\n"<<std::endl;
		system("pause");
		player2.Quero_addPalpite();
		if( Validar_Palpite( player2.getPalpite() , Monte.getCartasSolucao() ) )
		{
			std::cout<<"\t\t\tVOCE GANHOU!!!\n\n"<<std::endl;
		}
		else
		{
			system("cls");
			std::cout<<"\t\t\tVOCES ERRARAM!!!\n\n"<<std::endl;
			std::cout<<"\t\t\tNINGUEM GANHOU!!!"<<std::endl;
			

		}
	}
}

void Jogo::IniciaJogo()
{
	menu();
}

void Jogo::Loop()
{

	//INICIALIZACOES
	//SEQUENCIA DO JOGO

	MonteConfidencial Monte;
	Jogador player1, player2;
	std::string p;

	player1.setNome("Jogador 1");
	player2.setNome("Jogador 2");

	Monte.Leitura();

	Monte.Embaralhar();

	Monte.DistribuiCartas(&player1,&player2);
	player1.IniciaEvidencias_Oponente();
	player2.IniciaEvidencias_Oponente();

	//LOOP
	while(1)
	{
		Tela_Padrao(1);

		std::cout<<"\t\tJOGADOR 1"<<std::endl;
		player1.Quero_addPergunta();

		Tela_Padrao(2);

		std::cout<<"\t\tJOGADOR 2"<<std::endl;
		player2.addResposta(player1.getPergunta());

		Tela_Padrao(3);
		Tela_Padrao(1);

		std::cout<<"\t\tJOGADOR 1"<<std::endl;
		player1.ImprimeRespOponente(&player2.getResposta());

		Tela_Padrao(4);

		std::cin>>p;
		system("cls");
		if(p=="S"||p=="s")	
		{

			Processar_Palpite(player1, player2, Monte);

			break;
		}

		Tela_Padrao(2);

		std::cout<<"\t\tJOGADOR2"<<std::endl;
		player2.Quero_addPergunta();//

		Tela_Padrao(1);

		std::cout<<"\t\tJOGADOR 1"<<std::endl;
		player1.addResposta(player2.getPergunta());

		Tela_Padrao(3);
		Tela_Padrao(2);

		std::cout<<"\t\tJOGADOR 2"<<std::endl;
		player2.ImprimeRespOponente(&player1.getResposta());

		Tela_Padrao(4);

		std::cin>>p;
		system("cls");
		if(p=="S"||p=="s")	
		{

			Processar_Palpite(player2, player1,  Monte);
			break;
		}
		system("cls");

	}

	int a,b,c,i;

	std::vector<Cartas *> aux;
	aux= Monte.getCartasSolucao();
	for(i=0;i<3;i++)
	{ 
		if ( (aux[i])->getTipo() == "Suspeito" )
			a=i;

		else if ( (aux[i])->getTipo() == "Arma" )
			b=i;

		else if ( (aux[i])->getTipo() == "Lugar" )
			c=i;
	}
	std::cout<<"\n\n\t\t\t***SOLUCAO***"<<std::endl;
	std::cout<<"\n\nAssassino: "<< (aux[a])->getNome() <<std::endl;
	std::cout<<"\nArma: "<< (aux[b])->getNome()  <<std::endl;
	std::cout<<"\nLocal: "<< (aux[c])->getNome() <<std::endl;
	std::cout<<"\n\n\t\t\tFIM!!!\n"<<std::endl;


}

void Jogo::Tela_Padrao(int a)
{
	if(a==1)
	{
		system("cls");
		std::cout<<"\n\n\t\t\t***TURNO***"<<std::endl;
		std::cout<<"\t\t\t***DO***"<<std::endl;
		std::cout<<"\t\t\t***JOGADOR 1***"<<std::endl;
		std::cout<<"\nPRESSIONE QUALQUER BOTAO PARA COMECAR SUA JOGADA!!!\n"<<std::endl;
		system("pause");
		system("cls");
	}
	else if(a==2)
	{
		system("cls");
		std::cout<<"\n\n\t\t\t***TURNO***"<<std::endl;
		std::cout<<"\t\t\t***DO***"<<std::endl;
		std::cout<<"\t\t\t***JOGADOR 2***"<<std::endl;
		std::cout<<"\nPRESSIONE QUALQUER BOTAO PARA COMECAR SUA JOGADA!!!\n"<<std::endl;
		system("pause");
		system("cls");
	}
	else if(a==3)
	{
		std::cout<<std::endl;
		std::cout<<"PRESSIONE QUALQUER BOTAO PARA PASSAR A VEZ PARA O PROXIMO JOGADOR"<<std::endl;
		std::cout<<std::endl;
		system("pause");
		system("cls");
	}
	else if(a==4)
	{
		std::cout<<"Quer dar palpite?(Digite 'S' ou 's' se quiser)\n"<<std::endl;
		std::cout<<"SE NAO DIGITE QUALQUER LETRA E PASSE A VEZ PARA O PROXIMO JOGADOR"<<std::endl;
	}
	
}