#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_Ime 50
#define MAX_Prez 50
#define MAX_Bodovi 100 //*maksimalan broj bodova na ispitu *//

typedef struct Student
{
	char Ime[MAX_Ime];
	char Prez[MAX_Prez];
	int bodovi;
}Student;

int brojredakauDat()	// *broji redke u datoteci *//
{
	FILE *fp = fopen("studenti.txt", "r");

	if (fp == NULL)
	{
		printf("GREŠKA POKUŠAJ PONOVNO!!!");
		return 1;
	}

	int br = 0;
	char Ime[MAX_Ime];
	char Prez[MAX_Prez];
	int bodovi;

	while (fscanf(fp, "%s %s %d", Ime, Prez, &bodovi) == 3)		//* pokušava èitati 3 vrijednosti po redu *//
	{
		br++;
	}

	fclose(fp);

	return br;
}

int main()
{
	int i;
	double relativni;
	int brojStudenata = brojredakauDat();	//*koliko ima studenata *//

	if (brojStudenata <= 0)
	{
		printf("Datoteka je prazna.\n");
		return 1;
	}

	Student* studenti = (Student*)malloc(brojStudenata * sizeof(Student));
	if (studenti == NULL)
	{
		printf("Greska!!!");
		return 1;
	}

	FILE* fp = fopen("studenti.txt", "r");
	if (fp == NULL)
	{
		printf("Greska!!!");
		return 1;
	}

	for (i = 0; i < brojStudenata; i++)
	{
		fscanf(fp, "%s %s %d", studenti[i].Ime, studenti[i].Prez, &studenti[i].bodovi);
	}
	fclose(fp);

	printf("IME\t\tPREZIME\t\tAPSOLUTNI\t\tRELATIVNI(%%)\n");

	for (i = 0; i < brojStudenata; i++)
	{
		relativni = ((double)studenti[i].bodovi / MAX_Bodovi) * 100;
		printf("%s\t\t%s\t\t%d\t\t%.2f\n", studenti[i].Ime, studenti[i].Prez, studenti[i].bodovi, relativni);
	}

	
	return 0;
}