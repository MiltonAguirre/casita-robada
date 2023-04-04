#ifndef GESTOR_GRAFICO_H
#define GESTOR_GRAFICO_H
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include <vector>
#include "Carta.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
using namespace std;
using namespace sf;
class Gestor_grafico {
private:
	RenderWindow ventana;
	///Elementos graficos
	//textura y sprite MESA
	Sprite sprite_mesa;
	Texture textura_mesa;
	//texture y sprite MAZO	
	Texture textura_mazo;
	Sprite sprite_mazo;
	//Sprites cartas
	Sprite *spt_casa_hum;
	Texture *txr_casa_hum;
	Sprite *spt_casa_cpu;
	Texture *txr_casa_cpu;
	Sprite *spt_pozo;
	Texture *txr_pozo;
	Sprite *spt_manohum;
	Texture *txr_manohum;
	Sprite *spt_manocpu;	
	Font fuente_pts;
	Text *texto_pts;
	Text *turno_pts;
	Text *tecla;
	Texture textura_img;
	Sprite sprite_turno;
	Sprite btn_save_spr;
	Texture btn_save_txr;


protected:
public:
	Gestor_grafico();
	void Renderizar_juego(Jugador &cpu, Jugador &hum, vector<Carta> &p, int t, bool vacio);
	RenderWindow &ver_ventana();
	void Cerrar_ventana();
	void Limpiar_punteros();
	void Resultado(Jugador &c, Jugador &h, bool ri);
	Gestor_grafico &operator=(const Gestor_grafico gg);
	void Animar(int x,int y);
	~Gestor_grafico();
};
#endif
