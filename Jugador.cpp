#include "Jugador.h"
#include <string>
#include <vector>
#include "Carta.h"

using namespace std;

Jugador::Jugador() {	
}
Jugador::Jugador(string n):nombre(n){ 
}
string Jugador::Ver_nombre(){
	return nombre;
}
vector<Carta> &Jugador::Ver_mano(){
	return mano;
}
vector<Carta> &Jugador::Ver_casa(){
	return casa;
}
Jugador &Jugador::operator=(const Jugador &j){
	this->nombre=j.nombre;
	this->mano=j.mano;
	return *this;
}
Carta Jugador::Ver_carta(int i){
	return mano[i];
}
Jugador::~Jugador() {
}
