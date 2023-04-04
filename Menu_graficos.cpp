#include "Menu_graficos.h"
#include <iostream>
#include <string>
#include "InputText.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
using namespace sf;
using namespace std;
Menu_graficos::Menu_graficos():ventanappal(VideoMode(600,400),"Menú"){
	ventanappal.setPosition(sf::Vector2i(40,50));
	ventanappal.setFramerateLimit(60);
	ventanappal.setKeyRepeatEnabled(true);
	ventanappal.setVerticalSyncEnabled(true);
	ventanappal.setMouseCursorVisible(true);
	spt_fondo.setPosition(0.f,0.f);
}

Menu_graficos::~Menu_graficos() {
	
}

RenderWindow &Menu_graficos::ver_ventana(){
	return ventanappal;
}
void Menu_graficos::Cerrar_ventana(){
	cout<<"cerrar ventana"<<endl;
	ventanappal.close();
}
void Menu_graficos::Cargar_img(string s){
	txr_fondo.loadFromFile(s.c_str());
	spt_fondo.setTexture(txr_fondo);
	
}
void Menu_graficos::Render(){
	ventanappal.clear(sf::Color::Green);
	ventanappal.draw(spt_fondo);
	ventanappal.display();
}
void Menu_graficos::Acerca_de(){
	ventanappal.setVisible(false);
	RenderWindow vtna_acerca(VideoMode(600,400),"Acerca de...");
	vtna_acerca.clear(sf::Color::Blue);
	Text txt_acerca;	
	Text txt_click;	
	Font fte_acerca;
	fte_acerca.loadFromFile("LeagueGothic.otf");
	txt_click.setFont(fte_acerca);
	txt_click.setCharacterSize(30);
	txt_click.setPosition(100,350);
	txt_click.setColor(Color::Red);
	txt_click.setString("Click para volver al Menú");
	txt_acerca.setFont(fte_acerca);
	txt_acerca.setCharacterSize(25);
	txt_acerca.setPosition(50,50);
	txt_acerca.setColor(sf::Color::White);
	txt_acerca.setString("Este software emula un juego de naipes llamado Casita robada.\nHa sido creado para ser evaluado por profesores de\nla Universidad Nacional del Litoral en la mesa de exámen de la materia\nProgramación orientada objetos.\nAutor: Milton Luis Aguirre.\nCarrera: Ing. Informática.\nAño:2017.");
	Event e;
	RectangleShape cuadro(sf::Vector2f(500,300));
	cuadro.setPosition(30,25);
	cuadro.setFillColor(Color::Transparent);
	cuadro.setOutlineColor(Color::Green);
	cuadro.setOutlineThickness(15);
	vtna_acerca.draw(cuadro);
	vtna_acerca.draw(txt_acerca);
	vtna_acerca.draw(txt_click);
	vtna_acerca.display();
	while(vtna_acerca.waitEvent(e)){
		if (e.type==Event::Closed){
			vtna_acerca.close(); ventanappal.setVisible(true);
		}
		if (e.type==Event::MouseButtonReleased 
									&& e.mouseButton.button==Mouse::Left){
		vtna_acerca.close();ventanappal.setVisible(true);
		}
	}
	

}

string Menu_graficos::Leer_name(){
	RenderWindow w(VideoMode(350,200),"Ingrese nombre");
	
	// cargar una fuente para los textos
	sf::Font font;
	font.loadFromFile("arial.ttf");
	
	// crear un texto comun
	sf::Text text_comun("Ingrese un nombre (10 char máx):",font);
	text_comun.setCharacterSize(20);
	text_comun.setColor(sf::Color::Blue);
	text_comun.setPosition(30,50);
	
	string nom;
	// texto que ingresa el usuario
	InputText text_entrada(font,18,sf::Color::White);
	text_entrada.setPosition(100,100);
	text_entrada.setMaxChars(10); // no mas de 10 caracteres
	text_entrada.setSingleWord(true); // no permitir ingresar espacios, para que sea solo una palabra
	
	// bucle principal
	while(w.isOpen()) {
		
		// procesar eventos
		Event e;
		while(w.pollEvent(e)) {
			if(e.type == Event::Closed)
			{w.close();break;}	
			else if (e.type==sf::Event::KeyPressed && e.key.code==sf::Keyboard::Return) { // si apretó enter, se toma la palabra y se la agrega a la lista
				nom = text_entrada.getValue(); // obtener la palabra que se ingresó
				w.close();
			} else text_entrada.processEvent(e); // para que el texto tome las teclas que pulsamos
		}
		// dibujar
		w.clear(Color(25,200,155,255));
		text_entrada.update(); // para que el texto se dibuje correctamente (hay que hacer esta llamada despues de processEvent y antes del draw)
		w.draw(text_comun);
		w.draw(text_entrada);
		w.display();
	}
	nom=text_entrada.getValue();
	if(!nom.empty())ventanappal.close();
	return nom;
}
