// ConsoleApplication14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<ctime>
#include<string.h>
#include<fstream>
#include"structs.h"


#define nrCarti 52
#define hand 12


void menu();
void shuffle(unsigned int carti[52]);
void help();
void start();
void about();
void showCards(int vector[hand], int player);
void decodificare(int carte);
void incheiere(int playerCards[hand], int compCards[hand], int carti[nrCarti], int sumaPlayer,char name[25], int nivel);
void win(int $money, int bid);
void lose(int $compmoney, int bid);
void registerLogin(char name[25]);
void update(char name[25], int money);
void addList(node *head, jucator player);
void showList(node *head);
void scoreboard();
void quicksort(jucator *players, int left, int right);
void swap(int i, int j, jucator *a);
void updateHistory(string data);
void processUsedCards(int playerCards[hand], int compCards[hand]);
int handSum(int playerCards[hand], int sumaPlayer);
void showFrequency();
void preorder(btree *head);
int money = 1000;
int compmoney = 1000;
int bid;

string history=" ";

void shuffle(int carti[52])
{
	int i, j,l, nrShuffles, aux,cartiAux[52],k;
	

	srand(clock());
	nrShuffles = rand() % 3 + 1;
	for (i = 0; i <= nrCarti - 1; i++)
		carti[i] = i;

	for (j = 1; j<nrShuffles; j++)
		for (i = 0; i < nrCarti - 1; i++)
		{
			l = rand() % 52;
			
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
	cout << endl;
	cout << "  ---------------------------------------------  " << endl;
	cout << " |             This is Blackjack!!             | " << endl;
	cout << " |___________________RULES:____________________| " << endl;
	cout << " |     The goal of the game is to have less    | " << endl;
	cout << " |   or exactly 21 points. The closer you are  | " << endl;
	cout << " |             to 21, the better!              | " << endl;
	cout << " |---------------------------------------------| " << endl;
	cout << " | o Ace can be 1 or 11                        | " << endl;
	cout << " | o Blackjack or Winning Hand:                | " << endl;
	cout << " | (You get the double amount of what you bid) | " << endl;
	cout << " | o If Dealer gets Blackjack:                 | " << endl;
	cout << " |   - Player loses what he bets               | " << endl;
	cout << " | o If Dealer's score beats Player's score:   | " << endl;
	cout << " |   - Player loses what he bets               | " << endl;
	cout << " | o Push (Tie Score):                         | " << endl;
	cout << " |   - Regain your initial betting amount      | " << endl;
	cout << " |---------------------------------------------|  " << endl;
	cout << " | Scoreboard -                                | " << endl;
	cout << " | o You are ranked based on total money.      | " << endl;
	cout << " | o A rank of 0 means that you haven't played.| " << endl;
	cout << " |---------------------------------------------|  " << endl;
	cout << " | Game logs -                                 | " << endl;
	cout << " | o After you finish a game, it is saved      | " << endl;
	cout << " |   in a database so later you can show       | " << endl;
	cout << " |   your Blackjack skills to your mom         | " << endl;
	cout << " |---------------------------------------------|  " << endl;
	cout << " |    (start | help | score | about | exit)    | " << endl;
	cout << " |_____________________________________________| " << endl << endl; cout << endl;


};
void menu()
{
	char option[20];
	do{
	cin.getline(option, 20);
	

	if (strcmp(option, "help")==0)
		{
		help();
		}
	else if (strcmp(option, "start") == 0) start();
	else if (strcmp(option, "exit") == 0) return;
	else if (strcmp(option, "score") == 0) scoreboard();
	else if (strcmp(option, "about") == 0) about();
	else {
		cout << "You are in the menu now! What do you wish to do?\n(start | help | score | about | exit)" << endl;
		}
	} while (strcmp(option, "exit") != 0);
	
	
}
void start()
{
	char name[25], c, continua = 'n';
	int carti[52], k = 4, as, nivel = 1;
	int playerCards[6], compCards[6];
	char *data = " ";
	cout << endl << "Give us your name!" << endl;
	cin.getline(name, 25);
	registerLogin(name);
	if (money == 0)
	{
		cout << "I see you don't like to lose, so here are another 200 bucks. You are welcome :)\n";
		money = 200;
	}

	cout << "Choose the difficulty level! (1-easy | 2-medium | 3-hard)" << endl;
	cin >> nivel;
	while (nivel != 1 && nivel != 2 && nivel != 3 || std::cin.fail())
		{
			
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bad entry. Choose the difficulty level! (1-easy | 2-medium | 3-hard) \n";
				std::cin >> nivel;
			
	    }
		switch (nivel)
		{
		case 1:
			compmoney = 1000;
			break;
		case 2:
			compmoney = money;
			break;
		case 3:
			compmoney = money*2;
		}
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
		
		cout << "the dealer has " << compmoney << " bucks" << endl;
		
			cout << "you have " << money << " bucks! how much do you want to bid?" << endl;
			cin >> bid;

			while (!(bid > 0 && bid <= money && bid<=compmoney) || std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bad entry.  Enter a number between 1 and your current available amount of money: ";
				std::cin >> bid;
			}
		money = money - bid;
		compmoney = compmoney - bid;

		bid = bid * 2;

		shuffle(carti);
		//init carti
		playerCards[0] = carti[0];
		playerCards[1] = carti[1];
		compCards[0] = carti[2];
		compCards[1] = carti[3];

		showCards(playerCards,1);
		int sumaPlayer = 0;
		int l = 0;
		
		sumaPlayer = sumaPlayer + handSum(playerCards, sumaPlayer);

		if (sumaPlayer == 21)
		{
			cout << "You won this round!\n";
			money = money + bid;
		}
		else
		{
			sumaPlayer = 0;
			cout << "Draw another card? (Y/N)\n";
			cin >> c;
			isUnder21 = true;
			int pozUrmCarte = 2;
			k = 4;
			while ((c == 'y' || c == 'Y') && isUnder21 == true)
			{
				//se mai pune o carte in mana jucatorului
				playerCards[pozUrmCarte] = carti[k];
				k++;
				pozUrmCarte++;
				showCards(playerCards,1);

				l = 0;
				as = 0;
				sumaPlayer = 0;//ultima modificare
				sumaPlayer = sumaPlayer + handSum(playerCards, sumaPlayer);
				
				if (sumaPlayer == 21)
				{
					cout << "You won this round!\n";
					money = money + bid;
					isUnder21 = false;//ca sa se opreasca
					//return
					update(name, money);

					processUsedCards(playerCards, compCards);
				}
				else if (sumaPlayer > 21)
				{
					isUnder21 = false;
					cout << "You lost this round!\n";
					compmoney = compmoney + bid;
					update(name, money);
					processUsedCards(playerCards, compCards);
					//return
				}
				else
				{
					cout << "Draw another card? (Y/N)\n";
					cin >> c;
				}

			}
			if (c == 'n' || c == 'N')
			{
				//facem suma cartilor
				sumaPlayer = 0;
				sumaPlayer = sumaPlayer + handSum(playerCards, sumaPlayer);
				
				incheiere(playerCards, compCards, carti,sumaPlayer,name,nivel);
			}
		}
		//aici se incheie
		if (money > 0 && compmoney>0)
		{
			cout << "Play again?(Y/N)" << endl;
			cin >> continua;
			if (continua == 'n' || continua == 'N')
			{
				//concatenare
				history = history + name;
				history = history + " left the game. Bucks now: ";
				history = history + std::to_string(money);
				history = history + " difficulty: ";
				history = history + std::to_string(nivel);
				cout << history<<endl;
				updateHistory(history);
				history = " ";

				processUsedCards(playerCards, compCards);
				return;
			}
		}
		else if(money<=0){
			continua = 'n';
			//concatenare
			cout << "sorry, you have no money left :<"<<endl;
			history = history + name;
			history = history + " lost! No money left. Bucks now: ";
			history= history + std::to_string(money);
			history = history + " difficulty: ";
			history = history + std::to_string(nivel);

			updateHistory(history);
			history = " ";

			processUsedCards(playerCards, compCards);
			return;
			}
		else
		{
			continua = 'n';
			cout << "Congratulations! You won! The computer has no money left" << endl;
			history = history + name;
			history = history + " Won! The computer has no money left. Bucks now: ";
			history = history + std::to_string(money);
			history = history + " difficulty: ";
			history = history + std::to_string(nivel);

			updateHistory(history);
			history = " ";

			processUsedCards(playerCards, compCards);
			
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
			cout << y << "bucks !\n";
			write << y << endl;
			money = std::stoi(y);
			found = true;
		}
	}
	if (found == false)
	{
		cout << "You are new here. I just registered you. \nNow you have 1000 bucks. ";
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
	cout << "You won!";
	compmoney = compmoney + bid;
}
void win(int $money, int $compmoney, int bid)
{
	cout << endl << "You lost!";
	money = money + bid;

}
void incheiere(int playerCards[11], int compCards[11],int carti[52], int sumaPlayer, char name[25], int nivel)
{
	int sumaComp;
	

	int i = 0;
	
	cout << "Your sum:  " << sumaPlayer << endl;

	sumaComp = 0;
	sumaComp = handSum(compCards, sumaComp);
	
	showCards(compCards, 0);
	int k = 8;
	i = 2;
	switch (nivel)
	{
	case 1://easy
		int trage;
		trage = rand() % 2;
		while (trage == 1)
		{
			compCards[i] = carti[k];
			if (compCards[i] / 4 < 10) sumaComp = sumaComp + compCards[i] / 4 + 1;
			else sumaComp = sumaComp + 10;
			i++;
			k++;

			trage = rand() % 2;
			if (sumaComp > 21) trage = 0;
		}
		break;
	case 2://nivel mediu
		
		while (sumaComp < 17)
		{
			
			compCards[i] = carti[k];
			if (compCards[i] / 4 < 10)
				sumaComp = sumaComp + compCards[i] / 4 + 1;
			else sumaComp = sumaComp + 10;
			i++;
			k++;

		}
		break;
	case 3://hard
		int magic = 0;
		if (sumaPlayer == 20)
		{
			while (sumaComp < 20)
			{
				compCards[i] = carti[k];
				if (compCards[i] / 4 < 10)
				{
					sumaComp = sumaComp + compCards[i] / 4 + 1;
					if (compCards[i] / 4 == 0) magic = 1;
				}
				else sumaComp = sumaComp + 10;
				if (sumaComp + 10 <= 21 && magic == 1)
				{
					sumaComp = sumaComp + 10;
				}
				i++;
				k++;

			}
		}
		else if (sumaPlayer == 19)
		{
			while (sumaComp < 19)
			{
				compCards[i] = carti[k];
				if (compCards[i] / 4 < 10)
				{
					sumaComp = sumaComp + compCards[i] / 4 + 1;
					if (compCards[i] / 4 == 0) magic = 1;
				}
				else sumaComp = sumaComp + 10;
				if (sumaComp + 10 < 21 && magic == 1)
				{
					sumaComp = sumaComp + 10;
				}
				i++;
				k++;

			}
		}
		else
		{
			while (sumaPlayer >= sumaComp)
			{
				compCards[i] = carti[k];
				if (compCards[i] / 4 < 10)
				{
					sumaComp = sumaComp + compCards[i] / 4 + 1;
					if (compCards[i] / 4 == 0) magic = 1;
				}
				else sumaComp = sumaComp + 10;
				if (sumaComp + 10 <= 21 && magic == 1)
				{
					sumaComp = sumaComp + 10;
				}
				i++;
				k++;
			}
		}

	}
	showCards(compCards, 0);
	cout << "Dealer's sum " << sumaComp << endl;
	if (sumaComp > 21)
	{
		cout << "You won this round!\n";
		money = money + bid;
		update(name, money);
		processUsedCards(playerCards, compCards);
	}
	else if((sumaComp > sumaPlayer && sumaComp<21 && sumaPlayer<21) || sumaComp==21)
	{
		
		cout << "You lost this round!\n";
		compmoney = compmoney + bid;
		update(name, money);
		processUsedCards(playerCards, compCards);
	}
	else if (sumaComp == sumaPlayer && sumaComp < 21)
	{
		cout << "push! Tie score\n";
		money = money + bid/2;
		compmoney = compmoney + bid / 2;
		processUsedCards(playerCards, compCards);
	}
	else
	{
		cout << "You won this round!\n";
		money = money + bid;
		update(name, money);
		processUsedCards(playerCards, compCards);
	}
}
void showCards(int vector[hand], int player)
{
	int i = 0;
	if(player==1)
	{ 
	cout << "Your cards are \n";
	}
	else
	{
		cout << "Dealer's cards are\n";
	}
	while (vector[i] != -1)
	{
		decodificare(vector[i]);
		i++;
	}
	cout << endl;
}


void decodificare(int carte)
{
	if(carte/4<10 && carte/4>0)cout << carte / 4 + 1 << " of ";
	else
	{

		switch (carte / 4)
		{
		case 0: cout << "Ace ";
			break;
		case 10: cout << "J ";
			break;
		case 11: cout << "Q ";
			break;
		case 12: cout << "K ";
			break;
		default: cout << "wtf ";
			break;
		}
		cout << "of ";
		
	}
	switch (carte % 4)
	{
	case 0:
		cout << " Spades ";
		break;
	case 1:
		cout << " Clubs ";
		break;
	case 2:
		cout << " Hearts ";
		break;
	case 3:
		cout << " Diamonds ";
		break;
	default: cout << "wtf";
		break;
	}

	cout << endl;
}

void scoreboard()
{
	node *head;
	jucator players[500];
	ifstream read("players.txt");
	jucator aux;
	int k, j, i = 0;
	int ok = 0;
	string y;
	while (!read.eof())
	{
		getline(read, y);
		if (!y.empty() && ok == 0)
		{
			players[i].name = y;
			ok = 1;
		}
		else if (!y.empty())
		{
			players[i].bani = std::stoi(y);
			ok = 0;
			i++;
		}

	}
	i--;
	k = i;


	read.close();
	//quicksort(players, 0, k-1);

	for (i = 0; i <= k - 1; i++)
		for (j = i + 1; j <= k; j++)
		{
			if (players[j].bani > players[i].bani)
			{
				aux = players[i];
				players[i] = players[j];
				players[j] = aux;
			}
		}


	head = new node;
	head->next = NULL;
	head->money = players[0].bani;
	head->name = players[0].name;

	i = 0;
	i++;
	while (i <= k)
	{
		addList(head, players[i]);
		i++;
	}

	showList(head);
	cout << " (start | help | score | about | exit)" << endl;
}
void addList(node *head, jucator player)
{
	node *current;
	node *parcurgere;
	current = new node;
	current->money = player.bani;
	current->name = player.name;
	current->next = NULL;

	parcurgere = head;
	while (parcurgere->next != NULL)
	{
		parcurgere = parcurgere->next;
	}
	parcurgere->next = current;
}

void showList(node *head)
{
	node *parcurgere;
	parcurgere = head;
	int i = 1;
	while (parcurgere != NULL)
	{
		cout << i << ". " << parcurgere->name << " " << parcurgere->money << endl;
		parcurgere = parcurgere->next;
		i++;
	}
}

void swap(int i, int j, jucator *a) {
	jucator temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}


void quicksort(jucator *players, int left, int right) {
	int min = (left + right) / 2;
	cout << "QS:" << left << "," << right << "\n";

	int i = left;
	int j = right;
	int pivot = players[min].bani;

	while (left<j || i<right)
	{
		while (players[i].bani<pivot)
			i++;
		while (players[j].bani>pivot)
			j--;

		if (i <= j) {
			swap(i, j, players);
			i++;
			j--;
		}
		else {
			if (left<j)
				quicksort(players, left, j);
			if (i<right)
				quicksort(players, i, right);
			return;
		}
	}
}


void updateHistory(string history)
{
	ifstream reader("gamesHistory.txt");
	ofstream writer("tempGames.txt");
	string y;
	while (!reader.eof())
	{
		getline(reader, y);
		if(!y.empty())writer << y << endl;//aci
	}

	writer << history << endl;
	reader.close();
	writer.close();
	remove("gamesHistory.txt");
	rename("tempGames.txt", "gamesHistory.txt");

}

void about()
{
	cout << endl;
	cout << "  ---------------------------------------------  " << endl;
	cout << " | By Anton Catalin     UAIC, Computer Science | " << endl;
	cout << " |_Year I, Group B1____________________________| " << endl;
	cout << " |                                             | " << endl;
	cout << " |   Date: 1 / 7 / 2017                        | " << endl;
	cout << " |---------------------------------------------| " << endl;
	cout << " |   This program is free software. Although,  | " << endl;
	cout << " |       I do not provide any warranty         | " << endl;
	cout << " |            regarding the product            | " << endl;
	cout << " |---------------------------------------------|  " << endl;
	cout << " |    (start | help | score | about | exit)    | " << endl;
	cout << " |_____________________________________________| " << endl << endl; cout << endl;
}

void processUsedCards(int playerCards[hand], int compCards[hand])
{
	int i = 0, j = 0,k, frecventa[nrCarti];

	for (k = 0; k <= nrCarti - 1; k++)	//init
	{
		frecventa[k] = 0;
	}
	
	
	while (playerCards[i] != -1)
	{
		frecventa[playerCards[i]]++;
		i++;
	}
	while (compCards[j] != -1)
	{
		frecventa[compCards[j]]++;
		j++;
	}

	ifstream fin ("usedCards.txt");
	ofstream fout("tempUsedCards.txt");
	int fileData;
	int c = nrCarti;
	while (c>0)
	{
		fin >> fileData;
		fout << fileData;
		if (frecventa[fileData] == 1)
		{
			fin >> fileData;
			fileData++;
			fout << " " << fileData << endl;
		}
		else
		{
			fin >> fileData;
			fout << " " << fileData << endl;
		}
		c--;
	}
	fin.close();
	fout.close();
	remove("usedCards.txt");
	rename("tempUsedCards.txt", "usedCards.txt");
}

int handSum(int playerCards[hand], int sumaPlayer)
{
	int l, as;
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
	return sumaPlayer;
}

void showFrequency()
{
	ifstream citeste("usedCards.txt");
	int card;
	int frequency;

	btree *head;
	head = new btree;
	citeste >> card;
	citeste >> frequency;
	head = initTree(head, frequency, card);

	while (citeste>>card>>frequency)
	{
		head = insertTree(head, frequency, card);
	}
	preorder(head);
	citeste.close();
}

void preorder(btree *head)
{
	if (head != NULL)
	{
		cout << head->frequency << " ";
		decodificare(head->card);
		preorder(head->left);	
		preorder(head->right);	
	}
}
int main()
{
	 int carti[52];
	shuffle(carti);
	showFrequency();
	cout << "This is BlackJack! You are in the menu now" << endl << "type help for more information!" << endl;
	menu();
	system("pause");

	return 0;
}

