#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

void do_sth(Character& character) {
    cout << "\n現在要幹嘛?" << endl
         << "(1) 查看角色訊息" << endl
         << "(2) 查看角色屬性" << endl
         << "(3) 提升等級" << endl
         << "(4) 提升屬性" << endl
         << "(5) 返回" << endl;
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