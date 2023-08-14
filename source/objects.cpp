#include "../include/objects.h"
#include "../include/config.h"
#include "../include/msg.h"
#include "../include/rand.h"

vector<Skill> skill_list;
vector<Weapon> weapon_list;

Skill::Skill(string name, string desc) {
    this->name = name;
    this->desc = desc;
}

void Skill::show_skill(void) {
    cout << "�ޯ�W��:" << name << endl << "�ޯ�y�z:" << desc << endl;
}

Weapon::Weapon(string name, u16 atk, u16 def, u16 crit, u16 dodge, Skill skill)
    : name(name), atk(atk), def(def), crit(crit), dodge(dodge), skill(skill) {}

string Weapon::get_name(void) { return name; }

void Weapon::get_skill_desc(void) { skill.show_skill(); };

void Weapon::show_weapon_attr(void) {
    cout << "�Z���W��:" << name << endl
         << "���ɧ����O:" << atk << endl
         << "���ɨ��m�O:" << def << endl
         << "�����z���v:" << crit << endl
         << "���ɰj�ײv:" << dodge << endl;
    skill.show_skill();
}

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
    gold = attr_point = exp = weapon = 0;
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
    u16 atk_def_crit_dodge = condition(4) + 5;
    up_attr((ATTR)atk_def_crit_dodge);
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
    system_msg((gold > 0 ? "���o" : "���h") +
               to_string(gold > 0 ? gold : -gold) + "����");
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
        system_msg("����}�`");
        this->hp = 0;
        return false;
    }
    this->hp += hp;
    system_msg("�����_" + to_string(hp) + "�I�ͩR��");
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

void Character::show_weapons(void) { hard_msg("�˳ƪZ��"); }

void Player::inn(void) {
    cout << "��������" << get_gold() << "�A�O�_�n��O" << get_level() * 10
         << "������_�Ҧ���O?"
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

void Player::gachapon(void) { system_msg("��J!"); }

void Player::cheat(void) {
    hard_msg("�S�v���O");
    cout << " (1) �W�[�g��� "
         << " (2) �W�[���� "
         << " (3) ��֪��� "
         << " (4) �W�[�ͩR�� "
         << " (5) ��֥ͩR�� " << endl;
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
    default:
        break;
    }
}

void initialization(void) {
    init_random();

    // �s�W�ޯ�
    skill_list.push_back(Skill("�L", "���Z���L�Q�ʧޯ�"));
    skill_list.push_back(Skill("�y��", "Ĳ�o��C�^�X�H���y���ˮ`"));
    skill_list.push_back(Skill("�U�N", "�y��5%�̤j�ͩR�ȶˮ`"));

    // �s�W�Z��
    weapon_list.push_back(Weapon("�u�C", 5, 0, 5, 5, skill_list[0]));
    weapon_list.push_back(Weapon("���C", 20, 0, 0, 0, skill_list[0]));
    weapon_list.push_back(Weapon("��t", 10, 0, 5, 5, skill_list[1]));
    weapon_list.push_back(Weapon("�P���u�b", 10, 0, 5, 5, skill_list[2]));
}