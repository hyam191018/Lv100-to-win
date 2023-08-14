#include "../include/objects.h"
#include "../include/config.h"
#include "../include/msg.h"
#include "../include/rand.h"

vector<Skill> skill_list;
vector<Weapon> weapon_list;
vector<Mob> mob_list;

Skill::Skill(string name, string desc) {
    this->name = name;
    this->desc = desc;
}

void Skill::show_skill(void) { cout << "技能名稱:" << name << endl << "技能描述:" << desc << endl; }

Weapon::Weapon(string name, u16 atk, u16 def, u16 crit, u16 dodge, u16 sp, Skill skill)
    : name(name), atk(atk), def(def), crit(crit), dodge(dodge), skill_probability(sp),
      skill(skill) {}

void Weapon::get_skill_desc(void) {
    skill.show_skill();
    cout << "觸發機率:" << skill_probability << "%" << endl;
};

void Weapon::show_weapon_attr(void) {
    cout << "武器名稱:" << name << endl
         << "提升攻擊力:" << atk << endl
         << "提升防禦力:" << def << endl
         << "提升爆擊率:" << crit << endl
         << "提升迴避率:" << dodge << endl;
    skill.show_skill();
}

Attribute::Attribute(void) {
    str = random(5, 10);
    dex = random(5, 10);
    luk = random(5, 10);
    atk = 10 + (str << 1);
    def = 0;
    crit = luk;
    dodge = dex;
}

Attribute::Attribute(u16 n) { str = dex = luk = atk = def = crit = dodge = n; }

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
    gold = attr_point = exp = weapon = 0;
    hp = max_hp = 50;
    max_exp = 100;
    fill(items, items + 100, false);
    items[0] = true;
    equip(0);
}

void Character::show_char(void) {
    hard_msg("角色狀態");
    cout << "角色名稱:" << name << endl;
    cout << "等級:" << level << endl;
    cout << "生命值:" << hp << "/" << max_hp << endl;
    cout << "經驗值:" << exp << "/100" << endl;
    cout << "金幣:" << gold << endl;
    cout << "可用屬性點數:" << attr_point << endl;
    cout << "使用武器:" << weapon_list[weapon].get_name() << endl;
    weapon_list[weapon].get_skill_desc();
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
    u16 str_dex_luk = condition(3);
    up_attr((ATTR)str_dex_luk);
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
    system_msg((gold > 0 ? "取得" : "失去") + to_string(gold > 0 ? gold : -gold) + "金幣");
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
        this->hp = 0;
        return false;
    }
    this->hp += hp;
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

void Character::equip(u16 weapon) {
    set_atk(weapon_list[weapon].get_atk());
    set_def(weapon_list[weapon].get_def());
    set_crit(weapon_list[weapon].get_crit());
    set_dodge(weapon_list[weapon].get_dodge());
}

void Character::unequip(u16 weapon) {
    set_atk(-weapon_list[weapon].get_atk());
    set_def(-weapon_list[weapon].get_def());
    set_crit(-weapon_list[weapon].get_crit());
    set_dodge(-weapon_list[weapon].get_dodge());
}

void Character::set_weapon(u16 weapon) {
    // 移除角色能力
    unequip(this->weapon);
    this->weapon = weapon;
    // 提升角色能力
    equip(this->weapon);
}

void Character::set_item(u16 item) { this->items[item] = true; }

void Character::show_items(void) {
    hard_msg("更換武器");
    int i;
    cout << "(0) 返回" << endl;
    for (i = 0; i < 100; i++) {
        if (items[i]) {
            cout << "(" << i + 1 << ") " << weapon_list[i].get_name() << " - "
                 << "("
                 << "攻擊力:" + to_string(weapon_list[i].get_atk()) + ", "
                 << "防禦力:" + to_string(weapon_list[i].get_def()) + ", "
                 << "爆擊率:" + to_string(weapon_list[i].get_crit()) + ", "
                 << "迴避率:" + to_string(weapon_list[i].get_dodge()) << ") " << endl;
            weapon_list[i].get_skill_desc();
            cout << endl;
        }
    }
    u16 action = safe_action();
    if (action == 0 || (action > 99 && action < 0) || items[action - 1] == false) {
        return;
    }
    set_weapon(action - 1);
    system_msg("使用武器 - " + weapon_list[action - 1].get_name());
}

Mob::Mob(string name, u16 weapon) : name(name), weapon(weapon) {
    level = max_hp = hp = 0;
    attr = Attribute(0);
}

void Mob::show_mob(void) {
    cout << "名稱:" << name << endl
         << "等級:" << level << endl
         << "當前生命值:" << hp << endl
         << "最大生命值:" << max_hp << endl
         << "武器:" << weapon_list[weapon].get_name() << endl;
}

void Mob::set_level(u16 level) {
    this->level = level;
    // 隨機提升屬性
    this->max_hp = this->hp = level * 50;
    for (int i = 0; i < level; i++) {
        u16 state = condition(3);
        up_attr(STR);
    }
}

void Mob::equip(void) {
    Weapon weapon = weapon_list[this->weapon];
    set_atk(weapon.get_atk());
    set_def(weapon.get_def());
    set_crit(weapon.get_crit());
    set_dodge(weapon.get_dodge());
}

Mob create_mob(u16 type, u16 level) {
    Mob mob = mob_list[type];
    // 提升至對應等級
    mob.set_level(level);
    mob.equip();
    mob.show_mob();
    return mob;
}

void Player::call_result(void) {
    hard_msg("戰鬥結果");
    for (int i = 0; i < 100; i++) {
        if (mob_type[i] != 0) {
            cout << "擊殺了 " << mob_list[i].get_name() << " " << mob_type[i] << "次!" << endl;
        }
    }
    hard_msg("========");
}

bool Player::fight(void) {
    soft_msg("敵人出現");
    u16 type = condition(get_level() > 10 ? 12 : mob_list.size());
    Mob mob = create_mob(type, get_level());
    bool win = true;
    soft_msg("開始戰鬥");
    // 回合制戰鬥
    Weapon myWeapon = weapon_list[this->get_weapon()];
    Weapon enemyWeapon = weapon_list[mob.get_weapon()];
    bool isSkill, isCrit, isDodge;
    u16 myState = NORMAL, enemyState = NORMAL;
    string skill_name;
    u16 dmg;

    while (true) {
    me:
        // 我方先攻
        if (myState == BLOOD) {
            set_hp(-(get_max_hp() * 0.02));
            if (get_hp() <= 0) {
                win = false;
                goto end;
            }

        } else if (myState == SLEEP) {
            myState = NORMAL;
            goto enemy;
        }
        cout << get_name() << " 發動了攻擊" << endl;

        // 是否迴避
        isDodge = simulateProbability(mob.get_dodge());
        if (!isDodge) {
            // 是否觸發技能
            isSkill = simulateProbability(myWeapon.get_sp());
            if (isSkill) {
                // 技能效果
                cout << "觸發了被動技能"
                     << "[" << myWeapon.get_skill() << "]" << endl;
                skill_name = myWeapon.get_skill();

                if (skill_name.compare("流血") == 0) {
                    enemyState = BLOOD;
                } else if (skill_name.compare("噬血") == 0) {
                    set_hp(get_atk());
                    if (get_hp() > get_max_hp()) {
                        set_hp(-(get_hp() - get_max_hp()));
                    }
                } else if (skill_name.compare("燃燒") == 0) {
                    cout << mob.get_name() << " 受到了"
                         << to_string(static_cast<int>((mob.get_max_hp() * 0.1))) << "點傷害";
                    mob.set_hp(-(mob.get_max_hp() * 0.1));
                    cout << "，剩餘生命值:" << mob.get_hp() << endl;
                } else if (skill_name.compare("麻痺") == 0) {
                    enemyState = SLEEP;
                } else if (skill_name.compare("冰凍") == 0) {
                    enemyState = SLEEP;
                } else if (skill_name.compare("切割") == 0) {
                    cout << mob.get_name() << " 受到了" << to_string((mob.get_hp() / 2))
                         << "點傷害";
                    mob.set_hp(-(mob.get_hp() / 2));
                    cout << "，剩餘生命值:" << mob.get_hp() << endl;
                } else if (skill_name.compare("斬殺") == 0) {
                    cout << mob.get_name() << " 受到了" << to_string((mob.get_hp())) << "點傷害";
                    mob.set_hp(-(mob.get_hp()));
                    cout << "，剩餘生命值:" << mob.get_hp() << endl;
                }
            }
            // 造成傷害
            dmg = myWeapon.get_atk() + condition(myWeapon.get_atk());
            // 是否爆擊
            isCrit = simulateProbability(this->get_crit());
            if (isCrit) {
                // 造成傷害
                cout << "造成了爆擊! ";
                mob.set_hp(-((dmg << 1) - mob.get_def()));
                cout << mob.get_name() << " 受到了" << to_string(((dmg << 1) - mob.get_def()))
                     << "點傷害"
                     << "，剩餘生命值:" << mob.get_hp() << endl;
            } else {
                // 造成傷害
                mob.set_hp(-(dmg - mob.get_def()));
                cout << mob.get_name() << " 受到了" << to_string((dmg - mob.get_def())) << "點傷害"
                     << "，剩餘生命值:" << mob.get_hp() << endl;
            }
        } else {
            cout << mob.get_name() << " 迴避了攻擊!" << endl;
        }
        Sleep(500);
        // 是否分勝負
        if (mob.get_hp() <= 0) {
            win = true;
            goto end;
        }
    enemy:
        // 敵方攻擊
        if (enemyState == BLOOD) {
            mob.set_hp(-(mob.get_max_hp() * 0.02));
            if (mob.get_hp() <= 0) {
                win = true;
                goto end;
            }

        } else if (enemyState == SLEEP) {
            enemyState = NORMAL;
            goto me;
        }
        cout << mob.get_name() << " 發動了攻擊" << endl;

        // 是否迴避
        isDodge = simulateProbability(get_dodge());
        if (!isDodge) {
            // 是否觸發技能
            isSkill = simulateProbability(enemyWeapon.get_sp());
            if (isSkill) {
                // 技能效果
                cout << "觸發了被動技能"
                     << "[" << enemyWeapon.get_skill() << "]" << endl;
                skill_name = enemyWeapon.get_skill();

                if (skill_name.compare("流血") == 0) {
                    myState = BLOOD;
                } else if (skill_name.compare("噬血") == 0) {
                    mob.set_hp(mob.get_atk());
                    if (mob.get_hp() > mob.get_max_hp()) {
                        mob.set_hp(-(get_hp() - get_max_hp()));
                    }
                } else if (skill_name.compare("燃燒") == 0) {
                    cout << get_name() << " 受到了"
                         << to_string(static_cast<int>((get_max_hp() * 0.1))) << "點傷害";
                    set_hp(-(get_max_hp() * 0.1));
                    cout << "，剩餘生命值:" << get_hp() << endl;
                } else if (skill_name.compare("麻痺") == 0) {
                    myState = SLEEP;
                } else if (skill_name.compare("冰凍") == 0) {
                    myState = SLEEP;
                } else if (skill_name.compare("切割") == 0) {
                    cout << get_name() << " 受到了" << to_string((get_hp() / 2)) << "點傷害";
                    set_hp(-(get_hp() / 2));
                    cout << "，剩餘生命值:" << get_hp() << endl;
                } else if (skill_name.compare("斬殺") == 0) {
                    cout << get_name() << " 受到了" << to_string((get_hp())) << "點傷害";
                    set_hp(-(get_hp()));
                    cout << "，剩餘生命值:" << get_hp() << endl;
                }
            }
            // 造成傷害
            dmg = enemyWeapon.get_atk() + condition(enemyWeapon.get_atk());
            // 是否爆擊
            isCrit = simulateProbability(mob.get_crit());
            if (isCrit) {
                // 造成傷害
                cout << "造成了爆擊! ";
                set_hp(-((dmg << 1) - get_def()));
                cout << get_name() << " 受到了" << to_string(((dmg << 1) - get_def())) << "點傷害"
                     << "，剩餘生命值:" << get_hp() << endl;
            } else {
                // 造成傷害
                set_hp(-(dmg - get_def()));
                cout << get_name() << " 受到了" << to_string((dmg - get_def())) << "點傷害"
                     << "，剩餘生命值:" << get_hp() << endl;
            }
        } else {
            cout << get_name() << " 迴避了攻擊!" << endl;
        }
        Sleep(500);
        // 是否分勝負
        if (get_hp() <= 0) {
            win = false;
            goto end;
        }
    }
end:
    // 戰鬥結束
    if (win) {
        soft_msg("戰鬥勝利");
        if (type >= 48) {
            mob_type[type]++;
        }

        set_gold(20);
        set_exp(100);
        if (get_level() == 100) {
            system_msg("你升到了100等!");
            call_result();
            return false;
        }
        return true;
    } else {
        system_msg("勝敗乃兵家常事");
        call_result();
        return false;
    }
}

void Player::inn(void) {
    cout << "持有金幣" << get_gold() << "，是否要花費" << get_level() * 10 << "金幣恢復所有體力?"
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

void Player::gachapon(void) {
    cout << "持有金幣" << get_gold() << "，是否要花費" << 50 << "抽取武器?"
         << " (1) 好"
         << " (2) 不好" << endl;

    u16 action = safe_action();
    switch (action) {
    case A:
        if (set_gold(-50)) {
            u16 item = condition(10);
            system_msg("取得道具 - " + weapon_list[item].get_name());
            set_item(item);
        }
        break;
    default:
        break;
    }
}

void Player::cheat(void) {
    hard_msg("特權指令");
    cout << " (1) 增加經驗值 "
         << " (2) 增加金幣 "
         << " (3) 減少金幣 "
         << " (4) 增加生命值 "
         << " (5) 減少生命值 "
         << " (6) 目前戰況 " << endl;
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
    case F:
        call_result();
        break;
    default:
        break;
    }
}

void initialization(void) {
    init_random();

    // 新增技能
    // 技能名稱、被動技能
    skill_list.push_back(Skill("無", "此武器無被動技能"));
    skill_list.push_back(Skill("流血", "每回合受到2%最大生命傷害"));
    skill_list.push_back(Skill("噬血", "回復自身攻擊力的生命"));
    skill_list.push_back(Skill("燃燒", "造成10%最大生命值傷害"));
    skill_list.push_back(Skill("麻痺", "一回合無法行動"));
    skill_list.push_back(Skill("冰凍", "一回合無法行動"));
    skill_list.push_back(Skill("切割", "降低50%當前生命"));
    skill_list.push_back(Skill("斬殺", "直接擊殺對手"));

    // 新增武器
    // 武器名稱、攻擊力、防禦力、爆擊率、迴避率、技能觸發率、技能
    weapon_list.push_back(Weapon("短劍", 5, 0, 5, 5, 0, skill_list[0]));
    weapon_list.push_back(Weapon("長劍", 20, 0, 0, 0, 0, skill_list[0]));
    weapon_list.push_back(Weapon("風魔小太刀", 10, 0, 5, 5, 5, skill_list[1]));
    weapon_list.push_back(Weapon("飲血劍", 10, 10, 5, 5, 25, skill_list[2]));
    weapon_list.push_back(Weapon("浪速不知火", 20, 0, 0, 10, 25, skill_list[3]));
    weapon_list.push_back(Weapon("雷電國崩", 30, 5, 10, 0, 25, skill_list[4]));
    weapon_list.push_back(Weapon("極冰鬼切丸", 30, 5, 0, 10, 25, skill_list[5]));
    weapon_list.push_back(Weapon("村雨", 25, 0, 0, 0, 10, skill_list[6]));
    weapon_list.push_back(Weapon("三日月", 25, 0, 0, 10, 5, skill_list[7]));
    weapon_list.push_back(Weapon("天叢雲", 40, 0, 50, 0, 0, skill_list[0]));

    // 新增敵人
    // 敵人名稱、武器
    for (int i = 0; i < 8; i++) {
        mob_list.push_back(Mob("浪人", 1));
        mob_list.push_back(Mob("騎士", 1));
        mob_list.push_back(Mob("士兵", 1));
        mob_list.push_back(Mob("斥侯", 0));
        mob_list.push_back(Mob("忍者", 0));
        mob_list.push_back(Mob("俠盜", 0));
    }
    mob_list.push_back(Mob("風魔", 2));
    mob_list.push_back(Mob("風魔", 2));
    mob_list.push_back(Mob("赤童", 3));
    mob_list.push_back(Mob("赤童", 3));
    mob_list.push_back(Mob("葬", 4));
    mob_list.push_back(Mob("雷樣", 5));
    mob_list.push_back(Mob("寒", 6));
    mob_list.push_back(Mob("長綾", 7));
    mob_list.push_back(Mob("劍心", 8));
    mob_list.push_back(Mob("須左能呼", 9));
}
