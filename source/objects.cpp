#include "../include/objects.h"
#include "../include/config.h"
#include "../include/msg.h"
#include "../include/rand.h"

Attribute::Attribute(void) {
    str = random(2, 5);
    dex = random(2, 5);
    luk = random(2, 5);
    atk = 10 + (str << 1);
    def = 0;
    crit = luk;
    dodge = dex;
}

void Attribute::show_attr(void) {
    hard_msg("�����ݩ�");
    cout << "�O�q��:" << str << endl;
    cout << "�ӱ���:" << dex << endl;
    cout << "���B��:" << luk << endl;
    cout << "�����O:" << atk << endl;
    cout << "���m�O:" << def << endl;
    cout << "�z���v:" << crit << endl;
    cout << "�j�ײv:" << dodge << endl;
}

void Attribute::up_attr(ATTR attr) {
    switch (attr) {
    case STR:
        str++;
        atk += 2;
        break;
    case DEX:
        dex++;
        dodge++;
        break;
    case LUK:
        luk++;
        crit++;
        break;
    case ATK:
        atk++;
        break;
    case DEF:
        def++;
        crit++;
        break;
    case CRIT:
        crit++;
        break;
    case DODGE:
        dodge++;
        break;

    default:
        cout << "Error:up_attr" << endl;
        break;
    }
}

Character::Character(void) {
    cout << "�п�J����W��:";
    cin >> name;
    level = 1;
    gold = attr_point = exp = 0;
    hp = max_hp = 50;
    max_exp = 100;
}

void Character::show_char(void) {
    hard_msg("���⪬�A");
    cout << "����W��:" << name << endl;
    cout << "����:" << level << endl;
    cout << "�ͩR��:" << hp << "/" << max_hp << endl;
    cout << "�g���:" << exp << "/100" << endl;
    cout << "����:" << gold << endl;
    cout << "�i���ݩ��I��:" << attr_point << endl;
}

void Character::level_up(void) {
    define_msg("LEVEL UP", '#');
    level++;
    exp = 0;
    max_exp;
    attr_point++;
    max_hp += 50;
    hp = max_hp;
    // �H�������ݩ� 25% 1-atk, 25% 1-def, 25% 1-crit , 25% 1-dodge
    u16 atk_def_crit_dodge = condition(4) + 5;
    up_attr((ATTR)atk_def_crit_dodge);
}

void Character::use_attr_poing(void) {
    cout << "\n�i�ί�O�I��:" << attr_point << endl;
    if (!attr_point) {
        cout << "��O�I�Ƥ���..." << endl;
        return;
    }
    cout << "(1) ���ɤO�q��(���ɧ����O)" << endl
         << "(2) ���ɱӱ���(���ɰj�ײv)" << endl
         << "(3) ���ɩ��B��(�����z���v)" << endl
         << "(4) ��^" << endl;

    u16 action = safe_action();
    switch (action) {
    case A:
        attr_point--;
        up_attr(STR);
        break;
    case B:
        attr_point--;
        up_attr(DEX);
        break;
    case C:
        attr_point--;
        up_attr(LUK);
        break;
    default:
        break;
    }

    return;
}