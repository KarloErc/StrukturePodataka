/*5. Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
 rezultat. Stog je potrebno realizirati preko vezane liste.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>

typedef struct Knot* Position;
typedef struct Knot {
	int El;
	Position Next;
}Knot;

int Push(int, Position);
int Pop(Position);
int Print(Position);
int DecisionPostfix();

int main()
{
	int Result;

	Result = DecisionPostfix();

	printf("\nThe final result of the expression is: %d", Result);

	return 0;
}

int Push(int Number, Position P)
{
	Position q;
	q = (Position)malloc(sizeof(Knot));

	q->El = Number;

	q->Next = P->Next;
	P->Next = q;

	return 0;
}

int Pop(Position P)
{
	Position temp;
	int Number;

	if (P->Next == NULL)
	{
		printf("Stog iz empty.\n");
		return 0;
	}

	temp = P->Next;
	Number = temp->El;
	P->Next = temp->Next;
	free(temp);

	return Number;
}

int Print(Position P)
{
	if (P->Next == NULL)
	{
		printf("Stog is empty.\n");
		return 0;
	}

	printf("\nStog(from top to bottom) : ");
	P = P->Next;
	while (P != NULL) {
		printf("%d ", P->El);
		P = P->Next;
	}

	return 0;
}

int DecisionPostfix()
{
	FILE* fp = fopen("postfix.txt", "r");
	if (!fp) {
		printf("I cant't open to file!");
		return 0;
	}

	Knot Head = { 0, NULL };

	char Symbol;
	int Number, op1, op2, Result = 0;

	printf("Reading and calculating expressions from a file: ");
	while (fscanf(fp, " %c", &Symbol) == 1) {
		if (isdigit(Symbol)) {
			ungetc(Symbol, fp);	//vratiti znak nazad jer može bit više znamenki
			fscanf(fp, "%d", &Number);
			Push(Number, &Head);
			printf("\nPush: %d", Number);
		}
		else {
			op2 = Pop(&Head);
			op1 = Pop(&Head);

			switch (Symbol) {
			case '+': 
				Result = op1 + op2; 
				break;
			case '-':
				Result = op1 - op2;
				break;
			case '*':
				Result = op1 * op2;
				break;
			case '/':
				if (op2 == 0) {
					printf("Error: division by zero!\n");
					fclose(fp);
					return 0;
				}
				Result = op1 / op2;
				break;
			default:
				printf("Unknown operator: %c\n", Symbol);
				fclose(fp);
				return 0;
			}
			printf("\nOperation: %d %c %d = %d", op1, Symbol, op2, Result);
			Push(Result, &Head);
		}
		Print(&Head);
	}
	fclose(fp);

	return Pop(&Head);
}