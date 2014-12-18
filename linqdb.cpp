#include "linqdb.h"

using std::for_each;
using std::ostream;
using std::endl;

LinqDB::SPUser::SPUser(User* usr) : _p_usr(usr) {
    if(_p_usr)
        _p_usr->references++;
}
LinqDB::SPUser::SPUser(const SPUser& spusr) : _p_usr(spusr._p_usr) {
    if(_p_usr)
        _p_usr->references++;
}
LinqDB::SPUser::~SPUser() {
    if(_p_usr) {
        _p_usr->references--;
        if(!_p_usr->references)
            delete _p_usr;
    }
}
LinqDB::SPUser& LinqDB::SPUser::operator=(const SPUser& spusr) {
    if(this != &spusr) {
        User* u = _p_usr;
        _p_usr = spusr._p_usr;
        if(_p_usr) _p_usr->references++;
        if(u) {
            u->references--;
            if(!u->references) delete u;
        }
    }
    return *this;
}
User& LinqDB::SPUser::operator*() const {
    return *_p_usr;
}
User* LinqDB::SPUser::operator->() const {
    return _p_usr;
}
bool LinqDB::SPUser::operator==(const SPUser& spu) const {
    return(_p_usr == spu._p_usr);
}
bool LinqDB::SPUser::operator!=(const SPUser& spu) const {
    return(_p_usr != spu._p_usr);
}
/* parte db */
/*con std::for_each funzione in meno, per ogni elemento nel db creare json e scriverlo nella stessa funzione*/
vector<QJsonObject> LinqDB::toJson() const {
    vector<QJsonObject> vjs;
    for(int i = 0; i < this->size(); ++i) {
        QJsonObject jo;
        jo["username"] = _db[i]->account()->username()->login();
        jo["password"] = _db[i]->account()->username()->password();
        vjs.push_back(jo);
    }
    return vjs;
}
void LinqDB::write(vector<QJsonObject> json) const {
    QFile saveDB(QStringLiteral("database.json"));
    if (!saveDB.open(QIODevice::WriteOnly))
        qWarning("Couldn't open database.");
    for(int i = 0; i < json.size(); ++i) {
        QJsonDocument doc(json[i]);
        saveDB.write(doc.toJson());
    }
}
void LinqDB::save() const {
    vector<QJsonObject> js;
    js = toJson();
    write(js);
}
int LinqDB::size() const {
    return _db.size();
}
void LinqDB::addUser(User* u) {
    SPUser spu(u);
    _db.push_back(spu);
    // _db.insert(spu);
}
void LinqDB::removeUser(User* usr) {
    for(int i = 0; i < this->size(); ++i) {
        if(_db[i]->account()->username()->login() == usr->account()->username()->login())
            _db.erase(_db.begin() + i);
    }
}
// User* LinqDB::find(Username usr) {
//     User* ret = NULL;
//     for(int i = 0; i < this->size(); ++i) {
//         if(_db[i]->account()->username() == usr) {
//             switch(_db[i]->account()->prLevel()) {
//                 case basic:
//                 break;
//                 case business:
//                 break;
//                 case executive:
//                 break;
//             }
//         }
//     }
// }
LinqDB::SPUser LinqDB::operator[](const int& i) const {
    return _db[i];
}
ostream& operator<<(ostream& os, const LinqDB& db) {
    if(!db.size()) os << "Nessun utente inserito" << endl;
    else {
        for(int i = 0; i < db.size(); ++i){
            os << db[i]->account()->username()->login().toStdString() << " : ";
            os << db[i]->account()->username()->password().toStdString() << endl;
        }
        os << "DB size: " << db.size() << endl;
    }
    return os;
    // // if(!db._db.size()) os << "Nessun utente inserito" << endl;
    // // else {
    // //     for(db._db::iterator it = db._db.begin(); it != db._db.end(); ++it) {
    // //         os << *it->username()->login() << " : ";
    // //         os << *it->username()->password() << endl;
    // //     }
    // // }
    // return os;
}