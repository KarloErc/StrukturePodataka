/*6. Napisati program koji èita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
 predstavljaju pojedini raèun. Na poèetku svake datoteke je zapisan datum u kojem vremenu je
 raèun izdat u formatu YYYY-MM-DD. Svaki sljedeæi red u datoteci predstavlja artikl u formatu
 naziv, kolièina, cijena. Potrebno je formirati vezanu listu raèuna sortiranu po datumu. Svaki èvor
 vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla. Nakon toga potrebno je
 omoguæiti upit kojim æe korisnik saznati koliko je novaca sveukupno potrošeno na specifièni
 artikl u odreðenom vremenskom razdoblju i u kojoj je kolièini isti kupljen.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

typedef struct Article* Position;
typedef struct Article {
	char Name[N];
	int Quantity;
	float Price;
	Position Next;
}Article;

typedef struct Invoice* Positions;
typedef struct Invoice {
	char Date[N];
	Article* Items;
	Positions Next;
}Invoice;

Invoice* InsertInvoice(Invoice*, Invoice*);
Article* InsertArticle(Article*, Article*);
Invoice* LoadInvoice(char*);
Invoice* LoadAllInvoice();
int Query(Invoice*, float*);

int main()
{
	Invoice* AllInvoice = LoadAllInvoice();

	if (!AllInvoice)
	{
		printf("No invoice.\n");
		return 0;
	}

	float AllMoney;
	int AllQuantity = Query(AllInvoice, &AllMoney);

	printf("Total quantity: %d\n", AllQuantity);
	printf("Total spent: %.2f EUR\n", AllMoney);

	return 0;
}

//sortirano ubacivanje racuna po datumu
Invoice* InsertInvoice(Invoice* Head, Invoice* New)
{
	if (!Head || strcmp(New->Date, Head->Date) < 0)
	{
		New->Next = Head;
		return New;
	}

	Invoice* temp = Head;
	while (temp->Next && strcmp(New->Date, temp->Next->Date) > 0)
		temp = temp->Next;

	New->Next = temp->Next;
	temp->Next = New;

	return Head;
}

//soritrano ubacivanje artikala po nazivu
Article* InsertArticle(Article* Head, Article* New)
{
	if (!Head || strcmp(New->Name, Head->Name) < 0)
	{
		New->Next = Head;
		return New;
	}

	Article* temp = Head;
	while (temp->Next && strcmp(New->Name, temp->Next->Name) > 0)
		temp = temp->Next;

	New->Next = temp->Next;
	temp->Next = New;

	return Head;
}

//ucitavanje jednog racuna 
Invoice* LoadInvoice(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		printf("I can't open it %s\n.", filename);
		return NULL;
	}

	Invoice* Inv = (Invoice*)malloc(sizeof(Invoice));
	Inv->Next = NULL;
	Inv->Items = NULL;

	fgets(Inv->Date, N, fp);
	Inv->Date[strcspn(Inv->Date, "\n")] = 0;

	while (!feof(fp))
	{
		Article* A = (Article*)malloc(sizeof(Article));
		A->Next = NULL;

		if (fscanf(fp, "%[^,], %d, %f\n", A->Name, &A->Quantity, &A->Price) != 3)
		{
			free(A);
			break;
		}

		Inv->Items = InsertArticle(Inv->Items, A);
	}

	fclose(fp);

	return Inv;
}

//ucitava sve racune
Invoice* LoadAllInvoice()
{
	FILE* fp = fopen("Racuni.txt", "r");
	if (!fp)
	{
		printf("I can't open it\n.");
		return NULL;
	}

	Invoice* Head = NULL;
	char Filename[N];

	while (fgets(Filename, N, fp))
	{
		Filename[strcspn(Filename, "\n")] = 0;

		Invoice* Inv = LoadInvoice(Filename);
		if (Inv)
			Head = InsertInvoice(Head, Inv);
	}

	fclose(fp);
	return Head;
}

//upit vraca ukupnu kolicinu
int Query(Invoice* Head, float* TotalMoneyOut)
{
	char ItemName[N];
	char StartDate[N], EndDate[N];

	printf("\nEnter the name of the item: ");
	scanf(" %s", ItemName);

	printf("Enter start date (YYYY-MM-DD): ");
	scanf(" %s", StartDate);

	printf("Enter end date (YYYY-MM-DD): ");
	scanf(" %s", EndDate);

	int TotalQuantity = 0;
	float TotalMoney = 0;

	Invoice* Inv = Head;
	while (Inv)
	{
		if (strcmp(Inv->Date, StartDate) >= 0 && strcmp(Inv->Date, EndDate) <= 0)
		{
			Article* A = Inv->Items;
			while (A)
			{
				if (strcmp(A->Name, ItemName) == 0)
				{
					TotalQuantity += A->Quantity;
					TotalMoney += A->Quantity * A->Price;
				}
				A = A->Next;
			}
		}
		Inv = Inv->Next;
	}
	*TotalMoneyOut = TotalMoney;

	return TotalQuantity;
}