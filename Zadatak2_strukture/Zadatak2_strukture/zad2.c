/* 2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
 A. dinamièki dodaje novi element na poèetak liste,
 B. ispisuje listu,
 C. dinamièki dodaje novi element na kraj liste,
 D. pronalazi element u listi (po prezimenu),
 E. briše odreðeni element iz liste,
 U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_Name 50
#define MAX_Surname 50
typedef struct Person {
	char Name[MAX_Name];
	char Surname[MAX_Surname];
	int Birth;
	struct Person* Next;
}Person;
//Deklariranje funkcija
Person* CreatePerson();
void EnterPerson(Person* P);
void PrintList(Person* Head);
void Addbegining(Person** Head);
void Addend(Person** Head);
Person* Findsurname(Person* Head, const char* Surname);
void Deleteperson(Person** Head, const char* Surname);

int main() {

	Person* Head = NULL;
	int choice;
	char Surname[50];
	//Biranje sto zelimo s podacima
	do
	{
		printf("1- Add person to begining\n");
		printf("2- Print List\n");
		printf("3- Add person to the end\n");
		printf("4- Find person by the surname\n");
		printf("5- Delete person\n");
		printf("0-Exit\n");
		printf("Selection: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			Addbegining(&Head);
			break;
		case 2:
			PrintList(Head);
			break;
		case 3:
			Addend(&Head);
			break;
		case 4:
			printf("Enter the surname of the person you are looking for: ");
			scanf(" %49s", Surname);
			{
				Person* Wanted = Findsurname(Head, Surname);
				if (Wanted)
					printf("Found person: %s %s %d\n", Wanted->Name, Wanted->Surname, Wanted->Birth);
				else
					printf("Person with surname '%s' was not a found.\n", Surname);
			}
			break;
		case 5:
			printf("Enter the surname you want to delete: ");
			scanf(" %49s", Surname);
			Deleteperson(&Head, Surname);
			break;
		default:
			printf("Non-existent option.\n");
		}
	} while (choice != 0);

	Person* temp;
	while (Head != NULL) {
		temp = Head;
		Head = Head->Next;
		free(temp);
	}
	
	return 0;
}
//kreiranje osobe
Person* CreatePerson() 
{
	Person* New = (Person*)malloc(sizeof(Person));
	if (!New)
	{
		printf("Error: full memory!\n");
		return NULL;
	}
	EnterPerson(New);
	New->Next = NULL;
	
	return New;
}
//funkcija za Unosenje osoba 
void EnterPerson(Person* P) 
{
	printf("Enter name: ");
	scanf(" %49s", P->Name);
	printf("Enter surname: ");
	scanf(" %49s", P->Surname);
	printf("Enter Birth: ");
	scanf("%d",&P->Birth);
}
//ispis liste
void PrintList(Person* Head) 
{
	if (Head == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	printf("List content: \n");
	while (Head != NULL) 
	{
		printf("%s %s %d\n", Head->Name, Head->Surname, Head->Birth);
		Head = Head->Next;
	}
}
//Dodavanje osobe na pocetak liste
void Addbegining(Person** Head)
{
	Person* New = CreatePerson();
	if (New == NULL)
	{
		return;
	}
	New->Next = *Head;
	*Head = New;
}
//Dodavanje osobe na kraj liste
void Addend(Person** Head)
{
	Person* New = CreatePerson();
	if (New == NULL)
	{
		return;
	}
	if (*Head == NULL)
	{
		*Head = New;
		return;
	}

	Person* t = *Head;
	while (t->Next != NULL)
	{
		t = t->Next;
	}
	t->Next = New;
}
//funkcija za pronalazak osobe putem prezimena
Person* Findsurname(Person* Head, const char* Surname)
{
	while (Head != NULL) {
		if (strcmp(Head->Surname, Surname) == 0) {
			return Head;
		}
		Head = Head->Next;
	}
	return NULL;
}
//brisanje osoba s odredenim prezimenom
void Deleteperson(Person** Head, const char* Surname)
{
	Person* Now = *Head;
	Person* Ago = NULL;

	while (Now != NULL && strcmp(Now->Surname, Surname) != 0)
	{
		Ago = Now;
		Now = Now->Next;
	}

	if (Now == NULL)
	{
		printf("Person with surname '%s' is not a found.\n", Surname);
		return;
	}

	if (Ago == NULL)
	{
		*Head = Now->Next;
	}
	else {
		Ago->Next = Now->Next;
	}

	free(Now);
	printf("Person with surname '%s' has been delete.\n", Surname);
}