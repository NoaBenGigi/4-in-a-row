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
	char name[30];//�� ����
	int NumOfWin;//���� ��������
	int sign;
} player;//����-����
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
{//������� ������ ����� ����� �������
	printf("Please enter board's size-lines and column");//����� ������ ������ ���� �������
	scanf("%d%d", row, col);//����� ������
	while ((*row < 4 && *col < 2 )|| (*col < 4 && *row < 2))
	{//�� ��� ����� ���� ����
		printf("Size is incorrect!\nPlease enter new size for your game board");//����� ������ ���� ����
		scanf("%d%d", row, col);//����� ����
	}
	*matrix = (int**)malloc((*row) * sizeof(int*));//����� ������� �� ������
	if (!(*matrix))
	{//����� ������� ������
		printf("ERROR! cannot allocate memory\n");
		return;
	}
	for (int i = 0; i < (*row); i++)
	{//����� ������� ��� ����
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
{//������� ������ ����� ����� ������ �� ����� �����
	printf("Please enter your name: \n");//����� ����� ������ ����
	gets(ply->name);//����� �� �����
	ply->NumOfWin = 0; //����� ���� ��������� �0
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
{//�������� ����� ����� ����� ������� ������� �� ������� ������� ������
	for (int i = 0; i < row; i++)//����� �� ���� ������� �����
	{
		free(*(*matrix + i));//����� ��� ����
	}
	free(*matrix);//����� ������ ������� 
	matrix = NULL;
}//freeMatrix