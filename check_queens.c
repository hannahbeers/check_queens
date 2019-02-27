////////////////////////////////////////////////////////////////////////////////
// Main File:        check_queens.c
// This File:        check_queens.c
// Other Files:      check1.txt, check2.txt, check3.txt, check4.txt
// Semester:         CS 354 SPRING 2019
//
// Author:           Hannah Beers
// Email:            hbeers@wisc.edu
// CS Login:         beers
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
// Online sources:   None
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *COMMA = ",";

/* Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 *
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, fp) == -1) {
                printf("Error in reading the file\n");
                exit(1);
        }

        char *token = NULL;
        token = strtok(line, COMMA);
        *rows = atoi(token);

        token = strtok(NULL, COMMA);
        *cols = atoi(token);
}


/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 *
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {

    //check if there is at least one queen in the board
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (*(*(board + i) + j) == 1) {

                //check right side of queen for another queen
                for(int x = j + 1; x < cols; x++) {
                    if(*(*(board + i) + x) == 1) {
                        return 1;
                    }
                }

                //check left side of queen for another queen
                for(int x = j - 1; x >= 0; x--) {
                    if(*(*(board + i) + x) == 1) {
                        return 1;
                    }
                }

                //check above queen for another queen
                for(int x = i - 1; x >= 0; x--) {
                    if(*(*(board + x) + j) == 1) {
                        return 1;
                    }
                }

                //check below queen for another queen
                for(int x = i + 1; x < rows; x++) {
                    if(*(*(board + x) + j) == 1) {
                        return 1;
                    }
                }

                //check left down diagonal of queen for another queen
                for(int x = i + 1, y = j - 1;  x < rows && y >= 0; x++, y--) {
                    if(*(*(board + x) + y) == 1) {
                        return 1;
                    }
                }

                //check left up diagonal of queen for another queen
                for(int x = i - 1, y = j - 1; x >= 0 && y >= 0; x--, y--) {
                    if(*(*(board + x) + y) == 1) {
                        return 1;
                    }
                }

                //check right down diagonal of queen for another queen
                for(int x = i + 1, y = j + 1;  x < rows && y < cols; x++, y++) {
                    if(*(*(board + x) + y) == 1) {
                        return 1;
                    }
                }

                //check right up diagonal of queen for another queen
                for(int x = i - 1, y = j + 1;  x >= 0 && y < cols; x--, y++) {
                    if(*(*(board + x) + y) == 1) {
                        return 1;
                    }
                }
        }
    }
    }
	    return 0;

}


/* This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 *
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {

        //Check if number of command-line arguments is correct.
        if (argc != 2) {
            printf("Incorrect number of command-line arguments\n");
            exit(1);
        }


        //Open the file and check if it opened successfully.
        FILE *fp = fopen(*(argv + 1), "r");
        if (fp == NULL) {
                printf("Cannot open file for reading\n");
                exit(1);
        }


        //Declare local variables.
        //int rows - number of rows in board
        //int cols - number of cols in board
        int rows, cols;


        //Call get_dimensions to retrieve the board dimensions.
	    get_dimensions(fp, &rows, &cols);

        //Dynamically allocate a 2D array of dimensions retrieved above named board
        int **board = (int **)malloc(rows * sizeof(int *));
        for(int i = 0; i < rows; i++) {
            *(board + i) = (int *)malloc(cols * sizeof(int));
        }

        //Read the file line by line.
        //Tokenize each line wrt comma to store the values in your 2D array.
        char *line = NULL;
        size_t len = 0;
        char *token = NULL;
        for (int i = 0; i < rows; i++) {

                if (getline(&line, &len, fp) == -1) {
                        printf("Error while reading the file\n");
                        exit(1);
                }

                token = strtok(line, COMMA);

                //Initialize your 2D array.
                 for(int j = 0; j < cols; j++) {
                     *(*(board + i) + j) = 0;
                 }

                for(int j = 0; j < cols; j++) {
                    *(*(board + i) + j) = atoi(token);
                    token = strtok(NULL, COMMA);
                }
        }

        //Call the function check_queens and print the appropriate
        //output depending on the function's return value.
        if(check_queens(board, rows, cols) == 1) {
		    printf("true\n");
	    }
	    else {
		    printf("false\n");
	    }

        //Free all dynamically allocated memory.
        for (int i = 0; i < rows; i++) {
            free(*(board + i));
        }
        free(board);
        board = NULL;

        //Close the file.
        if (fclose(fp) != 0) {
                printf("Error while closing the file\n");
                exit(1);
        }

        return 0;
}
