#include "wsp.h"

int main() {
    int rowPuzzle, totalWords;
    readFile(&rowPuzzle, &totalWords);
    solve(rowPuzzle, totalWords);
    return 0;
}

void readFile(int *rowPuzzle, int *totalWords) {
    FILE *file; 
    char fileName[20];
    printf("Input file name (../test/namafile.txt): ");
    scanf("%s", fileName);
    file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Error in opening file!!!\n");
        exit(1);
    }
    else {
        char line[40], line2[40];
        int i, rows=0, cols;

        do
        {
            fgets(line,sizeof(line),file);
            cols = 0;
            for (i = 0; i < strlen(line)-1; i++)
            {
                if (line[i] != 32)
                {
                    puzzle[rows][cols] = line[i];
                    cols++;
                }
            }
            rows++;
        } while (puzzle[rows-1][0] != 0);
        *rowPuzzle = rows-1;

        rows = 0;
        while (!feof(file))
        {
            fgets(line2, sizeof(line2), file);
            for (i = 0; i < strlen(line2)-1; i++)
            {
                word[rows][i] = line2[i];
            }
            rows++;
        }
        word[rows-1][strlen(line2)-1] = line2[strlen(line2)-1];
            
        *totalWords = rows;
    }
}

void solve(int rowPuzzle, int totalWords) {
    int i, j, k;
    int wordLength, comparison = 0;
    int colPuzzle = strlen(puzzle[0]);
    clock_t time = clock();
    for (i = 0; i < totalWords; i++)
    {
        printf("\n");
        for (j = 0; j < rowPuzzle; j++)
        {
            for (k = 0; k < colPuzzle; k++)
            {
                wordLength = strlen(word[i]);
                if (checkLength(j-wordLength+1, k)&& searchUp(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionUp(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j-wordLength+1, k+wordLength-1) && searchUpRight(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionUpRight(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j, k+wordLength-1) && searchRight(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionRight(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j+wordLength-1, k+wordLength-1) && searchDownRight(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionDownRight(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j+wordLength-1, k) && searchDown(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionDown(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j+wordLength-1, k-wordLength+1) && searchDownLeft(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionDownLeft(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j, k-wordLength+1) && searchLeft(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionLeft(rowPuzzle, j, k, wordLength);
                }
                else if (checkLength(j-wordLength+1, k-wordLength+1) && searchUpLeft(j,k,wordLength,i,&comparison))
                {
                    printf("%d. %s\n", i+1, word[i]);
                    displaySolutionUpLeft(rowPuzzle, j, k, wordLength);
                }   
            }
        }
    }
    time = clock() - time;
    double time_elapsed = ((double) time)/CLOCKS_PER_SEC;
    printf("\nTime elapsed = %.3f seconds\n", time_elapsed);
}

int checkLength(int row, int col) {
    if (puzzle[row][col] != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int searchUp(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            row--;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchUpRight(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            row--;
            col++;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchRight(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            col++;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchDownRight(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            row++;
            col++;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchDown(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            row++;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchDownLeft(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            row++;
            col--;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchLeft(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            col--;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

int searchUpLeft(int row, int col, int wordLength, int x, int *comparison) {
    int match = 1;
    int i = 0;
    while (wordLength != 0 && match == 1)
    {
        if (puzzle[row][col] == word[x][i])
        {
            row--;
            col--;
            i++;
        }
        else
        {
            match = 0;
        }
        *comparison++;
        wordLength--;
    }
    return match;
}

void displaySolutionUp(int rowPuzzle, int row, int col, int wordLength) {
    int upLimit = row-wordLength+1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i >= upLimit && i <= row && j == col)
            {
                printf("%c ", puzzle[i][j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionUpRight(int rowPuzzle, int row, int col, int wordLength) {
    int x = 0;
    int upLimit = row-wordLength+1;
    int rightLimit = col+wordLength-1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i == upLimit+x && i <= row && j >= col && j == rightLimit-x)
            {
                printf("%c ", puzzle[i][j]);
                x++;
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionRight(int rowPuzzle, int row, int col, int wordLength) {
    int rightLimit = col+wordLength-1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i == row && j >= col && j <= rightLimit)
            {
                printf("%c ", puzzle[i][j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionDownRight(int rowPuzzle, int row, int col, int wordLength) {
    int x = 0;
    int lowLimit = row+wordLength-1;
    int rightLimit = col+wordLength-1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i == row+x && i <= lowLimit && j == col+x && j <= rightLimit)
            {
                printf("%c ", puzzle[i][j]);
                x++;
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionDown(int rowPuzzle, int row, int col, int wordLength) {
    int lowLimit = row+wordLength-1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i >= row && i <= lowLimit && j == col)
            {
                printf("%c ", puzzle[i][j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionDownLeft(int rowPuzzle, int row, int col, int wordLength) {
    int x = 0;
    int lowLimit = row+wordLength-1;
    int leftLimit = col-wordLength+1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i == row+x && i <= lowLimit && j >= leftLimit && j == col-x)
            {
                printf("%c ", puzzle[i][j]);
                x++;
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionLeft(int rowPuzzle, int row, int col, int wordLength) {
    int leftLimit = col-wordLength+1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i == row && j >= leftLimit && j <= col)
            {
                printf("%c ", puzzle[i][j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void displaySolutionUpLeft(int rowPuzzle, int row, int col, int wordLength) {
    int x = 0;
    int upLimit = row-wordLength+1;
    int leftLimit = col-wordLength+1;
    int colPuzzle = strlen(puzzle[0]);
    for (int i = 0; i < rowPuzzle; i++)
    {
        for (int j = 0; j < colPuzzle; j++)
        {
            if (i == upLimit+x && i <= row && j == leftLimit+x && j <= col)
            {
                printf("%c ", puzzle[i][j]);
                x++;
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

// TODO: tambah comparison, laporan, dan readme