#pragma once
#include<string>
#include<string.h>
using namespace std;
struct node
{
	char name[25];
	int money;
	node *next;
};

node addNode(node *head, char name[25],int money)
{
	node *current = new node;
	string x;
	x = name;
	current.name = x;
	current.money = money;

	head->next = current;
	current->next = NULL;
}