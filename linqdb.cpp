#include "linqdb.h"

using std::for_each;
using std::ostream;
using std::endl;

LinqDB::~LinqDB() {}
bool LinqDB::fromJsonObject() {
    QFile loadDB(QStringLiteral("database.json"));
    if (!loadDB.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open database.");
        return false;
    }
    QByteArray saveData = loadDB.readAll();
    loadDB.close();

    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    read(doc.array());
    return true;
}
void LinqDB::read(const QJsonArray& qjs) {
    UserInfo* uif;
    for(int i = 0; i < qjs.size(); ++i) {
        QJsonObject obj = qjs[i].toObject();
        Username* usr = new Username(obj["username"].toString(), obj["password"].toString());
        Info* uf = new UserInfo();
        uif = dynamic_cast<UserInfo*> (uf);
        Account* acc = new Account(uf, usr, basic);
        LinqNet* net = new LinqNet();
        uif->setName(obj["name"].toString());
        uif->setSurname(obj["surname"].toString());
        User* s = new BasicUser(acc, net);
        addUser(s);
    }
}
vector<QJsonObject> LinqDB::toJsonObject() const {
    vector<QJsonObject> vjs;
    UserInfo* uif;
    for(int i = 0; i < size(); ++i) {
        QJsonObject jUser, jInf;
        QJsonArray jArr, jInfo;
        uif = dynamic_cast<UserInfo*> (_db[i]->account()->info()); /*downcast a userinfo*/
        // jInfo.append(uif->name());
        // jInfo.append(uif->surname());
        // jInfo.append(uif->telephon());
        // jInfo.append(uif->birthdate());
        // jInfo.append(uif->email());
        // jInfo.append(uif->sex());
        // jInfo.append(uif->address());
        jInf["name"] = uif->name();
        jInf["surname"] = uif->surname();
        jInf["telephon"] = uif->telephon();
        jInf["birthdate"] = uif->birthdate();
        jInf["email"] = uif->email();
        jInf["sex"] = uif->sex();
        jInf["address"] = uif->address();
        jUser["username"] = _db[i]->account()->username()->login();
        jUser["password"] = _db[i]->account()->username()->password();
        // jUser["info"] = _db[i]->account()->info()->print();
        jUser["privilege"] = _db[i]->account()->prLevel();
        vector<Username*> list = _db[i]->net()->username();
        for(int i = 0; i < list.size(); ++i)
            jArr.append(list[i]->login());
        jUser["net"] = jArr;
        jUser["info"] = jInf;
        vjs.push_back(jUser);
    }
    return vjs;
}
void LinqDB::write(vector<QJsonObject> json) const {
    QFile saveDB(QStringLiteral("database.json"));
    if (!saveDB.open(QIODevice::WriteOnly))
        qWarning("Couldn't open database.");
    QJsonArray jarr;
    for(int i = 0; i < json.size(); ++i)
        jarr.append(json[i]);

    QJsonDocument doc(jarr);
    saveDB.write(doc.toJson());
    saveDB.close();
}
void LinqDB::save() const {
    write(toJsonObject());
}
void LinqDB::load() {
    bool s = fromJsonObject();
    if(!s) std::cout<<"Errore";
    else std::cout<<"OK";
}
int LinqDB::size() const {
    return _db.size();
}
void LinqDB::addUser(User* u) {
    SPUser spu(u);
    _db.push_back(spu);
}
void LinqDB::removeUser(User* usr) {
    for(int i = 0; i < size(); ++i) {
        if(_db[i]->account()->username()->login() == usr->account()->username()->login())
            _db.erase(_db.begin() + i);
    }
}
User* LinqDB::find(Username* usr) {
    User* ret;
    for(int i = 0; i < size(); ++i) {
        if(*(_db[i]->account()->username()) == *usr)
            ret = _db[i]->clone();
    }
    return ret;
}
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
}