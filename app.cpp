#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

bool do_sth(Player& player) {
    cout << "\n現在要幹嘛? "
         << "(1) 查看角色訊息 "
         << "(2) 查看角色屬性 "
         << "(3) 查看裝備武器 "
         << "(4) 提升屬性 "
         << "(5) 轉蛋(抽取武器) "
         << "(6) 休息(恢復體力) "
         << "(7) 結束" << endl;

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