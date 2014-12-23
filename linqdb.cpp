#include "linqdb.h"

using std::for_each;
using std::ostream;
using std::endl;

LinqDB::LinqDB() {
    load();
}
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
    readNet(doc.array());
    return true;
}
void LinqDB::read(const QJsonArray& qjs) {
    UserInfo* uif;
    for(int i = 0; i < qjs.size(); ++i) {
        QJsonObject obj = qjs[i].toObject();
        Username* usr = new Username(obj["username"].toString(), obj["password"].toString());
        Info* uf = new UserInfo();
        uif = dynamic_cast<UserInfo*> (uf);
        LinqNet* net = new LinqNet();
        QJsonObject info = obj["info"].toObject();
        if(uif) {
            uif->setName(info["name"].toString());
            uif->setSurname(info["surname"].toString());
            uif->setBirthdate(info["birthdate"].toString());
            uif->setEmail(info["email"].toString());
            uif->setAddress(info["address"].toString());
            uif->setTelephon(info["telephon"].toString());
            uif->setSex(info["sex"].toBool());
            QJsonArray skills = obj["skills"].toArray();
            for(int i = 0; i < skills.size(); ++i)
                uif->addSkill(skills[i].toString());
        }
        privLevel priv = static_cast<privLevel> (obj["privilege"].toInt());
        Account* acc = new Account(uif, usr, priv);
        User* s;
        switch(priv) {
            case 0:
                s = new BasicUser(acc, net);
            break;
            case 1:
                s = new BusinessUser(acc, net);
            break;
            case 2:
                s = new ExecutiveUser(acc, net);
            break;
            case 3:
            break;
        }
        addUser(s);
    }
}
void LinqDB::readNet(const QJsonArray& qjs) {
    for(int j = 0; j < size(); ++j) {
        for(int i = 0; i < qjs.size(); ++i) {
            QJsonObject obj = qjs[i].toObject();
            QJsonArray contacts = obj["net"].toArray();
            if(_db[j]->account()->username()->login() == obj["username"].toString()) {
                for(int k = 0; k < contacts.size(); ++k)
                    _db[j]->addContact(find(new Username(contacts[k].toString(), "")));
            }
        }
    }
}
vector<QJsonObject> LinqDB::toJsonObject() const {
    vector<QJsonObject> vjs;
    UserInfo* uif;
    for(int i = 0; i < size(); ++i) {
        QJsonObject jUser, jInf;
        QJsonArray jArr, jSkill;
        uif = dynamic_cast<UserInfo*> (_db[i]->account()->info()); /*downcast a userinfo*/
        jInf["name"] = uif->name();
        jInf["surname"] = uif->surname();
        jInf["telephon"] = uif->telephon();
        jInf["birthdate"] = uif->birthdate();
        jInf["email"] = uif->email();
        jInf["sex"] = uif->sex();
        jInf["address"] = uif->address();
        vector<QString> skills = uif->skills();
        for(int i = 0; i < skills.size(); ++i)
            jSkill.append(skills[i]);
        jUser["username"] = _db[i]->account()->username()->login();
        jUser["password"] = _db[i]->account()->username()->password();
        jUser["privilege"] = _db[i]->account()->prLevel();
        vector<Username*> list = _db[i]->net()->username();
        for(int i = 0; i < list.size(); ++i)
            jArr.append(list[i]->login());
        jUser["net"] = jArr;
        jUser["info"] = jInf;
        jUser["skills"] = jSkill;
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
    if(!s) std::cout << "Errore connessione DB" << std::endl;
    else std::cout<<"Connessione DB ok" << std::endl;
}
int LinqDB::size() const {
    return _db.size();
}
void LinqDB::addUser(User* u) {
    SPUser spu(u);
    _db.push_back(spu);
}
void LinqDB::removeUser(Username* usr) {
    for(int i = 0; i < size(); ++i) {
        if((_db[i]->account()->username()->login()) == usr->login()){
            _db.erase(_db.begin() + i);
            std::cout<<"db ciao"<<i<<size()<<std::endl;
        }
    }
}
User* LinqDB::find(Username* usr) {
    User* ret;
    for(int i = 0; i < size(); ++i) {
        if((_db[i]->account()->username()->login()) == usr->login()){
            // std::cout << "trovato" << std::endl;
            ret = _db[i]->clone();
        }
    }
    // std::cout << ret->account()->username()->login().toStdString() << std::endl;
    return ret;
}
vector<SPUser>::const_iterator LinqDB::begin() const{
    return _db.begin();
}
vector<SPUser>::const_iterator LinqDB::end() const{
    return _db.end();
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