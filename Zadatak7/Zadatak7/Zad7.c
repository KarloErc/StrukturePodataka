/*7. Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct Directory* Position;
typedef struct Directory {
	char Name[MAX];
	Position Child;		//prvo dijete
	Position Next;		//sljedeci direktorij
	Position Parent;	//roditeljski direktorij 
}Directory;

Position CreateDirectory(char*, Position);
int MakeDirectory(Position);
Position ChangeDirectory(Position);
Position GoBack(Position);
int PrintDirectory(Position);

int main()
{
	Directory HeadDirectory = { .Name = {0}, .Child = NULL, .Next = NULL};

	Position Root = CreateDirectory("C:", NULL);
	HeadDirectory.Next = Root;
	Position Current = Root;

	int choice = 0;

	do
	{
		printf("\nSelect an option: \n");
		printf("1 - Make Directory\n");
		printf("2 - Change Directory\n");
		printf("3 - Exit Directory\n");
		printf("4 - Print Directory\n");
		printf("5 - Exit\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			MakeDirectory(Current);
			break;
		case 2:
			Current = ChangeDirectory(Current);
			break;
		case 3:
			Current = GoBack(Current);
			break;
		case 4:
			PrintDirectory(Current);
			break;
		case 5:
			printf("Exit the program.\n");
			break;
		default:
			printf("Error choice!\n");
		}
	} while (choice != 5);


	return 0;
}

//kreiranje direktorija
Position CreateDirectory(char* Name, Position Parent)
{
	Position New = (Position)malloc(sizeof(Directory));

	if (!New)
	{
		printf("Error in memory!\n");
		return NULL;
	}

	strcpy(New->Name, Name);
	New->Child = NULL;
	New->Next = NULL;
	New->Parent = Parent;

	return New;
}

//stvaranje novog poddirektorija("1-md")
int MakeDirectory(Position Current)
{
	char Name[MAX];
	Position NewDirectory = NULL;
	Position temp = NULL;

	printf("Enter directory name: ");
	scanf("%s", Name);

	NewDirectory = CreateDirectory(Name, Current);

	if (!NewDirectory)
	{
		printf("Error!\n");
		return -1;
	}

	if (!Current->Child)
	{
		Current->Child = NewDirectory;
	}
	else
	{
		temp = Current->Child;
		while (temp->Next)
			temp = temp->Next;
		temp->Next = NewDirectory;
	}

	return 0;
}

//ulazak u poddirektorij(2-"cd dir")
Position ChangeDirectory(Position Current)
{
	char Name[MAX];
	Position temp = Current->Child;

	printf("Enter directory name: ");
	scanf("%s", Name);

	while (temp)
	{
		if (strcmp(temp->Name, Name) == 0)
			return temp;
		temp = temp->Next;
	}
	
	printf("The directory does not exist!\n");

	return Current;
}

//Povratak u roditeljski(prethodni) direktorij(3-"cd...")
Position GoBack(Position Current)
{
	if (Current->Parent)
		return Current->Parent;

	printf("You are already in the root directory!\n");

	return Current;
}

//ispis direktorija(4- "dir")
int PrintDirectory(Position Current)
{
	Position temp = Current->Child;

	if (!temp)
	{
		printf("Directory is empty!\n");
		return 0;
	}

	printf("Directory contents %s: \n", Current->Name);
	while (temp)
	{
		printf("DIRECTORY:\t%s\n", temp->Name);
		temp = temp->Next;
	}

	return 0;
}