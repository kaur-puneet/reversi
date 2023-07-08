
//
// Author:
//
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int score(char board[][26], int n, int row, int col, char colour);
bool isMoveValid(char board[][26], int n, int row, int col, char colour);
int* directions (int directionNum);

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
             
                if (l==0 && m==0 || l==0 && m==n-1 || l==n-1 && m==0 || l==n-1 && m==n-1){
                    score+=7;
                }
                if (l==0 || m==0 || l==n-1 || m==n-1){
                    score+=3;
                }
                if (l==0 && (m==1 || m==n-2)){
                    score+=5;
                }
                if (l==n-1 && (m==1 || m==n-2)){
                    score+=5;
                }
                if (m==0 && (l==1 || l==n-2)){
                    score+=5;
                }
                if (m==n-1 && (l==1 || l==n-2)){
                    score+=5;
                }
                if(l==3 && (m==3 || m==4)){
                    score+=3;
                }
                if(l==4 && (m==3 || m==4)){
                    score+=3;
                }
            l+=dir[0];
            m+=dir[1];
            while (board[l][m]!=colour){
                score++;
                if(l==3 && (m==3 || m==4)){
                    score+=3;
                }
                if(l==4 && (m==3 || m==4)){
                    score+=3;
                }
                l+=dir[0];
                m+=dir[1];
            }
        }
    }
    board[row][col]='U';
    return score;
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {
    int x, y, z=0;
    int validX [n*n];
    int validY[n*n];
    for (x=0; x<n; x++){
        for (y=0; y<n; y++){
            if (isMoveValid(board, n, x, y, turn)){
                validX[z]=x;
                validY[z]=y;
                z++;
            }
        }
    }
    int count, rowX=0, colY=0, scoreTrack=0, scoreNum =0;
    for (count=0;count<z;count++){
        scoreNum = score(board, n, validX[count], validY[count], turn);
        if (scoreNum>scoreTrack){
            scoreTrack = scoreNum;
            rowX = validX[count];
            colY = validY[count];
        }
    }
    *row = rowX;
    *col = colY;
    return 0;
}


