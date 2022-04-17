#include <stdio.h>
#include <stdlib.h>
#include "../../ArrayLib/src/ArrayLib.h"

int main() {
    printf("\nEnter table width: ");
    int tableWidth = 0;
    scanf("%d", &tableWidth);

    printf("Enter table height: ");
    int tableHeight = 0;
    scanf("%d", &tableHeight);

    //Use as chiTable[y][x]
    //Reminder *(array + 1) = array[1] = array item 2
    int** chiTable = malloc((tableHeight + 1) * sizeof(*chiTable));
    for (int i = 0; i < (tableHeight + 1); i++) {
        chiTable[i] = malloc((tableWidth + 1) * sizeof(**chiTable));
    }

    printf("\n");
    for (int i = 0; i < tableHeight; i++) {
        for (int j = 0; j < tableWidth; j++) {
            printf("Enter data for[%d][%d]: ", i, j);
            scanf("%d", &chiTable[i][j]);
        }
    }

    int freedom = (tableWidth - 1) * (tableHeight - 1);

    for (int i = 0; i < tableHeight; i++) {
        chiTable[i][tableWidth + 1] = 0;
        for (int j = 0; j < tableWidth; j++) {
            chiTable[i][tableWidth + 1] += chiTable[i][j];
        }
    }
    for (int i = 0; i < tableWidth; i++) {
        chiTable[tableHeight + 1][i] = 0;
        for (int j = 0; j < tableHeight; j++) {
            chiTable[tableHeight + 1][i] += chiTable[j][i];
        }
    }
    chiTable[tableHeight + 1][tableWidth + 1] = 0;
    for (int i = 0; i < tableHeight; i++) {
        int heightSum = 0;
        heightSum += chiTable[i][tableWidth + 1] = 0;
    }
    for (int i = 0; i < tableWidth; i++) {
        int widthSum = 0;
        widthSum += chiTable[i][tableHeight + 1] = 0;
    }
    if (heightSum != widthSum) {
        printf("What the fuck happened!");
    } else {
        chitable[tableHeight + 1][tableWidth + 1] = heightSum;
    }

    for (int i = 0; i < (tableHeight + 1); i++) {
        for (int j = 0; j < (tableWidth + 1); j++) {
            printf("%d", chiTable[i][j]);
        }
        printf("\n");
    }
}