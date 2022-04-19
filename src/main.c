#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    printf("\n\nModel? ");
    int model = 0;
    scanf("%d", &model);

    printf("\nEnter table width: ");
    int tableWidth = 0;
    scanf("%d", &tableWidth);

    printf("Enter table height: ");
    int tableHeight = 0;
    scanf("%d", &tableHeight);

    //Use as dataTable[y][x]
    //Reminder *(array + 1) = array[1] = array item 2
    float** dataTable = malloc((tableHeight + 1) * sizeof(*dataTable));
    for (int i = 0; i < (tableHeight + 1); i++) {
        dataTable[i] = malloc((tableWidth + 1) * sizeof(**dataTable));
    }
    printf("\n");
    for (int i = 0; i < tableHeight; i++) {
        for (int j = 0; j < tableWidth; j++) {
            printf("Enter data for [%d][%d]: ", i, j);
            scanf("%f", &dataTable[i][j]);
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
    printf("\nData:");
    for (int i = 0; i < (tableHeight + 1); i++) {
        printf("\n");
        for (int j = 0; j < (tableWidth + 1); j++) {
            printf("%.2f ", dataTable[i][j]);
        }
    }

    float** expectedTable = malloc(tableHeight * sizeof(*expectedTable));
    for (int i = 0; i < tableHeight; i++) {
        expectedTable[i] = malloc(tableWidth * sizeof(**expectedTable));
    }
    if (model == 1) {
        printf("\n\n");
        for (int i = 0; i < tableHeight; i++) {
            for (int j = 0; j < tableWidth; j++) {
                printf("Enter expectation for [%d][%d]: ", i, j);
                scanf("%f", &expectedTable[i][j]);
            }
        }
    } else {
        for (int i = 0; i < tableHeight; i++) {
            for (int j = 0; j < tableWidth; j++) {
                expectedTable[i][j] = dataTable[tableHeight][j] * dataTable[i][tableWidth] / dataTable[tableHeight][tableWidth];
            }
        }
        printf("\n");
    }
    printf("\nExpectation:");
    for (int i = 0; i < tableHeight; i++) {
        printf("\n");
        for (int j = 0; j < tableWidth; j++) {
            printf("%.2f ", expectedTable[i][j]);
        }
    }
    int changed = 0;
    int combineRowCount = 0;
    int combineColCount = 0;
    for (int i = 0; i < tableHeight; i++) {
        for (int j = 0; j < tableWidth; j++) {
            if (expectedTable[i][j] < 5 && expectedTable[i][j] != 0) {
                changed = 1;
                if (tableHeight < tableWidth) {
                    combineColCount += 1;
                    if (j != 0) {
                        for (int k = 0; k < tableHeight; k++) {
                            dataTable[k][j - 1] += dataTable[k][j];
                            expectedTable[k][j - 1] += expectedTable[k][j];
                            dataTable[k][j] = 0;
                            expectedTable[k][j] = 0;
                        }
                    } else {
                        for (int k = 0; k < tableHeight; k++) {
                            dataTable[k][j + 1] += dataTable[k][j];
                            expectedTable[k][j + 1] += expectedTable[k][j];
                            dataTable[k][j] = 0;
                            expectedTable[k][j] = 0;
                        }
                    }
                } else {
                    combineRowCount += 1;
                    if (i != 0) {
                        for (int k = 0; k < tableWidth; k++) {
                            dataTable[i - 1][k] += dataTable[i][k];
                            expectedTable[i - 1][k] += expectedTable[i][k];
                            dataTable[i][k] = 0;
                            expectedTable[i][k] = 0;
                        }
                    } else {
                        for (int k = 0; k < tableWidth; k++) {
                            dataTable[i + 1][k] += dataTable[i][k];
                            expectedTable[i + 1][k] += expectedTable[i][k];
                            dataTable[i][k] = 0;
                            expectedTable[i][k] = 0;
                        }
                    }
                }
            }
        }
    }
    if (changed == 1) {
        tableWidth -= combineColCount;
        tableHeight -= combineRowCount;

        printf("\n\nCombined data:");
        for (int i = 0; i < tableHeight; i++) {
            printf("\n");
            for (int j = 0; j < tableWidth; j++) {
                printf("%.2f ", dataTable[i][j]);
            }
        }

        printf("\n\nCombined expectation:");
        for (int i = 0; i < tableHeight; i++) {
            printf("\n");
            for (int j = 0; j < tableWidth; j++) {
                printf("%.2f ", expectedTable[i][j]);
            }
        }
    }

    int freedom = 0;
    if (model == 1) {
        int bins = tableHeight * tableWidth;

        printf("\n\nConstraints? ");
        int constraints = 0;
        scanf("%d", &constraints);

        freedom = bins - constraints;
    } else {
        freedom = (tableWidth - 1) * (tableHeight - 1);
        printf("\n");
    }
    printf("\nDegrees of freedom: %d", freedom);

    float chiValue = 0;
    if (freedom == 1) {
        float diff = 0;
        for (int i = 0; i < tableHeight; i++) {
            for (int j = 0; j < tableWidth; j++) {
                if (dataTable[i][j] != 0 && expectedTable[i][j] != 0) {
                    diff = dataTable[i][j] - expectedTable[i][j];
                    if (dataTable[i][j] < expectedTable[i][j]) {
                        diff *= -1;
                    }
                    chiValue += (diff - 0.5) * (diff - 0.5) / expectedTable[i][j];
                }
            }
        }
    } else {
        for (int i = 0; i < tableHeight; i++) {
            for (int j = 0; j < tableWidth; j++) {
                if (dataTable[i][j] != 0 && expectedTable[i][j] != 0) {
                    chiValue += (dataTable[i][j] - expectedTable[i][j]) * (dataTable[i][j] - expectedTable[i][j]) / expectedTable[i][j];
                }
            }
        }
    }
    printf("\n\nChi value: %.2f", chiValue);

    printf("\n");
}