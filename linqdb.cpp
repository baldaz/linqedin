#include "linqdb.h"

using std::for_each;
using std::ostream;
using std::endl;

vector<SPUser> LinqDB::fromJsonObject() {
    QFile loadDB(QStringLiteral("database.json"));
    if (!loadDB.open(QIODevice::ReadOnly))
        qWarning("Couldn't open database.");
    vector<SPUser> vsp;
    QByteArray saveData = loadDB.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    vsp = read(doc.object());
    return vsp;
}
vector<SPUser> LinqDB::read(const QJsonObject& qjs) {}
vector<QJsonObject> LinqDB::toJsonObject() const {
    vector<QJsonObject> vjs;
    for(int i = 0; i < size(); ++i) {
        QJsonObject jUser,jInfo;
        QJsonArray jArr;
        jUser["username"] = _db[i]->account()->username()->login();
        jUser["password"] = _db[i]->account()->username()->password();
        jUser["info"] = _db[i]->account()->info()->print();
        jArr.append(jInfo);
        vjs.push_back(jUser);
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
    write(toJsonObject());
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
SPUser LinqDB::operator[](const int& i) const {
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