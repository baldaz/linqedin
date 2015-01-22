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
            uif->setBirthdate(QDate::fromString(info["birthdate"].toString(), "dd.MM.yyyy"));
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
                Experience exp(0, sub["location"].toString().toStdString(), sub["role"].toString().toStdString(), QDate::fromString(sub["from"].toString(), "dd.MM.yyyy"), QDate::fromString(sub["to"].toString(), "dd.MM.yyyy"));
                uif->addExperience(exp);
            }
            QJsonArray works = obj["jobs"].toArray();
            QJsonObject wrk;
            for(int i = 0; i < works.size(); ++i) {
                wrk = works[i].toObject();
                Experience exp(1, wrk["location"].toString().toStdString(), wrk["role"].toString().toStdString(), QDate::fromString(wrk["from"].toString(), "dd.MM.yyyy"), QDate::fromString(wrk["to"].toString(), "dd.MM.yyyy"));
                uif->addExperience(exp);
            }
        }

        Account* acc = new Account(uif, usr, priv);

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
        QJsonArray outmail = obj["outmail"].toArray();
        QJsonArray inmail = obj["inmail"].toArray();
        QJsonObject in, out;
        for(int i = 0; i < outmail.size(); ++i) {
            out = outmail[i].toObject();
            Message mex(usr, Username(out["receiver"].toString().toStdString(), ""), out["object"].toString().toStdString(), out["body"].toString().toStdString(), true, QDate::fromString(out["sent"].toString(), "dd.MM.yyyy"), QDate::fromString(out["recv"].toString(), "dd.MM.yyyy"));
            s->loadOutMail(mex);    // add to outmail
        }
        for(int i = 0; i < inmail.size(); ++i) {
            in = inmail[i].toObject();
            Message mex(Username(in["sender"].toString().toStdString(), ""), usr, in["object"].toString().toStdString(), in["body"].toString().toStdString(), in["read"].toBool(), QDate::fromString(in["sent"].toString(), "dd.MM.yyyy"), QDate::fromString(in["recv"].toString(), "dd.MM.yyyy"));
            s->loadInMail(mex);// add to inmail
        }
        addUser(s);
        delete uif;
        delete acc;
        delete s;
    }
}
void LinqDB::readNet(const QJsonArray& qjs) {
    list<SmartPtr<User> >::iterator it = _db.begin();
    for(; it != _db.end(); ++it) {
        for(int i = 0; i < qjs.size(); ++i) {
            QJsonObject obj = qjs[i].toObject();
            QJsonArray contacts = obj["net"].toArray();
            if((*it)->account()->username().login() == obj["username"].toString().toStdString()) {
                for(int k = 0; k < contacts.size(); ++k){
                    Username usr(contacts[k].toString().toStdString(), ""); /* variante find(new username)*/
                    (*it)->addContact(find(usr));
                }
            }
        }
    }
}
vector<QJsonObject> LinqDB::writeJson() const {
    vector<QJsonObject> vjs;
    UserInfo* uif; Bio* bio;
    list<SmartPtr<User> >::const_iterator it = _db.begin();
    for(; it != _db.end(); ++it) {
        QJsonObject jUser, jInf, jFormations, jWork, jPayment, jMail;
        QJsonArray jArr, jLang, jSkill, jInterest, jForArr, jForWrk, jPay, jKWords;
        list<Experience> experience;
        list<Message*> inMail;
        list<Message*> outMail;
        vector<SmartPtr<Payment> > payments;
        Info* info = (*it)->account()->info();
        if(uif = dynamic_cast<UserInfo*> (info)) { /*downcast a userinfo*/
            jInf["name"] = QString::fromStdString(uif->name());
            jInf["surname"] = QString::fromStdString(uif->surname());
            jInf["telephon"] = QString::fromStdString(uif->telephon());
            jInf["birthdate"] = (uif->birthdate().toString("dd.MM.yyyy"));
            jInf["email"] = QString::fromStdString(uif->email());
            jInf["sex"] = uif->sex();
            jInf["address"] = QString::fromStdString(uif->address());
            jInf["website"] = QString::fromStdString(uif->website());
            experience = uif->experiences();
            if(bio = dynamic_cast<Bio*> (info))
                jInf["biography"] = QString::fromStdString(bio->bio());
        }
        for(list<Experience>::const_iterator j = experience.begin(); j != experience.end(); ++j) {
            if(j->type() == 0) {
                jFormations["location"] = QString::fromStdString(j->location());
                jFormations["from"] = (j->from().toString("dd.MM.yyyy"));
                jFormations["to"] = (j->to().toString("dd.MM.yyyy"));
                jFormations["role"] = QString::fromStdString(j->role());
                jForArr.append(jFormations);
            }
            else if(j->type() == 1) {
                jWork["location"] = QString::fromStdString(j->location());
                jWork["from"] = (j->from().toString("dd.MM.yyyy"));
                jWork["to"] = (j->to().toString("dd.MM.yyyy"));
                jWork["role"] = QString::fromStdString(j->role());
                jForWrk.append(jWork);
            }
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
        jUser["username"] = QString::fromStdString((*it)->account()->username().login());
        jUser["password"] = QString::fromStdString((*it)->account()->username().password());
        jUser["visitcount"] = (*it)->visitCount();
        jUser["privilege"] = (*it)->account()->prLevel();
        vector<Username> ulist = (*it)->net()->username();
        vector<Username>::const_iterator itu = ulist.begin();
        for(; itu < ulist.end(); ++itu)
            jArr.append(QString::fromStdString((*itu).login()));
        payments = (*it)->account()->history();
        vector<SmartPtr<Payment> >::const_iterator iter = payments.begin();
        for(; iter < payments.end(); ++iter) {
            jPayment["code"] = QString::fromStdString((*iter)->billMethod()->code());
            jPayment["nominee"] = QString::fromStdString((*iter)->billMethod()->nominee());
            jPayment["approved"] = (*iter)->approvation();
            jPay.append(jPayment);
        }
        if(const ExecutiveUser* ex = dynamic_cast<const ExecutiveUser*> (&(*(*it)))) {
            map<string, int> kw = ex->keywords();
            for(map<string, int>::iterator itm = kw.begin(); itm != kw.end(); ++itm) {
                for(int i = 0; i < itm->second; ++i)
                    jKWords.append(QString::fromStdString(itm->first));
            }
            jUser["keywords"] = jKWords;
        }
        inMail = (*it)->inMail();
        outMail = (*it)->outMail();
        list<Message*>::const_iterator m_it = inMail.begin();
        for(; m_it != inMail.end(); ++m_it) {
            jMail["receiver"] = QString::fromStdString((*it)->account()->username().login());
            jMail["sender"] = QString::fromStdString((*m_it)->sender().login());
            jMail["object"] = QString::fromStdString((*m_it)->object());
            jMail["body"] = QString::fromStdString((*m_it)->body());
            jMail["read"] = (*m_it)->isRead();
            jMail["sent"] = (*m_it)->sent().toString("dd.MM.yyyy");
            jMail["recv"] = (*m_it)->recv().toString("dd.MM.yyyy");
        }
        m_it = outMail.begin();
        for(; m_it != outMail.end(); ++m_it) {
            jMail["receiver"] = QString::fromStdString((*m_it)->receiver().login());
            jMail["sender"] = QString::fromStdString((*it)->account()->username().login());
            jMail["object"] = QString::fromStdString((*m_it)->object());
            jMail["body"] = QString::fromStdString((*m_it)->body());
            jMail["read"] = (*m_it)->isRead();
            jMail["sent"] = (*m_it)->sent().toString("dd.MM.yyyy");
            jMail["recv"] = (*m_it)->recv().toString("dd.MM.yyyy");
        }
        jUser["net"] = jArr;
        jUser["info"] = jInf;
        jUser["languages"] = jLang;
        jUser["skills"] = jSkill;
        jUser["interests"] = jInterest;
        jUser["formations"] = jForArr;
        jUser["jobs"] = jForWrk;
        jUser["payments"] = jPay;
        jUser["mailbox"] = jMail;
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
    list<SmartPtr<User> >::iterator it = _db.begin();
    bool alreadyIn = false;
    for(; it != _db.end() && !alreadyIn; ++it) {
        if(((*it)->account()->username()) == (u->account()->username()))
            alreadyIn = true;
    }
    if(!alreadyIn) _db.push_back(SmartPtr<User>(u));
}
void LinqDB::removeUser(const Username& usr) {
    list<SmartPtr<User> >::iterator it = _db.begin();
    bool found = false;
    for(; it != _db.end() && !found; ++it)
        if(((*it)->account()->username().login()) == usr.login()) {
            found = true;
            _db.erase(it);
        }
}
User* LinqDB::find(const Username& usr) const {
    User* ret = NULL;
    list<SmartPtr<User> >::const_iterator it = _db.begin();
    for(; it != _db.end(); ++it)
        if(((*it)->account()->username().login()) == usr.login())
            // ret = _db[i]->clone();
            ret = &(*(*it));
    return ret;
}
list<SmartPtr<User> >::const_iterator LinqDB::begin() const{
    return _db.begin();
}
list<SmartPtr<User> >::const_iterator LinqDB::end() const{
    return _db.end();
}