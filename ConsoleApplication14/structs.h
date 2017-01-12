#pragma once
#include<string.h>
#include<string>

using namespace std;
struct jucator
{
	int bani;
	string name;
};
struct node
{
	int money;
	string name;
	node *next;
};

struct btree
{
	int card;
	int frequency;
	btree *left;
	btree *right;

};

btree * initTree(btree *head, int value, int card)
{
	head = new btree;
	head->card = card;
	head->frequency = value;
	head->left = NULL;
	head->right = NULL;

	return head;
}

btree * insertTree(btree * root, int value, int card)
{
	if (root == NULL)
	{
		btree * temp = new btree();
		root = temp;
		root->frequency = value;
		root->card = card;
		root->left = root->right = NULL;

	}
	else
	{
		if (value < root->frequency)
		{
			root->left = insertTree(root->left, value, card);
		}
		else
		{
			root->right = insertTree(root->right, value, card);
		}
	}
	return root;
}

