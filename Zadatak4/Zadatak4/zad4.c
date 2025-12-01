/*4.  Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
 èitaju iz datoteke.
 Napomena: Eksponenti u datoteci nisu nužno sortirani.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Polinome* Position;
typedef struct Polinome {
	int Coef;
	int Exp;
	Position Next;
}Polinome;

Position CreatePolinome(int, int);
Position InsertSorted(Position, int, int);
Position ReadPolyFile(FILE* fp);
Position AddPoly(Position, Position);
Position MultiplyPoly(Position, Position);
int PrintPoly(Position);
int FreePoly(Position);

int main() 
{
	FILE* fp = fopen("polinomi.txt", "r");
	if (!fp)
	{
		printf("Error opening file.\n");
		return 1;
	}

	Position P1 = ReadPolyFile(fp);
	Position P2 = ReadPolyFile(fp);
	fclose(fp);

	printf("\nP1 = ");
	PrintPoly(P1);

	printf("\nP2 = ");
	PrintPoly(P2);

	Position Sum = AddPoly(P1, P2);
	Position Product = MultiplyPoly(P1, P2);

	printf("\nSum:\n");
	PrintPoly(Sum);

	printf("\nProduct:\n");
	PrintPoly(Product);

	FreePoly(P1);
	FreePoly(P2);
	FreePoly(Sum);
	FreePoly(Product);

	return 0;
}

//Kreiranje novog clana
Position CreatePolinome(int coef, int exp) 
{
	Position p;
	p = (Position)malloc(sizeof(Polinome));

	if (!p)
	{
		printf("Error!!");
		return NULL;
	}

	p->Coef = coef;
	p->Exp = exp;
	p->Next = NULL;

	return p;
}

//umetanje sortiranje po eksponentu
Position InsertSorted(Position Head, int coef, int exp)
{
	if (coef == 0)
		return Head;

	Position NewPoly = CreatePolinome(coef, exp);
	if (!NewPoly)
		return Head;

	if (Head == NULL || exp > Head->Exp) {
		NewPoly->Next = Head;
		return NewPoly;
	}

	Position temp = Head;
	while (temp->Next != NULL && temp->Next->Exp > exp)
		temp = temp->Next;

	if (temp->Next != NULL && temp->Next->Exp == exp)
	{
		temp->Next->Coef += coef;
		free(NewPoly);
		return Head;
	}

	NewPoly->Next = temp->Next;
	temp->Next = NewPoly;

	return Head;
}

//citanje jednog polinoma iz datoteke
Position ReadPolyFile(FILE* fp)
{
	int c, e;
	Position Head = NULL;

	while (fscanf(fp, "%d %d", &c, &e) == 2)
	{
		Head = InsertSorted(Head, c, e);

		//provjera kraja prvog polinoma
		int ch = fgetc(fp);
		if (ch == '\n' || ch == EOF)
			break;
		else
			ungetc(ch, fp);	//vracamo znak nazad

	}
	return Head;
}

//zbrajanje
Position AddPoly(Position A, Position B)
{
	Position C = NULL;

	while (A != NULL)
	{
		C = InsertSorted(C, A->Coef, A->Exp);
		A = A->Next;
	}

	while (B != NULL)
	{
		C = InsertSorted(C, B->Coef, B->Exp);
		B = B->Next;
	}
	return C;
}

//mnozenje
Position MultiplyPoly(Position A, Position B)
{
	Position C = NULL;
	Position p, q;
	for (p = A; p != NULL; p = p->Next) {
		for (q = B; q != NULL; q = q->Next) {
			C = InsertSorted(C, p->Coef * q->Coef, p->Exp + q->Exp);
		}
	}
	return C;
}

//ispis polinoma
int PrintPoly(Position P)
{
	if(P == NULL)
	{
		printf("Error!!");
		return 1;
	}

	while(P != NULL)
	{
		printf("%dx^%d", P->Coef, P->Exp);
		if (P->Next && P->Next->Coef >= 0)
			printf(" + ");
		else if (P->Next)
			printf(" ");
		P = P->Next;
	}
	return 1;
}

//oslobaðanje memorije
int FreePoly(Position P)
{
	Position temp;
	while (P != NULL) {
		temp = P;
		P = P->Next;
		free(temp);
	}
	return 1;
}