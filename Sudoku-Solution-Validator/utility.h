// Ultility functions for validate.c

#include <stdio.h>
#include <pthread.h>

// bool datatype
typedef enum boolean {false, true} bool;

// GLOBAL VARIABLES
int grid[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6},
};
// subgrids
int sub1[9], sub2[9], sub3[9], sub4[9], sub5[9], sub6[9], sub7[9], sub8[9], sub9[9];


// UTILITY FUNCTIONS
void setSubgrids()
{    
    int rmin, cmin, rmax, cmax;
    rmin = cmin = 0;
    rmax = cmax = 2;

    int i, j, k = 0;

    // subgrid 1
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub1[k++] = grid[i][j];
        }
    }

    // subgrid 2
    cmin += 3;
    cmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub2[k++] = grid[i][j];
        }
    }

    // subgrid 3
    cmin += 3;
    cmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub3[k++] = grid[i][j];
        }
    }

    // subgrid 4
    cmin = 0; cmax = 2;
    rmin += 3; rmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub4[k++] = grid[i][j];
        }
    }

    // subgrid 5
    cmin += 3;
    cmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub5[k++] = grid[i][j];
        }
    }

    // subgrid 6
    cmin += 3;
    cmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub6[k++] = grid[i][j];
        }
    }

    // subgrid 7
    cmin = 0; cmax = 2;
    rmin += 3; rmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub7[k++] = grid[i][j];
        }
    }

    // subgrid 8
    cmin += 3;
    cmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub8[k++] = grid[i][j];
        }
    }

    // subgrid 9
    cmin += 3;
    cmax += 3;
    k = 0;
    for (i = rmin; i <= rmax; i++)
    {
        for (j = cmin; j <= cmax; j++)
        {
            sub9[k++] = grid[i][j];
        }
    }
}

void printSubgrid(int subgrid[])
{
    int i;
    for (i = 0; i < 9; i++) printf("%d ", subgrid[i]);
    printf("\n");
}

void showGrid()
{
    /** Print the 9x9 grid */
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}

bool in_row(int lval, int uval, int val, int row)
{
    // Return true if val exists b/w grid[row][lval] and grid[row][uval]; return false otherise
    int i, j;
    for (i = lval; i <= uval; i++)
        if (grid[row][i] == val) return true;

    return false;
}

bool in_col(int lval, int uval, int val, int col)
{
    // Return true if val exists b/w grid[lval][col] and grid[uval][col]; return false otherise
    int i, j;
    for (i = lval; i <= uval; i++)
    {
        if (grid[i][col] == val) return true;
    }
    return false;
}

bool in_array(int array[], int x, int len)
{
    // Return true if x is present in subgrid; return false otherwise
    int i; 
    for (i = 0; i < len; i++)
    {
        if (array[i] == x)
            return true;
    }
    return false;
}
