
/********************************************
             GAME : TIC TAC TOE
           Created By : AMIT YADAV
                Branch : C.S.E
********************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include "colors.h" 
#define r 3 //for rows 
#define c 3 //for columns

char board[r*c];//making accessible to every function
char temp_board[r*c];//for keeping track of changes
int numFC=0;//Number of cells filled
int flag=0;
bool draw=false;
bool cpMode=false;
struct Player
{
    char name[30];
    char choice;
} player[2];

////////////////////////////////////////

void toUpperCase (char *n)
{
    int i;
    for( i=0; n[i]!='\n'&&n[i]!='\0'; i++) //n[i]!='\0'
    {
        if(n[i]!=' ')
            n[i]=(n[i]&'_');//convert to uppercase
    }
    n[i]='\0';
    return ;
}

void hrline(char x)//horizontal line for formatting purpose
{
    printf("\n\t\t\t\t");
    for(int i=0; i<69; i++)
        printf("%c",x);
    printf("\n");
}

void printSpace ()
{
    for(int i=0; i<14; i++)
        printf("    ");

}
/////////////////////////////////////////////////

void viewStatus ();
void logo()
{
    printf("\t\t\t\t######################################################################\n");
    printf("\t\t\t\t#                                                                    #\n");
    printf("\t\t\t\t#\t\t      "BOLD_MODE"        TIC-TAC-TOE    "COLOR_RESET"      \t\t     #\n");
    printf("\t\t\t\t#\t\t        "ITALIC_MODE"   game in C language"COLOR_RESET"    \t\t     #\n");
    printf("\t\t\t\t#                                                                    #\n");
    printf("\t\t\t\t######################################################################\n");
    if(cpMode)
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>"BOLD_MODE" HUMAN v/s COMPUTER"COLOR_RESET" <<<<<<<<<<<<<<<<<<<<<<<\n");
    else
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>"BOLD_MODE" HUMAN v/s HUMAN"COLOR_RESET" <<<<<<<<<<<<<<<<<<<<<<<<<\n");
}
void clrscr()
{
     //printf("\e[1;1H\e[2J");
     system("clear");
     
}
void createBoard ()
{
    for(int i=0; i<r*c; i++)
    {
           board[i]=' ';
           temp_board[i]=' ';
    }
       viewStatus ();
}

void createPlayers()
{
    printf("\n\t\t\tEnter player_1 name : ");
    fgets(player[0].name,30,stdin);
   toUpperCase(player[0].name);
  
  if(cpMode){
printf("\n\t\t\tPlayer_2 name  : ");
 strcpy(player[1].name,"COMPUTER");
 printf("%s\n",player[1].name);
  }
  else
  {
      printf("\n\t\t\tEnter player_2 name : ");
  fgets(player[1].name,30,stdin);
  toUpperCase(player[1].name);
  }
  
   
}
void tossCoin()
{
//use random function to get 0 and 1
//0 for head , 1 for tail
    int pChoice;
    int outCome=rand()%2;
    printf("\n\t\t\t%s :-- Choose head or tail.....\n",player[0].name);
    printf("\n\t\t\tpress 0 for head , 1 for tail :  ");
    scanf("%d",&pChoice);
    //pChoice=0;
    printf("\n\t\t\tOUTCOME OF TOSS : %d\n",outCome);
    if(pChoice==outCome)
    {
        printf("\n\t\t\t***%s has won the toss!!!\n",player[0].name);
        printf("\n\t\t\tChoose zero or Cross ['0' / 'X'] to start the game : ");
        scanf("\n%c",&player[0].choice);
       // player[0].choice='X';
       
        player[1].choice=(player[0].choice=='0')?'X':'0';
        flag=0;
    }
    else
    {
        printf("\n\t\t\t***%s has won the toss!!!\n",player[1].name);
        printf("\n\t\t\tChoose Zero or Cross ['0' / 'X'] to start the game : ");
        scanf("\n%c",&player[1].choice);
        //   player[1].choice='X';
        player[0].choice=(player[1].choice=='0')?'X':'0';
        flag=1;
    }
    clrscr();

}
void viewStatus ()
{
    logo();
    printf("\n\t\t\t\t\t\t\tCurrent Status of Board\n\n");
    printSpace(); 
    for(int i=0; i<r*c; i++)
    {
        if(draw)//draw ..set color to yellow
        {
            printf( BG_YELLOW" %c "COLOR_RESET"      ",board[i]);
        }
        else if(temp_board[i]=='G')
        {
        printf( BG_GREEN" %c "COLOR_RESET"      ",board[i]);
        }
        else if(temp_board[i]==' ')
        {
            printf( BG_BLACK BG_WHITE" %c "COLOR_RESET"      ",board[i]);
        }
        if((i+1)%3==0)//CHANGE LINE
        {
            printf("\n\n\n");
            printSpace(); 
        }
    }
}

bool cellValidation (int n)
{
    if(n<1||n>9)
    {
        hrline ('*');
         printf("\t\t\t\t\t\t"COLOR_RED"MESSAGE :"COLOR_RESET" This cell number is "BOLD_MODE"INVALID...."COLOR_RESET);
        hrline ('*');
         printf("\n\t\t\t\t\t\t*********Choose again : ");
        return false;
    }
    else
    {
        if(board[n-1]!=' ')
        {
            hrline ('*');
            printf("\t\t\t\t\t\t"COLOR_RED"MESSAGE :"COLOR_RESET" This cell is "BOLD_MODE"ALREADY OCCUPIED...."COLOR_RESET);
            hrline ('*');
             printf("\n\t\t\t\t\t\t*********Choose again : ");
            return false;
        }
    }
    return true;
}

void getUserInput(int num)
{
    int cellNum;
    
    printf("\n\t\t\t***"BOLD_MODE"%s"COLOR_RESET" ----> It's your turn  ",player[num].name);
    printf("\n\t\t\tChoose cell number (1 to 9) : ");
  if(num==0||cpMode==false){
   do{
    scanf("%d",&cellNum);
   }while(!cellValidation(cellNum));//validating cell number
    }
    else//computer
    {
   
       do{
       cellNum=rand()%9+1;
       }while(!((cellNum>=1&&cellNum<=9)&&board[cellNum-1]==' '));
       printf("%d",cellNum);
         printf("\n\t\t\tPress Enter...  ") ;
       while(getchar()!='\n');
       getchar();
    }
    board[cellNum-1]=player[num].choice;
      numFC++;//number of cells filled gets updated
    clrscr();
}

void setColor(int x,int y,int z)
{
    temp_board[x]='G';
    temp_board[y]='G';
    temp_board[z]='G'; 
    return;
}

bool hasWon (struct Player *p)
{
    char key=p->choice;
    bool flag1=false;
//checking rows
if(board[0]==key&&board[1]==key&&board[2]==key)
{
    // board[0]='G';
    // board[1]='G';
    // board[2]='G';
    setColor(0,1,2);//change color of row1
    flag1= true;
}
else if(board[3]==key&&board[4]==key&&board[5]==key)
{
    setColor(3,4,5);//change color of row2
    flag1 =true;
}
else if(board[6]==key&&board[7]==key&&board[8]==key)
{
    setColor(6,7,8);//change color of row3
    flag1= true;
}
    
///checking columns
else if(board[0]==key&&board[3]==key&&board[6]==key)
{
    setColor(0,3,6);//change color of col1
   flag1= true;
}
else if(board[1]==key&&board[4]==key&&board[7]==key)
{
    setColor(1,4,7); //change color of colm2
    flag1= true;
}
else if(board[2]==key&&board[5]==key&&board[8]==key)
{
    setColor(2,5,8);//change color of colum3
   flag1= true;
}
   
 //checking diagonals
else if(board[0]==key&&board[4]==key&&board[8]==key)
{
    setColor(0,4,8);//change color of primary diagonal
 flag1= true;
}
else if(board[1]==key&&board[4]==key&&board[7]==key)
{
    setColor(2,4,6);//change color of sec diagonal
   flag1 =true;
}

   if(flag1)
   {
        viewStatus ();//view updated board
        char*ptr=" won this game";
        int n=(70-strlen(p->name)-strlen(ptr))/2;
        hrline('-');
            printf("\t\t\t\t***************************"COLOR_GREEN"CONGRATULATIONS"COLOR_RESET"***************************");
            // printf("\n\t\t\t\t**********************%s has won this game!!!*****************",p->name);
           printf("\n\t\t\t\t");
           for(int i=0;i<n;i++)
           printf("*");
           printf("%s%s",p->name,ptr);
           for(int i=0;i<n;i++)
           printf("*");
           
            hrline('-');
           // hrline('.');
            printf("\t\t\t\t*****************************"COLOR_BLUE"GAME  OVER"COLOR_RESET"******************************");
                //hrline('.');
            return true;
   }
  
    //check if number of cells are exhausted
    if(numFC==9)
    {
         draw=true;
        viewStatus ();//view updated board
        hrline('-');
           printf("\t\t\t\t***************************"COLOR_YELLOW"IT WAS A DRAW"COLOR_RESET"*****************************");
        hrline('-');
      //  hrline('.');
            printf("\t\t\t\t*****************************"COLOR_BLUE"GAME  OVER"COLOR_RESET"******************************");
                 //hrline('.');
        return true;
    }
    return false;
}
void startGame()
{
    int num=flag;//player number
    while(1)
    {
        if(num==0)//for first player num=0
        {
            getUserInput (num);//pass player number
            if(hasWon(&player[num])) //check for winner
            {
                break;
            }
                viewStatus ();//view updated board
            num=1;//switching to player_2
        }
        else
        {
            getUserInput (num);//pass player number
            //check for winner
            if(hasWon(&player[num]))
            {
                break;
            } 
             viewStatus ();//view updated board
            num=0;//switching to player_1
        }
    }
}
void Game()
{
    numFC=0;
    draw=false;
    srand(time(0));
    printf("\n\t\t\tPress "BOLD_MODE"1"COLOR_RESET",for "BOLD_MODE"COMPUTER v/s HUMAN"COLOR_RESET" mode\n\t\t\tPress "BOLD_MODE"2"COLOR_RESET",for "BOLD_MODE"TWO PLAYER"COLOR_RESET" mode\n\n\t\t\tEnter your choice : ");
    int choice;
    scanf("%d",&choice);
    while(getchar()!='\n');//to remove extra newline from buffer....
    cpMode=(choice==1)?true:false;
    clrscr();
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
        printf("\n\t\t\t\tDO YOU WANT TO PLAY AGAIN ? ( y / n ) : ");
        scanf("\n%c",&choice);
        while(getchar()!='\n');//to remove extra newline from buffer....
        clrscr();
    } while(choice!='n');
    return 0;
}



