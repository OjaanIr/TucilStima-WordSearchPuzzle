#include "wsp.h"

int main() {
    int rowPuzzle, totalWords;
    readFile(&rowPuzzle, &totalWords);
    solve(rowPuzzle, totalWords);
    return 0;
}