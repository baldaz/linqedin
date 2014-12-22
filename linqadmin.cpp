#include "linqadmin.h"

LinqAdmin::LinqAdmin() : _db(new LinqDB()) {}
LinqAdmin::~LinqAdmin() { delete _db; }
void LinqAdmin::insertUser() {}
void LinqAdmin::removeUser() {}
void alterSubscription(Username* usr) {}
void LinqAdmin::find() const {}
void LinqAdmin::save() const {}