#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define maxLen 255

int checkFile(char *filename, int vertex){
    char buffer[maxLen], *token;
	int i = 0, j = 0;
	FILE *f = fopen(filename, "r");

    if (!f){
        printf("No file!");
        exit(1);
    }

    while (fgets(buffer, maxLen, f)){
        vertex++;
        token = strtok(buffer, "\n");
    }

    if (vertex == 0){
        printf("No file!");
        exit(1);
    }

	fclose(f);

    return vertex;
}

void arrMatrixAdjacent(char* filename, int vertex, int matriks[vertex][vertex]){
    char buffer[maxLen], array[maxLen][maxLen], *token;
	int i = 0, j = 0;
	FILE *f = fopen(filename, "r");

    while (fgets(buffer, maxLen, f)){
        token = strtok(buffer, "\n");
        // strcpy(array[i], token);
        printf("%s\n", token);
        ++i;
    }

    // for (i = 0; i < vertex; i++){
    //     for (j = 0; j < vertex; j++){
    //         matriks[i][j] = (array[i+1][2*j]) - 48;
    //         printf("%d, ", matriks[i][j]);
    //     }
    //     printf("\n");
    // }
    fclose(f);
}

// Referensi: https://www.geeksforgeeks.org/hamiltonian-path-using-dynamic-programming/
bool hamiltonianPath(int matriks[maxLen][maxLen], int vertex){
    printf("Tes kehadiran\n");
    int dp[vertex][(1 << vertex)];
    memset(dp, 0, sizeof dp);

    for (int i = 0; i < vertex; i++)
        dp[i][(1 << i)] = true;
 
    // Iterate over each subset
    // of nodes
    for (int i = 0; i < (1 << vertex); i++) {
 
        for (int j = 0; j < vertex; j++) {
            // If the jth nodes is included
            // in the current subset
            if (i & (1 << j)) {
 
                // Find K, neighbour of j
                // also present in the
                // current subset
                for (int k = 0; k < vertex; k++) {
 
                    if (i & (1 << k)
                        && matriks[k][j]
                        && j != k
                        && dp[k][i ^ (1 << j)]) {
 
                        // Update dp[j][i]
                        // to true
                        dp[j][i] = true;
                        break;
                    }
                }
            }
        }
    }
 
    // Traverse the vertices
    for (int i = 0; i < vertex; i++) {
 
        // Hamiltonian Path exists
        if (dp[i][(1 << vertex) - 1])
            return true;
    }
 
    // Otherwise, return false
    return false;
}

void printHamiltonianPath(int matriks[][maxLen], int path){

}

int main(){
    char file[maxLen];
    int vertices = 0, path = 0;

    printf(GRN "\nWelcome to Hamiltonian Path" RESET);

    printf("\nHamiltonian Path means that every vertices in a graph is traversed once only.");
    printf("\n\nEnter file name: ");
    gets(file);
    
    int vertex = checkFile(file, vertices);
    printf("Vertices: %d\n", vertex);
    int matriks[vertex][vertex];
    arrMatrixAdjacent(file, vertex, matriks);
    // hamiltonianPath(matriks, vertex);

    // Input
    // int matriks[maxLen][maxLen] = { { 0, 1, 1, 1, 0 },
    //                           { 1, 0, 1, 0, 1 },
    //                           { 1, 1, 0, 1, 1 },
    //                           { 1, 0, 1, 0, 0 },
    //                           { 0, 1, 1, 0, 0 } };
 
    // int vertex = 5;
    // Function Call

    if (hamiltonianPath(matriks, vertex)){
        printHamiltonianPath(matriks, path);
        printf(GRN "YES" RESET);
    }
    else
        printf(GRN "NO" RESET);
 
    return 0;
}