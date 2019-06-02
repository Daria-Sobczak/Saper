// saper.cpp : Ten plik zawiera funkcję „mn”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "Gra.h"
#include <ctime>






int main()
{
	srand(time(NULL));

	Gra G;

	G.graj();

	return 0;
}

