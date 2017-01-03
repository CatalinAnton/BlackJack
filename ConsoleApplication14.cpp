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
void incheiere(int playerCards[11], int compCards[11], int carti[nrCarti]);
void win(int $money, int bid);
void lose(int $compmoney, int bid);

int money = 100;
int compmoney = 100;
int bid;
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
	cout << "nananananana\n";

};
void menu()
{
	char option[20];
	
	cin.getline(option, 20);

	if (strcmp(option, "help")==0) {
		help();
		cout << "a intrat in help";
	}else if (strcmp(option, "start") == 0) start();

	else
	{
		cout << "don't know what's that. Want to try again?";
		menu();
	}
	

}
void start()
{
	char name[25], c;
	int carti[52], k = 4;
	int playerCards[6], compCards[6];

	
		bool isUnder21 = true;

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

		bid = bid * 2;

		shuffle(carti);
		shuffle(carti);
		//init carti
		playerCards[0] = carti[0];
		playerCards[1] = carti[1];
		compCards[0] = carti[2];
		compCards[1] = carti[3];

		showCards(playerCards);
		int sumaPlayer = 0;
		int l = 0;
		//facem suma cartilor
		while (playerCards[l] != -1)
		{
			if (playerCards[l] / 4 >= 10)sumaPlayer = sumaPlayer + 10;
			else sumaPlayer = sumaPlayer + playerCards[l] / 4;
			l++;
		}
		cout << sumaPlayer << endl;
		sumaPlayer = 0;
		cout << "tragi o carte? (Y/N)\n";
		cin >> c;
		isUnder21 = true;
		int pozUrmCarte = 2;

		while ((c == 'y' || c == 'Y') && isUnder21 == true)
		{

			cout << sumaPlayer << endl;
			//se mai pune o carte in mana jucatorului
			playerCards[pozUrmCarte] = carti[k];
			k++;
			pozUrmCarte++;
			showCards(playerCards);

			l = 0;
			while (playerCards[l] != -1)//face suma
			{
				if (playerCards[l] / 4 >= 10)sumaPlayer = sumaPlayer + 10;
				else sumaPlayer = sumaPlayer + playerCards[l] / 4;
				l++;
			}
			showCards(playerCards);
			cout << "\ncsuma: " << sumaPlayer;
			if (sumaPlayer == 21)
			{
				cout << "ai castigat!\n";
				money = money + bid;
				isUnder21 = false;//ca sa se opreasca
				//return
			}
			else if (sumaPlayer > 21)
			{
				isUnder21 = false;
				cout << "ai pierdut!\n";
				compmoney = compmoney + bid;
				//return
			}
			else
			{
				cout << "tragi o carte? (Y/N)\n";
				cin >> c;
			}

		}
		if (c == 'n' || c == 'N')
		{
			cout << "ai ajuns la nu";
			incheiere(playerCards, compCards, carti);
		}

	
}

void lose(int $compmoney, int bid)
{
	cout << "Ai pierdut!";
	compmoney = compmoney + bid;
}
void win(int $money, int $compmoney, int bid)
{
	cout << endl << "Ai castigat!";
	money = money + bid;

}
void incheiere(int playerCards[11], int compCards[11],int carti[52])
{
	int sumaPlayer, sumaComp;
	sumaPlayer = 0;

	int i = 0;

	while (playerCards[i] != -1)
	{
		if (playerCards[i]/4 >= 10)sumaPlayer = sumaPlayer + 10;
		else sumaPlayer = sumaPlayer + playerCards[i] / 4;
		i++;
	}
	showCards(playerCards);
	cout << "totalul tau: " << sumaPlayer << endl;

	sumaComp = 0;

	i = 0;

	while (compCards[i] != -1)
	{
		if (compCards[i] / 4 >= 10)sumaComp = sumaComp + 10;
		else sumaComp = sumaComp + compCards[i] / 4;
		i++;
	}
	showCards(compCards);

	int k = 2;
	while (sumaComp < 17)
	{
		compCards[i] = carti[k];
		if (compCards[i] / 4 < 10) sumaComp = sumaComp + compCards[1] / 4 + 1;
		else sumaComp = sumaComp + 10;
		i++;
		k++;
		
	}
	showCards(compCards);
	cout << "totalul lui: " << sumaComp << endl;
	if (sumaComp > 21)
	{
		cout << "ai castigat!\n";
		money = money + bid;
	}
	else
	{
		cout << "ai pierdut!\n";
		compmoney = compmoney + bid;
	}
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
	cout << "This is BlackJack! You are in the menu now" << endl << "type help for more information!" << endl;
	menu();
	cin >> n;

	return 0;
}

