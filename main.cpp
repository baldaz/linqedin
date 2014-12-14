#include <iostream>
#include "account.h"

using std::cout;
using std::endl;

main() {
    Username usr("Andrea", "password");
    UserInfo uf("Andrea", "Baldan", "08-10-1988", "a.g.baldan@gmail.com", "3450515048");
    Account acc(&uf, &usr);
    cout << acc.getInfo()->getName() << endl;
}