#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

bool do_sth(Player& player) {
    cout << "\n�{�b�n�F��? "
         << "(1) �d�ݨ��⪬�A "
         << "(2) ���ɨ����ݩ� "
         << "(3) �d�ݥi�ΪZ�� "
         << "(4) ��J(����Z��) "
         << "(5) ��(��_��O) "
         << "(6) ����" << endl;

    u16 action = safe_action();

    switch (action) {
    case A:
        player.show_char();
        player.show_attr();
        break;
    case B:
        player.use_attr_poing();
        break;
    case C:
        break;
    case D:
        player.gachapon();
        break;
    case E:
        player.inn();
        break;
    case 666:
        player.cheat();
        break;
    case F:
        return false;
        break;
    default:
        break;
    }
    return true;
}

int main(void) {
    initialization();
    Player player;
    while (do_sth(player))
        ;
}