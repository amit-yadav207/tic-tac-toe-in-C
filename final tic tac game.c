/********************************************
             GAME : TIC TAC TOE
           Created By : AMIT YADAV
                Branch : C.S.E
********************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define r 3 //for rows 
#define c 3 //for columns

char board[r][c];//making accessible to every function
int numFC=0;//Number of cells filled
int flag=0;
struct Player
{
    char name[30];
    char choice;
} player[2];

////////////////////////////////////////

void toUpperCase (char *n)
{
    int i;
    for( i=0; n[i]!='\n'; i++) //n[i]!='0'
    {
        if(n[i]!=' ')
            n[i]=(n[i]&'_');//convert to uppercase
    }
    n[i]='\0';
    return ;
}

void hrline(char x)//horizontal line for formatting purpose
{
    printf("\n\n");
    for(int i=0; i<40; i++)
        printf("%c",x);
    printf("\n\n");
}

void printSpace ()
{
    for(int i=0; i<3; i++)
        printf("   ");

}
/////////////////////////////////////////////////

void viewStatus ();
void clrscr()
{
     //printf("\e[1;1H\e[2J");
     system("clear");
     
}
void createBoard ()
{
//create 3X3 matrix of characters
//fill it with '-' to denote empty cells

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            board[i][j]='-';
        }
    }
  
    printf("\n*********New board has been set up**********\n");
    printf("\n**************9 Empty cells ***************\n");
      viewStatus ();
    
}

void createPlayers()
{
    printf("\n>>Enter player_1 name : ");
    fgets(player[0].name,30,stdin);
    toUpperCase(player[0].name);
    printf("\n>>Enter player_2 name : ");
    fgets(player[1].name,30,stdin);
    toUpperCase(player[1].name);
}
void tossCoin()
{
//use random function to get 0 and 1
//0 for head , 1 for tail
    int pChoice;
    int outCome=rand()%2;
    printf("\n>>%s :-- Choose head or tail.....\n",player[0].name);
    printf("\n>>press 0 for head , 1 for tail :  ");
    scanf("%d",&pChoice);
    printf("\n>>OUTCOME OF TOSS : %d\n",outCome);
    if(pChoice==outCome)
    {
        printf("\n>>***%s has won the toss!!!\n",player[0].name);
        printf("\n>>Choose zero or Cross ['0' / 'X'] to start the game : ");
        scanf("\n%c",&player[0].choice);
        player[1].choice=(player[0].choice=='0')?'X':'0';
        flag=0;
    }
    else
    {
        printf("\n>>***%s has won the toss!!!\n",player[1].name);
        printf("\n>>Choose Zero or Cross ['0' / 'X'] to start the game : ");
        scanf("\n%c",&player[1].choice);
        player[0].choice=(player[1].choice=='0')?'X':'0';
        flag=1;
    }
    clrscr();

}
void viewStatus ()
{
    printf("\n\tCurrent Status of Board\n\n");
    for(int i=0; i<r; i++)
    {
        printSpace();
        for(int j=0; j<c; j++)
        {
            if(j>=0)
                printf("   %c   ",board[i][j]);
            else
                printf("        ");
        }
        printf("\n\n\n");
    }
}

int cellValidation (int n)
{
    if(n<1||n>9)
    {
        hrline ('*');
         printf(">>MESSAGE : This cell number is INVALID....");
        hrline ('*');
        return 0;
    }
    else
    {
        int i=(n-1)/3;
        int j=n-1-i*3;//columm number
        if(board[i][j]!='-')
        {
            hrline ('*');
            printf(">>MESSAGE : This cell is ALREADY OCCUPIED....");
            hrline ('*');
            return 0;
        }
        return 1;
    }
}

void getUserInput(int num)
{
    int cellNum;
    printf("\n>>***%s ----> It's your turn : ",player[num].name);
    printf("\n>>Choose cell number (1 to 9) : ");
    scanf("%d",&cellNum);
    while(!cellValidation(cellNum))//validating cell number
    {
        printf("\n*********Choose again : ");
        scanf("%d",&cellNum);
    }
    int i,j;//for locating cell number
    i=(cellNum-1)/3;
    j=(cellNum-1)%3;//can be found by multiplication
    board[i][j]=player[num].choice;
    clrscr();
    viewStatus ();//view updated board
}

int hasWon (struct Player *p)
{
    int d1=0,d2=0;
    char key=p->choice;
    for(int i=0; i<r; i++)
    {
        int row=0,colm=0;
        for(int j=0; j<c; j++)
        {
            if(i==j&&board[i][j]==key)//primary diagonal
                d1++;
            if(i+j==2&&board[i][j]==key)//secondary diagonal
                d2++;
            if(board[i][j]==key)//row
                row++;
            if(board[j][i]==key)//column
                colm++;
        }
        if(row==3||colm==3||d1==3||d2==3)
        {
            hrline('-');
            printf("*********CONGRATULATIOS************");
            printf("\n*****%s has won this game!!!*****",p->name);
            hrline('-');
            return 1;
        }
    }
    //check if number of cells are exhausted
    if(numFC==9)
    {
        hrline('-');
        printf("*************IT WAS A DRAW****************");
        hrline('-');
        numFC=0;
        return 1;
    }
    return 0;
}
void startGame()
{
    int num=flag;//player number
    while(1)
    {
        if(num==0)//for first player num=0
        {
            getUserInput (num);//pass player number
            numFC++;//number of cells filled gets updated
            //check for winner
            if(hasWon(&player[num]))
            {
                hrline('.');
                printf("*************GAME  OVER*************");
                hrline('.');
                break;
            }
            num=1;//switching to player_2
        }
        else
        {
            getUserInput (num);//pass player number
            //check for winner
            numFC++;//number of cells filled gets updated
            if(hasWon(&player[num]))
            {
                break;
            }
            num=0;//switching to player_1
        }
    }
}
void Game()
{
    numFC=0;
    srand(time(0));
    createBoard();
    createPlayers();
    tossCoin();
    viewStatus();
    startGame();
    return;
}

int main()
{
    char choice;
    do
    {
        Game();
        printf("\n>>DO YOU WANT TO PLAY AGAIN ? ( y / n ) : ");
        scanf("\n%c",&choice);
        while(getchar()!='\n');//to remove extra newline from buffer....
        clrscr();
    } while(choice!='n');
    return 0;
}
