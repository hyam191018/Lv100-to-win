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

void Character::set_exp(u16 exp) {
    system_msg("取得" + to_string(exp) + "經驗值");
    this->exp += exp;
    if (this->exp >= max_exp) {
        this->exp -= max_exp;
        level_up();
    }
}

bool Character::set_gold(s16 gold) {
    if (gold < 0 && this->gold < -gold) {
        system_msg("金幣不足");
        return false;
    }
    system_msg((gold > 0 ? "取得" : "失去") +
               to_string(gold > 0 ? gold : -gold) + "金幣");
    if (this->gold + gold > 10000) {
        this->gold = 10000;
        system_msg("金幣上限:10,000");
    } else {
        this->gold += gold;
    }
    return true;
}

bool Character::set_hp(s16 hp) {
    if (hp < 0 && this->hp < -hp) {
        system_msg("角色陣亡");
        this->hp = 0;
        return false;
    }
    this->hp += hp;
    system_msg("角色恢復" + to_string(hp) + "點生命值");
    if (this->hp > max_hp) {
        this->hp = max_hp;
    }
    return true;
}

void Character::use_attr_poing(void) {
    system_msg("可用能力點數:" + to_string(attr_point));
    if (!attr_point) {
        system_msg("能力點數不足");
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

void Character::show_weapon(void) { hard_msg("裝備武器"); }

string Character::get_name(void) { return name; }

u16 Character::get_level(void) { return level; }

u16 Character::get_max_hp(void) { return max_hp; }

u16 Character::get_hp(void) { return hp; }

u16 Character::get_gold(void) { return gold; }

void Player::inn(void) {
    cout << "持有金幣" << get_gold() << "，是否要花費" << get_level() * 10
         << "金幣恢復所有體力?"
         << " (1) 好"
         << " (2) 不好" << endl;

    u16 action = safe_action();
    switch (action) {
    case A:
        if (set_gold(-(get_level() * 10))) {
            set_hp(get_max_hp());
        }
        break;
    default:
        break;
    }
}

void Player::gachapon(void) { system_msg("轉蛋!"); }

void Player::cheat(void) {
    hard_msg("特權指令");
    cout << " (1) 增加經驗值 "
         << " (2) 增加金幣 "
         << " (3) 減少金幣 "
         << " (4) 增加生命值 "
         << " (5) 減少生命值 " << endl;
    u16 action = safe_action();
    switch (action) {
    case A:
        cout << "增加多少? ";
        set_exp(safe_action());
        break;
    case B:
        cout << "增加多少? ";
        set_gold(safe_action());
        break;
    case C:
        cout << "減少多少? ";
        set_gold(-safe_action());
        break;
    case D:
        cout << "增加多少? ";
        set_hp(safe_action());
        break;
    case E:
        cout << "減少多少? ";
        set_hp(-safe_action());
        break;
    default:
        break;
    }
}