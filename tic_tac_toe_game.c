#include <stdio.h>
#define MAX_SIZE 10

void initialize_Game_Board(int grid_size, char grid[][MAX_SIZE])  //Oyun tahtas�n� belirtilen boyutta olu�turur ve t�m h�creleri bo�luk karakteriyle (' ') doldurur.
{
    int i, j;

    for (i = 0; i < grid_size; i++)
    {
        for (j = 0; j < grid_size; j++)
        {
            grid[i][j] = ' ';
        }
    }
}

void show_Game_Board(int grid_size, char grid[][MAX_SIZE]) //Oyun tahtas�n�n mevcut durumunu ekrana yazd�r�r.
{
    int i, j, k;
    
    printf("\n");
    
    for (i = 0; i < grid_size; i++)
    {
        for (j = 0; j < grid_size; j++)
        {
            printf("%c", grid[i][j]);
            if (j < grid_size - 1)
            {
                printf(" | ");
            }
        }
        printf("\n");
        if (i < grid_size - 1)
        {
            for (k = 0; k < (grid_size * 4) - 1; k++)
            {
                printf("-");
            }
            printf("\n");
        }
    }
}   

//Bu fonksiyonda yard�m ald�m.
void whose_turn(char **player, char *player1, char *player2) //S�radaki oyuncuyu belirler. 
{
    if (*player == player1)  //*player pointer'�n�n g�sterdi�i adres de�i�tirmek hedeflenir. Player pointer'�n�n i�aret etti�i adres, player1'in adresiyle ayn� ise
    {
        *player = player2; //player pointer'�n�n g�sterdi�i adres player2'nin adresine e�itlenir
    }
    else
    {
        *player = player1;
    }

    printf("%s's turn to move\n", *player);
}


void update_Game_Board(char grid[][MAX_SIZE], int row, int column, char symbol) //Oyuncunun hamlesini tahta �zerinde g�nceller.
{
    if (grid[row-1][column-1]==' ')
    {
        grid[row-1][column-1]=symbol;
    }

}   

void ask_for_destination(int *row, int *column,char grid[][MAX_SIZE], int grid_size) //Oyuncudan hamle yapmak istedi�i sat�r ve s�tunu girmesini ister. Girilen sat�r ve s�tunun ge�erli olup olmad���n� kontrol eder.
{
    printf("Enter selected row: ");
    scanf("%d", row);
    printf("Enter selected column: ");
    scanf("%d", column);
		
	if (*row > grid_size || *column > grid_size)
	{
		printf("Please enter a valid column/row number.\n");
		ask_for_destination(row, column, grid, grid_size);		
	}
	
	if (grid[*row-1][*column-1]!=' ')
    {
		printf("This place has already been taken, please change destination.\n");
		ask_for_destination(row, column, grid, grid_size);
	}
}

void which_symbol(char *symbol, char *symbol1, char *symbol2) //Oyunculara hangi sembol�n atanaca��n� belirler.
{
    if (*symbol == *symbol1)
    {
        *symbol = *symbol2;
    }
     
    else
    {
        *symbol = *symbol1;
    }

}

int check_for_win(int grid_size, char grid[][MAX_SIZE], char symbol, char symbol1, char symbol2, char *player) //Oyunun kazanan�n� kontrol eder. Yatay, dikey ve �apraz �izgilerde �� sembol�n ard���k olarak gelip gelmedi�ini kontrol eder.
{
    int i, j;


    //Yatay 3 basamakta e�le�me var m� diye kontrol eder
    for (i=0; i < grid_size; i++) 
	{
        for (j=0; j <= grid_size-3; j++) 
		{
            if (grid[i][j] == symbol && grid[i][j] == grid[i][j+1] && grid[i][j+1] == grid[i][j+2]) 
			{
                printf("%s wins the game!\n", player);
                return 0;
            }
        }
    }

    //Dikey 3 basamakta e�le�me var m� diye kontrol eder
    for (j=0; j < grid_size; j++) 
	{
        for (i=0; i <= grid_size-3; i++) 
		{
            if (grid[i][j] == symbol && grid[i][j] == grid[i+1][j] && grid[i+1][j] == grid[i+2][j]) 
			{
                printf("%s wins the game!\n", player);
                return 0;
            }
        }
    }

    //�apraz 3 basamakta e�le�me var m� diye kontrol eder (sol �stten sa� alta)
    for (i=0; i <= grid_size-3; i++) 
	{
        for (j=0; j <= grid_size-3; j++) 
		{
            if (grid[i][j] == symbol && grid[i][j] == grid[i+1][j+1] && grid[i+1][j+1] == grid[i+2][j+2])
			{
                printf("%s wins the game!\n", player);
                return 0;
            }
        }
    }

    //�apraz 3 basamakta e�le�me var m� diye kontrol eder (sa� �stten sol alta)
    for (i=0; i <= grid_size-3; i++) 
	{
        for (j = grid_size-1; j >= 2; j--) 
		{
            if (grid[i][j] == symbol && grid[i][j] == grid[i+1][j-1] && grid[i+1][j-1] == grid[i+2][j-2]) 
			{
                printf("%s wins the game!\n", player);
                return 0;
            }
        }
    }

    return 1;
}

//Bu fonksiyonda yard�m ald�m
int Menu() // Oyuna ba�lamak i�in ENTER tu�una bas�lmas�n� bekleyen bir men�.   
{
	int answer;
	char enter = '\n';
	char hungry; //karakterleri yutmas� i�in bir de�i�ken
	printf("\n------------------------------------\n");
	printf("--------Press ENTER to play---------\n");
	printf("------------------------------------\n");
	
	scanf("%c", &answer);
	
	scanf("%c", &hungry); //input buffer'�nda kalan karakterleri new-line karakterine gelene kadar yut.
		
	if (answer == enter) 
	{
		return 1;
	}

	else
	{
		return 0;
	}
	
}


void start_Game() //Oyunu oynar: oyun tahtas�n�n boyutunu belirler, semboller atar, s�rayla hamle yapar ve kazanan� belirler.
{
	printf("\n-----------------------------------\n");
	printf("-------------WElCOME---------------\n");
	printf("-----------------------------------\n");
	printf("\n\n");
	
    int row, column;
    char symbol, symbol1, symbol2;
    int grid_size, result;
    
    char *player = "player";
    char *player1 = "player1";
    char *player2 = "player2";
    int result2=0;

    char grid[MAX_SIZE][MAX_SIZE];
	
	
	result2 = Menu();
	
	while(result2)
	{
		printf("\nEnter requested grid size: (3 for 3x3 grid, 9 for 9x9 grid)\n ");
    	scanf("%d", &grid_size);
    	
    	initialize_Game_Board(grid_size, grid);

    	show_Game_Board(grid_size, grid);

    	player = player1;
    
   		printf("\nEnter preferred symbol for Player1: \n");
    	scanf(" %c", &symbol1);
    
    	symbol = symbol1; 
    
    	printf("Enter preferred symbol for Player2: \n");
    	scanf(" %c", &symbol2);
    
    	printf("\n-----player1 makes the first move-----\n");
    
    	result = check_for_win(grid_size, grid, symbol, symbol1, symbol2, player);
   
    	while(result)
    	{
        	ask_for_destination(&row, &column, grid, grid_size);
    
        	update_Game_Board(grid, row, column, symbol);
        
        	show_Game_Board(grid_size, grid);
        
        	result = check_for_win(grid_size, grid, symbol, symbol1, symbol2, player);
        	
       		if (!result)
			{ 
       	    	break;
       		}
        
	    	whose_turn(&player, player1, player2);
    
        	which_symbol(&symbol, &symbol1, &symbol2);
        	
    	}
    	
        result2 = Menu();
	}	    
    
}

int main()
{
    start_Game();

    return 0;
}

