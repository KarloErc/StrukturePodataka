/* 2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
 A. dinamièki dodaje novi element na poèetak liste,
 B. ispisuje listu,
 C. dinamièki dodaje novi element na kraj liste,
 D. pronalazi element u listi (po prezimenu),
 E. briše odreðeni element iz liste,
 U zadatku se ne smiju koristiti globalne varijable.*/
/* 3. Prethodnom zadatku dodati funkcije:
 A. dinamièki dodaje novi element iza odreðenog elementa,
 B. dinamièki dodaje novi element ispred odreðenog elementa,
 C. sortira listu po prezimenima osoba,
 D. upisuje listu u datoteku,
 E. èita listu iz datoteke. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct Person* Position;
typedef struct Person {
	char Name[MAX];
	char Surname[MAX];
	int Birth;
	Position Next;
}Person;

int InputB(Position);
int Print(Position);
int InputE(Position);
Position LookingFor(char*, Position);
Position SearchPrevious(char*, Position);
int Delete(char*, Position);
int InputBehind(char*, Position);
int InputFront(char*, Position);
int Sort(Position);
int WriteInFile(Position);
int ReadFile(Position);
int DeleteAll(Position);

int main()
{
	Person Head = { .Name = {0}, .Surname = {0}, .Birth = {0}, .Next = NULL };
	char Surname[MAX];

	printf("Add person to the beginning:\n");
	InputB(&Head);
	InputB(&Head);

	printf("Add person to the end:\n");
	InputE(&Head);
	InputE(&Head);

	Print(Head.Next);

	printf("Enter Surname you are looking for: ");
	scanf("%s", Surname);

	Position Found = LookingFor(Surname, Head.Next);
	if (Found != NULL)
		printf("Found Person: %s %s %d\n", Found->Name, Found->Surname, Found->Birth);
	else
		printf("Person with surname '%s' was not a found.\n", Surname);

	Delete(Surname, &Head);
	Print(Head.Next);

	printf("Enter the surname of the person you want to add a new person after: ");
	scanf("%s", Surname);
	InputBehind(Surname, &Head);
	Print(Head.Next);

	printf("Enter the surname of the person you want to add a new person to: ");
	scanf("%s", Surname);
	InputFront(Surname, &Head);
	Print(Head.Next);

	Sort(&Head);
	Print(Head.Next);

	WriteInFile(Head.Next);

	DeleteAll(&Head);

	printf("\nRead from file:\n");
	ReadFile(&Head);
	Print(Head.Next);

	return 0;
}
//dodavanje na pocetak
int InputB(Position P)
{
	Position q;
	q = (Position)malloc(sizeof(Person));

	printf("Enter your Name, Surname and Birth: ");
	scanf("%s %s %d", q->Name, q->Surname, &q->Birth);

	q->Next = P->Next;
	P->Next = q;

	return 0;
}
//ispis liste
int Print(Position P)
{
	printf("Print List:\n");
	while (P != NULL) {
		printf("%s %s %d\n", P->Name, P->Surname, P->Birth);
		P = P->Next;
	}

	return 0;
}
//dodavanje na kraj
int InputE(Position P)
{
	Position q;
	q = (Position)malloc(sizeof(Person));

	printf("Enter your Name, Surname and Birth: ");
	scanf("%s %s %d", q->Name, q->Surname, &q->Birth);

	q->Next = NULL;

	
	while (P->Next != NULL) {
		P = P->Next;
	}
	P->Next = q;

	return 0;
}

Position LookingFor(char* Surname, Position P)
{
	while (P != NULL) {
		if (strcmp(P->Surname, Surname) == 0)
			return P;
		P = P->Next;
	}
	return NULL;
}
//trazi prethodni
Position SearchPrevious(char* Surname, Position P)
{
	if (P == NULL || P->Next == NULL)
		return NULL;

	while (P->Next != NULL) {
		if (strcmp(P->Next->Surname, Surname) == 0)
			return P;
		P = P->Next;
	}
	return NULL;
}
//brisanje elementa liste
int Delete(char* Surname, Position P)
{
	Position temp;

	printf("Enter the surname you want to delete: ");
	scanf("%s", Surname);

	P = SearchPrevious(Surname, P);

	if (P != NULL && P->Next != NULL) {
		temp = P->Next;
		P->Next = temp->Next;

		free(temp);
		printf("Person with surname '%s' deleted successfully.\n", Surname);
	}
	else {
		printf("Person with surname '%s' not found.\n", Surname);
	}

	return 0;
}
//dodavanje elementa iza 
int InputBehind(char* Surname, Position P)
{
	Position q;
	P = LookingFor(Surname, P);

	if (P != NULL)
	{
		q = (Position)malloc(sizeof(Person));
		printf("Enter Person: ");
		scanf("%s %s %d", q->Name, q->Surname, &q->Birth);

		q->Next = P->Next;
		P->Next = q;

		printf("Person added successfully behind '%s'.\n", Surname);
	}
	else
	{
		printf("Person with surname '%s' not found.\n", Surname);
	}

	return 0;
}
//dodavanje elementa ispred
int InputFront(char* Surname, Position P)
{
	Position q;
	P = SearchPrevious(Surname, P);

	if (P != NULL)
	{
		q = (Position)malloc(sizeof(Person));
		printf("Enter Person: ");
		scanf("%s %s %d", q->Name, q->Surname, &q->Birth);

		q->Next = P->Next;
		P->Next = q;

		printf("Person successfully added in front of '%s'.\n", Surname);
	}
	else
	{
		printf("Person with surname '%s' not found.\n", Surname);
	}

	return 0;
}
//sortiraj po prezimenima
int Sort(Position P)
{
	Position i, j;
	Person temp;

	if (P->Next == NULL || P->Next->Next == NULL)
		return 0;

	for (i = P->Next; i != NULL; i = i->Next) 
	{
		for (j = i->Next; j != NULL; j = j->Next) 
		{
			if (strcmp(i->Surname, j->Surname) > 0) 
			{
				strcpy(temp.Name, i->Name);
				strcpy(temp.Surname, i->Surname);
				temp.Birth = i->Birth;

				strcpy(i->Name, j->Name);
				strcpy(i->Surname, j->Surname);
				i->Birth = j->Birth;

				strcpy(j->Name, temp.Name);
				strcpy(j->Surname, temp.Surname);
				j->Birth = temp.Birth;
			}
		}
	}
	return 0;
}
//upisuje listu u datoteku
int WriteInFile(Position P)
{
	FILE* fp = fopen("Lista.txt", "w");
	if (fp == NULL)
	{
		printf("Error opening file.\n");
		return -1;
	}

	while (P != NULL)
	{
		fprintf(fp, "%s %s %d\n", P->Name, P->Surname, P->Birth);
		P = P->Next;
	}
	fclose(fp);

	printf("\nThe data is written to the file.\n");

	return 0;
}
//cita listu iz datoteke
int ReadFile(Position P)
{
	Position q;
	FILE* fp = fopen("Lista.txt", "r");

	if (fp == NULL)
	{
		printf("Error opening file.\n");
		return -1;
	}

	Position Last = P; //pokazivac na kraj postojece liste
	while (Last->Next != NULL)
		Last = Last->Next;

	while (1)
	{
		q = (Position)malloc(sizeof(Person));
		if (q == NULL)
		{
			printf("Memory allocation error.\n");
			fclose(fp);
			return -1;
		}

		if (fscanf(fp, "%s %s %d", q->Name, q->Surname, &q->Birth) != 3)
		{
			free(q);
			break;
		}

		q->Next = NULL; //bit ce zadnji u listi
		Last->Next = q; //povezuje stari cvor s novim cvorom
		Last = q;
	}

	fclose(fp);
	printf("\nData loaded from file.\n");

	return 0;
}
//izbrisi sve
int DeleteAll(Position P)
{
	Position temp;

	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;

		free(temp);
	}

	return 0;
}