/* Do not make any changes in the skeleton. Your submission will be invalidated if the skeleton is changed */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 36
int grida[N][N];
int flag = 0 ; 

typedef struct {
            int row;
            int col;    
            int size; 
            int num ;
            int final; 
            int runner ; 
            int grid[N][N];    
}mystruct;

void read_grid_from_file(int size, char *ip_file, int grid[N][N]) {
	FILE *fp;
	int i, j;
	fp = fopen(ip_file, "r");
	for (i=0; i<size; i++) 
		for (j=0; j<size; j++) {
			fscanf(fp, "%d", &grid[i][j]);
	}
} 

void print_grid(int size, int grid[N][N]) {
	int i, j;
	/* The segment below prints the grid in a standard format. Do not change */
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++)
			printf("%d\t", grid[i][j]);
		printf("\n");
	}
}

int check(int grid[N][N],int size){
    int check = 0;
    for(int i = 0 ; i < size ; i++)
    for(int j = 0 ; j < size; j++)
    if(grid[i][j] == 0)
    check++; 
    return check ; 

}


int isValid(int grid[N][N], int row,int col, int num,int size)
{
    for (int x = 0; x <= size-1; x++)
        if (grid[row][x] == num)
            return 0;
 
   
    for (int x = 0; x <= size-1; x++)
        if (grid[x][col] == num)
            return 0;
    int s = sqrt(size);
   
    int startRow = row - row %s ,
                 startCol = col - col % s ; 
   
    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++)
            if (grid[i + startRow][j +
                          startCol] == num)
                return 0;
 
    return 1;
}


void *solvei(void* val)
{   
    mystruct *sx= (mystruct*) val;
    int row = sx->row; 
    int col = sx->col; 
    int size = sx->size;
    int num = sx->num;
    int final = sx->final; 
    int runner = sx->runner; 
    int grid[N][N];
    for( int k = 0 ; k < size; k++)
    for(int j = 0 ; j < size; j++)
        grid[k][j] =  sx->grid[k][j] ;


    table:
    
     if(check(grid,size) == 0)
        {   for(int i = 0 ; i < size ; i++)
            for(int j = 0 ; j < size ; j++)
            grida[i][j] = grid[i][j]; 
            //print_grid(size,grid);
             //printf("\n");
            //printf(".........................completed\n");
            flag = 1;
            pthread_exit(NULL);

        }

    if(row >= size)
        {//printf(".......................completed\n");
        flag = 1;
        }

    if (col >= size)
        {
         row++;
         col = 0;
        // printf("%d%d Row Incimented\n",row,col);
        }
     

     if(grid[row][col] != 0){
        col = col+1;
        //printf("%d%d Occupied Col Updated\n" ,row,col); 
        goto table;
    }
   
        


    
    
    if(flag == 0 && grid[row][col] == 0 && row < size && col < size )
    {

    //printf("Row %d Col %d\n", row,col);
         //print_grid(size,grid);
    //printf("\n");

    
    mystruct s[N]; 
    pthread_t pid[N] ={0};
   
    


    
    int e = 0;
                                             


for(int k = 1 ; k <= size; k++){

    int y = isValid(grid,  row, col,  k, size) ;
    if(y == 1)
      {  
             
        s[e].row = row; 
        s[e].col = col+1; 
        s[e].size = size;
        s[e].num = num ;
        s[e].final = 1;
        s[e].grid;
        s[e].runner = runner ;
         for( int k = 0 ; k < size; k++)
        for(int j = 0 ; j < size; j++)
        s[e].grid[k][j] =  grid[k][j] ;

        s[e].grid[row][col] = k;
        pthread_create(&pid[e],NULL,solvei,(void*)&s[e]);
         e++; 
        
    }  
    
    }
    for(int i = 0 ; i < e ; i++)
    pthread_join(pid[i],NULL);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

  int grid[36][36], size, i, j;
	
	if (argc != 3) {
		printf("Usage: ./sudoku.out grid_size inputfile");
		exit(-1);
	}
	
	size = atoi(argv[1]);
 
    

	read_grid_from_file(size, argv[2], grid);         
    pthread_t tid = 1;
    mystruct ss;
    ss.row = 0; 
    ss.col = 0; 
    ss.size = size;
    ss.num = 1;
    ss.grid;
    ss.final = 0; 
    ss.runner = 0 ;
    for( int k = 0 ; k < size; k++)
    for(int j = 0 ; j < size; j++)
        ss.grid[k][j] =  grid[k][j] ;

  
    pthread_create(&tid, NULL,solvei, &ss) ; 
    pthread_join(tid,NULL);
    if(flag ==1){
    print_grid(size,grida);}
    if(flag == 0)
    printf("No solution");	

return 0 ; 
}   
