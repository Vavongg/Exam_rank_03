#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_board(int *board, int n)
{
	int i = 0;
	while (i < n)
	{
		printf("%d", board[i]);
		if (i < n - 1)
			printf(" ");
		++i;
	}
	printf("\n");
}

int is_valid(int * board, int row, int col)
{
	int i = 0;
	while (i < row)
	{
		if (board[i] == col || board[i] - i == col - row || board[i] - i == col + row)
			return (0);
		++i;
	}
	return (1); 
}

void nqueen(int n, int *board, int row)
{
	int col = 0;
	
	if (row == n)
	{
		print_board(board, n);
		return ;
	}
	while (col < n)
	{
		if (is_valid(board, row, col))
		{
			board[row] = col;
			nqueen(n, board, row + 1);
		}
		++col;
	}
}
int main(int argc, char **argv)
{
	int n;
	if (argc == 2)
		n = atoi(argv[1]);
	else
		return (1);
	int board[10000];
	int i = 0;
	while (i < n)
	{
		board[i] = 0;
		++i;
	}
	nqueen(n, board, 0);
	return (0);
} 
