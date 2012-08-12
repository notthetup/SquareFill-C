#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

const int max_iterations_multiplier = 5;


int generate_latin_square(int, int**);
int generate_latin_row(int*dim, int** c_unused, int* next_row);
int* array_intersect(int* array1, int* array2, int* dim);
int array_length(int* array, int *dim);
void print2Darray(int** array, int *dim);
void print1Darray(int* array, int* dim);

int main(int argc, char** argv){
	//print2Darray(generate_latin_square(atoi(argv[1])), atoi(argv[1]));
	int t = 6;
	int err = 0;

	int ** l_square = (int**)malloc(sizeof(int *)*t);

	srand((unsigned int)time(NULL));

	err = generate_latin_square(t, l_square);

	if (err == 0)
		print2Darray(l_square, &t);
	else
		printf("BooHoo\n");
	
	//printf("Time = %d\n",(int)time(NULL));
	return 0;	
}



int generate_latin_square(int dim, int** l_square)
{
	int row_index, col_index, total_iterations, err;
	int max_total_iterations = max_iterations_multiplier * dim;

	if(dim < 2)
	{
		dim = 2;
	}

	int *next_row = (int*)malloc(sizeof(int)*dim);
	int ** c_unused = (int**)malloc(sizeof(int *)*dim);
	
	for(row_index = 0 ; row_index < dim; row_index++)
	{
		l_square[row_index] = (int*)malloc(sizeof(int)*dim);
		c_unused[row_index] = (int*)malloc(sizeof(int)*dim);

		for(col_index = 0 ; col_index < dim; col_index++)
		{
			c_unused[row_index][col_index] = col_index+1;
		}
	}

	for(row_index = 0 ; row_index < dim; row_index++)
	{
		err = -1;
		total_iterations = 0;

		while(err != 0 && total_iterations < max_total_iterations)
		{
			err = generate_latin_row(&dim,c_unused, next_row);
			total_iterations++;
		}

		if(err != 0)
		{
			return -1;
		}

		memcpy(l_square[row_index],next_row,sizeof(int)*dim);
	}

	for(row_index = 0 ; row_index < dim; row_index++)
	{
		free(c_unused[row_index]);
	}
	free(c_unused);

	return 0;
}



int generate_latin_row(int*dim, int** c_unused, int* next_row)
{
	int* row_unused = (int*)malloc(sizeof(int)* *dim);
	int col_index = 0, allowed_range_length = 0;
	int* allowed_range;
	int rand_index;

	for(col_index = 0 ; col_index < *dim; col_index++)
	{
		row_unused[col_index] = col_index + 1;
	}

	for(col_index = 0 ; col_index < *dim; col_index++)
	{
		allowed_range = array_intersect(c_unused[col_index], row_unused, dim);
		allowed_range_length = array_length(allowed_range, dim);
		if (allowed_range_length < 1)
		{
			printf("None Left!! - Trying Again ------- \n");
			return -1;
		}

		rand_index = rand() % allowed_range_length;
		next_row[col_index] = allowed_range[rand_index];
		row_unused[allowed_range[rand_index]-1] = 0;
	}

	for(col_index = 0 ; col_index < *dim; col_index++)
	{
		c_unused[col_index][next_row[col_index]-1] = 0;
	}
	return 0;
}

int* array_intersect(int* array1, int* array2, int* dim)
{
	int col_index = 0, col_index2, ret_col_index = 0;
	int * return_array = malloc(sizeof(int) * *dim);

	for(col_index = 0 ; col_index < *dim; col_index++)
	{	
		return_array[col_index] = 0;

		if(array1[col_index] == 0)
		{
			continue;
		}
		for(col_index2 = 0 ; (col_index2 < *dim) && (array1[col_index] != array2[col_index2]); col_index2++);

		if(col_index2 != *dim)
		{
			return_array[ret_col_index] = array2[col_index2];
			ret_col_index++;
		}
	}
	return return_array;
}

int array_length(int* array, int* dim)
{
	int array_index, count = 0;
	for(array_index = 0 ; array_index < *dim; array_index++)
	{
		if(array[array_index] != 0)
			count++;
	}
	return count;
}

void print2Darray(int** array, int *dim)
{
	int array_index;

	for(array_index = 0; array_index < *dim; array_index++)
	{
		print1Darray(array[array_index], dim);
	}
}

void print1Darray(int* array, int* dim)
{
	int array_index;
	for(array_index = 0; array_index < *dim; array_index++)
	{
		printf("%d ", array[array_index]);
	}
	printf("\n");
}

