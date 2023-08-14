#ifndef OBJECTS_H
#define OBJECTS_H

#include "config.h"

typedef enum { STR, DEX, LUK, MAX_HP, HP, ATK, DEF, CRIT, DODGE } ATTR;

typedef enum { Z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O } ACTIONS;

class Skill {
  private:
    string name; // �ޯ�W��
    string desc; // �ޯ�y�z
  public:
    Skill(string name, string desc);
    void show_skill(void);
};

class Weapon {
  private:
    string name; // �Z���W��
    u16 atk;
    u16 def;
    u16 crit;
    u16 dodge;
    Skill skill;

  public:
    Weapon(string name, u16 atk, u16 def, u16 crit, u16 dodge, Skill skill);
    string get_name(void);
    void show_weapon_attr(void);
    void get_skill_desc(void);
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
  public:
    Attribute(void);
    void show_attr(void); // �d���ݩʰT��
};

class Character : public Attribute {
  private:
    string name;     // ����W��
    u16 level;       // ���ⵥ��
    u16 max_hp;      // �̤j�ͩR��
    u16 hp;          // ��e�ͩR��
    u16 exp;         // �g���
    u16 max_exp;     // �ɵ��g���
    u16 gold;        // ����
    u16 attr_point;  // �i���ݩ��I��
    Attribute attr;  // �ݩʭ�
    u16 weapon;      // �˳ƪZ��
    void level_up(); // ����ɵ�
  protected:
    void set_exp(u16);  // �W�[�g���
    bool set_gold(s16); // ���o(���h)����:���\�^��true
    bool set_hp(s16); // �W�[(���)�ͩR��:���\�^��true:���ѥN����}�`
    string get_name(void) { return name; }
    u16 get_level(void) { return level; }
    u16 get_max_hp(void) { return max_hp; }
    u16 get_hp(void) { return hp; }
    u16 get_gold(void) { return gold; }

  public:
    Character(void);
    void show_char(void);      // �d�ݨ��⪬�A
    void show_weapons(void);   // �d�ݥi�ΪZ��
    void use_attr_poing(void); // �����ݩʭ�
};

class Player : public Character {
  private:
    u32 instruction_count;

  public:
    void inn(void);
    void gachapon(void);
    void cheat(void);
};

void initialization();

#endif