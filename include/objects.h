#ifndef OBJECTS_H
#define OBJECTS_H

#include "config.h"

typedef enum { STR, DEX, LUK, MAX_HP, HP, ATK, DEF, CRIT, DODGE } ATTR;

typedef enum { Z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O } ACTIONS;

typedef enum { NORMAL, BLOOD, SLEEP } STATES;

class Skill {
  private:
    string name; // �ޯ�W��
    string desc; // �ޯ�y�z
  public:
    Skill(string name, string desc);
    void show_skill(void);
    string get_name() { return name; }
};

class Weapon {
  private:
    string name; // �Z���W��
    u16 atk;
    u16 def;
    u16 crit;
    u16 dodge;
    u16 skill_probability; // �ޯ�Ĳ�o���v
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
    u16 str;   // �O�q��: �W�[2�I�����O
    u16 dex;   // �ӱ���: �W�[1%�j�ײv
    u16 luk;   // ���B��: �W�[1%�z���v
    u16 atk;   // �����O: ��¦�������ˮ`
    u16 def;   // ���m�O: ��K�@�w��Ҫ��ˮ`
    u16 crit;  // �z���v: �y�������ˮ`
    u16 dodge; // �j�ײv: �@�w���v����������
  protected:
    void up_attr(ATTR); // �����ݩ�
    void set_atk(s16 a) { atk += a; }
    void set_def(s16 d) { def += d; }
    void set_crit(s16 c) { crit += c; }
    void set_dodge(s16 d) { dodge += d; }

  public:
    Attribute(void);
    Attribute(u16);
    void show_attr(void); // �d���ݩʰT��
    u16 get_atk(void) { return atk; }
    u16 get_def(void) { return def; }
    u16 get_crit(void) { return crit; }
    u16 get_dodge(void) { return dodge; }
};

class Character : public Attribute {
  private:
    string name;     // ����W��
    u16 level;       // ���ⵥ��
    u16 max_hp;      // �̤j�ͩR��
    s16 hp;          // ��e�ͩR��
    u16 exp;         // �g���
    u16 max_exp;     // �ɵ��g���
    u16 gold;        // ����
    u16 attr_point;  // �i���ݩ��I��
    u16 weapon;      // �˳ƪZ��
    bool items[100]; // �����Z��
    void level_up(); // ����ɵ�
  protected:
    void set_exp(u16);    // �W�[�g���
    bool set_gold(s16);   // ���o(���h)����:���\�^��true
    bool set_hp(s16);     // �W�[(���)�ͩR��:���\�^��true:���ѥN����}�`
    void set_item(u16);   // ���o�Z��
    void equip(u16);      // ��Z��
    void unequip(u16);    // ��Z��
    void set_weapon(u16); // �󴫪Z��
    void hp_to_one(void) { hp = 1; } // �ͩR�k1
    string get_name(void) { return name; }
    u16 get_level(void) { return level; }
    u16 get_max_hp(void) { return max_hp; }
    s16 get_hp(void) { return hp; }
    u16 get_gold(void) { return gold; }
    u16 get_weapon(void) { return weapon; }

  public:
    Character(void);
    void show_char(void);      // �d�ݨ��⪬�A
    void show_items(void);     // �d�ݥi�ΪZ��
    void use_attr_poing(void); // �����ݩʭ�
};

class Mob : public Attribute {
  private:
    string name;
    u16 level;
    u16 max_hp;
    s16 hp;
    u16 weapon;     // �Z��
    Attribute attr; // �ݩ�

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