#ifndef CARTA_H
#define CARTA_H
#include <string>
using namespace std;

class Carta {
private:
	char palo;
	int numero;
protected:
public:
	Carta();
	Carta(char pa, int nu);
	Carta(const Carta &arg);
	int Ver_numero();
	char Ver_palo();
	string Ver_direccion();
	bool operator==(const Carta &c);
	bool operator!=(const Carta &c);
	bool operator<(const Carta &c)const;
	bool operator>(const Carta &c);
	bool operator<=(const Carta &c);
	bool operator>=(const Carta &c);
	Carta &operator=(const Carta c);
	~Carta();
};

#endif

