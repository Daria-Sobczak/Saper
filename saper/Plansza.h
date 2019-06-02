#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include  "pole.h"
#define ROZM_POLA 30

enum Poziom_Trudnosci { LATWY, SREDNI, TRUDNY };


class plansza
{
	pole **plansza_;
	int roz_x;
	int roz_y;
	Poziom_Trudnosci Poziom;
	sf::RenderWindow *Okno;
	int ilosc_min;
	void ustaw_miny();
public:

	plansza(sf::RenderWindow *, Poziom_Trudnosci,int);
	void zmien_status_flagi(int, int);
	void odkryj_pole(int, int);
	void debug();
	void Rysuj_okno();
	bool trafiles_na_mine();
	void menu()
	{
		sf::Font czcionka;
		czcionka.loadFromFile("arial.ttf");
		sf::Text text;
		text.setFont(czcionka);



		text.setCharacterSize(roz_x);
		text.setFillColor(sf::Color::Red);
		text.setPosition(ROZM_POLA * roz_x + 30, 30);
		text.setString(" A-resret \n\n POZIOM \n W-Latwy \n S-Sredni \n X-Trudny \n\n ROZMIAR \n E-Maly \n D-Sredni \n C-Duzy");
		Okno->draw(text);
	}
	bool Wygrales()
	{
		int miny=0; 
		//cout << ilosc_min;
		int wszystkie = roz_x * roz_y;
		int wszystkie_odkryte = 0;;
		for (int i = 0; i < roz_x; i++)
			for (int j = 0; j < roz_y; j++)
			{
				if (plansza_[i][j].czy_mina && !plansza_[i][j].czy_odkryte)
				{
					miny++;
				}
				if (plansza_[i][j].czy_odkryte)
				{
					wszystkie_odkryte++;
				}
			}
		//cout << miny << " " << wszystkie_odkryte;
		if (wszystkie_odkryte == wszystkie- ilosc_min && ilosc_min == miny)
		{
			return true;
		}
		return false;
	}
	int zliczminy(int x, int y) const;


};