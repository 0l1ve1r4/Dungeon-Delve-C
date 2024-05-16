#ifndef MENU_H
#define MENU_H

#include "defs.h"
#include "map/maps.h"
#include "utils/utils.h"

#define BACKGROUND_COLOR {1, 1, 26, 255}

#define LOGO_PATH "res/static/background.png"
#define WALL_PATH "res/static/wall.png"
#define FIRE_ANIM_PATH "res/static/fire.gif"
#define RAIN_ANIM_PATH "res/static/rain.gif"

#define BACKGROUND_MENU_MUSIC "res/sounds/menu_background.mp3"
#define CHANGE_OPTION_SOUND "res/static/change_option.mp3"
#define SELECT_OPTION_SOUND "res/static/select.mp3"
#define LIGHTNING_SOUND "res/static/lightning.mp3"

#define MAX_OPTIONS 4
#define MAX_INPUT_CHARS 9

typedef enum {
    OPTION_SINGLEPLAYER,
    OPTION_MULTIPLAYER,
    OPTION_OPTIONS,
    OPTION_EXIT
    }    MenuOption;


// Updates

void UpdateRaining(Sound lightning);
void UpdateOptions(MenuOption* selectedOptionPtr, Sound change_option, Sound select_option);


// Draws

void DrawBackground(Texture2D logo, Texture2D wall, Texture2D texFireAnim, Texture2D texRain, int selectedOption);
void DrawAllOptions(int selectedOption);
void DrawWorldSettings(int selectedOption);
void startSinglePlayer(void);

#endif