// ConsoleApplication14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<string.h>
#include<fstream>



using namespace std;

#define nrCarti 52

void menu();
void shuffle(unsigned int carti[52]);
void help();
void start();
void showCards(int vector[7]);
void decodificare(int carte);
void incheiere(int playerCards[11], int compCards[11], int carti[nrCarti], int sumaPlayer,char name[25]);
void win(int $money, int bid);
void lose(int $compmoney, int bid);
void registerLogin(char name[25]);
void update(char name[25], int money);
int money = 100;
int compmoney = 1000;
int bid;
void shuffle(int carti[52])
{
	int i, j,l, nrShuffles, aux,cartiAux[52],k;
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
	i = 0;
	l = 25;
	k = 0;
	int aleatoriu;
	while (i <= 24 && l <= 51)
	{
		aleatoriu = rand() % 2;
		if (aleatoriu == 0)
		{
			cartiAux[k] = carti[i];
			i++;
			k++;
		}
		else
		{
			cartiAux[k] = carti[l];
			l++;
			k++;
		}
		
	}
	while (i <= 24)
	{
		cartiAux[k] = carti[i];
		i++;
		k++;
	}
	while (l <= 51)
	{
		cartiAux[k] = carti[l];
		l++;
		k++;
	}

	for (i = 0; i <= 51; i++)
	{
		carti[i] = cartiAux[i];
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

	else if (strcmp(option, "exit") == 0) return;
	else
	{
		cout << "don't know what's that. Want to try again?";
		menu();
	}
	

}

void start()
{
	char name[25], c,continua='n';
	int carti[52], k = 4,as;
	int playerCards[6], compCards[6];

	cout << endl << "Give us your name!" << endl;
	cin.getline(name, 25);
	registerLogin(name);
	do {

		shuffle(carti);
		//de aici incepe
		bool isUnder21 = true;
		//initializeaza mainile jucatorilor
		for (int i = 0; i <= 5; i++)
		{
			playerCards[i] = -1;
			compCards[i] = -1;
		}
		

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
		l = 0;
		as = 0;
		while (playerCards[l] != -1)//face suma
		{
			if (playerCards[l] / 4 >= 10)sumaPlayer = sumaPlayer + 10;
			else if (playerCards[l] / 4 != 0)sumaPlayer = sumaPlayer + playerCards[l] / 4 + 1;
			else
			{
				as = 1;
				sumaPlayer++;
			}
			l++;
		}
		if (sumaPlayer + 10 <= 21 && as == 1) sumaPlayer = sumaPlayer + 10;
		cout << sumaPlayer << endl;
		if (sumaPlayer == 21)
		{
			cout << "Ai castigat!\n";
			money = money + bid;
		}
		else
		{
			sumaPlayer = 0;
			cout << "tragi o carte? (Y/N)\n";
			cin >> c;
			isUnder21 = true;
			int pozUrmCarte = 2;
			k = 4;
			while ((c == 'y' || c == 'Y') && isUnder21 == true)
			{

				cout << sumaPlayer << endl;
				//se mai pune o carte in mana jucatorului
				playerCards[pozUrmCarte] = carti[k];
				k++;
				pozUrmCarte++;
				showCards(playerCards);

				l = 0;
				as = 0;
				sumaPlayer = 0;//ultima modificare
				while (playerCards[l] != -1)//face suma
				{
					if (playerCards[l] / 4 >= 10)sumaPlayer = sumaPlayer + 10;
					else if (playerCards[l] / 4 != 0)sumaPlayer = sumaPlayer + playerCards[l] / 4 + 1;
					else
					{
						as = 1;
						sumaPlayer++;
					}
					l++;
				}
				if (sumaPlayer + 10 <= 21 && as == 1) sumaPlayer = sumaPlayer + 10;
				showCards(playerCards);
				cout << "\ncsuma: " << sumaPlayer;
				if (sumaPlayer == 21)
				{
					cout << "ai castigat!\n";
					money = money + bid;
					isUnder21 = false;//ca sa se opreasca
					//return
					update(name, money);
				}
				else if (sumaPlayer > 21)
				{
					isUnder21 = false;
					cout << "ai pierdut!\n";
					compmoney = compmoney + bid;
					update(name, money);
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
				//facem suma cartilor
				sumaPlayer = 0;
				l = 0;
				as = 0;
				while (playerCards[l] != -1)//face suma
				{
					if (playerCards[l] / 4 >= 10)sumaPlayer = sumaPlayer + 10;
					else if (playerCards[l] / 4 != 0)sumaPlayer = sumaPlayer + playerCards[l] / 4 + 1;
					else
					{
						as = 1;
						sumaPlayer++;
					}
					l++;
				}
				if (sumaPlayer + 10 <= 21 && as == 1) sumaPlayer = sumaPlayer + 10;
				incheiere(playerCards, compCards, carti,sumaPlayer,name);
			}
		}
		//aici se incheie
		if (money > 0)
		{
			cout << "mai joci?(Y/N)" << endl;
			cin >> continua;
		}
		else {
			continua = 'n';
			cout << "sorry, you have no money left :<";
			}
	} while (continua == 'y' || continua == 'Y');
}

void registerLogin(char name[25])
{
	string x = name;
	string y;
	ifstream read("players.txt");
	ofstream write("playersUpdated.txt");
	bool found = false;
	while (!read.eof())
	{
		getline(read, y);
		write << y << endl;
		if (y == x)
		{
			cout << "welcome back, " << x << "! you have ";
			getline(read, y);
			cout << y << "bucks !";
			write << y << endl;
			money = std::stoi(y);
			found = true;
		}
	}
	if (found == false)
	{
		cout << "you are new here. I just registered you. Now you have 1000 bucks";
		money = 1000;
		/*while (!read.eof())
		{
			getline(read, y);
			write << y << endl;
		}
		*/
		write << x << endl << 1000;
	}
	read.close();
	write.close();
	remove("players.txt");
	rename("playersUpdated.txt", "players.txt");
}

void update(char name[25], int money)
{
	string x = name;
	string y;
	ifstream read("players.txt");
	ofstream write("playersUpdated.txt");
	while (!read.eof())
	{
		getline(read, y);
		if(!y.empty())write << y << endl;

		if (y == x)
		{

			getline(read, y);
			write << money << endl;

		}
	}
	read.close();
	write.close();
	remove("players.txt");
	rename("playersUpdated.txt", "players.txt");
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
void incheiere(int playerCards[11], int compCards[11],int carti[52], int sumaPlayer, char name[25])
{
	int sumaComp;
	
	int asc;

	int i = 0;
	/*
	int l = 0;
	int as = 0;
	while (playerCards[l] != -1)//face suma
	{
		if (playerCards[l] / 4 >= 10)sumaPlayer = sumaPlayer + 10;
		else if (playerCards[l] / 4 != 0)sumaPlayer = sumaPlayer + playerCards[l] / 4 + 1;
		else
		{
			as = 1;
			sumaPlayer++;
		}
		l++;
	}
	if (sumaPlayer + 10 <= 21 && as == 1) sumaPlayer = sumaPlayer + 10;
	showCards(playerCards);
	*/
	cout << "totalul tau: " << sumaPlayer << endl;

	sumaComp = 0;

	i = 0;
	asc = 0;
	while (compCards[i] != -1)
	{
		if (compCards[i] / 4 >= 10)sumaComp = sumaComp + 10;
		else if (compCards[i] / 4 != 0)sumaComp = sumaComp + compCards[i] / 4 + 1;
		else
		{
			asc = 1;
			sumaComp++;
		}
		i++;
	}
	if (sumaComp + 10 <= 21 && asc == 1) sumaComp = sumaComp + 10;
	cout << "cartile comp-----";
	showCards(compCards);

	int k = 2;
	while (sumaComp < 17)
	{
		compCards[i] = carti[k];
		if (compCards[i] / 4 < 10) sumaComp = sumaComp + compCards[i] / 4 + 1;
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
		update(name, money);
	}
	else if((sumaComp > sumaPlayer && sumaComp<21 && sumaPlayer<21) || sumaComp==21)
	{
		
		cout << "ai pierdut!\n";
		compmoney = compmoney + bid;
		update(name, money);
	}
	else if (sumaComp == sumaPlayer && sumaComp < 21)
	{
		cout << "egal!\n";
		money = money + bid/2;
		compmoney = compmoney + bid / 2;
	}
	else
	{
		cout << "ai castigat!\n";
		money = money + bid;
		update(name, money);
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
	if(carte/4<10)cout << carte / 4 + 1 << " de ";
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
		break;
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
	system("pause");

	return 0;
}

