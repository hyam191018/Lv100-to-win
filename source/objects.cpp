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

void Skill::show_skill(void) { cout << "�ޯ�W��:" << name << endl << "�ޯ�y�z:" << desc << endl; }

Weapon::Weapon(string name, u16 atk, u16 def, u16 crit, u16 dodge, u16 sp, Skill skill)
    : name(name), atk(atk), def(def), crit(crit), dodge(dodge), skill_probability(sp),
      skill(skill) {}

void Weapon::get_skill_desc(void) {
    skill.show_skill();
    cout << "Ĳ�o���v:" << skill_probability << "%" << endl;
};

void Weapon::show_weapon_attr(void) {
    cout << "�Z���W��:" << name << endl
         << "���ɧ����O:" << atk << endl
         << "���ɨ��m�O:" << def << endl
         << "�����z���v:" << crit << endl
         << "���ɰj�ײv:" << dodge << endl;
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
    gold = attr_point = exp = weapon = 0;
    hp = max_hp = 50;
    max_exp = 100;
    fill(items, items + 100, false);
    items[0] = true;
    equip(0);
}

void Character::show_char(void) {
    hard_msg("���⪬�A");
    cout << "����W��:" << name << endl;
    cout << "����:" << level << endl;
    cout << "�ͩR��:" << hp << "/" << max_hp << endl;
    cout << "�g���:" << exp << "/100" << endl;
    cout << "����:" << gold << endl;
    cout << "�i���ݩ��I��:" << attr_point << endl;
    cout << "�ϥΪZ��:" << weapon_list[weapon].get_name() << endl;
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
    // �H�������ݩ� 25% 1-atk, 25% 1-def, 25% 1-crit , 25% 1-dodge
    u16 str_dex_luk = condition(3);
    up_attr((ATTR)str_dex_luk);
}

void Character::set_exp(u16 exp) {
    system_msg("���o" + to_string(exp) + "�g���");
    this->exp += exp;
    if (this->exp >= max_exp) {
        this->exp -= max_exp;
        level_up();
    }
}

bool Character::set_gold(s16 gold) {
    if (gold < 0 && this->gold < -gold) {
        system_msg("��������");
        return false;
    }
    system_msg((gold > 0 ? "���o" : "���h") + to_string(gold > 0 ? gold : -gold) + "����");
    if (this->gold + gold > 10000) {
        this->gold = 10000;
        system_msg("�����W��:10,000");
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
    system_msg("�i�ί�O�I��:" + to_string(attr_point));
    if (!attr_point) {
        system_msg("��O�I�Ƥ���");
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
    // ���������O
    unequip(this->weapon);
    this->weapon = weapon;
    // ���ɨ����O
    equip(this->weapon);
}

void Character::set_item(u16 item) { this->items[item] = true; }

void Character::show_items(void) {
    hard_msg("�󴫪Z��");
    int i;
    cout << "(0) ��^" << endl;
    for (i = 0; i < 100; i++) {
        if (items[i]) {
            cout << "(" << i + 1 << ") " << weapon_list[i].get_name() << " - "
                 << "("
                 << "�����O:" + to_string(weapon_list[i].get_atk()) + ", "
                 << "���m�O:" + to_string(weapon_list[i].get_def()) + ", "
                 << "�z���v:" + to_string(weapon_list[i].get_crit()) + ", "
                 << "�j�ײv:" + to_string(weapon_list[i].get_dodge()) << ") " << endl;
            weapon_list[i].get_skill_desc();
            cout << endl;
        }
    }
    u16 action = safe_action();
    if (action == 0 || (action > 99 && action < 0) || items[action - 1] == false) {
        return;
    }
    set_weapon(action - 1);
    system_msg("�ϥΪZ�� - " + weapon_list[action - 1].get_name());
}

Mob::Mob(string name, u16 weapon) : name(name), weapon(weapon) {
    level = max_hp = hp = 0;
    attr = Attribute(0);
}

void Mob::show_mob(void) {
    cout << "�W��:" << name << endl
         << "����:" << level << endl
         << "��e�ͩR��:" << hp << endl
         << "�̤j�ͩR��:" << max_hp << endl
         << "�Z��:" << weapon_list[weapon].get_name() << endl;
}

void Mob::set_level(u16 level) {
    this->level = level;
    // �H�������ݩ�
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
    // ���ɦܹ�������
    mob.set_level(level);
    mob.equip();
    mob.show_mob();
    return mob;
}

void Player::call_result(void) {
    hard_msg("�԰����G");
    for (int i = 0; i < 100; i++) {
        if (mob_type[i] != 0) {
            cout << "�����F " << mob_list[i].get_name() << " " << mob_type[i] << "��!" << endl;
        }
    }
    hard_msg("========");
}

bool Player::fight(void) {
    soft_msg("�ĤH�X�{");
    u16 type = condition(get_level() > 10 ? 12 : mob_list.size());
    Mob mob = create_mob(type, get_level());
    bool win = true;
    soft_msg("�}�l�԰�");
    // �^�X��԰�
    Weapon myWeapon = weapon_list[this->get_weapon()];
    Weapon enemyWeapon = weapon_list[mob.get_weapon()];
    bool isSkill, isCrit, isDodge;
    u16 myState = NORMAL, enemyState = NORMAL;
    string skill_name;
    u16 dmg;

    while (true) {
    me:
        // �ڤ����
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
        cout << get_name() << " �o�ʤF����" << endl;

        // �O�_�j��
        isDodge = simulateProbability(mob.get_dodge());
        if (!isDodge) {
            // �O�_Ĳ�o�ޯ�
            isSkill = simulateProbability(myWeapon.get_sp());
            if (isSkill) {
                // �ޯ�ĪG
                cout << "Ĳ�o�F�Q�ʧޯ�"
                     << "[" << myWeapon.get_skill() << "]" << endl;
                skill_name = myWeapon.get_skill();

                if (skill_name.compare("�y��") == 0) {
                    enemyState = BLOOD;
                } else if (skill_name.compare("����") == 0) {
                    set_hp(get_atk());
                    if (get_hp() > get_max_hp()) {
                        set_hp(-(get_hp() - get_max_hp()));
                    }
                } else if (skill_name.compare("�U�N") == 0) {
                    cout << mob.get_name() << " ����F"
                         << to_string(static_cast<int>((mob.get_max_hp() * 0.1))) << "�I�ˮ`";
                    mob.set_hp(-(mob.get_max_hp() * 0.1));
                    cout << "�A�Ѿl�ͩR��:" << mob.get_hp() << endl;
                } else if (skill_name.compare("�·�") == 0) {
                    enemyState = SLEEP;
                } else if (skill_name.compare("�B��") == 0) {
                    enemyState = SLEEP;
                } else if (skill_name.compare("����") == 0) {
                    cout << mob.get_name() << " ����F" << to_string((mob.get_hp() / 2))
                         << "�I�ˮ`";
                    mob.set_hp(-(mob.get_hp() / 2));
                    cout << "�A�Ѿl�ͩR��:" << mob.get_hp() << endl;
                } else if (skill_name.compare("�ٱ�") == 0) {
                    cout << mob.get_name() << " ����F" << to_string((mob.get_hp())) << "�I�ˮ`";
                    mob.set_hp(-(mob.get_hp()));
                    cout << "�A�Ѿl�ͩR��:" << mob.get_hp() << endl;
                }
            }
            // �y���ˮ`
            dmg = myWeapon.get_atk() + condition(myWeapon.get_atk());
            // �O�_�z��
            isCrit = simulateProbability(this->get_crit());
            if (isCrit) {
                // �y���ˮ`
                cout << "�y���F�z��! ";
                mob.set_hp(-((dmg << 1) - mob.get_def()));
                cout << mob.get_name() << " ����F" << to_string(((dmg << 1) - mob.get_def()))
                     << "�I�ˮ`"
                     << "�A�Ѿl�ͩR��:" << mob.get_hp() << endl;
            } else {
                // �y���ˮ`
                mob.set_hp(-(dmg - mob.get_def()));
                cout << mob.get_name() << " ����F" << to_string((dmg - mob.get_def())) << "�I�ˮ`"
                     << "�A�Ѿl�ͩR��:" << mob.get_hp() << endl;
            }
        } else {
            cout << mob.get_name() << " �j�פF����!" << endl;
        }
        Sleep(500);
        // �O�_���ӭt
        if (mob.get_hp() <= 0) {
            win = true;
            goto end;
        }
    enemy:
        // �Ĥ����
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
        cout << mob.get_name() << " �o�ʤF����" << endl;

        // �O�_�j��
        isDodge = simulateProbability(get_dodge());
        if (!isDodge) {
            // �O�_Ĳ�o�ޯ�
            isSkill = simulateProbability(enemyWeapon.get_sp());
            if (isSkill) {
                // �ޯ�ĪG
                cout << "Ĳ�o�F�Q�ʧޯ�"
                     << "[" << enemyWeapon.get_skill() << "]" << endl;
                skill_name = enemyWeapon.get_skill();

                if (skill_name.compare("�y��") == 0) {
                    myState = BLOOD;
                } else if (skill_name.compare("����") == 0) {
                    mob.set_hp(mob.get_atk());
                    if (mob.get_hp() > mob.get_max_hp()) {
                        mob.set_hp(-(get_hp() - get_max_hp()));
                    }
                } else if (skill_name.compare("�U�N") == 0) {
                    cout << get_name() << " ����F"
                         << to_string(static_cast<int>((get_max_hp() * 0.1))) << "�I�ˮ`";
                    set_hp(-(get_max_hp() * 0.1));
                    cout << "�A�Ѿl�ͩR��:" << get_hp() << endl;
                } else if (skill_name.compare("�·�") == 0) {
                    myState = SLEEP;
                } else if (skill_name.compare("�B��") == 0) {
                    myState = SLEEP;
                } else if (skill_name.compare("����") == 0) {
                    cout << get_name() << " ����F" << to_string((get_hp() / 2)) << "�I�ˮ`";
                    set_hp(-(get_hp() / 2));
                    cout << "�A�Ѿl�ͩR��:" << get_hp() << endl;
                } else if (skill_name.compare("�ٱ�") == 0) {
                    cout << get_name() << " ����F" << to_string((get_hp())) << "�I�ˮ`";
                    set_hp(-(get_hp()));
                    cout << "�A�Ѿl�ͩR��:" << get_hp() << endl;
                }
            }
            // �y���ˮ`
            dmg = enemyWeapon.get_atk() + condition(enemyWeapon.get_atk());
            // �O�_�z��
            isCrit = simulateProbability(mob.get_crit());
            if (isCrit) {
                // �y���ˮ`
                cout << "�y���F�z��! ";
                set_hp(-((dmg << 1) - get_def()));
                cout << get_name() << " ����F" << to_string(((dmg << 1) - get_def())) << "�I�ˮ`"
                     << "�A�Ѿl�ͩR��:" << get_hp() << endl;
            } else {
                // �y���ˮ`
                set_hp(-(dmg - get_def()));
                cout << get_name() << " ����F" << to_string((dmg - get_def())) << "�I�ˮ`"
                     << "�A�Ѿl�ͩR��:" << get_hp() << endl;
            }
        } else {
            cout << get_name() << " �j�פF����!" << endl;
        }
        Sleep(500);
        // �O�_���ӭt
        if (get_hp() <= 0) {
            win = false;
            goto end;
        }
    }
end:
    // �԰�����
    if (win) {
        soft_msg("�԰��ӧQ");
        if (type >= 48) {
            mob_type[type]++;
        }

        set_gold(20);
        set_exp(100);
        if (get_level() == 100) {
            system_msg("�A�ɨ�F100��!");
            call_result();
            return false;
        }
        return true;
    } else {
        system_msg("�ӱѤD�L�a�`��");
        call_result();
        return false;
    }
}

void Player::inn(void) {
    cout << "��������" << get_gold() << "�A�O�_�n��O" << get_level() * 10 << "������_�Ҧ���O?"
         << " (1) �n"
         << " (2) ���n" << endl;

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
    cout << "��������" << get_gold() << "�A�O�_�n��O" << 50 << "����Z��?"
         << " (1) �n"
         << " (2) ���n" << endl;

    u16 action = safe_action();
    switch (action) {
    case A:
        if (set_gold(-50)) {
            u16 item = condition(10);
            system_msg("���o�D�� - " + weapon_list[item].get_name());
            set_item(item);
        }
        break;
    default:
        break;
    }
}

void Player::cheat(void) {
    hard_msg("�S�v���O");
    cout << " (1) �W�[�g��� "
         << " (2) �W�[���� "
         << " (3) ��֪��� "
         << " (4) �W�[�ͩR�� "
         << " (5) ��֥ͩR�� "
         << " (6) �ثe�Ԫp " << endl;
    u16 action = safe_action();
    switch (action) {
    case A:
        cout << "�W�[�h��? ";
        set_exp(safe_action());
        break;
    case B:
        cout << "�W�[�h��? ";
        set_gold(safe_action());
        break;
    case C:
        cout << "��֦h��? ";
        set_gold(-safe_action());
        break;
    case D:
        cout << "�W�[�h��? ";
        set_hp(safe_action());
        break;
    case E:
        cout << "��֦h��? ";
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

    // �s�W�ޯ�
    // �ޯ�W�١B�Q�ʧޯ�
    skill_list.push_back(Skill("�L", "���Z���L�Q�ʧޯ�"));
    skill_list.push_back(Skill("�y��", "�C�^�X����2%�̤j�ͩR�ˮ`"));
    skill_list.push_back(Skill("����", "�^�_�ۨ������O���ͩR"));
    skill_list.push_back(Skill("�U�N", "�y��10%�̤j�ͩR�ȶˮ`"));
    skill_list.push_back(Skill("�·�", "�@�^�X�L�k���"));
    skill_list.push_back(Skill("�B��", "�@�^�X�L�k���"));
    skill_list.push_back(Skill("����", "���C50%��e�ͩR"));
    skill_list.push_back(Skill("�ٱ�", "�����������"));

    // �s�W�Z��
    // �Z���W�١B�����O�B���m�O�B�z���v�B�j�ײv�B�ޯ�Ĳ�o�v�B�ޯ�
    weapon_list.push_back(Weapon("�u�C", 5, 0, 5, 5, 0, skill_list[0]));
    weapon_list.push_back(Weapon("���C", 20, 0, 0, 0, 0, skill_list[0]));
    weapon_list.push_back(Weapon("���]�p�ӤM", 10, 0, 5, 5, 5, skill_list[1]));
    weapon_list.push_back(Weapon("����C", 10, 10, 5, 5, 25, skill_list[2]));
    weapon_list.push_back(Weapon("���t������", 20, 0, 0, 10, 25, skill_list[3]));
    weapon_list.push_back(Weapon("�p�q��Y", 30, 5, 10, 0, 25, skill_list[4]));
    weapon_list.push_back(Weapon("���B�����Y", 30, 5, 0, 10, 25, skill_list[5]));
    weapon_list.push_back(Weapon("���B", 25, 0, 0, 0, 10, skill_list[6]));
    weapon_list.push_back(Weapon("�T���", 25, 0, 0, 10, 5, skill_list[7]));
    weapon_list.push_back(Weapon("���O��", 40, 0, 50, 0, 0, skill_list[0]));

    // �s�W�ĤH
    // �ĤH�W�١B�Z��
    for (int i = 0; i < 8; i++) {
        mob_list.push_back(Mob("���H", 1));
        mob_list.push_back(Mob("�M�h", 1));
        mob_list.push_back(Mob("�h�L", 1));
        mob_list.push_back(Mob("���J", 0));
        mob_list.push_back(Mob("�Ԫ�", 0));
        mob_list.push_back(Mob("�L�s", 0));
    }
    mob_list.push_back(Mob("���]", 2));
    mob_list.push_back(Mob("���]", 2));
    mob_list.push_back(Mob("����", 3));
    mob_list.push_back(Mob("����", 3));
    mob_list.push_back(Mob("��", 4));
    mob_list.push_back(Mob("�p��", 5));
    mob_list.push_back(Mob("�H", 6));
    mob_list.push_back(Mob("����", 7));
    mob_list.push_back(Mob("�C��", 8));
    mob_list.push_back(Mob("������I", 9));
}
