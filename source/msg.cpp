#include "../include/msg.h"
#include "../include/config.h"

u16 safe_action(void) {
    try {
        string input;
        cin >> input;
        u32 action = stoi(input);
        if (action > 10000) {
            cout << "超出上限" << endl;
            return 0;
        }
        return action;
    } catch (const invalid_argument&) {
        return -1;
    }
}

void soft_msg(string msg) {
    cout << "----------" << msg << "----------" << endl;
}

void hard_msg(string msg) {
    cout << "==========" << msg << "==========" << endl;
}

void define_msg(string msg, char sign) {
    for (int i = 0; i < 10; i++)
        cout << sign;
    cout << msg;
    for (int i = 0; i < 10; i++)
        cout << sign;
    cout << endl;
}

void system_msg(string msg) { cout << "系統訊息:" << msg << endl; }