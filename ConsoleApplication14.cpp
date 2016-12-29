// ConsoleApplication14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<string.h>

using namespace std;

#define nrCarti 52

void menu();
void shuffle(unsigned int carti[52]);
void help();
void start();
void showCards(int vector[7]);
void decodificare(int carte);
void incheiere(int playerCards[11], int compCards[11]);

void shuffle(int carti[52])
{
	int i, j,l, nrShuffles, aux;
	nrShuffles = 3;

	for (i = 0; i <= nrCarti - 1; i++)
		carti[i] = i;

	for (j = 1; j<nrShuffles; j++)
		for (i = 0; i < nrCarti - 1; i++)
		{
			l = rand() % 51;

			aux = carti[i];
			carti[i] = carti[l];
			carti[l] = aux;

		}
}
void help()
{
	cout << "nananananana";
	cout << "apasa start ca sa icnepi jocul\n";

};
void menu()
{
	char option[20];
	cout << "This is BlackJack! You are in the menu now" << endl << "type help for more information!"<<endl;
	cin.getline(option, 20);

	if (strcmp(option, "help")==0) {
		help();
		cout << "a intrat in help";
	}
	if (strcmp(option, "start") == 0) start();
	

}
void start()
{
	char name[25], c;
	int carti[52], k = 4;
	unsigned int money = 100, compmoney = 100, bid, sum;
	sum = 0;
	int playerCards[6], compCards[6];

	for (int i = 0; i <= 5; i++)
	{
		playerCards[i] = -1;
		compCards[i] = -1;
	}
	cout << endl << "Give us your name!" << endl;
	cin.getline(name, 25);

	cout << "you have " << money << " bucks! how much do you want to bid?";
	cin >> bid;

	money = money - bid;
	compmoney = compmoney - bid;

	sum = bid * 2;

	shuffle(carti);
	shuffle(carti);
	//init carti
	playerCards[0] = carti[0];
	playerCards[1] = carti[1];
	compCards[0] = carti[2];
	compCards[1] = carti[3];

	showCards(playerCards);
	cout << "mai tragi o carte? (Y/N)\n";
	cin >> c;
	if (c == 'Y'|| c=='y')
	{
		playerCards[2] = carti[k];
		k++;

		showCards(playerCards);
	}
	else if (c == 'N' || c== 'n')
	{
		incheiere(playerCards, compCards);
	}

	
}

void incheiere(int playerCards[11], int compCards[11])
{
	int sumaPlayer, sumaComp;
	sumaPlayer = 0;

	int i = 0;

	while (playerCards[i] != -1)
	{
		if (playerCards[i]/4 == 10)sumaPlayer = sumaPlayer + 12;
		else if (playerCards[i]/4 == 11)sumaPlayer = sumaPlayer + 13;
		else if (playerCards[i]/4 == 12)sumaPlayer = sumaPlayer + 14;
		else if (sumaPlayer + 11 > 21 && playerCards[i] / 4 == 0) sumaPlayer++;
		else sumaPlayer = sumaPlayer + playerCards[i] / 4;
		i++;
	}
	showCards(playerCards);
	cout << "totalul tau: " << sumaPlayer << endl;
}
void showCards(int vector[52])
{
	int i = 0;
	cout << "\ncartile tale sunt \n";
	while (vector[i] != -1)
	{
		decodificare(vector[i]);
		i++;
	}
	cout << endl;
}

void decodificare(int carte)
{
	if(carte<10)cout << carte / 4 + 1 << " de ";
	else cout<< carte / 4 + 2 << " de ";
	switch (carte % 4)
	{
	case 0:
		cout << " frunza ";
		break;
	case 1:
		cout << " trefla ";
		break;
	case 2:
		cout << " inima ";
		break;
	case 3:
		cout << " romb ";
		break;
	default: cout << "nu exista simbolul asta";
	}

	cout << endl;
}
int main()
{
	 int carti[52];
	shuffle(carti);
	int n, i;

	for (i = 0; i < nrCarti; i++)
		cout << carti[i] << " ";
	cout << endl;

	menu();
	cin >> n;

	return 0;
}

