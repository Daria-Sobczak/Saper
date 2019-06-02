#include "pch.h"
#include "Gra.h"


Gra::Gra()
{
	poziom = SREDNI;
	rozmiar = 20; 
	P = new plansza(&oknoAplikacji, poziom, rozmiar);

}

void Gra::graj()
{
	int x, y;
	int opcja;
	while (oknoAplikacji.isOpen())
	{
		sf::Event event;
		while (oknoAplikacji.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				oknoAplikacji.close();

		}

		//reset
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			P = new plansza(&oknoAplikacji,poziom,rozmiar);
		}
		// poziomy
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			poziom = LATWY;
			P = new plansza(&oknoAplikacji, poziom, rozmiar);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			poziom = SREDNI;
			P = new plansza(&oknoAplikacji, poziom, rozmiar);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			poziom = TRUDNY;
			P = new plansza(&oknoAplikacji, poziom, rozmiar);
		}
		//rozmiar
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			rozmiar = 10;
			P = new plansza(&oknoAplikacji, poziom, rozmiar);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			rozmiar = 20;
			P = new plansza(&oknoAplikacji, poziom, rozmiar);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			rozmiar = 30;
			P = new plansza(&oknoAplikacji, poziom, rozmiar);
		}



		x = (sf::Mouse::getPosition(oknoAplikacji).x + 15) / 30;
		y = (sf::Mouse::getPosition(oknoAplikacji).y + 15) / 30;
		if (x - 1 >= 0 && x - 1 <= rozmiar-1 && y - 1 >= 0 && y - 1 <= rozmiar-1)
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				P->odkryj_pole(x - 1, y - 1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				P->zmien_status_flagi(x - 1, y - 1);


			sf::sleep(sf::milliseconds(80));
		}

		oknoAplikacji.clear();
		if (P->trafiles_na_mine())
		{

			P->Rysuj_okno();
			sf::RectangleShape Rect(sf::Vector2f(350, 50));
			Rect.setPosition(30, 30);
			Rect.setFillColor(sf::Color::Green);
			sf::Font czcionka;
			czcionka.loadFromFile("arial.ttf");

			sf::Text text;
			text.setFont(czcionka);


			text.setString("PRZEGRALES!!!!");
			text.setCharacterSize(40);
			text.setFillColor(sf::Color::Black);
			text.setPosition(30, 30);
			oknoAplikacji.draw(Rect);
			oknoAplikacji.draw(text);
		}
		else if (P->Wygrales())
		{
			P->Rysuj_okno();
			sf::RectangleShape Rect(sf::Vector2f(350, 50));
			Rect.setPosition(30, 30);
			Rect.setFillColor(sf::Color::Green);
			sf::Font czcionka;
			czcionka.loadFromFile("arial.ttf");

			sf::Text text;
			text.setFont(czcionka);


			text.setString("WYGRALES!!!!");
			text.setCharacterSize(40);
			text.setFillColor(sf::Color::Black);
			text.setPosition(30, 30);
			oknoAplikacji.draw(Rect);
			oknoAplikacji.draw(text);
		}
		else 
		{
			P->Rysuj_okno();
		}

		P->menu();
		oknoAplikacji.display();
	}


}

Gra::~Gra()
{
}
