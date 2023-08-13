#ifndef OBJECTS_H
#define OBJECTS_H

#include "config.h"

typedef enum { STR, DEX, LUK, MAX_HP, HP, ATK, DEF, CRIT, DODGE } ATTR;

typedef enum { N, A, B, C, D, E, F, G } ACTIONS;

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
    string name;    // ����W��
    u16 level;      // ���ⵥ��
    u16 max_hp;     // �̤j�ͩR��
    u16 hp;         // ��e�ͩR��
    u16 exp;        // �g���
    u16 max_exp;    // �ɵ��g���
    u16 gold;       // ����
    u16 attr_point; // �i���ݩ��I��
    Attribute attr; // �ݩʭ�

  public:
    Character(void);
    void show_char(void);  // �d�ݨ��⪬�A
    void level_up();       // ����ɵ�
    void use_attr_poing(); // �����ݩʭ�
};

#endif