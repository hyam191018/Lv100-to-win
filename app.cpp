#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

bool do_sth(Player& player) {
    cout << "\n�{�b�n�F��? "
         << "(1) �d�ݨ���T�� "
         << "(2) �d�ݨ����ݩ� "
         << "(3) �d�ݸ˳ƪZ�� "
         << "(4) �����ݩ� "
         << "(5) ��J(����Z��) "
         << "(6) ��(��_��O) "
         << "(7) ����" << endl;

    u16 action = safe_action();

    switch (action) {
    case A:
        player.show_char();
        break;
    case B:
        player.show_attr();
        break;
    case C:
        player.show_weapon();
        break;
    case D:
        player.use_attr_poing();
        break;
    case E:
        player.gachapon();
        break;
    case F:
        player.inn();
        break;
    case 666:
        player.cheat();
        break;
    case G:
        return false;
        break;
    default:
        break;
    }
    return true;
}

int main(void) {
    init_random();
    Player player;

    while (do_sth(player))
        ;
}