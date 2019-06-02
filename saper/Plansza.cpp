#include "pch.h"
#include "Plansza.h"

plansza::plansza(sf::RenderWindow *Okno,Poziom_Trudnosci Poziom,int Rozmiar )
{
	this->Okno = Okno;
	roz_x = Rozmiar;
	roz_y = Rozmiar;
	this->Poziom = Poziom;
	plansza_ = new pole*[roz_x];
	for (int i = 0; i < roz_x; i++)
		plansza_[i] = new pole[roz_y];

	for (int i = 0; i < roz_x; i++)
	{
		for (int j = 0; j < roz_y; j++)
		{
			plansza_[i][j].czy_flaga = false;
			plansza_[i][j].czy_mina = false;
			plansza_[i][j].czy_odkryte = false;
		}
	}
	this->Okno->create(sf::VideoMode(ROZM_POLA* roz_y + 30+ (Rozmiar*10), ROZM_POLA * roz_x + 30), "Saper :) ");


	ustaw_miny();
}




void plansza::debug()
{
	for (int i = 0; i < roz_x; i++)
	{
		for (int j = 0; j < roz_y; j++)
		{
			cout << "[" << plansza_[i][j].czy_flaga << plansza_[i][j].czy_mina << plansza_[i][j].czy_odkryte << "]";
		}
		cout << endl;
	}

}

void plansza::ustaw_miny()
{
	float  wspolczynik_min;
	int x, y;
	switch (Poziom)
	{

	case LATWY:
		wspolczynik_min = 0.1;
		break;

	case SREDNI:
		wspolczynik_min = 0.3;
		break;

	case TRUDNY:
		wspolczynik_min = 0.5;
		break;
	default:

		break;
	}
	ilosc_min = roz_x * roz_y * wspolczynik_min;
	for (int j = 0; j < ilosc_min;)
	{
		x = rand() % roz_x;
		y = rand() % roz_y;
		if (!plansza_[x][y].czy_mina)
		{
			plansza_[x][y].czy_mina = true;
			j++;
		}
	}
	cout << endl;

}

void plansza::zmien_status_flagi(int x, int y)
{
	if (plansza_[x][y].czy_flaga)
	{
		plansza_[x][y].czy_flaga = false;
	}
	else
	{
		plansza_[x][y].czy_flaga = true;
	}

}
bool  plansza::trafiles_na_mine()
{
	for (int i = 0; i < roz_x; i++)
		for (int j = 0; j < roz_y; j++)
		{
			if (plansza_[i][j].czy_mina && plansza_[i][j].czy_odkryte)
			{
				return true;
			}
		}
	return false;
}
void plansza::odkryj_pole(int x, int y)
{
	plansza_[x][y].czy_odkryte = true;
}

void plansza::Rysuj_okno()
{
	int posx = 15, posy = 15;
	sf::RectangleShape Rect(sf::Vector2f(ROZM_POLA, ROZM_POLA));
	Rect.setPosition(posx, posy);
	Rect.setOutlineColor(sf::Color::Blue);
	Rect.setOutlineThickness(2);
	sf::Font czcionka;
	czcionka.loadFromFile("arial.ttf");

	sf::Text text;
	text.setFont(czcionka);



	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Red);

	for (int i = 0; i < roz_x; i++)
	{
		for (int j = 0; j < roz_y; j++)
		{
			Rect.setPosition(posx, posy);
			text.setPosition(posx + 2, posy + 2);


			if (plansza_[i][j].czy_odkryte == false && plansza_[i][j].czy_flaga == false)
				text.setString("_");
			else if (plansza_[i][j].czy_odkryte == false && plansza_[i][j].czy_flaga == true)
				text.setString("F");
			else if (plansza_[i][j].czy_odkryte == true && plansza_[i][j].czy_mina == true)
				text.setString("*");
			else
				text.setString(to_string(zliczminy(i, j)));
			Okno->draw(Rect);
			Okno->draw(text);

			posy += ROZM_POLA;
		}
		posy = 15;
		posx += ROZM_POLA;
	}



}


int plansza::zliczminy(int x, int y) const
{
	int ile_min = 0;


	if (x == 0 && y == 0)
	{



		if (plansza_[x + 1][y].czy_mina && x < roz_x - 1)
		{
			ile_min++;
		}

		if (plansza_[x][y + 1].czy_mina && y < roz_y - 1)
		{
			ile_min++;
		}

		if (plansza_[x + 1][y + 1].czy_mina && y < roz_y - 1 && x < roz_x - 1)
		{
			ile_min++;
		}





	}
	else if (x == 0 && y == roz_y - 1)
	{



		if (plansza_[x + 1][y].czy_mina && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x][y - 1].czy_mina && y > 0)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y - 1].czy_mina && x < roz_x - 1 && y>0)
		{
			ile_min++;
		}


	}
	else if (x == roz_x - 1 && y == 0)
	{



		if (plansza_[x - 1][y].czy_mina && x > 0)
		{
			ile_min++;
		}


		if (plansza_[x][y + 1].czy_mina && y < roz_y - 1)
		{
			ile_min++;
		}

		if (plansza_[x - 1][y + 1].czy_mina && x > 0 && y < roz_y - 1)
		{
			ile_min++;
		}

	}
	else if (x == roz_x - 1 && y == roz_y - 1)
	{



		if (plansza_[x - 1][y].czy_mina && x > 0)
		{
			ile_min++;
		}

		if (plansza_[x][y - 1].czy_mina && y > 0)
		{
			ile_min++;
		}

		if (plansza_[x - 1][y - 1].czy_mina && x > 0 && y > 0)
		{
			ile_min++;
		}

	}
	else if (x == 0)
	{


		if (plansza_[x + 1][y].czy_mina && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x][y - 1].czy_mina && y > 0)
		{
			ile_min++;
		}
		if (plansza_[x][y + 1].czy_mina && y < roz_y - 1)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y + 1].czy_mina && y < roz_y - 1 && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y - 1].czy_mina && x < roz_x - 1 && y>0)
		{
			ile_min++;
		}



	}
	else if (y == 0)
	{

		if (plansza_[x - 1][y].czy_mina && x > 0)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y].czy_mina && x < roz_x - 1)
		{
			ile_min++;
		}

		if (plansza_[x][y + 1].czy_mina && y < roz_y - 1)
		{
			ile_min++;
		}

		if (plansza_[x + 1][y + 1].czy_mina && y < roz_y - 1 && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x - 1][y + 1].czy_mina && x > 0 && y < roz_y - 1)
		{
			ile_min++;
		}

	}
	else if (x == roz_x - 1)
	{
		if (plansza_[x - 1][y].czy_mina && x > 0)
		{
			ile_min++;
		}

		if (plansza_[x][y - 1].czy_mina && y > 0)
		{
			ile_min++;
		}
		if (plansza_[x][y + 1].czy_mina && y < roz_y - 1)
		{
			ile_min++;
		}
		if (plansza_[x - 1][y - 1].czy_mina && x > 0 && y > 0)
		{
			ile_min++;
		}

		if (plansza_[x - 1][y + 1].czy_mina && x > 0 && y < roz_y - 1)
		{
			ile_min++;
		}



	}
	else if (y == roz_y - 1)
	{
		if (plansza_[x - 1][y].czy_mina && x > 0)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y].czy_mina && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x][y - 1].czy_mina && y > 0)
		{
			ile_min++;
		}

		if (plansza_[x - 1][y - 1].czy_mina && x > 0 && y > 0)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y - 1].czy_mina && x < roz_x - 1 && y>0)
		{
			ile_min++;
		}





	}
	else
	{
		if (plansza_[x - 1][y].czy_mina && x > 0)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y].czy_mina && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x][y - 1].czy_mina && y > 0)
		{
			ile_min++;
		}
		if (plansza_[x][y + 1].czy_mina && y < roz_y - 1)
		{
			ile_min++;
		}
		if (plansza_[x - 1][y - 1].czy_mina && x > 0 && y > 0)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y + 1].czy_mina && y < roz_y - 1 && x < roz_x - 1)
		{
			ile_min++;
		}
		if (plansza_[x - 1][y + 1].czy_mina && x > 0 && y < roz_y - 1)
		{
			ile_min++;
		}
		if (plansza_[x + 1][y - 1].czy_mina && x < roz_x - 1 && y>0)
		{
			ile_min++;
		}
	}



	return ile_min;

}
