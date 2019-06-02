#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Plansza.h"
#include <ctime>


class Gra
{
	sf::RenderWindow oknoAplikacji;
	plansza *P;
	Poziom_Trudnosci poziom;
	int rozmiar;
public:

	void debugger() { P->debug(); };
	void graj();
	Gra();
	~Gra();
};

