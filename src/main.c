#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../ArrayLib/src/ArrayLib.h"

int main() {
    printf("\nEnter table width: ");
    int tableWidth = 0;
    scanf("%d", &tableWidth);

    printf("Enter table height: ");
    int tableHeight = 0;
    scanf("%d", &tableHeight);

    //Use as dataTable[y][x]
    //Reminder *(array + 1) = array[1] = array item 2
    int** dataTable = malloc((tableHeight + 1) * sizeof(*dataTable));
    for (int i = 0; i < (tableHeight + 1); i++) {
        dataTable[i] = malloc((tableWidth + 1) * sizeof(**dataTable));
    }

    printf("\n");
    for (int i = 0; i < tableHeight; i++) {
        for (int j = 0; j < tableWidth; j++) {
            printf("Enter data for [%d][%d]: ", i, j);
            scanf("%d", &dataTable[i][j]);
        }
    }

    for (int i = 0; i < tableHeight; i++) {
        dataTable[i][tableWidth] = 0;
        for (int j = 0; j < tableWidth; j++) {
            dataTable[i][tableWidth] += dataTable[i][j];
        }
    }
    for (int i = 0; i < tableWidth; i++) {
        dataTable[tableHeight][i] = 0;
        for (int j = 0; j < tableHeight; j++) {
            dataTable[tableHeight][i] += dataTable[j][i];
        }
    }
    dataTable[tableHeight][tableWidth] = 0;
    int rowSums = 0;
    int columnSums = 0;
    for (int i = 0; i < tableHeight; i++) {
        rowSums += dataTable[i][tableWidth];
    }
    for (int i = 0; i < tableWidth; i++) {
        columnSums += dataTable[tableHeight][i];
    }
    if (rowSums == columnSums) {
        dataTable[tableHeight][tableWidth] = rowSums;
    } else {
        printf("\nWhat the fuck happened!\nWidth sum: %d\nHeight sum:%d", columnSums, rowSums);
    }
    printf("\n\nData:");
    for (int i = 0; i < (tableHeight + 1); i++) {
        printf("\n");
        for (int j = 0; j < (tableWidth + 1); j++) {
            printf("%d ", dataTable[i][j]);
        }
    }

    float** expectedTable = malloc(tableHeight * sizeof(*expectedTable));
    for (int i = 0; i < tableHeight; i++) {
        expectedTable[i] = malloc(tableWidth * sizeof(**expectedTable));
    }
    for (int i = 0; i < tableHeight; i++) {
        for (int j = 0; j < tableWidth; j++) {
            expectedTable[i][j] = ((float)dataTable[tableHeight][j] * (float)dataTable[i][tableWidth]) / (float)dataTable[tableHeight][tableWidth];
        }
    }

    printf("\n\nExpectation:");
    for (int i = 0; i < tableHeight; i++) {
        printf("\n");
        for (int j = 0; j < tableWidth; j++) {
            printf("%.2f ", expectedTable[i][j]);
        }
    }

    int freedom = (tableWidth - 1) * (tableHeight - 1);
    printf("\n\nDegrees of freedom: %d", freedom);

    float chiValue = 0;
    for (int i = 0; i < tableHeight; i++) {
        for (int j = 0; j < tableWidth; j++) {
            chiValue += ((((float)dataTable[i][j] - expectedTable[i][j]) * ((float)dataTable[i][j] - expectedTable[i][j])) / expectedTable[i][j]);
        }
    }
    printf("\n\nChi value: %.2f", chiValue);

    printf("\n");
}