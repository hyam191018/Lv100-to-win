#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

bool do_sth(Player& player) {
    cout << "\n�{�b�n�F��? "
         << "(1) �԰� "
         << "(2) �d�ݨ��⪬�A "
         << "(3) ���ɨ����ݩ� "
         << "(4) �󴫪Z�� "
         << "(5) ��J(����Z��) "
         << "(6) ��(��_��O) "
         << "(7) ����" << endl;

    u16 action = safe_action();

    switch (action) {
    case A:
        if (!player.fight()) {
            return false;
        }
        break;
    case B:
        player.show_char();
        player.show_attr();
        break;
    case C:
        player.use_attr_poing();
        break;
    case D:
        player.show_items();
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
    initialization();
    Player player;
    while (do_sth(player))
        ;
    string a;
    cin >> a;
}