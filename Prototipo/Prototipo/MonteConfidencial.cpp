#include "MonteConfidencial.h"



MonteConfidencial::MonteConfidencial()
{
}


MonteConfidencial::~MonteConfidencial()
{
}
std::vector<Cartas *> MonteConfidencial::getCartasDistribuidas() {return CartasDistribuidas; }
void MonteConfidencial::setCartasDistribuidas(std::vector<Cartas *> &a) {CartasDistribuidas=a;} 

std::vector<Cartas *> MonteConfidencial::getCartasSolucao() {return CartasSolucao; }
void MonteConfidencial::setCartasSolucao(std::vector<Cartas *> &a) {CartasSolucao=a;} 


/*LÊ O ARQUIVO TXT , RETIRA 3 CARTAS (1 DE CADA TIPO) E COLOCA NO MONTE DO CONFIDENCIAL, DEPOIS AS CARTAS RESTANTES
SÃO COLOCADAS EM UM MONTE DE EVIDENCIAS QUE SERÁ DISTRIBUIDO ENTRE OS JOGADORES*/
void MonteConfidencial::Leitura() 
{
	bool nomeRecuperado = false;
	bool tipoRecuperado = false;
	std::string nome_aux, tipo_aux;
	std::ifstream arquivo( "DefinicaoCartas.txt");
	std::string valor;
	int n_cartas=0;
	std::vector<Cartas *> vetor_aux;

	//le arquivo
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
				Cartas *carta_aux = new Cartas(nome_aux,tipo_aux,"Evidencia"); //cria um objeto auxiliar para armazenar os valores (carta da cor evidencia pro monte confidencial)
				vetor_aux.push_back(carta_aux); //joga os valores do objeto auxiliar no vector de cartas
				nomeRecuperado = false;
				tipoRecuperado = false;
				n_cartas++;

			}
		}


	}

	MonteConfidencial::setNumero_Cartas(3);
	//sorteio
	int i,pos=0,sorteio[3],temp;
	bool controle = false;
	srand(time(0));
	Cartas *carta_aux = new Cartas(nome_aux,tipo_aux,"Evidencia");
	std::string tipo_confere[3];
	while(1) //loop do sorteio
	{


		i=rand()%n_cartas;
		carta_aux = vetor_aux[i];

		for(temp=0; temp<3;temp++) //verifica se o numero ja foi sorteado
		{
			if(sorteio[temp] == i) 
			{
				controle=true;
				break;
			}


		}
		if(controle == false) //se não tiver numero repetido, verifique o tipo
		{

			for(temp=0; temp<3;temp++) //verifica se o tipo ja foi sorteado
			{
				if(tipo_confere[temp] == carta_aux->getTipo()) 
				{
					controle=true;
					break;
				}


			}
		}
		if(controle == false) //se o tipo nem o numero foram sorteados, atribuir
		{
			sorteio[pos] = i;
			tipo_confere[pos] = carta_aux->getTipo();
			CartasSolucao.push_back(carta_aux);
			pos++;


		}
		controle = false;
		if (pos==3)
			break;

	}

	for(temp=0 ; temp <3 ; temp++) // elimina os elementos que foram sorteados
	{
		vetor_aux.erase ( vetor_aux.begin() + sorteio[temp]);
		n_cartas--;
	}
	setCartasDistribuidas(vetor_aux);
	setNumero_Cartas(n_cartas);

	arquivo.close();//fecha o arquivo
	

}

/*DEPOIS QUE AS 3 CARTAS SÃO RETIRADAS PARA O MONTE CONFIDENCIAL, O MONTE DE EVIDENCIAS É EMBARALHADO. */
void  MonteConfidencial::Embaralhar() 
{
	int metade = (Numero_Cartas / 2);

	std::vector<Cartas *> esquerda;
	std::vector<Cartas *> direita;
	int pos=0,x,y=0;
	srand(time(0));

	x=rand()%100 + 30; //embaralha de 30 a 100 vezes
	for(int j = 0 ; j< x ; j++) // numero de vezes que vai embaralhar
	{
		for (int i = 0; i < metade; i++)
			esquerda.push_back(CartasDistribuidas[i]);

		pos = 0;
		for (int i = metade; i < Numero_Cartas; i++)
			direita.push_back(CartasDistribuidas[i]);

		pos = 0;
		CartasDistribuidas.clear();
		for (int i = 0; i < metade; i ++)
		{ 
			if(y=0)
			{
				CartasDistribuidas.push_back(esquerda[i]) ;
				CartasDistribuidas.push_back(direita[i]) ;
				y=1;
			}
			else
			{				
				CartasDistribuidas.push_back(direita[i]) ;
				CartasDistribuidas.push_back(esquerda[i]) ;
				y=0;
			}
		}
	}
	
}

/*DEPOIS Q AS CARTAS FORAM EMBARALHADAS ELAS SÃO DISTRIBUIDAS ENTRE OS JOGADORES*/
void MonteConfidencial::DistribuiCartas(Jogador *p1, Jogador *p2)
{
	//Jogador j;
	Baralho aux,b_p1,b_p2;
	MonteConfidencial aux_p1,aux_p2;
	std::vector<Cartas *> vec_cartas_p1;
	std::vector<Cartas *> vec_cartas_p2;
	int k=1,i,n1=0,n2=0;

	//lê as cartas do txt e atribui aos jogadores as cartas padrões de arquivo
	//CARTAS ARQUIVO
	aux.Leitura();
	p1->setMao_arquivo(aux);
	p2->setMao_arquivo(aux);
	//CARTAS EVIDENCIA
	for( i = 0 ; i< Numero_Cartas; i++) //distribui as cartas igualmente num vetor pra cada player
	{
		/*diversas alternâncias pra ficar melhor a distribuição
		visto que deixando somente a ordem p1 e p2 um deles ficava com muitos suspeitos
		e outro com muitas armas e lugares, assim é como se embaralhássemos mais uma vez para garantir
		que as cartas sejam bem distribuidas (isso simularia o "CORTE" que é feito em alguns jogos de carta)
		*/
		if(k==1 )
		{
			vec_cartas_p1.push_back(CartasDistribuidas[i]);
			k++;
			n1++;
		}
			
		else if (k==2)
		{
			vec_cartas_p2.push_back(CartasDistribuidas[i]);
			k++;
			n2++;
		}
		else if (k==3)
		{
			vec_cartas_p2.push_back(CartasDistribuidas[i]);
			k++;
			n2++;
		}
		else 
		{
			vec_cartas_p1.push_back(CartasDistribuidas[i]);
			k=1;
			n1++;
		}
			
	}
	//atribui o vetor aos baralhos auxiliares b_p1 e b_p2
	b_p1.setcolecaoCartas(vec_cartas_p1);
	b_p1.setNumero_Cartas(n1);
	b_p2.setcolecaoCartas(vec_cartas_p2);
	b_p2.setNumero_Cartas(n2);

	//atribui os baralhos aos players
	p1->setMao_evidencia(b_p1);
	p2->setMao_evidencia(b_p2);
	
	
}
