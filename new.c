#include <stdio.h>

#define boolean unsigned char
#define true 1
#define false 0

#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define maxLen 255

boolean hasHamiltonian = false;

void printSolution(int vertices, int p[]) {
    for (int i = 0; i < vertices; i++)
        printf("%d ", p[i]);
    printf("%d\n", p[0]);
}

boolean isSafe(int vertices, int n, boolean g[vertices][vertices], int path[], int pos) {
    if (g [path[pos-1]][n] == 0)
        return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == n)
            return false;
    return true;
}

void hamiltonianCycle(int vertices, boolean g[vertices][vertices], int path[], int pos) {
   //If all vertices are included in Hamiltonian Cycle
    if (pos == vertices) {
        if (g[ path[(sizeof(path)/sizeof(path[0]))-1] ][ path[0] ] == 1){
            printSolution(vertices, path);
            hasHamiltonian = true;
        }
    }
    for (int n = 1; n < vertices; n++) {
        if (isSafe(vertices, n, g, path, pos)) //Check if this vertex can be added to Hamiltonian Cycle
        {
            path[pos] = n;
            //recur to construct rest of the path
            hamiltonianCycle(vertices, g, path, pos+1);
            path[pos] = -1; //remove vertex if it doesn’t lead to the solution
        }
    }
}

void hamiltonianPath(int vertices, boolean g[vertices][vertices]) {
    int path[vertices];
    for (int i = 0; i < vertices; i++)
        path[i] = -1;

    path[0] = 0;
    hamiltonianCycle(vertices, g, path, 1);
    if (hasHamiltonian == false) {
        printf("\nCycle does not exist");
    }
}

int main() {
    // Read from file
    FILE *fp;
    char c;
    int row, col;
    int vertices;

    char file[maxLen];
    printf(GRN "\nWelcome to Hamiltonian Path" RESET);

    printf("\nHamiltonian Path means that every vertices in a graph is traversed once only.");
    printf("\n\nEnter file name: ");
    gets(file);

    fp = fopen(file, "r");

    if (fp == NULL) {
        printf("File tidak dapat dibuka\n");
        return 0;
    }

    // Read first line to get number of vertices present
    c = fgetc(fp);
    vertices = c - '0';
    printf("%d\n", vertices);

    // Create adjacency matrix
    boolean matrix[vertices][vertices];

    // Read to skip \n
    c = fgetc(fp);

    row = 0;
    col = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            row++;
            col = 0;
        } 
        else if (c != ' ' && c != ',') {
            if (c == '1') {
                matrix[row][col] = true;
            } 
            else {
                matrix[row][col] = false;
            }
            col++;
        }
    }

    fclose(fp);

    // Print adjacency matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Search for Hamiltonian Path
    hamiltonianPath(vertices, matrix);

    return 0;
}