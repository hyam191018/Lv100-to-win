#include "include/config.h"
#include "include/msg.h"
#include "include/objects.h"
#include "include/rand.h"

bool do_sth(Player& player) {
    cout << "\n現在要幹嘛? "
         << "(1) 戰鬥 "
         << "(2) 查看角色狀態 "
         << "(3) 提升角色屬性 "
         << "(4) 更換武器 "
         << "(5) 轉蛋(抽取武器) "
         << "(6) 休息(恢復體力) "
         << "(7) 結束" << endl;

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