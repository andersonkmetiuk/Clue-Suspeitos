#include "Cartas.h"


Cartas::Cartas()
{

}

Cartas::Cartas(std::string nome, std::string tipo)
{
	this->Nome = nome;
	this->Tipo = tipo;
}

Cartas::Cartas(std::string nome, std::string tipo,std::string cor)
{
	this->Nome = nome;
	this->Tipo = tipo;
	this->Cor = cor;
}

Cartas::~Cartas()
{
}


std::string Cartas::getNome(){return Nome;}
void Cartas::setNome(std::string a){Nome= a;}

std::string Cartas::getTipo(){return Tipo;}
void Cartas::setTipo(std::string a){Tipo=a;}

std::string Cartas::getCor(){return Cor;}
void Cartas::setCor(std::string a) {Cor=a;}

