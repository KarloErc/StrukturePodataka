#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_Ime 50
#define MAX_Prez 50
#define MAX_Bodovi 100

typedef struct Student
{
	char Ime[MAX_Ime];
	char Prez[MAX_Prez];
	int Bodovi;
}Student;

int brojredakauDat()
{
	FILE* fp = fopen("studenti.txt", "r");

	if (fp == NULL)
	{
		printf("Greska pokusaj ponovno!!");
		return 1;
	}

	int br = 0;
	char Ime[MAX_Ime];
	char Prez[MAX_Prez];
	int Bodovi;

	while(fscanf(fp, "%s %s %d", Ime, Prez, &Bodovi) == 3)
	{
		br++;
	}
	fclose(fp);

	return br;
}

int main()
{
	int i;
	double relativno;
	int brojstudenata = brojredakauDat();

	if (brojstudenata <= 0)
	{
		printf("Greska");
		return 1;
	}

	
	Student* studenti = (Student*)malloc(brojstudenata * sizeof(Student));
	if (studenti == NULL)
	{
		printf("Greska!!");
		return 1;
	}

	FILE* fp = fopen("studenti.txt", "r");
	if (fp == NULL)
	{
		printf("Greska pokusaj ponovno!!");
		return 1;
	}

	for (i = 0; i < brojstudenata; i++)
	{
		fscanf(fp, "%s %s %d", studenti[i].Ime, studenti[i].Prez, studenti[i].Bodovi);
	}

	fclose(fp);

	printf("IME\t\tPREZIME\t\tAPSOLUTNI\t\tRELATIVNI(%%)\n");

	for (i = 0; i < brojstudenata; i++)
	{
		relativno = ((double)studenti[i].Bodovi / MAX_Bodovi) * 100;
		printf("%s\t\t%s\t\t%d\t\t%.2f\n", studenti[i].Ime, studenti[i].Prez, studenti[i].Bodovi, relativno);
	}

	return 0;
}

