/*-----------------------------FINAL PROJECT-----------------------------
----------------------NOA BEN GIGI, ID:318355633-------------------------
----------------------LION DAHAN, ID:318873338---------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define QUIT 7
typedef struct
{
	char name[30];//שם מוצר
	int sign;
} player;//מבנה-שחקן
typedef enum { FALSE, TRUE }boolean;
void BuildMatrix(int*** matrix, int* row, int* col);
void PrintMatrix(int** matrix, int row, int col);
void BuildPlayer(player* ply);
int cheakIndex(int*** matrix, int row, int col, int index1, int index2, player ply);
boolean DrawGame(int** matrix, int row, int col);
boolean WinGame(int** matrix, int row, int col, player ply, int i, int j);
boolean CheckStraight(int** matrix, int row, int col, player ply, int i, int j);
boolean CheckDiagonal(int** matrix, int row, int col, player ply, int i, int j);
void GAME(int*** matrix, int row, int col, player* ply1, player* ply2);
void DiagonalDown(int** matrix, int row, int col, player ply, int index1, int index2, int* sum);
void DiagonalUp(int** matrix, int row, int col, player ply, int index1, int index2, int* sum);
void DiagonalDown2(int** matrix, int row, int col, player ply, int index1, int index2, int* sum);
void DiagonalUp2(int** matrix, int row, int col, player ply, int index1, int index2, int* sum);
void freeMatrix(int*** matrix, int row);
int main()
{
	int** board = NULL;
	int row, col;
	BuildMatrix(&board, &row, &col);
	PrintMatrix(board, row, col);
	player ply1, ply2;
	BuildPlayer(&ply1);
	BuildPlayer(&ply2);
	GAME(&board, row, col, &ply1, &ply2);
	freeMatrix(&board, row);
	return 0;
}
void BuildMatrix(int*** matrix, int* row, int* col)
{//פונקציה המקבלת מצביע למערך מחרוזות
	printf("Please enter board's size-lines and column");//הדפסה למשתמש להכנסת גודל המטריצה
	scanf("%d%d", row, col);//קליטת הגדלים
	while ((*row) < 4 || (*col) < 4)
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
	for (int i = 0; i < (*row); ++i)
	{
		for (int j = 0; j < (*col); ++j)
		{
			(*matrix)[i][j] = -1;
		}
	}
}// BuildMatrix
void PrintMatrix(int** matrix, int row, int col)
{//הדפסת כל איבר במטריצה 
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%4d",matrix[i][j]);
		}
		printf("\n");
	}
}
void BuildPlayer(player* ply)
{//פונקציה המקבלת מצביע למבנה וקולטת את נתוני השחקן
	printf("Please enter your name: \n");//הדפסה לשחקן להכנסת שמות
	getchar();
	scanf("%s",ply->name);//קליטת שם השחקן
	return;
}//BuildPlayer
void FreeMatrix(int*** matrix, int row)
{/*פונקציה אשר תקבל מצביע למערך דו מימדי דינאמי וכמות שורות
 ותשחרר את כל הזיכרון שהמטריצה תפסה
 */
	for (int i = 0; i < row; i++)
	{
		free(*(*matrix + i));//שחרור המערכים החד מימדים
	}
	free(*matrix);//שחרור המצביע לשורות
}//FreeMatrix
int cheakIndex(int*** matrix, int row, int col, int index1, int index2, player ply)
{//size2 עמודות
//size1שורות 
	//פונקציה המקבלת את המיקום שהשחקן הכניס ובודקת האם המקום הזה פנוי, אם לא היא עושה השמה בשורה שמעל 
	if (index1 < row && index2 < col)
	{
		for (int i =row-1; i >= 0; i--)
		{
			if ((*matrix)[i][index2] == -1)//משמע המיקום ריק ועדיין לא בוצעה שם השמה 
			{
				return i;
			}
		}
	}
	return -1;
}
boolean DrawGame(int** matrix, int row, int col)
{//פונקציה מקבלת את השורה הראשונה מהמטריצה ובודקת אם יש תיקו או שעדיין יש מקומות ריקים
	for (int i = 0; i < col; i++)//מעבר על כל התאים בשורה הראשונה  
	{
		if (matrix[0][i] == -1)//זאת אומרת לא הוכנס תו לתא הנוכחי
		{
			return FALSE;//אין תיקו
		}
	}
	return TRUE;//אם יצאנו מהפור משמע כל השורה נבדקה ויש תיקו 
}//DrawGame
boolean WinGame(int** matrix, int row, int col, player ply, int i, int j)
{
	boolean win;
	win = CheckStraight(matrix, row, col, ply, i, j);
	if (win)
		return TRUE;
	win = CheckDiagonal(matrix, row, col, ply, i, j);
	if (win)
		return TRUE;
	return FALSE;
}
boolean CheckStraight(int** matrix, int row, int col, player ply, int i, int j)
{
	int sum=0;
	for (int x = 0; x < col ;x++)
	{
		while (matrix[i][x] == ply.sign && x < col)
		{
			sum++;
			++x;
			if (sum >= 4)
				return TRUE;
			if (x >= col)
				break;
		}
		if (sum >= 4)
			return TRUE;
		else
		{
			sum = 0;
		}
	}
	
	for (int x = row-1; x >= 0; x--)
	{
		while (matrix[x][j] == ply.sign && x>=0)
		{
			sum++;
			--x;
			if (sum >= 4)
				return TRUE;
			if (x == -1)
				break;

		}
		if (sum >= 4)
			return TRUE;
		else
		{
			sum = 0;
		}
	}
	return FALSE;
}
boolean CheckDiagonal(int** matrix, int row, int col, player ply, int index1, int index2)
{
	int sum = 1;
	DiagonalDown(matrix, row, col, ply, index1+1, index2-1, &sum);
	if (index1 == row - 1 && index2 > -1 && index2<col && matrix[index1][index2]==ply.sign)
		sum++;
	if (sum >= 4)
		return TRUE;
	DiagonalUp(matrix, row, col, ply, index1-1, index2+1, &sum);
	if (index1 == 0 && index2 < col && index2>-1 && matrix[index1][index2] == ply.sign)
		sum++;
	if (sum >= 4)
		return TRUE;
	sum = 1;
	DiagonalDown2(matrix, row, col, ply, index1+1, index2+1, &sum);
	if (index1 == row-1 && index2 >-1 && index2<col && matrix[index1][index2] == ply.sign)
		sum++;
	if (sum >= 4)
		return TRUE;
	DiagonalUp2(matrix, row, col, ply, index1-1, index2-1, &sum);
	if (index1 == 0 && index2 > 0 && index2<col  && matrix[index1][index2] == ply.sign)
		sum++;
	if (sum >= 4)
		return TRUE;
	return FALSE;
}
void DiagonalDown(int** matrix, int row, int col, player ply, int index1, int index2, int* sum)
{
	if (index1 == row || index2 == -1 || *sum == 4)
		return;
	if (matrix[index1][index2] == ply.sign)
	{
		++(*sum);
		DiagonalDown(matrix, row, col, ply, index1 + 1, index2 - 1, sum);
	}
	return;
}
void DiagonalUp(int** matrix, int row, int col, player ply, int index1, int index2, int* sum)
{
	if (index1 == -1 || index2 == col || *sum == 4)
		return;
	if (matrix[index1][index2] == ply.sign)
	{
		++(*sum);
		DiagonalUp(matrix, row, col, ply, index1 - 1, index2 + 1, sum);
	}
}
void DiagonalDown2(int** matrix, int row, int col, player ply, int index1, int index2, int* sum)
{
	if (index1 == row || index2 == col || *sum == 4)
		return;
	if (matrix[index1][index2] == ply.sign)
	{
		++(*sum);
		DiagonalDown(matrix, row, col, ply, index1 + 1, index2 + 1, sum);
	}
	return;
}
void DiagonalUp2(int** matrix, int row, int col, player ply, int index1, int index2, int* sum)
{
	if (index1 == -1 || index2 == -1 || *sum == 4)
		return;
	if (matrix[index1][index2] == ply.sign)
	{
		++(*sum);
		DiagonalUp(matrix, row, col, ply, index1 - 1, index2 - 1, sum);
	}

}
void GAME(int*** matrix, int row, int col, player* ply1, player* ply2)
{
	ply1->sign= 0;
	ply2->sign = 1;
	int choise;
	int rematch = 0;
	int indexRow;
	int index1 = 0, index2 = 0;
	boolean gameOver = FALSE;
	printf("For PLAYING enter 1 For QUIT enter 7\n");
	scanf("%d", &choise);
	while (choise != QUIT)
	{
		if (rematch > 0)
		{
			freeMatrix(matrix, row);
			BuildMatrix(matrix, &row, &col);
			system("cls");
			PrintMatrix(*matrix, row, col);
		}
		++rematch;
		do
		{
			printf("%s please enter your choice-row and coloumn\n", ply1->name);
			scanf("%d %d", &index1, &index2);
			indexRow = cheakIndex(matrix, row, col, index1, index2, *ply1);
			while (indexRow == -1)
			{
				printf("%s inncorrect chice\n", ply1->name);
				printf("please enter a new choice\n");
				scanf("%d %d", &index1, &index2);
				indexRow = cheakIndex(matrix, row, col, index1, index2, *ply1);
			}
			(*matrix)[indexRow][index2] = ply1->sign;
			system("cls");
			PrintMatrix(*matrix, row, col);
			if (WinGame(*matrix, row, col, *ply1, indexRow, index2) == TRUE || DrawGame(*matrix, row, col) == TRUE)
				break;
			printf("%s please enter your choice-row and coloumn\n", ply2->name);
			scanf("%d %d", &index1, &index2);
			indexRow = cheakIndex(matrix, row, col, indexRow, index2, *ply2);
			while (indexRow == -1)
			{
				printf("%s inncorrect chice\n", ply2->name);
				printf("please enter a new choice\n");
				scanf("%d %d", &index1, &index2);
				indexRow = cheakIndex(matrix, row, col, indexRow, index2, *ply2);
			}
			(*matrix)[indexRow][index2] = ply2->sign;
			system("cls");
			PrintMatrix(*matrix, row, col);
		} while (WinGame(*matrix, row, col, *ply2, indexRow, index2) == FALSE && DrawGame(*matrix, row, col)==FALSE);
		if (WinGame(*matrix, row, col, *ply2, indexRow, index2))
		{
			printf("\n ----------%s IS THE WINNER----------\n", ply2->name);
		}
		if (WinGame(*matrix, row, col, *ply1, indexRow, index2))
		{
			printf("\n----------%s IS THE WINNER----------\n", ply1->name);
		}
		if (DrawGame(*matrix, row, col))
		{
			printf("\n------------DRAW GAME------------\n");
		}
		printf("\nWant to play another game?\nENTER 1\nfor QUIT ENTER 7\n");
		scanf("%d", &choise);
	}
	if (choise == 7)
		printf("\n------------GOODBYE!------------\n");
}
void freeMatrix(int*** matrix, int row)
{//הפונקציה מקבלת מצביע למערך מחרוזות ומשחררת את הזיכרון הדינאמי שהוקצה
	for (int i = 0; i < row; i++)//שחרור כל שורה במטריצה בנפרד
	{
		free(*(*matrix + i));//שחרור לפי שורה
	}
	free(*matrix);//שחרור המצביע למטריצה 
	matrix = NULL;
}//freeMatrix