#ifndef MENU_GRAFICOS_H
#define MENU_GRAFICOS_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Menu_graficos {
private:
	RenderWindow ventanappal;
	Sprite spt_fondo;
	Texture txr_fondo;
	///Inpput text
	
protected:
public:
	Menu_graficos();
	~Menu_graficos();
	RenderWindow &ver_ventana();
	void Cerrar_ventana();
	void Cargar_img(string s);
	void Render();
	void Acerca_de();
	string Leer_name();
};

#endif

