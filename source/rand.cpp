#include "../include/rand.h"
#include "../include/config.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void init_random(void) { srand(time(NULL)); }

bool simulateProbability(u16 successRate) {
    if (successRate >= rand() % 100 + 1) {
        return true;
    }
    return false;
}

u16 random(u16 min, u16 max) { return rand() % (max - min + 1) + min; }

u16 condition(u16 number) { return rand() % number; }