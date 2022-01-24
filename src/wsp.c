#include "wsp.h"

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
        char line[100], line2[40];
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
    int i, j, k, wordLength, comparison;
    int wordsDir[totalWords], listComparison[totalWords], listWordLength[totalWords];
    int listRow[totalWords], listCol[totalWords];
    int colPuzzle = strlen(puzzle[0]);
    clock_t start = clock();
    
    for (i = 0; i < totalWords; i++)
    {
        comparison = 0;
        for (j = 0; j < rowPuzzle; j++)
        {
            for (k = 0; k < colPuzzle; k++)
            {
                wordLength = strlen(word[i]);
                listWordLength[i] = wordLength;
                if (checkLength(j-wordLength+1, k)&& searchUp(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 1;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j-wordLength+1, k+wordLength-1) && searchUpRight(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 2;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j, k+wordLength-1) && searchRight(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 3;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j+wordLength-1, k+wordLength-1) && searchDownRight(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 4;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j+wordLength-1, k) && searchDown(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 5;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j+wordLength-1, k-wordLength+1) && searchDownLeft(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 6;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j, k-wordLength+1) && searchLeft(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 7;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }
                else if (checkLength(j-wordLength+1, k-wordLength+1) && searchUpLeft(j,k,wordLength,i,&comparison))
                {
                    wordsDir[i] = 8;
                    listRow[i] = j;
                    listCol[i] = k;
                    listComparison[i] = comparison;
                }   
            }
        }
    }
    clock_t end = clock();
    double seconds = ((double) end - start)/CLOCKS_PER_SEC;
    double ms = 1000 * seconds;

    for (i = 0; i < totalWords; i++) 
    {
        printf("\n");
        if (wordsDir[i] == 1) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionUp(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 2) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionUpRight(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 3) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionRight(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 4) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionDownRight(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 5) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionDown(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 6) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionDownLeft(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 7) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionLeft(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
        else if (wordsDir[i] == 8) {
            printf("%d. %s - %d comparisons \n", i+1, word[i], listComparison[i]);
            displaySolutionUpLeft(rowPuzzle, listRow[i], listCol[i], listWordLength[i]);
        }
    }

    printf("\nTime elapsed = %f s or %f ms\n", seconds, ms);
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
        *comparison += 1;
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
        *comparison += 1;
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
        *comparison += 1;
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
        *comparison += 1;
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
        *comparison += 1;
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
        *comparison += 1;
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
        *comparison += 1;
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
        *comparison += 1;
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