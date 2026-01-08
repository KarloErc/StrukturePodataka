/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u èvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraæa
pokazivaè na korijen stabla.
b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat æe se u stablo na
slici Slika 2.
c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira sluèajne brojeve u rasponu <10, 90>. Takoðer, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node* Position;
typedef struct Node {
	int Number;
	Position Left;
	Position Right;
}Node;

Position CreateNode(int);
Position Insert(Position, int);
int Replace(Position);
int InorderFILE(Position, FILE*);
int PrintTree(Position, int);
int FreeMemory(Position);

int main()
{
	Position Root = NULL;
	int i;
	int A[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	//a)
	int n = sizeof(A) / sizeof(A[0]);

	for (i = 0; i < n; i++)
		Root = Insert(Root, A[i]);

	printf("Tree(Picture 1):\n");
	PrintTree(Root, 0);
	
	//b)
	Replace(Root);
	printf("Tree after replace(Picture 2):\n");
	PrintTree(Root, 0);

	FreeMemory(Root);

	//c)
	Root = NULL;
	int Value;
	FILE* fp = fopen("inorder.txt", "w");
	if (fp == NULL)
	{
		printf("Cannot open file!!\n");
		return -1;
	}
	srand((unsigned)time(NULL));
	n = 10;

	for (i = 0; i < n; i++)
	{
		Value = rand() % (90 - 10 + 1) + 10;
		Root = Insert(Root, Value);
	}

	fprintf(fp, "Inorder after insert:\n");
	InorderFILE(Root, fp);
	fprintf(fp, "\n");

	Replace(Root);

	fprintf(fp, "Inorder after replace:\n");
	InorderFILE(Root, fp);
	fprintf(fp, "\n");

	fclose(fp);
	FreeMemory(Root);

	return 0;
}

//stvara novi cvor stabla
Position CreateNode(int Value)
{
	Position Node = NULL;
	Node = (Position)malloc(sizeof(*Node));

	if (Node == NULL)
	{
		printf("Cannot allocate memory for new node!!");
		return NULL;
	}

	Node->Number = Value;
	Node->Left = NULL;
	Node->Right = NULL;

	return Node;
}

//ubacuje novi element u stablo
Position Insert(Position Root, int Value)
{
	if (Root == NULL)
		return CreateNode(Value);

	if (Value >= Root->Number)
		Root->Left = Insert(Root->Left, Value);
	else
		Root->Right = Insert(Root->Right, Value);

	return Root;
}



int Replace(Position Root)
{
	if (Root == NULL)
		return 0;

	int LeftSum = Replace(Root->Left);
	int RightSum = Replace(Root->Right);

	int BeforeValue = Root->Number;
	Root->Number = LeftSum + RightSum;

	return Root->Number + BeforeValue;
}

int PrintTree(Position Root, int Level)
{
	if (Root == NULL)
		return 0;

	for (int i = 0; i < Level; i++)
		printf("    ");

	printf("%d\n", Root->Number);

	PrintTree(Root->Left, Level + 1);
	PrintTree(Root->Right, Level + 1);

	return 0;
}

int InorderFILE(Position Root, FILE* fp)
{
	if (Root == NULL)
		return 0;

	InorderFILE(Root->Left, fp);
	fprintf(fp, "%d ", Root->Number);
	InorderFILE(Root->Right, fp);

	return 0;
}

int FreeMemory(Position Root)
{
	if (Root == NULL)
		return 0;

	FreeMemory(Root->Left);
	FreeMemory(Root->Right);
	free(Root);

	return 0;
}