#ifndef OBJECTS_H
#define OBJECTS_H

#include "config.h"

typedef enum { STR, DEX, LUK, MAX_HP, HP, ATK, DEF, CRIT, DODGE } ATTR;

typedef enum { Z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O } ACTIONS;

typedef enum { NORMAL, BLOOD, SLEEP } STATES;

class Skill {
  private:
    string name; // 技能名稱
    string desc; // 技能描述
  public:
    Skill(string name, string desc);
    void show_skill(void);
    string get_name() { return name; }
};

class Weapon {
  private:
    string name; // 武器名稱
    u16 atk;
    u16 def;
    u16 crit;
    u16 dodge;
    u16 skill_probability; // 技能觸發機率
    Skill skill;

  public:
    Weapon(string name, u16 atk, u16 def, u16 crit, u16 dodge, u16 sp, Skill skill);
    u16 get_atk(void) { return atk; }
    u16 get_def(void) { return def; }
    u16 get_crit(void) { return crit; }
    u16 get_dodge(void) { return dodge; }
    u16 get_sp(void) { return skill_probability; }
    void show_weapon_attr(void);
    void get_skill_desc(void);
    string get_skill(void) { return skill.get_name(); }
    string get_name(void) { return name; }
};

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
    void set_atk(s16 a) { atk += a; }
    void set_def(s16 d) { def += d; }
    void set_crit(s16 c) { crit += c; }
    void set_dodge(s16 d) { dodge += d; }

  public:
    Attribute(void);
    Attribute(u16);
    void show_attr(void); // 查看屬性訊息
    u16 get_atk(void) { return atk; }
    u16 get_def(void) { return def; }
    u16 get_crit(void) { return crit; }
    u16 get_dodge(void) { return dodge; }
};

class Character : public Attribute {
  private:
    string name;     // 角色名稱
    u16 level;       // 角色等級
    u16 max_hp;      // 最大生命值
    s16 hp;          // 當前生命值
    u16 exp;         // 經驗值
    u16 max_exp;     // 升等經驗值
    u16 gold;        // 金幣
    u16 attr_point;  // 可用屬性點數
    u16 weapon;      // 裝備武器
    bool items[100]; // 持有武器
    void level_up(); // 角色升等
  protected:
    void set_exp(u16);    // 增加經驗值
    bool set_gold(s16);   // 取得(失去)金幣:成功回傳true
    bool set_hp(s16);     // 增加(減少)生命值:成功回傳true:失敗代表角色陣亡
    void set_item(u16);   // 取得武器
    void equip(u16);      // 穿武器
    void unequip(u16);    // 脫武器
    void set_weapon(u16); // 更換武器
    void hp_to_one(void) { hp = 1; } // 生命歸1
    string get_name(void) { return name; }
    u16 get_level(void) { return level; }
    u16 get_max_hp(void) { return max_hp; }
    s16 get_hp(void) { return hp; }
    u16 get_gold(void) { return gold; }
    u16 get_weapon(void) { return weapon; }

  public:
    Character(void);
    void show_char(void);      // 查看角色狀態
    void show_items(void);     // 查看可用武器
    void use_attr_poing(void); // 提升屬性值
};

class Mob : public Attribute {
  private:
    string name;
    u16 level;
    u16 max_hp;
    s16 hp;
    u16 weapon;     // 武器
    Attribute attr; // 屬性

  public:
    Mob(string, u16);
    void set_level(u16);
    void show_mob(void);
    void equip(void);
    void set_hp(u16 hp) { this->hp += hp; }
    string get_name(void) { return name; }
    u16 get_level(void) { return level; }
    u16 get_max_hp(void) { return max_hp; }
    s16 get_hp(void) { return hp; }
    u16 get_weapon(void) { return weapon; }
};

class Player : public Character {
  private:
    u16 mob_type[100];

  public:
    Player(void) { fill(mob_type, mob_type + 100, 0); }
    bool fight(void);
    void inn(void);
    void gachapon(void);
    void call_result(void);
    void cheat(void);
};

void initialization();

#endif