#include "Gestor_grafico.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Jugador.h"
#include <vector>
#include "Carta.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iomanip>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

Gestor_grafico::Gestor_grafico():ventana(VideoMode(900,600),"Casita robada"){
	cout<<"Propiedades de ventana"<<endl;
	ventana.setPosition(Vector2i(50,50));
	ventana.setFramerateLimit(60);
	ventana.setKeyRepeatEnabled(true);
	ventana.setVerticalSyncEnabled(true);
	ventana.setMouseCursorVisible(true);
	cout<<"textura y sprite de la mesa"<<endl;
	textura_mesa.loadFromFile("tablero.png");
	sprite_mesa.setTexture(textura_mesa);
	sprite_mesa.setPosition(Vector2f(0.f,0.f));
	cout<<"textura y sprite mazo"<<endl;
	textura_mazo.loadFromFile("Carta_reverso.png");
	sprite_mazo.setTexture(textura_mazo);
	sprite_mazo.setPosition(Vector2f(25.f,210.f));
	sprite_mazo.setScale(Vector2f(0.25,0.25));
	textura_img.loadFromFile("turno.png");
	sprite_turno.setTexture(textura_img);
	cout<<"paso sprite maso"<<endl;
	fuente_pts.loadFromFile("arial.ttf");
	tecla=new Text[4];
	tecla[0].setString("H");
	tecla[1].setString("J");
	tecla[2].setString("K");
	tecla[3].setString("L");
	cout<<"paso teclas string"<<endl;
	
	for(int i=0;i<4;i++){
		tecla[i].setFont(fuente_pts);
		tecla[i].setColor(Color::White);
		tecla[i].setCharacterSize(20);
		tecla[i].setPosition(Vector2f(float(250+(105*i)), 500.f));
		tecla[i].Bold;
		tecla[i].setStyle(1);
	}
	
	btn_save_spr.setPosition(700.f,200.f);
	btn_save_txr.loadFromFile("btn_save.png");
	btn_save_spr.setTexture(btn_save_txr);
	btn_save_spr.setScale(.25,.25);
	

}
void Gestor_grafico::Renderizar_juego(Jugador &cpu, Jugador &hum, vector<Carta> &p, int t, bool vacio){
	///Elementos graficos
	stringstream ss, sst;
	cout<<"Entro al renderizar grafios" <<endl;
	spt_casa_hum=new Sprite;
	txr_casa_hum=new Texture;
	spt_casa_cpu=new Sprite;
	txr_casa_cpu=new Texture;
	spt_pozo=new Sprite[p.size()];
	txr_pozo=new Texture[p.size()];
	spt_manohum=new Sprite[hum.Ver_mano().size()];
	txr_manohum=new Texture[hum.Ver_mano().size()];
	spt_manocpu=new Sprite[cpu.Ver_mano().size()];
	texto_pts=new Text;
	turno_pts=new Text;

	cout<<"Inicilizo los Puntoros SFML"<<endl;
	ss<<"-"+cpu.Ver_nombre()<<endl<<setw(8)<<"Casa: "<<cpu.Ver_casa().size()<<" pisos"<<endl;
	ss<<endl<<"-"+hum.Ver_nombre()<<endl<<setw(8)<<"Casa: "<<hum.Ver_casa().size()<<" pisos";
	texto_pts->setString(ss.str());
	texto_pts->setFont(fuente_pts);
	texto_pts->setCharacterSize(18);
	texto_pts->setPosition(745,240);
	texto_pts->setColor(Color::White);
	turno_pts->setCharacterSize(18);
	turno_pts->setColor(Color::Cyan);
	turno_pts->setFont(fuente_pts);
	sprite_turno.setScale(0.5,0.5);
	if (t%2==0){
		sst<<"Turno "<<cpu.Ver_nombre()<<endl;
		turno_pts->setString(sst.str());
		turno_pts->setPosition(10,60);
		sprite_turno.setPosition(45,100);
	}
	else{
		sst<<"Turno "<<hum.Ver_nombre()<<endl;
		turno_pts->setString(sst.str());
		turno_pts->setPosition(20,490);
		sprite_turno.setPosition(45,520);
	}
	if(!hum.Ver_casa().empty()){
		txr_casa_hum->loadFromFile(hum.Ver_casa().back().Ver_direccion());
		spt_casa_hum->setTexture(*txr_casa_hum);	
		spt_casa_hum->setPosition(Vector2f(750.f,400.f));
		spt_casa_hum->setScale(Vector2f(0.275,0.275));
	}
	else cout<<"graficos>> casa HUM vacia"<<endl;
	if(!cpu.Ver_casa().empty()){
		//Cargar Sprite Casa_CPU;
		txr_casa_cpu->loadFromFile(cpu.Ver_casa().back().Ver_direccion());
		spt_casa_cpu->setTexture(*txr_casa_cpu);	
		spt_casa_cpu->setPosition(Vector2f(750.f,20.f));
		spt_casa_cpu->setScale(Vector2f(0.275,0.275));
	}
	else cout<<"graficos>> casa CPU vacia"<<endl;
	//Cargar sprite mano_HUM;
	for (size_t n=0;n<hum.Ver_mano().size();n++){
		txr_manohum[n].loadFromFile(hum.Ver_carta(n).Ver_direccion());
		spt_manohum[n].setTexture(txr_manohum[n]);
		spt_manohum[n].setScale(Vector2f(0.25,0.25));
		spt_manohum[n].setPosition(Vector2f(float(223+(105*n)), 505.f));
	//	cout<<"Cargo mano_hum"<<endl;
	}
	//Cargar Sprite mano_CPU;
	for (size_t n=0;n<cpu.Ver_mano().size();n++){
		spt_manocpu[n].setTexture(textura_mazo);
		spt_manocpu[n].setScale(Vector2f(0.23,0.22));
		spt_manocpu[n].setPosition(Vector2f(float(223+(105*n)), -65.f));
		//cout<<"Cargo mano_cpu"<<endl;
	}
	//Cargar Sprite POZO;
	for (size_t n=0;n<p.size();n++){
		txr_pozo[n].loadFromFile(p[n].Ver_direccion());
		spt_pozo[n].setTexture(txr_pozo[n]);
		spt_pozo[n].setScale(Vector2f(0.225,0.225));
		if(n<4)spt_pozo[n].setPosition(Vector2f(float(225+(105*n)),150.f));
		else spt_pozo[n].setPosition(Vector2f(float((105*n)-195),305.f));
		cout<<"Cargo pozo"<<endl;
	}
	ventana.clear(Color::Green);
	ventana.draw(sprite_mesa);
	if(!vacio)ventana.draw(sprite_mazo);
	//DRAW CASAS
	ventana.draw(*spt_casa_hum);
	///cout<<"DRAW casa_hum"<<endl;
	ventana.draw(*spt_casa_cpu);
	///	cout<<"DRAW casa_cpu"<<endl;
	//DRAW MANO HUM
	for(size_t i=0;i<cpu.Ver_mano().size();i++){
		ventana.draw(spt_manocpu[i]);
	///	cout<<"DRAW mano_hum"<<endl;
	}
	for(size_t i=0;i<hum.Ver_mano().size();i++){
		ventana.draw(spt_manohum[i]);
		///cout<<"DRAW mano_cpu"<<endl;
	}
	for(size_t i=0;i<p.size();i++){
		ventana.draw(spt_pozo[i]);
	///	cout<<"DRAW pozo"<<endl;
	}
	ventana.draw(*texto_pts);
	ventana.draw(*turno_pts);
	ventana.draw(sprite_turno);
	ventana.draw(btn_save_spr);
	for(int i=0;i<4;i++) { 
		ventana.draw(tecla[i]);
	}
	cout<<"termino los draw"<<endl; 
	ventana.display();
	
}
RenderWindow &Gestor_grafico::ver_ventana(){
	return ventana;
}
void Gestor_grafico::Cerrar_ventana(){
	cout<<"cerrar ventana"<<endl;
	ventana.close();
}
void Gestor_grafico::Limpiar_punteros(){
	cout<<"Limpiar_punteros "<<endl;
	delete spt_casa_hum;
	delete txr_casa_hum;
	delete spt_casa_cpu;
	delete txr_casa_cpu;
	delete []spt_pozo;
	delete []txr_pozo;
	delete []spt_manohum;
	delete []txr_manohum;
	delete[]spt_manocpu;	
}
void Gestor_grafico::Resultado(Jugador &c, Jugador &h, bool ri){
	Text resultado;
	string ganador("El Ganador es: ");
	RectangleShape cartel(sf::Vector2f(400.f,150.f));
	
	
	if(ri)ganador+=c.Ver_nombre();
	else{
		if(c.Ver_casa().size()>h.Ver_casa().size())
			ganador+=c.Ver_nombre();
		else
			if(h.Ver_casa().size()>c.Ver_casa().size())
				ganador+=h.Ver_nombre();
			else
				ganador="¡Empate!";
	}
	ganador+="\n\nClick para salir";
	cartel.setFillColor(sf::Color::Cyan);
	cartel.setOutlineColor(Color::Black);
	cartel.setOutlineThickness(15);
	cartel.setPosition(230,370);
	resultado.setCharacterSize(30);
	resultado.setPosition(275,400);
	resultado.setColor(Color::Red);
	resultado.setFont(fuente_pts);
	resultado.setString(ganador.c_str());
	ventana.draw(cartel);
	ventana.draw(resultado);
	ventana.display();
	
}

Gestor_grafico &Gestor_grafico::operator=(const Gestor_grafico gg){
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
}
Gestor_grafico::~Gestor_grafico() {
}
