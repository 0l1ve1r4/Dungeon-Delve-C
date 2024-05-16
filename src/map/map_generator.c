#include "maps.h"
#include "noise.h"

#define VOID_TILE 0
#define FLOOR_1 1
#define FLOOR_2 2
#define FLOOR_3 3
#define FLOOR_4 4
#define FLOOR_5 5
#define FLOOR_6 6
#define FLOOR_7 7
#define FLOOR_8 8
#define WALL_LEFT 9
#define WALL_MID 10
#define WALL_RIGHT 11
#define HOLE 12
#define FLOOR_STAIRS 13
#define WALL_HOLE_1 14
#define WALL_HOLE_2 15
#define WALL_BANNER 16

#define VOID_TILE_PATH ""
#define FLOOR_1_PATH "res/frames/floor_1.png"
#define FLOOR_2_PATH "res/frames/floor_2.png"
#define FLOOR_3_PATH "res/frames/floor_3.png"
#define FLOOR_4_PATH "res/frames/floor_4.png"
#define FLOOR_5_PATH "res/frames/floor_5.png"
#define FLOOR_6_PATH "res/frames/floor_6.png"
#define FLOOR_7_PATH "res/frames/floor_7.png"
#define FLOOR_8_PATH "res/frames/floor_8.png"
#define WALL_LEFT_PATH "res/frames/wall_left.png"
#define WALL_MID_PATH "res/frames/wall_mid.png"
#define WALL_RIGHT_PATH "res/frames/wall_right.png"
#define HOLE_PATH "res/frames/hole.png"
#define STAIRS_PATH "res/frames/floor_stairs.png"
#define WALL_ROLE_1_PATH "res/frames/wall_hole_1.png"
#define WALL_ROLE_2_PATH "res/frames/wall_hole_2.png"
#define WALL_BANNER_PATH "res/frames/wall_banner.png"

void generateMap(MapNode* TileMap) {
    Texture2D* textures = malloc(sizeof(Texture2D) * 17);
    textures[0] = LoadTexture(VOID_TILE_PATH);
    textures[1] = LoadTexture(FLOOR_1_PATH);
    textures[2] = LoadTexture(FLOOR_2_PATH);
    textures[3] = LoadTexture(FLOOR_3_PATH);
    textures[4] = LoadTexture(FLOOR_4_PATH);
    textures[5] = LoadTexture(FLOOR_5_PATH);
    textures[6] = LoadTexture(FLOOR_6_PATH);
    textures[7] = LoadTexture(FLOOR_7_PATH);
    textures[8] = LoadTexture(FLOOR_8_PATH);
    textures[9] = LoadTexture(WALL_LEFT_PATH);
    textures[10] = LoadTexture(WALL_MID_PATH);
    textures[11] = LoadTexture(WALL_RIGHT_PATH);
    textures[12] = LoadTexture(HOLE_PATH);
    textures[13] = LoadTexture(STAIRS_PATH);
    textures[14] = LoadTexture(WALL_ROLE_1_PATH);
    textures[15] = LoadTexture(WALL_ROLE_2_PATH);
    textures[16] = LoadTexture(WALL_BANNER_PATH);
    
    TileMap->textures = textures;

    generateWalls(TileMap);
    
    // clean spawnpoint
    int spawn_x = TileMap->matrix_width / 2;
    int spawn_y = TileMap->matrix_height / 2;

    for (int i = spawn_y -1; i <= spawn_y + 1; i++)
        for (int j = spawn_x - 1; j <= spawn_x + 1; j++){
            TileMap->matrix[i][j] = FLOOR_1;
            TileMap->tile_info[i][j].blocking = false;

        }



    int num_objects = TileMap->matrix_width / 50;

    for (int i = 0; i < num_objects; i++) {

        TileMap->matrix[rand() % TileMap->matrix_width][rand() % TileMap->matrix_height] = HOLE;

        int stair_x = rand() % TileMap->matrix_width;
        int stair_y = rand() % TileMap->matrix_height;
        TileMap->matrix[stair_y][stair_x] = FLOOR_STAIRS;
        TileMap->tile_info[stair_y][stair_x].blocking = false;
        TileMap->tile_info[stair_y][stair_x].isBreakable = false;
    
    }


    // Create borders with WALL_LEFT, WALL_MID, and WALL_RIGHT
    for (int i = 0; i < TileMap->matrix_width; i++) {
        TileMap->matrix[i][0] = WALL_LEFT;
        TileMap->matrix[i][TileMap->matrix_width - 1] = WALL_RIGHT;
        TileMap->tile_info[i][0].isBreakable = false;

    }
    for (int j = 0; j < TileMap->matrix_width; j++) {
        TileMap->matrix[0][j] = WALL_MID;
        TileMap->matrix[TileMap->matrix_height - 1][j] = WALL_MID;
        TileMap->tile_info[0][j].isBreakable = false;


    }

    return;
}

void generateWalls(MapNode* TileMap) {
  // Fill the map with Perlin noise
    for (int i = 0; i < TileMap->matrix_height; i++) {
        for (int j = 0; j < TileMap->matrix_width; j++) {
            
            int y_seed = rand() % 23;
            int x_seed = rand() % 43;

            float noise = perlin2d((double)i / y_seed, (double)j / x_seed);
            if (noise < 0.5) {

                int floor = rand() % 30;
                if(floor > 8 || floor == 0) floor = FLOOR_1;
                
                TileMap->matrix[i][j] = floor;
                TileMap->tile_info[i][j].blocking = false;
                
            } else {

                int rand_wall = rand() % 10000;
                if (rand_wall < 9000) TileMap->matrix[i][j] = WALL_MID;
                else if (rand_wall < 9500) TileMap->matrix[i][j] = WALL_HOLE_1;
                else if (rand_wall < 9900) TileMap->matrix[i][j] = WALL_HOLE_2;
                else if (rand_wall <= 10000) TileMap->matrix[i][j] = WALL_BANNER;

                TileMap->tile_info[i][j].blocking = true;
            
            }
        }
    }

    // Making sure that always will have paths

    for (int i = 0; i < TileMap->matrix_height; i++) {
    for (int j = 0; j < TileMap->matrix_width; j++) {

        if (TileMap->matrix[i][j] == WALL_MID) {
            if (i - 1 >= 0 && TileMap->matrix[i - 1][j] == FLOOR_1 && i + 1 < TileMap->matrix_height && TileMap->matrix[i + 1][j] == FLOOR_1
                || j - 1 >= 0 && TileMap->matrix[i][j - 1] == FLOOR_1 && j + 1 < TileMap->matrix_width && TileMap->matrix[i][j + 1] == FLOOR_1
            
            ) {
                TileMap->matrix[i][j] = FLOOR_1;
                TileMap->tile_info[i][j].blocking = false;

                }
            }
        }
    }
}
        



