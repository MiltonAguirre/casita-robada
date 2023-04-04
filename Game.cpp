#include "Game.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Carta.h"
#include <iterator>
#include <forward_list>
#include <cstddef>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <SFML/System/Time.hpp>
#include <windows.h>
#include <cstring>
#include <fstream>
using namespace std;
Game::Game(){
	
}
Game::Game(string n="Player"):humano(n), cpu("Maquina"){
	srand(time(NULL));
	ocurrio_event=0;
	ronda=0;	
	turno=rand()%2;	
	me_rindo=false;
	mazo_vacio=true;
	e=1;
}
void Game::Crear_mazo(){
	cout<<"Cargar_mazo"<<endl;
	Carta *c;
	for(int i=1;i<13;i++){
		c=new Carta('b',i);
		mazo.push_back(*c);
	}
	for(int i=1;i<13;i++){
		c=new Carta('c',i);
		mazo.push_back(*c);
	}
	for(int i=1;i<13;i++){
		c=new Carta('e',i);
		mazo.push_back(*c);
	}
	for(int i=1;i<13;i++){
		c=new Carta('o',i);
		mazo.push_back(*c);
	}
	delete c;
}
void Game::Mezclar_mazo(){
	cout<<"MEZCLAR MAZO"<<endl;
	srand(time(NULL));
	random_shuffle(mazo.begin(),mazo.end());
	srand(time(NULL));
	random_shuffle(mazo.begin(),mazo.end());
	srand(time(NULL));
	random_shuffle(mazo.begin(),mazo.end());
	cout<<"fin Mezclar"<<endl;
	srand(time(NULL));
	random_shuffle(mazo.begin(),mazo.end());
	srand(time(NULL));
	random_shuffle(mazo.begin(),mazo.end());
	srand(time(NULL));
	random_shuffle(mazo.begin(),mazo.end());
	cout<<"fin Mezclar"<<endl;
}
void Game::Repartir(){
	cout<<"Repartir"<<endl;
	while(humano.Ver_mano().size()<4||cpu.Ver_mano().size()<4){
		if(!mazo.empty()){
			cout<<"Mano no estan llenas"<<endl;
			if (turno%2==0){
				humano.Ver_mano().push_back(mazo.back());
				mazo.pop_back();
				turno++;
			}
			else{
				cpu.Ver_mano().push_back(mazo.back());
				mazo.pop_back();
				turno++;
			}
		}
		else{cout<<"Mazo vacio"<<endl;break;}
	}
	while(pozo.size()<8){
		if(!mazo.empty()){
			cout<<"Menos de 4 cartas en el pozo"<<endl;
			pozo.push_back(mazo.back());
			mazo.pop_back();
		}
		else{
			cout<<"Mazo vacio"<<endl;break;
		}
	}
	sort(humano.Ver_mano().begin(),humano.Ver_mano().end());
	sort(cpu.Ver_mano().begin(),cpu.Ver_mano().end());
	mazo_vacio=mazo.empty();
	if(!ronda){
		cout<<"1ra ronda"<<endl;
		cpu.Ver_casa().push_back(mazo.back());
		mazo.pop_back();
		humano.Ver_casa().push_back(mazo.back());
		mazo.pop_back();
	}
}
void Game::Save_game(){
	cout<<"SAVE_GAME()"<<endl;
	int *tam=new int[7];
	*tam=int(mazo.size());
	*(tam+1)=int(pozo.size());
	*(tam+2)=int(cpu.Ver_mano().size());
	*(tam+3)=int(cpu.Ver_casa().size());
	*(tam+4)=int(humano.Ver_mano().size());
	*(tam+5)=int(humano.Ver_casa().size());
	int pos=0;
	int n;
	ofstream save_file("save_game.dat",ios::trunc|ios::binary);
	if (!save_file.is_open()){cout<<"ERROR file dont open"<<endl;exit(0);}
	else
		for(int i=0;i<9;i++) {
			switch(i){
			case 0:{
				for(int j=0;j<6;j++) {
					save_file.seekp(pos);
					save_file.write(reinterpret_cast<char*>(tam+j),sizeof(int));
					cout<<"Guardo tamaño mazo: "<<*(tam+j)<<endl;
					pos=(j+1)*sizeof(int);
				}break;
			};
			case 1:{
				save_file.seekp(pos);
				string s1 =humano.Ver_nombre();
				char aux1[256];
				strcpy ( aux1, s1.c_str() );
				save_file.write( aux1, 256 );
				pos+=256;
				cout<<"Guardo nombre: "<<s1.c_str()<<endl;break;
			};
			case 2:{
				save_file.seekp(pos);
				n=turno;
				save_file.write(reinterpret_cast<char*>(&n),sizeof(int));
				pos+=sizeof(int);
				cout<<"Guardo turno "<<n<<endl;break;
			};
			case 3:{
				n=1;
				while(n<=*tam){
					save_file.seekp(pos);
					Carta c;
					c=*(mazo.begin()+n-1);
					save_file.write(reinterpret_cast<char*>(&c),sizeof(Carta));
					n++;	
					cout<<"Guardo del mazo en pos "<<pos<<" carta: "<<c.Ver_direccion()<<endl;
					pos+=n*sizeof(Carta);
					
				}break;
			};
			case 4:{
				n=1;
				while(n<=*(tam+1)){
					save_file.seekp(pos);
					Carta c;
					c=*(pozo.begin()+n-1);
					save_file.write(reinterpret_cast<char*>(&c),sizeof(Carta));
					n++;
					cout<<"Guardo del pozo en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=n*sizeof(Carta);
				}break;
			};
			case 5:{
				n=1;
				while(n<=*(tam+2)){
					save_file.seekp(pos);
					Carta c;
					c=*(cpu.Ver_mano().begin()+n-1);
					save_file.write(reinterpret_cast<char*>(&c),sizeof(Carta));
					n++;
					cout<<"Guardo del cpu_mano en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=n*sizeof(Carta);
				} break;
			};
			case 6:{
				n=1;
				while(n<=*(tam+3)){
					save_file.seekp(pos);
					Carta c;
					c=cpu.Ver_casa()[n-1];
					save_file.write(reinterpret_cast<char*>(&c),sizeof(Carta));
					n++;
					cout<<"Guardo de cpu_casa en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=n*sizeof(Carta);
				}break;
			};
			case 7:{
				n=1;
				while(n<=*(tam+4)){
					save_file.seekp(pos);
					Carta c;
					c=humano.Ver_mano()[n-1];
					save_file.write(reinterpret_cast<char*>(&c),sizeof(Carta));
					n++;
					cout<<"Guardo de hum_mano en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=n*sizeof(Carta);
				}break;
			};	
			case 8:{
				n=1;
				while(n<=*(tam+5)){
					save_file.seekp(pos);
					Carta c;
					c=humano.Ver_casa()[n-1];
					save_file.write(reinterpret_cast<char*>(&c),sizeof(Carta));
					n++;
					cout<<"Guardo de hum_casa en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=n*sizeof(Carta);
				}break;
			};
			default: break;
			}
		}
		save_file.close();
		exit(0);
		e=0;
}
void Game::Load_game(){
	cout<<"Load_game()"<<endl;
	ifstream save_file("save_game.dat", ios::binary);
	int *tam=new int[7];
	int n;
	int pos=0;
	if(!save_file.is_open())
		{cout<<"load_file dont open" <<endl;exit(0);}
	else{
		cout<<"abrio archivo"<<endl;
		for(int k=0;k<9;k++) { 
			switch(k){
			case 0:{cout<<"case 0"<<endl;
					for(int h=0;h<6;h++) {
						save_file.seekg(pos);
						save_file.read(reinterpret_cast<char*>(tam+h),sizeof(int));
						cout<<"Cargo tamaño: "<<*(tam+h)<<endl;
						pos=(h+1)*sizeof(int);
					}	break;
			};
			case 1:{
				save_file.seekg(pos);
				char aux[256];
				save_file.read(aux, 256);
				string s = aux;
				Jugador *j=new Jugador(s);
				humano=*j;
				cout<<"Cargo en pos "<<pos<<"nombre: "<<s<<endl;
				pos+=256;
				break;
			};
			case 2:{
				save_file.seekg(pos);
				save_file.read(reinterpret_cast<char*>(&n),sizeof(int));
				turno=n;
				cout<<"read turno: "<<turno<<endl;
				pos+=sizeof(int);
				break;
			};
			case 3:{
				n=1;
				mazo.erase(mazo.begin(),mazo.end());
				while(n<=*tam && !save_file.eof()){
					Carta c;
					save_file.seekg(pos);
					save_file.read(reinterpret_cast<char*>(&c),sizeof(Carta));
					mazo.push_back(c);		n++;
					cout<<"Cargo en mazo de pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=sizeof(Carta)*n;
				}break;
			};
			case 4:{
				n=1;
				pozo.erase(pozo.begin(),pozo.end());
				
				while(n<=*(tam+1)&& !save_file.eof()){
					save_file.seekg(pos);
					Carta c;
					save_file.read(reinterpret_cast<char*>(&c),sizeof(Carta));
					pozo.push_back(c);		n++;
					cout<<"Cargo en pozo en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=sizeof(Carta)*n;	
				}break;	
			};
			case 5:{
				n=1;
				cpu.Ver_mano().erase(cpu.Ver_mano().begin(), cpu.Ver_mano().end());
				
				while(n<=*(tam+2)&& !save_file.eof()){
					save_file.seekg(pos);
					Carta c;
					save_file.read(reinterpret_cast<char*>(&c),sizeof(Carta));
					cpu.Ver_mano().push_back(c);	++n;
					cout<<"Cargo en cpu_mano en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=sizeof(Carta)*n;
				}break;
			};
			case 6:{
				n=1;
				cpu.Ver_casa().erase(cpu.Ver_casa().begin(), cpu.Ver_casa().end());
				while(n<=*(tam+3)&& !save_file.eof()){
					Carta c;
					save_file.seekg(pos);
					save_file.read(reinterpret_cast<char*>(&c),sizeof(Carta));
					cpu.Ver_casa().push_back(c);	++n;
					cout<<"Cargo en cpu_casa en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=sizeof(Carta)*n;
				}break;
			};
			case 7:{
				n=1;
				humano.Ver_mano().erase(humano.Ver_mano().begin(), humano.Ver_mano().end());
				while(n<=*(tam+4)&& !save_file.eof()){
					Carta c;
					save_file.seekg(pos);
					save_file.read(reinterpret_cast<char*>(&c),sizeof(Carta));
					humano.Ver_mano().push_back(c);		++n;
					cout<<"Cargo en hum_mano en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=sizeof(Carta)*n;
				}
				break;
			};
			case 8:{
				n=1;
				humano.Ver_casa().erase(humano.Ver_casa().begin(), humano.Ver_casa().end());
				while(n<=*(tam+5)&& !save_file.eof()){
					Carta c;
					save_file.seekg(pos);
					save_file.read(reinterpret_cast<char*>(&c),sizeof(Carta));
					humano.Ver_casa().push_back(c);			++n;
					cout<<"Cargo en hum_casa en pos "<<pos<<" carta "<<c.Ver_direccion()<<endl;
					pos+=sizeof(Carta)*n;
				}	
				break;
			};
			default:{break;}
			}
		}
		save_file.close();
	}		
}
void Game::inicializar(int x){
	cout<<"INICIA JUEGO "<<endl;
	if(x){
		Load_game();	e=0;
	}
	else {
		Crear_mazo();
		Mezclar_mazo();
		e=1;
	}
	isPlay=true;
	mazo_vacio=mazo.empty();
	reloj.restart();
	ocurrio_event=0;
}
void Game::eventos(){
	cout<<"Eventos"<<endl;
	miEvento=new Event();
	Scene();
	
}
void Game::actualizar(){
	cout<<"ACTUALIZAR"<<endl;
	int cant_elim=0, i=0, alzo=0;
	int *eliminar=new int[50];
	vector<Carta> alza;
//	if(ronda>0){
		cout<<"JUGO UNA CARTA"<<endl;
		for(size_t h=0;h<pozo.size();h++){///"Compara con pozo "
			if(*(pozo.begin()+h)==elegida){
				alza.push_back(*(pozo.begin()+h));
				eliminar[cant_elim]=h;
				cant_elim++;
				alzo=1;
			}cout<<"comparo con elegida"<<endl;
		}
		cout<<"1 ";
		if (turno%2!=0){cout<<"2 ";
			if(humano.Ver_casa().back()==elegida){			cout<<"Coincidió CASA con carta elegida"<<endl;
				while(!humano.Ver_casa().empty()){	
					cpu.Ver_casa().push_back(humano.Ver_casa().back());
					humano.Ver_casa().pop_back();
				}		alzo=1;			cout<<"Robo la casa"<<endl;
			}
			else{cout<<"no coincido con casa"<<endl;}
			if(alzo){
				while(i<cant_elim) { 
					pozo.erase(pozo.begin()+(eliminar[i]-i)); cout<<"elimino del pozo carta nro: "<<eliminar[i]-i<<endl;
					i++;
				}
				while(!alza.empty()){
					cpu.Ver_casa().push_back(alza.back());
					alza.pop_back();
				}
				cpu.Ver_casa().push_back(elegida);
			}
			else {			cout<<"No alzo carta"<<endl;
				pozo.push_back(elegida);
			}
		}
		else{cout<<"3";
			if(cpu.Ver_casa().back()==elegida){			cout<<"Coincidió CASA con carta elegida"<<endl;
				while(!cpu.Ver_casa().empty()){	
					humano.Ver_casa().push_back(cpu.Ver_casa().back());
					cpu.Ver_casa().pop_back();
				}		alzo=1;			cout<<"Robo la casa"<<endl;
			}
			else{
				cout<<"no coincido con casa"<<endl;
			}
			cout<<"4";
			if(alzo){
				while(i<cant_elim) { 
					pozo.erase(pozo.begin()+(eliminar[i]-i)); cout<<"elimino del pozo carta nro: "<<eliminar[i]-i<<endl;
					i++;
				}
				cout<<"5";
				while(!alza.empty()){
					humano.Ver_casa().push_back(alza.back());
					alza.pop_back();
				}
				humano.Ver_casa().push_back(elegida);
			}
			else {			cout<<"No alzo carta"<<endl;
				pozo.push_back(elegida);
			}
		}
		ocurrio_event=0;
		mazo_vacio=mazo.empty();
//	}
}
void Game::render(){
	graficos.Renderizar_juego(cpu,humano,pozo,turno, mazo_vacio);
	graficos.Limpiar_punteros();
}
void Game::limpiar(){
	graficos.Cerrar_ventana();
}
void Game::run(int x){
	//inicia y pisa los datos cargados desde el archivo[SOLUCIONAR]
	inicializar(x);
	render();
	while(graficos.ver_ventana().isOpen()){
		while(isPlay){
			if(!ocurrio_event)eventos();
			else 
				actualizar();
			render();
		}
		graficos.Resultado(cpu,humano,me_rindo);
		while(graficos.ver_ventana().pollEvent(*miEvento)){
			if (miEvento->type==Event::MouseButtonReleased && miEvento->mouseButton.button==Mouse::Left)
				limpiar();
		}
		cout<<"<-FIN DEL JUEGO->"<<endl;
	}
}
void Game::Scene(){
	switch(e){
		case 0:{	
					cout<<"Entro Escena 0"<<endl;///TIME OUT
					if(reloj.getElapsedTime().asSeconds()>3.f){
						cout<<"paso tiempo: "<<reloj.getElapsedTime().asSeconds()<<endl;
						if (!humano.Ver_mano().empty() || !cpu.Ver_mano().empty())
							if(turno%2==0) e=2;
							else e=3;
						else{
							cout<<"manos vacias,scene"<<endl;
							if (!mazo.empty()){ronda++;e=1;}
							else isPlay=false;
						}break;
					}else break;
					
			};
		case 1:{
				cout<<"Entro Escena 1"<<endl;///Repartir
				Repartir();		e=0;
				reloj.restart();
				break;
			};
		case 2:{
				///turno CPU++
				cout<<"Entro Escena 2"<<endl;	
				srand(time(NULL));
				juega_carta=rand()%cpu.Ver_mano().size();
				elegida=*(cpu.Ver_mano().begin()+juega_carta);
				cpu.Ver_mano().erase(cpu.Ver_mano().begin()+juega_carta);
				turno++; e=0;ocurrio_event=1;
				reloj.restart();
				break;
			};
		case 3:{
			
			if(graficos.ver_ventana().waitEvent(*miEvento)){	///turno HUM
				if(miEvento->type==Event::Closed){
					isPlay=false;
					me_rindo=true;
					break;
				}
				cout<<"Entro Escena 3"<<endl;
//				if (miEvento.type==Event::MouseButtonReleased && miEvento.mouseButton.button==Mouse::Left){
//					coordenadas=Mouse::getPosition();
//					for(int k=0;k<4; k++){	
//						if(coordenadas.x>(250+(105*k)) && coordenadas.x<(250+(105*(k+1)))){
//							if(coordenadas.y>=500 && !humano.Ver_mano().empty()){
//								juega_carta=k;	
//								ocurrio_event=1;
//								e=0; turno++;
//								reloj.restart();
//								elegida=*(humano.Ver_mano().begin()+juega_carta);
//								humano.Ver_mano().erase(humano.Ver_mano().begin()+juega_carta);
//							}
//						}
//					}
//				}
				if(miEvento->type==miEvento->KeyPressed){
				   switch(miEvento->key.code){
						case Keyboard::G:{
								Save_game();cout<<"g press"<<endl;
								break;
							};
						case Keyboard::H:{
								if(!humano.Ver_mano().empty()){
									juega_carta=0;	ocurrio_event=1;
									e=0; turno++;reloj.restart();
									elegida=*(humano.Ver_mano().begin()+juega_carta);
									humano.Ver_mano().erase(humano.Ver_mano().begin()+juega_carta);
								}
								break;
							};
						case Keyboard::J:{
								if(humano.Ver_mano().size()>1){
									juega_carta=1;	ocurrio_event=1;
									e=0;turno++;reloj.restart();
									elegida=*(humano.Ver_mano().begin()+juega_carta);
									humano.Ver_mano().erase(humano.Ver_mano().begin()+juega_carta);
								}
								break;
							};
						case Keyboard::K:{
								if(humano.Ver_mano().size()>2){
									juega_carta=2;ocurrio_event=1;
									e=0;turno++;reloj.restart();
									elegida=*(humano.Ver_mano().begin()+juega_carta);
									humano.Ver_mano().erase(humano.Ver_mano().begin()+juega_carta);
								}
								break;
							};
						case Keyboard::L:{
								if(humano.Ver_mano().size()>3){
									juega_carta=3;ocurrio_event=1;
									e=0;turno++;reloj.restart();
									elegida=*(humano.Ver_mano().begin()+juega_carta);
									humano.Ver_mano().erase(humano.Ver_mano().begin()+juega_carta);
								}	
								break;
							};
						default: break;
					}break;
			   	}else{ cout<<"NO RECIBIO EVENTO KEYPRESS"<<endl;}
				
			}break;
			
		};
	}
}
Game::~Game(){
}

