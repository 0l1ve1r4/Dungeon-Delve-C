#ifndef UTILS_H
#define UTILS_H

#include "../defs.h"
#include "../structs.h"

void debug_log(char *message, char* escape_code);

// GAME INFO - FUNCTIONS //
void GetGameInfo(Player* player);
void ShowControls(void);
void InitRandomSeed(void);
unsigned long mix(unsigned long a, unsigned long b, unsigned long c);
#endif