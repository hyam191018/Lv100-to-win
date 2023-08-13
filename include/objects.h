#ifndef OBJECTS_H
#define OBJECTS_H

#include "config.h"

typedef enum { STR, DEX, LUK, MAX_HP, HP, ATK, DEF, CRIT, DODGE } ATTR;

typedef enum { N, A, B, C, D, E, F, G } ACTIONS;

class Attribute {
  private:
    u16 str;   // 力量值: 增加2點攻擊力
    u16 dex;   // 敏捷值: 增加1%迴避率
    u16 luk;   // 幸運值: 增加1%爆擊率
    u16 atk;   // 攻擊力: 基礎的攻擊傷害
    u16 def;   // 防禦力: 減免一定比例的傷害
    u16 crit;  // 爆擊率: 造成雙倍傷害
    u16 dodge; // 迴避率: 一定機率讓攻擊失效
  protected:
    void up_attr(ATTR); // 提升屬性
  public:
    Attribute(void);
    void show_attr(void); // 查看屬性訊息
};

class Character : public Attribute {
  private:
    string name;    // 角色名稱
    u16 level;      // 角色等級
    u16 max_hp;     // 最大生命值
    u16 hp;         // 當前生命值
    u16 exp;        // 經驗值
    u16 max_exp;    // 升等經驗值
    u16 gold;       // 金幣
    u16 attr_point; // 可用屬性點數
    Attribute attr; // 屬性值

  public:
    Character(void);
    void show_char(void);  // 查看角色狀態
    void level_up();       // 角色升等
    void use_attr_poing(); // 提升屬性值
};

#endif