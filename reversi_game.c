//
// Author: Puneet Kaur
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int* directions (int directionNum);
bool isMoveValid(char board[][26], int n, int row, int col, char colour);
void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
int score(char board[][26], int n, int row, int col, char colour);
void humanMove(char board[][26], int n, char colour, char compColour);
bool checkGameEnd(char board[][26], int n);
void winner(char board[][26], int n);
int availMovesNum(char board[][26], int n, char colour);
void compMove(char board[][26], int n, char colour, char humColour);

void printBoard(char board[][26], int n) {
  int count = 0;
  char letters[n];
  char alph = 'a';
  while (count<n){
    letters[count]=alph;
    alph++;
    count++;
  }
  int a;
  printf("  ");
  for (a=0;a<n;a++){
    printf("%c", letters[a]);
  }
  printf("\n");

  int x, y;
  for (x=0; x<n; x++){
    printf("%c ", letters[x]);
    for (y=0; y<n; y++){
      printf("%c", board[x][y]);
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col) {
  bool bounds = true;
  if (row>=n || row<0 || col>=n || col<0){
    bounds = false;
  }
  return bounds;
}

bool isMoveValid(char board[][26], int n, int row, int col, char colour){
  bool valid = false;
  int array[2];
  int count;
  if(positionInBounds(n, row, col)==false){
    valid = false;
  }
  else if (board[row][col]=='W'){
    valid=false;
  }
  else if (board[row][col]=='B'){
    valid=false;
  }
  else{
    for (count=0; count<8; count++){
      array[0]=*directions(count);
      array[1]=*(directions(count)+1);
      valid = valid || checkLegalInDirection(board, n, row, col, colour, array[0], array[1]);
  }
  }
  return valid;
}

/*
char[][] availMoves(char board[][26], int n, char colour){
  int a, b, c=0;
  char moves[2][n*n];
  for (a=0; a<n;a++){
    for (b=0;b<n;b++){
      if (isMoveValid(board, n, a, b, colour)==true){
        moves[0][c]= a+'a';
        moves[1][c]= b+'a';
        c++;
      }
    }
  }
  return moves;
}
*/
int availMovesNum(char board[][26], int n, char colour){
  int a, b, numMoves = 0;
  for (a=0; a<n;a++){
    for (b=0;b<n;b++){
      if (isMoveValid(board, n, a, b, colour)==true){
        numMoves++;
      }
    }
  }
  return numMoves;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
char colour, int deltaRow, int deltaCol) {
   bool valid = false;
   int x, y;
   x = row+deltaRow;
   y=col+deltaCol;
   if (x<0 || x>=n || y<0 || y>=n){
     valid = false;
   }
   else if (board[x][y] == 'U'){
     valid =false;
   }
   else if (board[x][y] == colour){
     valid =false;
   }
   else{
     while(x>=0 && x<n && y>=0 && y<n && board[x][y]!= 'U' && board[x][y]!=colour){
       x+=deltaRow;
       y+=deltaCol;
       }
       if (x<0 || x>=n || y<0 || y>=n){
         valid = false;
       }
       else if (board[x][y]==colour){
         valid = true;
       }
     }
     return valid;
}



int* directions (int directionNum){
    static int dirArray[2];
    if (directionNum == 1){
        dirArray[0]=1;
        dirArray[1]=0;
    }
    else if (directionNum == 2){
        dirArray[0]=1;
        dirArray[1]=-1;
    }
    else if (directionNum == 3){
        dirArray[0]=0;
        dirArray[1]=-1;
    }
    else if (directionNum == 4){
        dirArray[0]=-1;
        dirArray[1]=-1;
    }
    else if (directionNum == 5){
        dirArray[0]=-1;
        dirArray[1]=0;
    }
    else if (directionNum == 6){
        dirArray[0]=-1;
        dirArray[1]=1;
    }
    else if (directionNum == 7){
        dirArray[0]=0;
        dirArray[1]=1;
    }
    else{
        dirArray[0]=1;
        dirArray[1]=1;
    }
    return dirArray;
}

int score(char board[][26], int n, int row, int col, char colour){
    board[row][col]=colour;
    int dir[2];
    int count;
    int score = 0;
    for (count=0; count<8; count++){
        int l=row, m=col;
        dir[0] = *(directions(count));
        dir[1] = *(directions(count)+1);
        if (checkLegalInDirection(board, n, row, col, colour, dir[0], dir[1])){
            l+=dir[0];
            m+=dir[1];
            while (board[l][m]!=colour){
                score++;
                l+=dir[0];
                m+=dir[1];
            }
        }
    }
    board[row][col]='U';
    return score;
}


void flipTheTiles(char board[][26], int n, int row, int col, char colour){
  board[row][col]=colour;
  int dir[2];
  int count;
  for (count=0; count<8; count++){
    int l=row, m=col;
    dir[0] = *(directions(count));
    dir[1] = *(directions(count)+1);
    if (checkLegalInDirection(board, n, row, col, colour, dir[0], dir[1])){
      l+=dir[0];
      m+=dir[1];
      while (board[l][m]!=colour){
        board[l][m]= colour;
        l+=dir[0];
        m+=dir[1];
      }
    }
  }
}

void compMove(char board[][26], int n, char colour, char humColour){
    int x, y, z=0;
    int validX [n*n];
    int validY[n*n];
    for (x=0; x<n; x++){
        for (y=0; y<n; y++){
            if (isMoveValid(board, n, x, y, colour)){
                validX[z]=x;
                validY[z]=y;
                z++;
            }
        }
    }
    if (z==0){
        if (checkGameEnd(board, n)){
            winner(board,n);
        }
        else{
            printf("%c player has no valid move.\n", colour);
            humanMove(board, n, humColour, colour);
        }
    }
    else{
        int count, row=0, col=0, scoreTrack=0, scoreNum =0;
        for (count=0;count<z;count++){
            scoreNum = score(board, n, validX[count], validY[count], colour);
            if (scoreNum>scoreTrack){
                scoreTrack = scoreNum;
                row = validX[count];
                col = validY[count];
            }
        }
        printf("Computer places %c at %c%c.\n", colour, row+'a', col+'a');
        flipTheTiles(board, n,row, col, colour);
        printBoard(board, n);
        humanMove(board, n, humColour, colour);
    }
}

void humanMove(char board[][26], int n, char colour, char compColour){
    if (availMovesNum(board, n, colour)<=0){
        if (checkGameEnd(board, n)){
            winner(board,n);
        }
        else{
            printf("%c player has no valid move.\n", colour);
            compMove(board, n, compColour, colour);
        }
    }
    else{
        printf("Enter move for colour %c (RowCol): ", colour);
        char one, two;
        scanf("\n%c%c", &one, &two);
        if (isMoveValid(board, n, (int)(one-'a'), (int)(two-'a'), colour)==false){
            printf("Invalid move.\n");
            printf("%c player wins.", compColour);
        }
        else{
            flipTheTiles(board, n, (int)(one-'a'), (int)(two-'a'), colour);
            printBoard(board, n);
            compMove(board, n, compColour, colour);
        }
    }
}

void winner(char board[][26], int n){
     int a, b, bNum=0, wNum=0;
        for (a=0; a<n;a++){
            for (b=0;b<n;b++){
                if(board[a][b]=='W'){
                    wNum++;
                }
                else if(board[a][b]=='B'){
                    bNum++;
                }
            }
        }
        if (bNum==wNum){
            printf("Draw!");
        }
        else if (bNum>wNum){
            printf("B player wins.");
        }
        else if (bNum<wNum){
            printf("W player wins.");
        }
}

bool checkGameEnd(char board[][26], int n){
    bool result = false;
    if (availMovesNum(board, n, 'W')<=0 && availMovesNum(board, n, 'B')<=0){
        result = true;
    }
    else{
        int a, b;
        for (a=0; a<n;a++){
            for (b=0;b<n;b++){
                if(board[a][b]=='U'){
                    result = result && false;
                }
            }
        }
    }
    return result;
}

int main(void) {
  int n;
  printf("Enter the board dimension: ");
  scanf("%d", &n);
  char compColour;
  printf("Computer plays (B/W): ");
  scanf(" %c", &compColour);
  char board[26][26];
  int x, y;
  for (x=0; x<n; x++){
    for (y=0; y<n; y++){
      if((x==(n/2)-1) && (y==(n/2)-1)){
        board[x][y]='W';
      }
      else if((x==(n/2)-1) && (y==(n/2))){
        board[x][y]='B';
      }
      else if((x==(n/2)) && (y==(n/2)-1)){
        board[x][y]='B';
      }
      else if((x==(n/2)) && (y==(n/2))){
        board[x][y]='W';
      }
      else{
        board[x][y]='U';
      }
    }
  }
  printBoard (board, n);

  if (compColour=='B'){
      compMove(board, n, 'B', 'W');
  }
  else{
      humanMove(board, n, 'B', 'W');
  }

  /*
  printf("Available moves for W:\n");
  availMoves(board, n ,'W');
  printf("Available moves for B:\n");
  availMoves(board, n ,'B');
  printf("Enter a move:\n");
  char move[3];
  scanf("%s", move);
  if (isMoveValid(board, n, move[1]-97, move[2]-97, move[0])){
    printf("Valid move.\n");
    flipTheTiles(board, n, move[1]-97, move[2]-97, move[0]);
  }
  else{
    printf("Invalid move.\n");
  }
  printBoard(board,n);
  
  */

  return 0;
}


