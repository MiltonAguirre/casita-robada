#include "Carta.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

Carta::Carta() {
}
Carta::Carta(char pa, int nu):palo(pa),numero(nu){
}
Carta::Carta(const Carta &arg) {
	palo=arg.palo;
	numero=arg.numero;
}
char Carta::Ver_palo(){
	return palo;
}
int Carta::Ver_numero(){
	return numero;
}
string Carta::Ver_direccion(){
	stringstream dir;
	dir<<palo<<numero<<".png";
	return dir.str();
}
bool Carta::operator==(const Carta &c){
	return (this->numero==c.numero || this->palo==c.palo);
}
bool Carta::operator!=(const Carta &c){
	return !(this->numero==c.numero || this->palo==c.palo) ;
}
bool Carta::operator<(const Carta &c)const{
	return this->numero<c.numero;
}
bool Carta::operator>(const Carta &c){
	return this->numero>c.numero;
}
bool Carta::operator<=(const Carta &c){
	return this->numero<=c.numero;
}
bool Carta::operator>=(const Carta &c){
	return this->numero>=c.numero;
}
Carta &Carta::operator=(const Carta c){
	this->palo=c.palo;
	this->numero=c.numero;
	return *this;
}
Carta::~Carta() {
}
