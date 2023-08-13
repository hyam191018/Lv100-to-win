#ifndef RAND_H
#define RAND_H

#include "config.h"

/**
 * 設定亂數種子
 */
void init_random(void);

/**
 * 給予一個機率值(0~100)，回傳是否成功。
 */
bool simulateProbability(u16 successRate);

/**
 * 隨機給予一個值且 min <= returnValue <= max
 */
u16 random(u16 min, u16 max);

/**
 * 給予一個數值X，回傳0~X-1。
 */
u16 condition(u16 number);

#endif