#ifndef WSP_H
#define WSP_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char word[2000][30];
char puzzle[40][40];

/* Membaca file puzzle*/
void readFile(int *rowPuzzle, int *totalWords);
/* Menyelesaikan word search puzzle */
void solve(int rowPuzzle, int totalWords);
/* Cek apakah panjang kata cukup di puzzle */
int checkLength(int row, int col);
/* String matching ke atas */
int searchUp(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke kanan atas */
int searchUpRight(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke kanan */
int searchRight(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke kanan bawah */
int searchDownRight(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke bawah */
int searchDown(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke kiri bawah */
int searchDownLeft(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke kiri */
int searchLeft(int row, int col, int wordLength, int x, int *comparison);
/* String matching ke kiri atas */
int searchUpLeft(int row, int col, int wordLength, int x, int *comparison);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke atas)*/
void displaySolutionUp(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke atas kanan)*/
void displaySolutionUpRight(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke kanan)*/
void displaySolutionRight(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke bawah kanan)*/
void displaySolutionDownRight(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke bawah)*/
void displaySolutionDown(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke bawah kiri)*/
void displaySolutionDownLeft(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke kiri)*/
void displaySolutionLeft(int rowPuzzle, int row, int col, int wordLength);
/* Menampilkan solusi (kata berada di puzzle dengan posisi ke atas kiri)*/
void displaySolutionUpLeft(int rowPuzzle, int row, int col, int wordLength);

#endif 