#include <stdio.h>
#include <stdlib.h>

#define n 3

char board[3][3];
char player;

void init()
{
	char x = '1';
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = x++;
		}
	}
}

void printt()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	printf("==TIC TAC TOE==\n");
	printf("-------------\n");
	for (int i = 0; i < n; i++)
	{
		printf("| ");
		for (int j = 0; j < n; j++)
			printf("%c | ", board[i][j]);
		printf("\n-------------\n");
	}
}

int win()
{
	for (int i = 0; i < n; i++)
	{
		if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
			(board[0][i] == player && board[1][i] == player && board[2][i] == player) ||
			(board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
			(board[0][2] == player && board[1][1] == player && board[2][0] == player))
			return 1;
	}
	return 0;
}

int equal()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
				return 0;
		}
	}
	return 1;
}

int mark(int pos)
{
	int row = (pos - 1) / 3;
	int col = (pos - 1) % 3;
	if (board[row][col] != 'X' && board[row][col] != 'O')
	{
		board[row][col] = player;
		return 1;
	}
	return 0;
}

void save(char* result)
{
	FILE* f = fopen("results.txt", "a");
	if (f == NULL)
	{
		printf("Error opening results file\n");
		exit(-1);
	}

	fprintf(f, "%s\n", result);

	if (fclose(f) != 0)
	{
		printf("Error closing results file\n");
		exit(-1);
	}
}

void results()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
	FILE* f = fopen("results.txt", "r");
	if (f == NULL)
	{
		printf("Error opening results file\n");
		return;
	}
	printf("==RESULTS==\n\n");
	char line[101];
	while (fgets(line, sizeof(line), f))
	{
		printf("%s", line);
	}
	printf("Press Enter to return to menu\n");
	while (getchar() != '\n');
	if (fclose(f) != 0)
	{
		printf("Error closing results file\n");
		exit(-1);
	}
}

void play()
{
	int move;
	player = 'X';
	init();
	while (1)
	{
		printt();
		printf("Player %c, enter position (1-9): ", player);
		if (scanf("%d", &move) != 1)
		{
			printf("Reading error\n");
			exit(-1);
		}
		while (getchar() != '\n');
		if (move < 1 || move>9 || !mark(move))
		{
			printf("\nInvalid move. Press Enter to try again.");
			while (getchar() != '\n');
			continue;
		}
		if (win())
		{
			printt();
			printf("Player %c wins!\n", player);
			char result[101];
			sprintf(result, "Player %c won.", player);
			save(result);
			printf("Press Enter to return to menu\n");
			while (getchar() != '\n');
			break;
		}
		if (equal())
		{
			printt();
			printf("It's equal!\n");
			save("Equal.");
			printf("Press Enter to return to menu\n");
			while (getchar() != '\n');
			break;
		}
		if (player == 'X')
			player = 'O';
		else
			player = 'X';
	}
}

int main()
{
	fclose(fopen("results.txt", "w"));
	while (1)
	{
		#ifdef _WIN32
				system("cls");
		#else
				system("clear");
		#endif

		printf("==TIC TAC TOE==\n\n");
		printf("1. Start\n");
		printf("2. Result\n");
		printf("3. Exit\n");
		printf("\nChoose an option: ");
		int op;
		if (scanf("%d", &op) != 1)
		{
			printf("Read error\n");
			exit(-1);
		}
		while (getchar() != '\n');
		switch (op)
		{
		case 1:
			play();
			break;
		case 2:
			results();
			break;
		case 3:
			#ifdef _WIN32
						system("cls");
			#else
						system("clear");
			#endif
			printf("Goodbye!\n");
			return 0;
		default:
			printf("Invalid option. Press Enter to try again");
			while (getchar() != '\n');

		}
	}
	return 0;
}