#include "linqdb.h"

using std::ostream;
using std::endl;

LinqDB::LinqDB() {
    load();
}
LinqDB::~LinqDB() { _db.clear(); }
bool LinqDB::readJson() {
    QFile loadDB("database.json");
    if (!loadDB.open(QIODevice::ReadOnly)) {
        std::cout << "Couldn't open database." << std::endl;
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
    for(int i = 0; i < qjs.size(); ++i) {
        QJsonObject obj = qjs[i].toObject();
        Username usr(obj["username"].toString().toStdString(), obj["password"].toString().toStdString());
        UserInfo* uif = new UserInfo;
        privLevel priv = static_cast<privLevel> (obj["privilege"].toInt());
        QJsonObject info = obj["info"].toObject();
        if(uif) {
            uif->setName(info["name"].toString().toStdString());
            uif->setSurname(info["surname"].toString().toStdString());
            uif->setBirthdate(info["birthdate"].toString().toStdString());
            uif->setEmail(info["email"].toString().toStdString());
            uif->setAddress(info["address"].toString().toStdString());
            uif->setTelephon(info["telephon"].toString().toStdString());
            uif->setSex(info["sex"].toBool());
            uif->setWebsite(info["website"].toString().toStdString());
            QJsonArray languages = obj["languages"].toArray();
            for(int i = 0; i < languages.size(); ++i)
                uif->addLanguage(languages[i].toString().toStdString());
            QJsonArray skills = obj["skills"].toArray();
            for(int i = 0; i < skills.size(); ++i)
                uif->addSkill(skills[i].toString().toStdString());
            QJsonArray interests = obj["interests"].toArray();
            for(int i = 0; i < interests.size(); ++i)
                uif->addInterest(interests[i].toString().toStdString());
            QJsonArray formations = obj["formations"].toArray();
            QJsonObject sub;
            for(int i = 0; i < formations.size(); ++i) {
                sub = formations[i].toObject();
                Instruction ins(sub["location"].toString().toStdString(), sub["from"].toString().toStdString(), sub["to"].toString().toStdString());
                uif->addFormation(&ins);
            }
        }
        Account* acc = new Account(uif, &usr, priv);

        QJsonArray payments = obj["payments"].toArray();
        QJsonObject subP;
        for(int i = 0; i < payments.size(); ++i) {
            subP = payments[i].toObject();
            Subscription subscr(priv);
            CreditCard bmeth(subP["code"].toString().toStdString(), subP["nominee"].toString().toStdString());
            Payment pay(&usr, &subscr, &bmeth, subP["approved"].toBool());
            acc->addPayment(pay);
        }
        User* s = NULL;
        ExecutiveUser* us;
        QJsonArray keys;
        switch(priv) {
            case 0:
                s = new BasicUser(acc);
            break;
            case 1:
                s = new BusinessUser(acc);
            break;
            case 2:
                s = new ExecutiveUser(acc);
                keys = obj["keywords"].toArray();
                us = dynamic_cast<ExecutiveUser*> (s);
                for(int i = 0; i < keys.size(); ++i)
                    us->addKeyword(keys[i].toString().toStdString());
            break;
            case 3:
            break;
        }
        s->setVisitCount(obj["visitcount"].toInt());
        addUser(s);
        delete uif;
        delete acc;
        delete s;
    }
}
void LinqDB::readNet(const QJsonArray& qjs) {
    for(int j = 0; j < size(); ++j) {
        for(int i = 0; i < qjs.size(); ++i) {
            QJsonObject obj = qjs[i].toObject();
            QJsonArray contacts = obj["net"].toArray();
            if(_db[j]->account()->username()->login() == obj["username"].toString().toStdString()) {
                for(int k = 0; k < contacts.size(); ++k){
                    Username usr(contacts[k].toString().toStdString(), ""); /* variante find(new username)*/
                    _db[j]->addContact(find(usr));
                }
            }
        }
    }
}
vector<QJsonObject> LinqDB::writeJson() const {
    vector<QJsonObject> vjs;
    UserInfo* uif; Bio* bio;
    for(int i = 0; i < size(); ++i) {
        QJsonObject jUser, jInf, jFormations, jPayment;
        QJsonArray jArr, jLang, jSkill, jInterest, jForArr, jPay, jKWords;
        vector<SmartPtr<Experience> > formations;
        vector<SmartPtr<Payment> > payments;
        Info* info = _db[i]->account()->info();
        if(uif = dynamic_cast<UserInfo*> (info)) { /*downcast a userinfo*/
            jInf["name"] = QString::fromStdString(uif->name());
            jInf["surname"] = QString::fromStdString(uif->surname());
            jInf["telephon"] = QString::fromStdString(uif->telephon());
            jInf["birthdate"] = QString::fromStdString(uif->birthdate());
            jInf["email"] = QString::fromStdString(uif->email());
            jInf["sex"] = uif->sex();
            jInf["address"] = QString::fromStdString(uif->address());
            jInf["website"] = QString::fromStdString(uif->website());
            formations = uif->formations();
            if(bio = dynamic_cast<Bio*> (info))
                jInf["biography"] = QString::fromStdString(bio->bio());
        }
        Instruction* ins;
        for(unsigned j = 0; j < formations.size(); ++j){
            ins = dynamic_cast<Instruction*> (&(*formations[j]));
            if(ins) {
                jFormations["location"] = QString::fromStdString(ins->location());
                jFormations["from"] = QString::fromStdString(ins->from());
                jFormations["to"] = QString::fromStdString(ins->to());
            }
            jForArr.append(jFormations);
        }
        vector<string>::const_iterator itr;
        vector<string> languages = uif->languages();
        itr = languages.begin();
        for(; itr < languages.end(); ++itr)
            jLang.append(QString::fromStdString(*itr));
        vector<string> skills = uif->skills();
        itr = skills.begin();
        for(; itr < skills.end(); ++itr)
            jSkill.append(QString::fromStdString(*itr));
        vector<string> interests = uif->interests();
        itr = interests.begin();
        for(; itr < interests.end(); ++itr)
            jInterest.append(QString::fromStdString(*itr));
        jUser["username"] = QString::fromStdString(_db[i]->account()->username()->login());
        jUser["password"] = QString::fromStdString(_db[i]->account()->username()->password());
        jUser["visitcount"] = _db[i]->visitCount();
        jUser["privilege"] = _db[i]->account()->prLevel();
        vector<SmartPtr<Username> > list = _db[i]->net()->username();
        vector<SmartPtr<Username> >::const_iterator it = list.begin();
        for(; it < list.end(); ++it)
            jArr.append(QString::fromStdString((*it)->login()));
        payments = _db[i]->account()->history();
        vector<SmartPtr<Payment> >::const_iterator iter = payments.begin();
        for(; iter < payments.end(); ++iter) {
            jPayment["code"] = QString::fromStdString((*iter)->billMethod()->code());
            jPayment["nominee"] = QString::fromStdString((*iter)->billMethod()->nominee());
            jPayment["approved"] = (*iter)->approvation();
            jPay.append(jPayment);
        }
        if(const ExecutiveUser* ex = dynamic_cast<const ExecutiveUser*> (&(*_db[i]))) {
            vector<string> kw = ex->keywords();
            for(vector<string>::iterator it = kw.begin(); it < kw.end(); ++it)
                jKWords.append(QString::fromStdString(*it));
            jUser["keywords"] = jKWords;
        }
        jUser["net"] = jArr;
        jUser["info"] = jInf;
        jUser["languages"] = jLang;
        jUser["skills"] = jSkill;
        jUser["interests"] = jInterest;
        jUser["formations"] = jForArr;
        jUser["payments"] = jPay;
        vjs.push_back(jUser);
    }
    return vjs;
}
void LinqDB::write(const vector<QJsonObject>& json) const {
    QFile saveDB(QStringLiteral("database.json"));
    if (!saveDB.open(QIODevice::WriteOnly))
        qWarning("Couldn't open database.");
    QJsonArray jarr;
    for(unsigned int i = 0; i < json.size(); ++i)
        jarr.append(json[i]);

    QJsonDocument doc(jarr);
    saveDB.write(doc.toJson());
    saveDB.close();
}

vector<Message*> LinqDB::readMessageDb(const string& path) {
    vector<Message*> v;
    QFile loadMessageDB(QStringLiteral("messageDB.json"));
    if (!loadMessageDB.open(QIODevice::ReadOnly))
        qWarning("Couldn't open database.");
    QByteArray saveMessages = loadMessageDB.readAll();
    loadMessageDB.close();

    QJsonDocument doc(QJsonDocument::fromJson(saveMessages));
    QJsonArray qjs = doc.array();

    return v;
}
void LinqDB::writeMessageDb(const string& path) const {

}

void LinqDB::save() const {
    write(writeJson());
}
void LinqDB::load() {
    bool s = readJson();
    if(!s) std::cout << "Errore connessione DB" << std::endl;
    else std::cout<<"Connessione DB ok" << std::endl;
}
int LinqDB::size() const {
    return _db.size();
}
void LinqDB::addUser(User* u) {
    vector<SmartPtr<User> >::iterator it = _db.begin();
    bool alreadyIn = false;
    for(; it < _db.end() && !alreadyIn; ++it) {
        if(*((*it)->account()->username()) == *(u->account()->username()))
            alreadyIn = true;
    }
    if(!alreadyIn) _db.push_back(SmartPtr<User>(u));
}
void LinqDB::removeUser(const Username& usr) {
    for(int i = 0; i < size(); ++i)
        if((_db[i]->account()->username()->login()) == usr.login())
            _db.erase(_db.begin() + i);
}
User* LinqDB::find(const Username& usr) const {
    User* ret = NULL;
    for(int i = 0; i < size(); ++i)
        if((_db[i]->account()->username()->login()) == usr.login())
            // ret = _db[i]->clone();
            ret = &(*_db[i]);
    return ret;
}
vector<SmartPtr<User> >::const_iterator LinqDB::begin() const{
    return _db.begin();
}
vector<SmartPtr<User> >::const_iterator LinqDB::end() const{
    return _db.end();
}
SmartPtr<User> LinqDB::operator[](const int& i) const {
    return _db[i];
}