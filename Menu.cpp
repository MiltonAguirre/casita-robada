#include "Menu.h"
#include <iostream>
#include "Game.h"
using namespace std;
using namespace sf;
Menu::Menu() {
	
}

Menu::~Menu() {
	
}
void Menu::inicializar(){
	cout<<"iniciar menu"<<endl;
	paso_evento=0;
	acerca=0;
	play=0;
	load_g=0;
	click_left=false;
	graficos=new Menu_graficos();
}
void Menu::eventos(){
	cout<<"Eventos menu"<<endl;
	Vector2i vec;
	vec=sf::Mouse::getPosition(graficos->ver_ventana());
	mouseX=vec.x;
	mouseY=vec.y;
	while(graficos->ver_ventana().pollEvent(evento)){
		
		if(evento.type==Event::Closed){
			limpiar(); exit(0);
		}
		if(evento.type==Event::MouseButtonReleased && evento.mouseButton.button==Mouse::Left){
			click_left=true;
			paso_evento=1;
			mouseX=evento.mouseButton.x;
			mouseY=evento.mouseButton.y;
			cout<<"x: "<<mouseX<<" y: "<<mouseY<<endl;
			break;
		}
		if(evento.type==evento.KeyPressed && evento.key.code==Keyboard::G){
			cout<<"evento->load_g"<<endl;
			load_g=1;break;
		}
	}
}
void Menu::actualizar(){
	cout<<"actualizar menu"<<endl;
		
	if(click_left){
		if(mouseX>=154 && mouseX<=438){
			if(mouseY>=190 && mouseY<=256)//Si click en boton Jugar...
				{graficos->Cargar_img("menu_click_jugar.png");	
				play=1;}
			else
				if(mouseY>=270&&mouseY<=336){//Si click en boton Acerca de...
					graficos->Cargar_img("menu_click_acerca.png");
					acerca=1;
				}
				else
					graficos->Cargar_img("menu.png");
		}
		else
			if(mouseX>=500 && mouseX<=580)
				if(mouseY>=300 && mouseY<=380){
					graficos->Cargar_img("menu_click_x.png");
					render();limpiar(); exit(0);
				}
				else
					graficos->Cargar_img("menu.png");
			else
				graficos->Cargar_img("menu.png");
		click_left=false;
		paso_evento=0;
	}
	else
		if(mouseX>=154 && mouseX<=438)
			if(mouseY>=190 && mouseY<=256)//Si sobre boton Jugar...
				graficos->Cargar_img("menu_sobre_jugar.png");
			else
				if(mouseY>=270&&mouseY<=336)//Si sobre boton Acerca de...
					graficos->Cargar_img("menu_sobre_acerca.png");
				else
					graficos->Cargar_img("menu.png");
		else
			if(mouseX>=500 && mouseX<=580)
				if(mouseY>=300 && mouseY<=380)
					graficos->Cargar_img("menu_sobre_x.png");
				else
					graficos->Cargar_img("menu.png");
			else
				graficos->Cargar_img("menu.png");
	mouseX=0;mouseY=0;
}

void Menu::render(){
	cout<<"Render menu"<<endl;
	graficos->Render();
}
void Menu::run(){
	inicializar();
	while(graficos->ver_ventana().isOpen()){
		while(!play){
			eventos();
			actualizar();
			render();
			if(acerca){
				graficos->Acerca_de();
				acerca=0;
			}
			if (load_g){
				Game Juego("Player");
				Juego.run(load_g);
				load_g=0;
			}
		}
		nombre=graficos->Leer_name();
		if(nombre.empty()){				
			play=0;	
		}
		else{
			Game Juego(nombre);
			Juego.run(load_g);
		}
	}
	play=0;
}

void Menu::limpiar(){
	graficos->Cerrar_ventana();
	delete graficos;
}
