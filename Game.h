#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Carta.h"
#include "Jugador.h"
#include "Gestor_grafico.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include <iterator>
#include <cstddef>
using namespace std;
using namespace sf;
class Game{
private:
	int e;
	///Variables SFML
	Event *miEvento;
	Clock reloj;
	///Elementos del juego
	Gestor_grafico graficos;
	Jugador humano, cpu;
//	fstream mazo_file;
	vector<Carta> mazo;
	vector<Carta> pozo;
	///Variables para eventos
	bool isPlay, me_rindo, mazo_vacio;
	int ronda, turno;
	int juega_carta;	
	int ocurrio_event;
//	vector<int> tam;
	Carta elegida;
	Vector2i coordenadas;
	///METODOS
	void Crear_mazo();
	void Mezclar_mazo();
	void Repartir();
	void Save_game();
	void Load_game();
	//Estructura del juego
	void inicializar(int x);
	void eventos();
	void actualizar();
	void render();
	void limpiar();
	void Scene();
		
public:
	Game();
	Game(string n);
	Game(const Game &g);
	void run(int x);
	~Game();
};
#endif
