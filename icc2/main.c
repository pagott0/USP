#include <stdio.h>
#include <stdlib.h>

//Enzo Vasconcellos Pagotto - 13632844
//Bruno Giacomini Volpe - 14651980
//Gabriel Pietro Leone - 13874729
//Guilherme Aureliano Xavier da Silva - 14575641

typedef struct {
    int rows;
    int columns;
    int **paths;
} Maze;

// Function prototypes
Maze initializeMaze();
void readPaths(Maze *maze);
int findMaxFriends(Maze maze, int position, int *memo);
int calculateFriends(Maze maze);
void freeMemory(Maze maze);

int main() {
    Maze maze = initializeMaze();
    readPaths(&maze);

    int result = calculateFriends(maze);
    printf("%d", result);

    freeMemory(maze);

    return 0;
}

Maze initializeMaze() {
    Maze maze;
    scanf("%d %d", &maze.rows, &maze.columns);

    int gridSize = maze.rows * maze.columns;

    maze.paths = (int **)malloc(sizeof(int *) * gridSize);
    for (int i = 0; i < gridSize; i++) {
        maze.paths[i] = (int *)malloc(sizeof(int) * gridSize);
    }

    return maze;
}

void readPaths(Maze *maze) {
    int rowPos, colPos;
    for (int i = 0; i < (((maze->rows - 1) * maze->columns) + ((maze->columns - 1) * maze->rows)); i++) {
        scanf("%d %d", &rowPos, &colPos);
        scanf("%d", &maze->paths[rowPos][colPos]);
    }
}

int findMaxFriends(Maze maze, int position, int *memo) {
    int rightMax = 0;
    int downMax = 0;
    int maxFriends;
    int gridSize = maze.rows * maze.columns;

    if (memo[position] == -1) {
        if (position == gridSize - 1) {
            maxFriends = 0;
        } else {
            if ((position % maze.columns) != (maze.columns - 1)) {
                rightMax = maze.paths[position][position + 1] + findMaxFriends(maze, position + 1, memo);
            } 
            if (position < (gridSize - maze.columns)) {
                downMax = maze.paths[position][position + maze.columns] +
                           findMaxFriends(maze, position + maze.columns, memo);
            }

            maxFriends = (downMax > rightMax) ? downMax : rightMax;
        }
    }

    memo[position] = maxFriends;
    return memo[position];
}

int calculateFriends(Maze maze) {
    int *memo = (int *)malloc(sizeof(int) * ((maze.rows * maze.columns) + 1));

    for (int i = 0; i <= (maze.rows * maze.columns); i++) {
        memo[i] = -1;
    }

    int result = findMaxFriends(maze, 0, memo);
    free(memo);

    return result;
}

void freeMemory(Maze maze) {
    for (int i = 0; i < maze.rows; i++) {
        free(maze.paths[i]); 
    }
    free(maze.paths);
}