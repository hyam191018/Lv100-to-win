#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

bool do_sth(Player& player) {
    cout << "\n現在要幹嘛? "
         << "(1) 查看角色狀態 "
         << "(2) 提升角色屬性 "
         << "(3) 查看可用武器 "
         << "(4) 轉蛋(抽取武器) "
         << "(5) 休息(恢復體力) "
         << "(6) 結束" << endl;

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