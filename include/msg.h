#ifndef MSG_H
#define MSG_H

#include "config.h"

/**
 * 安全輸入ACTION，只會回傳整數
 */
u16 safe_action(void);

/**
 * 印出訊息: ---------- (msg) ----------
 */
void soft_msg(string msg);

/**
 * 印出訊息: ========== (msg) ==========
 */
void hard_msg(string msg);

/**
 * 印出自訂符號的訊息
 */
void define_msg(string msg, char sign);

/**
 * 系統訊息
 */
void system_msg(string msg);

#endif