#include "../include/msg.h"
#include "../include/config.h"

u16 safe_action(void) {
    try {
        string input;
        cin >> input;
        u16 action = stoi(input);
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