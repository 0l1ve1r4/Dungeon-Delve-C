#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 25
#define FLOOR 0
#define WALL 1
#define DOOR 3

void generateMap(int map[HEIGHT][WIDTH]) {
    // Initialize the seed for random number generation
    srand((unsigned int)time(NULL));

    // Generate walls (1) and floors (0)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) {
                // Place walls around the edges of the map
                map[y][x] = WALL;
            } else {
                // Randomly place walls and floors
                int randomValue = rand() % 100;
                map[y][x] = (randomValue < 75) ? FLOOR : WALL; // 75% chance for floor, 25% for wall
            }
        }
    }

    // Randomly place doors (3)
    for (int i = 0; i < HEIGHT; i++) {
        int doorX = rand() % WIDTH;
        int doorY = rand() % HEIGHT;
        if (map[doorY][doorX] == WALL) {
            map[doorY][doorX] = DOOR;
        }
    }
}

/*

void printMap(int map[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
}

int main() {
    int map[HEIGHT][WIDTH];
    generateMap(map);
    printMap(map);
    return 0;
}
*/