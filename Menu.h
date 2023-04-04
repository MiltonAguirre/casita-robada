#ifndef MENU_H
#define MENU_H
#include "Menu_graficos.h"
#include <SFML/Window/Event.hpp>
#include <string>
using namespace std;
using namespace sf;
class Menu {
private:
	Menu_graficos *graficos;
	Event evento;
	int paso_evento;
	int mouseX, mouseY;
	int play;
	int load_g;
	bool click_left;
	int acerca;
	string nombre;
protected:
public:
	Menu();
	void Load_game();
	void inicializar();
	void eventos();
	void actualizar();
	void render();
	void run();
	void limpiar();
	~Menu();
};

#endif

