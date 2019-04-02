/* Author: Amir David
 * CS2263 - assignment 4, Programming in C
 * This program takes two command line arguments as row and column input and creates a row*coloumn grid with random values of 1's and 0's.
 * The program then continuously asks for i and j coordinates and returns the size of the 'blob' (1's connected horizontally, vertically or diagonally) in the  * grid. When a non-integer is entered, the program halts.
 */
#include "CountingPixels.h"

int main(int argc, char *argv[]){
	if(argc!=3){
		printf("Please enter two coordinates");
	}
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);
	
	int *a;
	a = malloc((row*col)*sizeof(int));
	
	srand(time(NULL)); //populate array with random values
	int i, j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			a[i*col+j] = rand()%2;
			printf("%d ",a[i*col+j]); 
		}
		printf("\n");
	}
	
	printf("enter coordinates i,j (non-numeric to quit): ");
	int val1, val2;
	while(scanf("%d,%d", &val1, &val2)==2){
		//check to see if coordinates are out of bounds
		if( ((val1>=row) || (val2>=col)) || ((val1<0) || (val2<0)) ){
			printf("invalid coordinates\n");
		}else{
			int blob = count(a, val1, val2, row, col);
			double percentage = ((double)blob / (double)(row*col))*100;
			printf("Blob size : %d (%0.1f %% of all 1's)\n", blob, percentage);

			//unmark the "marked" elements
			for(i=0; i<row*col; i++){
				if(a[i] == 2){
					a[i] = 1;
				}
			}
		}
		printf("enter coordinates i,j (non-numeric to quit): ");
	}
	//free memeory location at a
	free(a);
	return 0;
} //end of main function

//recursive function for determining blob

int count(int *a, int i, int j, int row, int col){
	int counter = 0;
	if( ((i>=row) || (j>=col)) || ((i<0) || (j<0)) ){
			return 0;
	}
	//check to see if the square at i,j is marked 0
	if(a[i*col+j]==0){
		return 0;
	}
	//check if the square was already check, ie. if the square is marked 2
	if(a[i*col+j]==2){
		return 0;
	}
	/*if all other tests failed, it means that the current square is marked with 1.
	*mark the current square with 2, and increment counter by calling the function with coordinates for the 8 neighbors
	*/
	if(a[i*col+j]==1){
		a[i*col+j]=2; //mark the element
		counter += 1 
			+ count(a, i+1, j, row, col) 
			+ count(a, i, j+1, row, col) 
			+ count(a, i+1, j+1, row, col) 
			+ count(a, i-1, j, row, col) 
			+ count(a, i, j-1, row, col) 
			+ count(a, i-1, j-1, row, col) 
			+ count(a, i+1, j-1, row, col) 
			+ count(a, i-1, j+1, row, col);
	}

	return counter;
} //end of count function


