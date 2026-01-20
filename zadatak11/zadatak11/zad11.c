/*11. Prepraviti zadatak 10 na naèin da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova države zatim
raèuna ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Države s istim kljuèem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki èvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 128
#define SIZE 11

typedef struct City* PositionCity;
typedef struct City {
    char Name[MAX];
    int NumberPop;
    PositionCity Left;
    PositionCity Right;
} City;

typedef struct Country* PositionCountry;
typedef struct Country {
    char Name[MAX];
    char NameFile[MAX];
    PositionCity Cities;      
    PositionCountry Next;     
} Country;

PositionCity CreateCity(char*, int);
PositionCountry CreateCountry(char*, char*);
int CompareCities(PositionCity, PositionCity);
PositionCity InsertCityTree(PositionCity, PositionCity);
PositionCountry InsertCountryHash(PositionCountry, PositionCountry);
int ReadCitiesFile(PositionCountry);
int PrintCitiesTree(PositionCity);

int Hash(char*);
int PrintHashTable(PositionCountry[]);

int main()
{
	FILE* fp = fopen("drzave.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}

	PositionCountry HashTable[SIZE] = { NULL };
	char name[MAX], file[MAX];

	while (fscanf(fp, " %s %s", name, file) == 2)
	{
		PositionCountry country = CreateCountry(name, file);
		if (country == NULL)
			return -1;

		ReadCitiesFile(country);
		int key = Hash(name);
		HashTable[key] = InsertCountryHash(HashTable[key], country);
	}
	fclose(fp);

	printf("HASH TABLE_______\n");
	PrintHashTable(HashTable);

	return 0;
}

PositionCity CreateCity(char* Name, int Population)
{
	PositionCity city;
	city = (PositionCity)malloc(sizeof(City));
	if (city == NULL)
	{
		printf("Problem alokacije memorije!!\n");
		return NULL;
	}

	strcpy(city->Name, Name);
	city->NumberPop = Population;
	city->Left = city->Right = NULL;

	return city;
}

PositionCountry CreateCountry(char* Name, char* NameFile)
{
	PositionCountry country;
	country = (PositionCountry)malloc(sizeof(Country));
	if (country == NULL)
	{
		printf("Problem alokacije memorije!!\n");
		return NULL;
	}

	strcpy(country->Name, Name);
	strcpy(country->NameFile, NameFile);
	country->Cities = NULL;
	country->Next = NULL;

	return country;
}

int CompareCities(PositionCity A, PositionCity B)
{
	if (A->NumberPop != B->NumberPop)
		return B->NumberPop - A->NumberPop;

	return strcmp(A->Name, B->Name);
}

PositionCity InsertCityTree(PositionCity Root, PositionCity NewCity)
{
	if (Root == NULL)
		return NewCity;

	if (CompareCities(NewCity, Root) < 0)
		Root->Left = InsertCityTree(Root->Left, NewCity);
	else
		Root->Right = InsertCityTree(Root->Right, NewCity);

	return Root;
}

PositionCountry InsertCountryHash(PositionCountry Head, PositionCountry NewCountry)
{
	if(Head == NULL || strcmp(NewCountry->Name, Head->Name) < 0)
	{
		NewCountry->Next = Head;
		return NewCountry;
	}
	PositionCountry temp = Head;
	while (temp->Next != NULL && strcmp(NewCountry->Name, temp->Next->Name) > 0)
		temp = temp->Next;

	NewCountry->Next = temp->Next;
	temp->Next = NewCountry;

	return Head;
}

int ReadCitiesFile(PositionCountry country)
{
	FILE* fp = fopen(country->NameFile, "r");
	if (fp == NULL)
	{
		printf("Error opening file!!\n");
		return -1;
	}

	char Name[MAX];
	int Population;

	while (fscanf(fp, " %[^,],%d", Name, &Population) == 2)
	{
		PositionCity city = CreateCity(Name, Population);
		if (city == NULL)
			return -1;
		country->Cities = InsertCityTree(country->Cities, city);
	}
	fclose(fp);

	return 0;
}

int PrintCitiesTree(PositionCity Root)
{
	if (Root == NULL)
		return 0;

	PrintCitiesTree(Root->Left);
	printf("   %s (%d)\n", Root->Name, Root->NumberPop);
	PrintCitiesTree(Root->Right);

	return 0;
}

int Hash(char* Name)
{
	int i, sum = 0;
	for (i = 0; i < 5 && Name[i] != '\0'; i++)
	{
		sum += (int)Name[i];
	}
	return sum % SIZE;
}

int PrintHashTable(PositionCountry Table[])
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		printf("\n[%d]\n", i);
		PositionCountry temp = Table[i];
		while (temp != NULL)
		{
			printf("%s\n", temp->Name);
			PrintCitiesTree(temp->Cities);
			temp = temp->Next;
		}
	}
	return 0;
}
