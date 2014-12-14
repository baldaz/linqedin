#include <iostream>
#include "username.h"

using std::cout;
using std::endl;

main() {
    string login = "Andrea";
    string pwd = "password";
    Username usr(login, pwd);
    cout << usr.getLogin() << endl;
}