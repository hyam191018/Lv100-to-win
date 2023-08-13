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
    hard_msg("角色屬性");
    cout << "力量值:" << str << endl;
    cout << "敏捷值:" << dex << endl;
    cout << "幸運值:" << luk << endl;
    cout << "攻擊力:" << atk << endl;
    cout << "防禦力:" << def << endl;
    cout << "爆擊率:" << crit << endl;
    cout << "迴避率:" << dodge << endl;
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
    cout << "請輸入角色名稱:";
    cin >> name;
    level = 1;
    gold = attr_point = exp = 0;
    hp = max_hp = 50;
    max_exp = 100;
}

void Character::show_char(void) {
    hard_msg("角色狀態");
    cout << "角色名稱:" << name << endl;
    cout << "等級:" << level << endl;
    cout << "生命值:" << hp << "/" << max_hp << endl;
    cout << "經驗值:" << exp << "/100" << endl;
    cout << "金幣:" << gold << endl;
    cout << "可用屬性點數:" << attr_point << endl;
}

void Character::level_up(void) {
    define_msg("LEVEL UP", '#');
    level++;
    exp = 0;
    max_exp;
    attr_point++;
    max_hp += 50;
    hp = max_hp;
    // 隨機提升屬性 25% 1-atk, 25% 1-def, 25% 1-crit , 25% 1-dodge
    u16 atk_def_crit_dodge = condition(4) + 5;
    up_attr((ATTR)atk_def_crit_dodge);
}

void Character::use_attr_poing(void) {
    cout << "\n可用能力點數:" << attr_point << endl;
    if (!attr_point) {
        cout << "能力點數不足..." << endl;
        return;
    }
    cout << "(1) 提升力量值(提升攻擊力)" << endl
         << "(2) 提升敏捷值(提升迴避率)" << endl
         << "(3) 提升幸運值(提升爆擊率)" << endl
         << "(4) 返回" << endl;

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