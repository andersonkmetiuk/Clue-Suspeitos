#pragma once
#include <string>

class Cartas
{
private:
	 
	std::string Nome,Tipo,Cor;
	
public:
	

	Cartas();
	~Cartas();
	Cartas(std::string nome, std::string tipo);
	Cartas(std::string nome, std::string tipo,std::string cor);

	std::string getNome();
	void setNome(std::string a);

	std::string getTipo();
	void setTipo(std::string a);

	std::string getCor();
	void setCor(std::string a);

};

