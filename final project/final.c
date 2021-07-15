/*-----------------------------FINAL PROJECT-----------------------------
----------------------NOA BEN GIGI, ID:318355633-------------------------
----------------------LION DAHAN, ID:318873338---------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef struct
{
	char name[30];//שם מוצר
	int NumOfWin;//מספר ניצחונות
	int sign;
} player;//מבנה-שחקן
typedef enum { FALSE , TRUE }boolean;
void BuildMatrix(int*** matrix, int* row, int* col);
void BuildPlayer(player* ply);
void PrintRows(int** matrix, int row, int col);
void PrintCols(int** matrix, int row, int col);
void freeMatrix(char*** matrix, int row);
int main()
{
	int** board = NULL;
	int row, col;
	BuildMatrix(&board, &row, &col);
	PrintRows(board, row, col);
	freeMatrix(&board, row);
	return 0;
}
void BuildMatrix(int*** matrix, int* row, int* col)
{//פונקציה המקבלת מצביע למערך מחרוזות
	printf("Please enter board's size-lines and column");//הדפסה למשתמש להכנסת גודל המטריצה
	scanf("%d%d", row, col);//קליטת הגדלים
	while ((*row < 4 && *col < 2 )|| (*col < 4 && *row < 2))
	{//כל עוד הגודל אינו תקין
		printf("Size is incorrect!\nPlease enter new size for your game board");//הדפסה שהגודל אינו תקין
		scanf("%d%d", row, col);//קליטת מחדש
	}
	*matrix = (int**)malloc((*row) * sizeof(int*));//הקצאה דינאמית של השורות
	if (!(*matrix))
	{//בדיקה שההקצאה הצליחה
		printf("ERROR! cannot allocate memory\n");
		return;
	}
	for (int i = 0; i < (*row); i++)
	{//הקצאה דינאמית לכל שורה
		*(*matrix + i) = (int*)malloc((*col) * sizeof(int));
		if (*(*matrix + i) == NULL)
		{
			printf("ERROR! cannot allocate memory\n");
			return;
		}
	}
	for (int i = 0; i < (*row) ; ++i)
	{
		for (int j = 0; j < (*col) ; ++j)
		{
			*matrix[i][j]= 0;
		}
	}
}// BuildMatrix
void BuildPlayer(player* ply)
{//פונקציה המקבלת מצביע למבנה וקולטת את נתוני השחקן
	printf("Please enter your name: \n");//הדפסה לשחקן להכנסת שמות
	gets(ply->name);//קליטת שם השחקן
	ply->NumOfWin = 0; //אתחול מספר הניצחונות ל0
	return;
}//BuildPlayer
void PrintRows(int** matrix, int row, int col)
{
	if (row == 0)
		return;
	return PrintMatrix(matrix, row - 1, col-1);
	PrintCols((*matrix), row, col);
}
void PrintCols(int** matrix, int row, int col)
{
	if (col == 0)
		return;
	return PrintCols((*matrix) + 1, row - 1, col - 1);
	print("%d", matrix[row][col]);
}
void freeMatrix(char*** matrix, int row)
{//הפונקציה מקבלת מצביע למערך מחרוזות ומשחררת את הזיכרון הדינאמי שהוקצה
	for (int i = 0; i < row; i++)//שחרור כל שורה במטריצה בנפרד
	{
		free(*(*matrix + i));//שחרור לפי שורה
	}
	free(*matrix);//שחרור המצביע למטריצה 
	matrix = NULL;
}//freeMatrix