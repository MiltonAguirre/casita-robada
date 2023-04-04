#include "Game.h" 
#include "Menu.h"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;
int main(int argc, char *argv[]){
	while (1){
		Menu menu;	
		menu.run();
	}
	return 0;
}

