#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <vector>
#include "Carta.h"
using namespace std;

class Jugador {
private:
	std::string nombre;
	std::vector<Carta> mano;
	std::vector<Carta> casa;
protected:
public:
	Jugador();
	Jugador(string n);
	string Ver_nombre();
	vector<Carta> &Ver_mano();
	vector<Carta> &Ver_casa();
	Carta Ver_carta(int i);
	Jugador &operator=(const Jugador &j);
	~Jugador();
};

#endif

