#include "wsp.h"

int main() {
    int rowPuzzle, totalWords;
    readFile(&rowPuzzle, &totalWords);
    solve(totalWords);
    return 0;
}

void readFile(int *rowPuzzle, int *totalWords) {
    FILE *file; 
    file = fopen("../test/test.txt", "r");

    if (file == NULL)
    {
        printf("Error in opening file!!!\n");
    }
    else {
        char line[40], line2[40];
        int i, rows=0, cols;

        do
        {
            fgets(line,sizeof(line),file);
            for (i = 0; i < strlen(line)-1; i++)
            {
                if (line[i] != 32)
                {
                    puzzle[rows][i] = line[i];
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
        *totalWords = rows;
    }
}

void solve(int totalWords) {
    int i, j, k;
    int wordLength, comparison = 0;
    clock_t time = clock();
    for (i = 0; i < totalWords; i++)
    {
        for (j = 0; j < 40; i++)
        {
            for (k = 0; k < 40; i++)
            {
                if (puzzle[i][j] == word[i][0])
                {
                    wordLength = strlen(word[i]);
                    if (checkLength(j-wordLength+1, k) == 1 && searchUp(j,k,wordLength,i,word,&comparison) == 1)
                    {
                        displaySolution();
                    }
                    else if (checkLength(j-wordLength+1, k+wordLength-1) && searchUpRight(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }
                    else if (checkLength(j, k+wordLength-1) && searchRight(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }
                    else if (checkLength(j+wordLength-1, k+wordLength-1) && searchDownRight(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }
                    else if (checkLength(j+wordLength-1, k) && searchDown(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }
                    else if (checkLength(j-wordLength+1, k-wordLength+1) && searchDownLeft(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }
                    else if (checkLength(j, k-wordLength+1) && searchLeft(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }
                    else if (checkLength(j-wordLength+1, k-wordLength+1) && searchUpLeft(j,k,wordLength,i,word,&comparison))
                    {
                        displaySolution();
                    }   
                    else
                    {
                        printf("Word %s doesn't exist in the puzzle!!!\n", word[i]);
                    }
                }
            }
        }
    }
    time = clock() - time;
    double time_elapsed = ((double) time)/CLOCKS_PER_SEC;
    printf("Time elapsed = %.2f\n", time_elapsed);
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

int searchUp(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchUpRight(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchRight(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchDownRight(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchDown(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchDownLeft(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchLeft(int row, int col, int wordLength, int x, char word, int *comparison) {
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

int searchUpLeft(int row, int col, int wordLength, int x, char word, int *comparison) {
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

void displaySolution() {

}