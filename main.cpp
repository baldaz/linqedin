#include <iostream>
#include "username.h"

using std::cout;
using std::endl;

main() {
    string login = "Andrea";
    string pwd = "password";
    Username usr(login, pwd);
    Username usr2("Baldan", "ciao");
    cout << usr.getLogin() << endl;
    cout << usr2.getLogin() << endl;
    usr.setPassword("pwd");
    cout << usr.getPassword() << endl;
}