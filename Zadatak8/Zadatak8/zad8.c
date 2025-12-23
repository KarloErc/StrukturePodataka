/*8. Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node* Position;
typedef struct Node {
	int Number;
	Position Left;
	Position Right;
}Node;

Position CreateNode(int);
Position Insert(Position, int);
Position Search(int, Position);
Position DeleteElement(int, Position);
int Preorder(Position);
int Inorder(Position);
int Postorder(Position);
int Levelorder(Position);
int PrintTree(Position, int);

int main()
{
	int choose = 0;
	int Number = 0;
	Position Root = NULL;
	Position Result = NULL;

	while (1)
	{
		printf("1-Insert element\n");
		printf("2-Search element\n");
		printf("3-Delete element\n");
		printf("4-Print preorder\n");
		printf("5-Print inorder\n");
		printf("6-Print postorder\n");
		printf("7-Print level order\n");
		printf("8-Print tree\n");
		printf("0-Exit\n");
		printf("Choice: ");
		scanf("%d", &choose);

		switch (choose)
		{
		case 1:
			printf("Enter number: ");
			scanf("%d", &Number);
			Root = Insert(Root, Number);
			break;

		case 2:
			printf("Enter number to search: ");
			scanf("%d", &Number);
			Result = Search(Number, Root);
			if (Result != NULL)
				printf("Element exists in tree.\n");
			else
				printf("Element does not exist.\n");
			break;

		case 3:
			printf("Enter number to delete: ");
			scanf("%d", &Number);
			Root = DeleteElement(Number, Root);
			break;

		case 4:
			printf("Preorder: ");
			Preorder(Root);
			break;

		case 5:
			printf("Inorder: ");
			Inorder(Root);
			break;

		case 6:
			printf("Postorder: ");
			Postorder(Root);
			break;

		case 7:
			printf("Level order: ");
			Levelorder(Root);
			break;

		case 8:
			PrintTree(Root, 0);
			break;

		case 0:
			printf("Exit!!\n");
			return 0;

		default:
			printf("Invalid choice!\n");
		}
	}

	return 0;
}

//stvara novi cvor stabla
Position CreateNode(int Value)
{
	Position Node = NULL;
	Node = (Position)malloc(sizeof(*Node));

	if (Node == NULL)
	{
		printf("Cannot allocate memory for new node!!");
		return NULL;
	}

	Node->Number = Value;
	Node->Left = NULL;
	Node->Right = NULL;

	return Node;
}

//ubacuje novi element u stablo
Position Insert(Position Root, int Value)
{
	if (Root == NULL)
		return CreateNode(Value);

	if (Root->Number > Value)
		Root->Left = Insert(Root->Left, Value);
	else if (Root->Number <= Value)
		Root->Right = Insert(Root->Right, Value);

	return Root;
}

//provjerava postoji li pojedini elemet u stablu
Position Search(int Value, Position Root)
{
	if (Root == NULL)
		return NULL;

	if (Root->Number == Value)
		return Root;

	if (Root->Number > Value)
		return Search(Value, Root->Left);

	else 
		return Search(Value, Root->Right);
}

//brise odredeni element iz stabla
Position DeleteElement(int Value, Position Root)
{
	if (Root == NULL)
	{
		printf("The tree is empty!!");
		return NULL;
	}

	if (Value > Root->Number)
		Root->Right = DeleteElement(Value, Root->Right);

	else if(Value < Root->Number)
		Root->Left = DeleteElement(Value, Root->Left);

	//pronasli smo taj element, provjerit broj djece
	//imaju samo jedno ili nijedno dijete
	else
	{
		if (Root->Left == NULL && Root->Right == NULL)
		{
			free(Root);
			return NULL;
		}

		if (Root->Left == NULL && Root->Right != NULL)
		{
			Position temp = Root->Right;
			free(Root);
			return temp;
		}

		if (Root->Right == NULL && Root->Left != NULL)
		{
			Position temp = Root->Left;
			free(Root);
			return temp;
		}
		//ako ima oba djeteta
		Position temp = Root->Right;
		while (temp->Left != NULL)
		{
			temp = temp->Left;
		}
		Root->Number = temp->Number;
		Root->Right = DeleteElement(temp->Number, Root->Right);
	}
	return Root;
}

int Preorder(Position Root)
{
	if (Root != NULL)
	{
		//root, lijeva strana, desna strana
		printf("%d ", Root->Number);
		Preorder(Root->Left);
		Preorder(Root->Right);
	}
	return 0;
}

int Inorder(Position Root)
{
	if (Root != NULL)
	{
		//lijeva strana, root, desna strana
		Inorder(Root->Left);
		printf("%d ", Root->Number);
		Inorder(Root->Right);
	}
	return 0;
}

int Postorder(Position Root)
{
	if (Root != NULL)
	{
		//lijeva strana, desna strana, root
		Postorder(Root->Left);
		Postorder(Root->Right);
		printf("%d ", Root->Number);
	}
	return 0;
}

//ispisuje stabla po razinama
int Levelorder(Position Root)
{
	if (Root == NULL)
		return 0;

	Position Queue[100];
	int Front = 0, Rear = 0;

	Queue[Rear++] = Root;

	while (Front < Rear)
	{
		Position Current = Queue[Front++];
		printf("%d ", Current->Number);

		if (Current->Left != NULL)
			Queue[Rear++] = Current->Left;

		if (Current->Right != NULL)
			Queue[Rear++] = Current->Right;
	}
	return 0;
}

int PrintTree(Position Root, int Level)
{
	if (Root == NULL)
		return 0;

	PrintTree(Root->Right, Level + 1);

	for (int i = 0; i < Level; i++)
		printf("\t");

	printf("%d\n", Root->Number);

	PrintTree(Root->Left, Level + 1);

	return 0;
}