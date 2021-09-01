#include <stdio.h>
#include <stdlib.h>

#define UP 0
#define DOWN 2
#define RIGHT 1
#define LEFT 3

typedef struct{
    int l,r;
} position;

typedef struct{
    position p;
    int dir;
} move;

int max_depth=0, solved=0;

move moves[100];

position forward(position p, int dir){
    position pr;
    switch(dir){
    case UP:
        pr.l=p.l-1;
        pr.r=p.r;
        return pr;
    case DOWN:
        pr.l=p.l+1;
        pr.r=p.r;
        return pr;
    case RIGHT:
        pr.l=p.l;
        pr.r=p.r+1;
        return pr;
    case LEFT:
        pr.l=p.l;
        pr.r=p.r-1;
        return pr;
    }
}

position left(position p, int dir){
    position pr;
    switch(dir){
    case UP:
        pr.l=p.l;
        pr.r=p.r-1;
        return pr;
    case DOWN:
        pr.l=p.l;
        pr.r=p.r+1;
        return pr;
    case RIGHT:
        pr.l=p.l-1;
        pr.r=p.r;
        return pr;
    case LEFT:
        pr.l=p.l+1;
        pr.r=p.r;
        return pr;
    }
}

position right(position p, int dir){
    position pr;
    switch(dir){
    case UP:
        pr.l=p.l;
        pr.r=p.r+1;
        return pr;
    case DOWN:
        pr.l=p.l;
        pr.r=p.r-1;
        return pr;
    case RIGHT:
        pr.l=p.l+1;
        pr.r=p.r;
        return pr;
    case LEFT:
        pr.l=p.l-1;
        pr.r=p.r;
        return pr;
    }
}

int rotateRight(int dir){
    int directions[] = {UP, RIGHT, DOWN, LEFT};
    return directions[(dir+1)%4];
}

int rotateLeft(int dir){
    int directions[] = {UP, RIGHT, DOWN, LEFT};
    return directions[(dir+3)%4];
}

int isSolved(char maze[10][10], position p){
    return maze[p.l][p.r]=='*';
}

void solveMaze(char maze[10][10], position p, int dir, int depth){
    if(isSolved(maze, p)){
        solved=1;
        /*printf("Depth: %d\n", depth);
        printf("max_depth: %d\n", max_depth);
        printCurrentState(maze, p, dir);*/
        max_depth=depth;
        return;
    }
    position futPos;
    move mv;
    if(!solved){
        futPos=forward(p, dir);
        if(maze[futPos.l][futPos.r]==' ' || maze[futPos.l][futPos.r]=='*'){
            mv.p=futPos;
            mv.dir=dir;
            moves[depth]=mv;
            solveMaze(maze, futPos, dir, depth+1);
        }
    }
    if(!solved){
        futPos=right(p, dir);
        if(maze[futPos.l][futPos.r]==' ' || maze[futPos.l][futPos.r]=='*'){
            mv.p=futPos;
            mv.dir=rotateRight(dir);
            moves[depth]=mv;
            solveMaze(maze, futPos, rotateRight(dir), depth+1);
        }
    }

    if(!solved){
        futPos=left(p, dir);
        if(maze[futPos.l][futPos.r]==' ' || maze[futPos.l][futPos.r]=='*'){
            mv.p=futPos;
            mv.dir=rotateLeft(dir);
            moves[depth]=mv;
            solveMaze(maze, futPos, rotateLeft(dir), depth+1);
        }
    }

}

void printCurrentState(char maze[10][10], position p, int dir){
    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            if(i==p.l && k==p.r){
                switch(dir){
                case UP:
                    printf("^ ");
                    break;
                case DOWN:
                    printf("v ");
                    break;
                case LEFT:
                    printf("< ");
                    break;
                case RIGHT:
                    printf("> ");
                    break;
                }
            }
            else printf("%c ", maze[i][k]);
        }
        printf("\n");
    }
}

int main()
{
    char maze[10][10]=
    {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#',' ',' ','#',' ',' ',' ','#',' ','#'},
        {'#',' ','#',' ',' ','#',' ',' ',' ','#'},
        {'#',' ','#',' ','#','#','#','#','#','#'},
        {'#',' ','#',' ',' ',' ',' ',' ',' ','#'},
        {'#',' ','#','#','#','#','#','#',' ','#'},
        {'#',' ','#','*',' ',' ',' ','#',' ','#'},
        {'#',' ','#','#','#',' ','#','#',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };
    position p;
    p.l=1;
    p.r=8;
    int dir=DOWN;
    solveMaze(maze, p, dir, 0);
    printCurrentState(maze, p, dir);
    for(int i=0; i<max_depth; i++){
        printCurrentState(maze, moves[i].p, moves[i].dir);
    }

    return 0;
}
