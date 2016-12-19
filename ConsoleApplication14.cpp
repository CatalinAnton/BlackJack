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
void showcards();
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
	char name[25],c;
	int carti[52],k=4;
	unsigned int money = 100, compmoney=100, bid, sum;
	sum = 0;
	int playerCards[6], compCards[6];
	cout << endl << "Give us your name!" << endl;
	cin.getline(name,25);

	cout << "you have " << money << " bucks! how much do you want to bid?";
	cin >> bid;

	money = money - bid;
	compmoney = compmoney - bid;

	sum = bid * 2;

	shuffle(carti);
	playerCards[0] = carti[0];
	playerCards[1] = carti[1];
	compCards[0] = carti[2];
	compCards[1] = carti[3];

	cout << "\ncartile tale sunt " << playerCards[0] << "si " << playerCards[1] << endl;
	cout << "mai tragi o carte? (Y/N)\n";
	cin >> c;
	if (c == 'Y')
	{
		playerCards[2] = carti[k];
		k++;

		cout << "\ncartile tale sunt " << playerCards[0] << "si " << playerCards[1] << "si " << playerCards[2] <<endl;
	}
	else if (c == 'N')
	{
		cout << "ok, deci nu vrei.\n";
	}

	
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

