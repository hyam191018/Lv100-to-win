#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

void do_sth(Character& character) {
    cout << "\n�{�b�n�F��?" << endl
         << "(1) �d�ݨ���T��" << endl
         << "(2) �d�ݨ����ݩ�" << endl
         << "(3) ���ɵ���" << endl
         << "(4) �����ݩ�" << endl
         << "(5) ��^" << endl;
    u16 action = safe_action();

    switch (action) {
    case A:
        character.show_char();
        break;
    case B:
        character.show_attr();
        break;
    case C:
        character.level_up();
        break;
    case D:
        character.use_attr_poing();
        break;

    default:
        break;
    }
}

int main(void) {
    init_random();
    Character character;

    while (1) {
        do_sth(character);
    }
}