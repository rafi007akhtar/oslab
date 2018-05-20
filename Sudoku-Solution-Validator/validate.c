/** Check if the solution to a Sudoku puzzle is valid or not using 11 threads:
 * One for all the rows
 * One for all the columns
 * Nine for each 3x3 subgrid
 */

#include "utility.h" // contains utility functions for this program

int results[11]; // 0 for rows, 1 for columns, 2 to 11 for subgrids

void *checkRows(void*);
void *checkCols(void*);
void *checkSubgrid(void*);

int main()
{
    int i, j, ch;

    printf("Enter 0 to proceed with the default board, or 1 to enter your own board: ");
    scanf("%d", &ch);
    if (ch == 1)
    {
        printf("Enter the solution:\n");

        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
                scanf("%d", &grid[i][j]);
        }
    }

    printf("\nThe board is:\n");
    showGrid();
    printf("\n");

    pthread_t rowT;
    pthread_t colT;
    pthread_t gridT[9];

    // check for rows
    pthread_create(&rowT, NULL, checkRows, &rowT);
    pthread_join(rowT, NULL);

    // check for columns
    pthread_create(&colT, NULL, checkCols, &colT);
    pthread_join(colT, NULL);

    // set the subgrids
    setSubgrids();
    
    // check for subgrids
    for (i = 0; i < 9; i++)
    {
        pthread_create(&gridT[i], NULL, checkSubgrid, &i);
        pthread_join(gridT[i], NULL);
    }

    // check for validity in the result array
    printf("\n");
    if (in_array(results, 0, 11))
            printf("The solution is an invalid one\n");
    else
        printf("The solution is a valid one\n");


    return 0;
}

void* checkRows(void *arg)
{
    /** Checks if each row contains all integers 1 through 9
     * Puts results[0] = 1 if yes
     * Puts results[0] = 0 otherwise
     */

    int i,j;
    int lval, uval;

    lval = 0; uval = 8; // boundaries of a row

    // pthread_t id = *((pthread_t *) arg);

    for (i = 0; i < 9; i++) // i value = row number
    {
        for (j = 1; j <= 9; j++) // j value = value to check if present
        {
            if (!in_row (lval, uval, j, i)) // check if j is present b/w grid[i][lval] and grid[i][uval]
            {
                printf("Row check failed since %d does not exist in row %d\n", j, i+1);
                results[0] = 0;
                pthread_exit(NULL);
            }
        }
    }

    printf("Row check passed\n");
    results[0] = 1;
    pthread_exit(NULL);

}

void *checkCols (void *arg)
{
    /** Checks if all columns contain all the integers 1 through 9
     * Puts results[1] = 1 if so
     * Puts results[1] = 0 otherwise
     */

    int i,j;
    int lval, uval;

    lval = 0; uval = 8; // boundaries of a column

    for (i = 0; i < 9; i++) // i value = row number
    {
        for (j = 1; j <= 9; j++) // j value = value to check if present
        {
            if (!in_col (lval, uval, j, i)) // check if j is present b/w grid[lval][i] and grid[uval][i]
            {
                printf("Column check failed since %d does not exist in column %d\n", j, i+1);
                results[1] = 0;
                pthread_exit(NULL);
            }
        }
    }

    printf("Column check passed\n");
    results[1] = 1;
    pthread_exit(NULL);
}

void *checkSubgrid (void *arg)
{
    int i, j;
    int gridNumber = *((int *)arg);
    int subgrid[9];
    switch (gridNumber) // get the subgrid from the grid number
    {
        case 0: 
            for (i = 0; i < 9; i++) subgrid[i] = sub1[i]; 
            break;
        case 1: 
            for (i = 0; i < 9; i++) subgrid[i] = sub2[i];
            break;
        case 2: 
            for (i = 0; i < 9; i++) subgrid[i] = sub3[i];
            break;
        case 3: 
            for (i = 0; i < 9; i++) subgrid[i] = sub4[i];
            break;
        case 4: 
            for (i = 0; i < 9; i++) subgrid[i] = sub5[i];
            break;
        case 5: 
            for (i = 0; i < 9; i++) subgrid[i] = sub6[i];
            break;
        case 6: 
            for (i = 0; i < 9; i++) subgrid[i] = sub7[i];
            break;
        case 7: 
            for (i = 0; i < 9; i++) subgrid[i] = sub8[i];
            break;
        case 8: 
            for (i = 0; i < 9; i++) subgrid[i] = sub9[i];
            break;
        default: 
            printf("There has been some error; program terminating\n");
            pthread_exit(NULL);
    }

    // check if all numbers 1 through 9 are present in the current subgrid
    for (i = 1; i <=9; i++)
    {
        // check if i (1..9) is present in subgrid
        if (! in_array(subgrid, i, 9))
        {
            printf("Failed for subgrid %d since %d is not present in it\n", gridNumber+1, i);
            results[gridNumber + 2] = 0;
            pthread_exit(NULL);
        }
    }
    printf("Passed for subgrid %d\n", gridNumber+1);
    results[gridNumber + 2] = 1;
    pthread_exit(NULL);
}
