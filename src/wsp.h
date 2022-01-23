#ifndef WSP_H
#define WSP_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char word[30][30];
char puzzle[40][40];

void readFile(int *rowPuzzle, int *totalWords);
/* Membaca file puzzle*/
void solve(int totalWords);
/* Menyelesaikan word search puzzle */
int checkLength(int row, int col);
/* Cek apakah panjang kata cukup di puzzle */
int searchUp(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke atas */
int searchUpRight(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke kanan atas */
int searchRight(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke kanan */
int searchDownRight(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke kanan bawah */
int searchDown(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke bawah */
int searchDownLeft(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke kiri bawah */
int searchLeft(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke kiri */
int searchUpLeft(int row, int col, int wordLength, int x, char word, int *comparison);
/* String matching ke kiri atas */
void displaySolution();
/* Menampilkan solusi */


#endif 