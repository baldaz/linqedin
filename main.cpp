#include <iostream>
#include "account.h"
#include "linqnet.h"
#include "linqdb.h"

using std::cout;
using std::endl;

int main() {
    LinqDB db; /*DB utenti*/
    LinqNet net; /*Rete amicizie*/
    LinqNet net2;
    LinqNet net3;
    Username usr("Baldaz", "password");
    Info* uf = new UserInfo(1, "Andrea", "Baldan", "08-10-1988", "a.g.baldan@gmail.com", "via 4 novembre 12", "3450515048");
    Username usr2("Pablito", "maurisio");
    Info* uf2 = new UserInfo(1, "Pablos", "Escobar", "15-12-1923", "escobar@cartello.cb", "calle de la muerte 1", "9873478233");
    Username usr3("Atilio", "piovra");
    Info* uf3 = new UserInfo(1, "Atos", "Bierta", "15-10-1973", "atos@bierta.es", "calle de la muerte 2", "4872474213");
    Account acc(uf, &usr, basic);
    Account acc2(uf2, &usr2, basic);
    Account acc3(uf3, &usr3, basic);
    // cout << acc.getInfo()->getName() << endl;
    User* s3 = new BasicUser(&acc3, &net3);
    User* s2 = new BasicUser(&acc2, &net2);
    User* s = new BasicUser(&acc, &net);
    net.addUser(s2); /*inserisco pablo negli amici di andrea*/
    net.addUser(s3);
    net2.addUser(s3);
    net3.addUser(s2);
    db.addUser(s);
    db.addUser(s2);
    db.addUser(s3);
    cout<<endl;
    cout<<db;
    net.delUser(s3);
    cout << "*******" << endl;
    cout << s->account()->username()->login().toStdString() << endl << uf->print().toStdString() << " >> " << net << endl;
    cout << "*******" << endl;
    cout << s2->account()->username()->login().toStdString() << endl << uf2->print().toStdString() << " >> " << net2 << endl;
    cout << "*******" << endl;
    cout << s3->account()->username()->login().toStdString() << endl << uf3->print().toStdString() << " >> " << net3 << endl;
    cout << "*******" << endl;
    db.save();
    // SPUser sp(s);
    // db.addUser(sp);
    // cout<<db;
    // User s;
    // db.addUser(s);
    return 0;
}