/*10. Napisati program koji èita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki èvor vezane liste
sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo država sortirano po nazivu. Svaki èvor stabla sadrži vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati države i gradove te omoguæiti korisniku putem
tastature pretragu gradova odreðene države koji imaju broj stanovnika veæi od unosa na
tastaturi.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 128

typedef struct City* PositionCity;
typedef struct City {
	char Name[128];
	int NumberPop;
	PositionCity Next;
	PositionCity Right;
	PositionCity Left;
}City;

typedef struct Country* PositionCountry;
typedef struct Country {
	char Name[MAX];
	char FileName[MAX];
	City* Cities;
	PositionCountry Next;
	PositionCountry Right;
	PositionCountry Left;
}Country;

PositionCity CreateCity(char*, int);
PositionCountry CreateCountry(char*, char*);
int CompareCities(PositionCity, PositionCity);
int CompareCountries(PositionCountry, PositionCountry);
PositionCity InsertCityTree(PositionCity, PositionCity);
int ReadCitiesTree(PositionCountry);
PositionCountry InsertCountry(PositionCountry, PositionCountry);
int PrintCitiesTree(PositionCity);
int PrintCountries(PositionCountry);
//b)
PositionCity InsertCity(PositionCity, PositionCity);
int PrintCities(PositionCity);
PositionCountry InsertCountryTree(PositionCountry, PositionCountry);
int PrintCountriesTree(PositionCountry);
int ReadCitiesList(PositionCountry);
//c
PositionCountry FindCountryList(PositionCountry, char*);
PositionCountry FindCountryTree(PositionCountry, char*);
int PrintCitiesTreeTop(PositionCity, int);
int PrintCitiesListTop(PositionCity, int);
int main()
{
	FILE* fp = fopen("drzave.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening file!!");
		return -1;
	}

	PositionCountry CountryList = NULL;
	char Name[MAX], File[MAX];

	while (fscanf(fp, " %s %s", Name, File) == 2)
	{
		PositionCountry C = CreateCountry(Name, File);
		if (C == NULL)
		{
			printf("Error!!");
			return -1;
		}

		ReadCitiesTree(C);
		CountryList = InsertCountry(CountryList, C);
	}
	fclose(fp);

	printf("A)----------------\n");
	PrintCountries(CountryList);
	
	fp = fopen("drzave.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening file!!");
		return -1;
	}
	PositionCountry CountryTree = NULL;
	while (fscanf(fp, " %s %s", Name, File) == 2)
	{
		PositionCountry C = CreateCountry(Name, File);
		if (C == NULL)
		{
			printf("Error!!");
			return -1;
		}
		ReadCitiesList(C);
		CountryTree = InsertCountryTree(CountryTree, C);
	}
	fclose(fp);

	printf("B)----------\n");
	PrintCountriesTree(CountryTree);
	
	//C)
	char CountryName[MAX];
	int min;

	printf("\nEnter name country: ");
	scanf(" %s", CountryName);

	printf("Enter the minimum number of inhabitants: ");
	scanf("%d", &min);

	printf("\nSearch(FindCountryList):\n"); //lista drzava i stablo gradova
	PositionCountry C1 = FindCountryList(CountryList, CountryName);

	if (C1)
		PrintCitiesTreeTop(C1->Cities, min);
	else
		printf("Country not a found.\n");

	printf("\nSearch(FindCountryTree):\n");
	PositionCountry C2 = FindCountryTree(CountryTree, CountryName);

	if (C2)
		PrintCitiesListTop(C2->Cities, min);
	else
		printf("Country not a found.\n");

	return 0;
}

//kreiranje grada
PositionCity CreateCity(char* Name, int Population)
{
	PositionCity city;
	city = (PositionCity)malloc(sizeof(City));

	if (city == NULL)
	{
		printf("Memory allocation error!!");
		return NULL;
	}

	strcpy(city->Name, Name);
	city->NumberPop = Population;
	city->Next = city->Left = city->Right = NULL;

	return city;
}

//kreiranje drzave
PositionCountry CreateCountry(char* Name, char* File)
{
	PositionCountry country;
	country = (PositionCountry)malloc(sizeof(Country));

	if (country == NULL)
	{
		printf("Memory allocation error!!");
		return NULL;
	}

	strcpy(country->Name, Name);
	strcpy(country->FileName, File);
	country->Cities = NULL;
	country->Next = country->Left = country->Right = NULL;

	return country;
}

//usporedba gradova
int CompareCities(PositionCity A, PositionCity B)
{
	if (A->NumberPop != B->NumberPop)
		return B->NumberPop - A->NumberPop;

	return strcmp(A->Name, B->Name);
}

//usporedba drzava
int CompareCountries(PositionCountry A, PositionCountry B)
{
	return strcmp(A->Name, B->Name);
}

PositionCity InsertCityTree(PositionCity Root, PositionCity NewCity)
{
	if (Root == NULL)
	{
		return NewCity;
	}

	if (CompareCities(NewCity, Root) > 0)
		Root->Right = InsertCityTree(Root->Right, NewCity);
	else if (CompareCities(NewCity, Root) < 0)
		Root->Left = InsertCityTree(Root->Left, NewCity);
	else
		Root->Right = InsertCityTree(Root->Right, NewCity);	//ako su jednaki

	return Root;
}

//ucitavanje gradova iz datoteke
int ReadCitiesTree(PositionCountry Country)
{
	FILE* fp = fopen(Country->FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file!!");
		return -1;
	}

	char CityName[MAX];
	int Population;

	while (fscanf(fp, " %[^,],%d", CityName, &Population) == 2)
	{
		PositionCity city = CreateCity(CityName, Population);
		if (city == NULL)
		{
			return -1;
		}
		Country->Cities = InsertCityTree(Country->Cities, city);
	}

	fclose(fp);
	return 1;
}

//umetanje drzava u sortiranu listu
PositionCountry InsertCountry(PositionCountry Head, PositionCountry NewCountry)
{
	if (Head == NULL || CompareCountries(NewCountry, Head) < 0)
	{
		NewCountry->Next = Head;
		return NewCountry;
	}

	PositionCountry temp = Head;
	while (temp->Next != NULL && CompareCountries(NewCountry, temp->Next) > 0)
		temp = temp->Next;

	NewCountry->Next = temp->Next;
	temp->Next = NewCountry;

	return Head;
}

//ispis gradova
int PrintCitiesTree(PositionCity Root)
{
	if (Root == NULL)
	{
		return 0;
	}

	PrintCitiesTree(Root->Left);
	printf("   %s (%d)\n", Root->Name, Root->NumberPop);
	PrintCitiesTree(Root->Right);

	return 1;
}

//ispis drzava s gradovima
int PrintCountries(PositionCountry Head)
{
	while (Head)
	{
		printf("%s\n", Head->Name);
		PrintCitiesTree(Head->Cities);
		Head = Head->Next;
	}
	return 1;
}

//b)

PositionCity InsertCity(PositionCity Head, PositionCity NewCity)
{
	if (Head == NULL || CompareCities(NewCity, Head) < 0)
	{
		NewCity->Next = Head;
		return NewCity;
	}

	PositionCity temp = Head;
	while (temp->Next != NULL && CompareCities(NewCity, temp->Next) >= 0)
	{
		temp = temp->Next;
	}

	NewCity->Next = temp->Next;
	temp->Next = NewCity;

	return Head;
}

int PrintCities(PositionCity Head)
{
	int Count = 0;
	while (Head)
	{
		printf("   %s (%d)\n", Head->Name, Head->NumberPop);
		Head = Head->Next;
		Count++;
	}
	return Count;
}

PositionCountry InsertCountryTree(PositionCountry Root, PositionCountry NewCountry)
{
	if (Root == NULL)
		return NewCountry;

	if (CompareCountries(NewCountry, Root) < 0)
		Root->Left = InsertCountryTree(Root->Left, NewCountry);
	else
		Root->Right = InsertCountryTree(Root->Right, NewCountry);

	return Root;
}

int PrintCountriesTree(PositionCountry Root)
{
	if (Root == NULL)
		return 0;

	int Count = 0;

	Count += PrintCountriesTree(Root->Left);
	printf("%s\n", Root->Name);
	Count += PrintCities(Root->Cities);
	Count += PrintCountriesTree(Root->Right);

	return Count;
}

int ReadCitiesList(PositionCountry Country)
{
	FILE* fp = fopen(Country->FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}

	char CityName[MAX];
	int Population;

	while (fscanf(fp, " %[^,],%d", CityName, &Population) == 2)
	{
		PositionCity city = CreateCity(CityName, Population);
		if (city == NULL)
			return -1;

		Country->Cities = InsertCity(Country->Cities, city); 
	}

	fclose(fp);
	return 1;
}

//c)
//pretraga listu drzava
PositionCountry FindCountryList(PositionCountry Head, char* Name)
{
	while (Head != NULL)
	{
		if (strcmp(Head->Name, Name) == 0)
			return Head;
		Head = Head->Next;
	}
	return NULL;
}

//pretraga stabla drzava
PositionCountry FindCountryTree(PositionCountry Root, char* Name)
{
	if (Root == NULL)
		return NULL;

	if (strcmp(Name, Root->Name) == 0)
		return Root;
	else if (strcmp(Name, Root->Name) < 0)
		return FindCountryTree(Root->Left, Name);
	else
		return FindCountryTree(Root->Right, Name);
}

//lista drzava i stablo gradova
int PrintCitiesTreeTop(PositionCity Root, int Min)
{
	if (Root == NULL)
		return 0;

	int count = 0;

	if (Root->NumberPop > Min)
	{
		printf("   %s (%d)\n", Root->Name, Root->NumberPop);
		count++;

		count += PrintCitiesTreeTop(Root->Left, Min);
		count += PrintCitiesTreeTop(Root->Right, Min);
	}
	else
		count += PrintCitiesTreeTop(Root->Left, Min);

	return count;
}

//stablo država i lista gradova
int PrintCitiesListTop(PositionCity Head, int Min)
{
	int count = 0;

	while (Head != NULL)
	{
		if (Head->NumberPop > Min)
		{
			printf("   %s (%d)\n", Head->Name, Head->NumberPop);
			count++;
		}
		Head = Head->Next;
	}
	return count;
}