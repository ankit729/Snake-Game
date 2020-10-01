#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<windows.h>
#define height 20
#define width 20
#define limit 100
int x,y,foodx,foody,flag=4,score=0,length=0;
int tailx[limit],taily[limit];
char grid[height+1][width+1];
bool gameEnd=false,update=false;
void food(){
    l1:;
    foodx=(rand()%(height-1))+1;
    foody=(rand()%(width-1))+1;
    if(grid[foodx][foody]!=' '){
        goto l1;
    }
    grid[foodx][foody]='@';
}
void logic(){
    int i;
    if(length>0){
        if(!update){
            grid[tailx[length-1]][taily[length-1]]=' ';
        }
        for(i=length-1;i>0;i--){
            tailx[i]=tailx[i-1];
            taily[i]=taily[i-1];
            grid[tailx[i]][taily[i]]='o';
        }
        tailx[0]=x;
        taily[0]=y;
        grid[tailx[0]][taily[0]]='o';
    }
    if(length==0){
        grid[x][y]=' ';
    }
    update=false;
    switch(flag){
        case 1:{
            x--;
            break;
        }
        case 2:{
            x++;
            break;
        }
        case 3:{
            y--;
            break;
        }
        case 4:{
            y++;
            break;
        }
    }
    if(grid[x][y]=='*' || grid[x][y]=='o'){
        gameEnd=true;
    }
    grid[x][y]='O';
    if(x==foodx && y==foody){
        update=true;
        food();
        score+=10;
        length++;
    }
}
void input(){
    if(kbhit()){
        switch(getch()){
            case 'w':{
                if(flag==3 || flag==4){
                    flag=1;
                }
                break;
            }
            case 's':{
                if(flag==3 || flag==4){
                    flag=2;
                }
                break;
            }
            case 'a':{
                if(flag==1 || flag==2){
                    flag=3;
                }
                break;
            }
            case 'd':{
                if(flag==1 || flag==2){
                    flag=4;
                }
                break;
            }
        }
    }
}
void setup(){
    int i,j;
    for(i=0;i<=height;i++){
        for(j=0;j<=width;j++){
            if(i==0 || i==height || j==0 || j==width){
                grid[i][j]='*';
            }
            else{
                grid[i][j]=' ';
            }
        }
    }
    x=(width>>1);
    y=(height>>1);
    grid[x][y]='O';
    food();
}
void draw(){
    system("cls");
    int i,j;
    for(i=0;i<=height;i++){
        for(j=0;j<=width;j++){
            printf("%c",grid[i][j]);
        }
        printf("\n");
    }
}
int main(){
    setup();
    while(!gameEnd){
        input();
        draw();
        logic();
        Sleep(30);
        printf("Your score is %d",score);
    }
    return 0;
}
