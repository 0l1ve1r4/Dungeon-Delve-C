#ifndef UTILS_H
#define UTILS_H

#include "../defs.h"
#include "../structs.h"

void debug_log(char *message, char* escape_code);

// GAME INFO - FUNCTIONS //
void GetGameInfo(Player* player);
void ShowControls(void);

#endif