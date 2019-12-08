/*
 *  Program to find shortest path in between two indices in a matrix using DFS(Depth First Search) Algorithm.
 *  In the matrix 'x' represents the index which is not allowed to pass through or traverse, whereas '1' represents the
    indices which are allowed to visit and traverse.
 *  And 's', 'g' represents start and end points.
 *  Path is printed in the reverse order. i.e. from 'g' to 's' (without the index of 's').
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ROW 5
#define COL 5
#define TOTAL ROW*COL

struct coord{
    int x;
    int y;
    struct coord *next;
};

struct coord *push(struct coord *points, int r, int c){
    struct coord *newnode = (struct coord*)malloc(sizeof(struct coord));
    newnode->x = r;
    newnode->y = c;
    if(points == NULL){
        points = newnode;
        points->next = NULL;
        return points;   
    }
    newnode->next = points;
    return newnode;
}

struct coord *pop(struct coord *points){
    struct coord *temp;
    if(points == NULL){
        return NULL;
    }
    temp = points;
    points = points->next;
    free(temp);
    return points;
}

int display(struct coord *points){
    int count=0;
    struct coord *temp;
    if(points == NULL){
        return 0;
    }
    temp = points;
    while(temp != NULL){
        printf("Points : [%d][%d]\n", temp->x, temp->y);
        temp = temp->next;
        ++count;
    }
    printf("\n");
    return count;
}

struct coord *replace(struct coord *new, struct coord *old){
    struct coord *told = old;
    struct coord *tnew = new;
    struct coord *temp;

    while(tnew != NULL){
        if(old == NULL){
            struct coord *newnode = (struct coord*)malloc(sizeof(struct coord));
            newnode->x = tnew->x;
            newnode->y = tnew->y;
            newnode->next = NULL;
            temp = told = old = newnode;
        }else{
            if(told == NULL){
                struct coord *newnode = (struct coord*)malloc(sizeof(struct coord));
                newnode->x = tnew->x;
                newnode->y = tnew->y;
                newnode->next = NULL;
                temp->next = newnode;
                told = temp = newnode;
            }else{
                told->x = tnew->x;
                told->y = tnew->y;
                temp = told;
            }
        }
        told = told->next;
        tnew = tnew->next;
    }
    if(temp->next != NULL){
        temp->next = NULL;
    }
    while(told != NULL){
        temp = told;
        told = told->next;
        free(temp);
    }
    
    return old;
}

struct coord *check(char map[ROW][COL], char done[ROW][COL], int crow, int ccol, int count){ 
    static unsigned int short_path;
    static struct coord *points;
    static struct coord *short_nodes = NULL;

    char visited[ROW][COL];

    if(map[crow][ccol] == 'g'){
        if(count < short_path || short_path == 0){
            short_path = count;
            short_nodes = replace(points, short_nodes);
        }
        return short_nodes;
    }else{
        //printf("Position now : [%d] [%d]\n", crow, ccol);
        done[crow][ccol] = '1';
        memcpy(visited, done, TOTAL); //TOTAL * 1 bytes

        //up
        if(crow - 1 >=0){
            if(map[crow-1][ccol] != 'x' && visited[crow-1][ccol] == '0'){
                points = push(points, crow-1, ccol);
                check(map, visited, crow-1, ccol, count+1);
                points = pop(points);
                //printf("Back at [%d] [%d]\n", crow, ccol);
            }
        }
        //right
        if(ccol+1 <= COL-1){
            if(map[crow][ccol+1] != 'x' && visited[crow][ccol+1] == '0'){
                points = push(points, crow, ccol+1);
                check(map, visited, crow, ccol+1, count+1);
                points = pop(points);
                //printf("Back at [%d] [%d]\n", crow, ccol);
            }
        }
        //bottom
        if(crow+1 <= ROW-1){
            if(map[crow+1][ccol] != 'x' && visited[crow+1][ccol] == '0'){
                points = push(points, crow+1, ccol);
                check(map, visited, crow+1, ccol, count+1);
                points = pop(points);
                //printf("Back at [%d] [%d]\n", crow, ccol);
            }
        }
        //left
        if(ccol-1 >= 0){
            if(map[crow][ccol-1] != 'x' && visited[crow][ccol-1] == '0'){
                points = push(points, crow, ccol-1);
                check(map, visited, crow, ccol-1, count+1);
                points = pop(points);
                //printf("Back at [%d] [%d]\n", crow, ccol);
            }
        }
        return short_nodes;
    }
}

int main(){
    int i, j, st_row, st_col, len;
    struct coord *short_path;
    char map[ROW][COL] = {
                            {'1', '1', '1', '1', '1'},
                            {'1', 'x', 'x', '1', 'g'},
                            {'1', '1', 'x', '1', '1'},
                            {'x', 'x', '1', '1', 'x'},
                            {'1', 'x', '1', '1', 's'}
                         };
    char done[ROW][COL];

    //initializing the matrix with character zero.
    memset(done, '0', TOTAL);

    //finding the starting position.
    for(i=0; i<ROW; i++){
        for(j=0; j<COL;j++){
            if(map[i][j] == 's'){
                st_row = i;
                st_col = j;
                done[i][j] = '1';
                break;
            }
        }
    }

    short_path = check(map, done, st_row, st_col, 0);
    len = display(short_path);
    if (len > 0){
        printf("Shortest path in %d steps\n", len);
    }else{
        printf("No path exists\n");
    }
    return 0;
}
