#include "linqdb.h"
#include "error.h"

using std::ostream;
using std::endl;

LinqDB::LinqDB() {
    load();
}
LinqDB::~LinqDB() {
    _db.clear();
    for(list<Group*>::const_iterator i = _grp.begin(); i != _grp.end(); ++i)
        delete *i;
    _grp.clear();
}
bool LinqDB::readJson() throw(Error) {
    QFile loadDB("database.json");
    if (!loadDB.open(QIODevice::ReadOnly)) {
        loadDB.open(QIODevice::WriteOnly | QIODevice::ReadOnly);
        QJsonObject db, jadm;
        jadm["username"] = QString("root");
        jadm["password"] = QString("toor");
        db["admin"] = jadm;
        QJsonDocument doc(db);
        loadDB.write(doc.toJson());
        loadDB.close();
        throw Error(IO, "Database not found");
        return false;
    }
    QByteArray saveData = loadDB.readAll();
    loadDB.close();

    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    QJsonObject db = doc.object();
    read(db["users"].toArray());
    readNet(db["users"].toArray());
    initGroups(db["groups"].toArray()); // populate _grp list
    readGroups(db["groups"].toArray());
    return true;
}
void LinqDB::read(const QJsonArray& qjs) {
    Info* info = NULL;
    // Account* acc = NULL;
    for(int i = 0; i < qjs.size(); ++i) {
        QJsonObject obj = qjs[i].toObject();
        Username usr(obj["username"].toString().toStdString(), obj["password"].toString().toStdString());
        privLevel priv = static_cast<privLevel> (obj["privilege"].toInt());
        if((obj["info"].toObject()).contains("biography"))
            info = new Bio;
        else info = new UserInfo;
        readInfo(info, obj);
        // acc = new Account(info, usr, priv);
        Account ac(info, usr, priv);
        Avatar avt(obj["avatar"].toString().toStdString());
        // acc->setAvatar(avt);
        ac.setAvatar(avt);
        QJsonArray payments = obj["payments"].toArray();
        QJsonObject subP;
        for(int i = 0; i < payments.size(); ++i) {
            subP = payments[i].toObject();
            Subscription subscr(priv);
            CreditCard bmeth(subP["code"].toString().toStdString(), subP["nominee"].toString().toStdString());
            Payment pay(&usr, &subscr, &bmeth, subP["approved"].toBool(), QDate::fromString(subP["appdate"].toString(), "dd.MM.yyyy"));
            // acc->addPayment(pay);
            ac.addPayment(pay);
        }
        User* s = NULL;
        ExecutiveUser* us;
        QJsonArray keys, visitors;
        switch(priv) {
            case 0:
                s = new BasicUser(&ac);
            break;
            case 1:
                s = new BusinessUser(&ac);
            break;
            case 2:
                s = new ExecutiveUser(&ac);
                keys = obj["keywords"].toArray();
                us = dynamic_cast<ExecutiveUser*> (s);
                for(int i = 0; i < keys.size(); ++i)
                    us->addKeyword(keys[i].toString().toStdString());
                visitors = obj["visitors"].toArray();
                for(int i = 0; i < visitors.size(); ++i) {
                    Username usr(visitors[i].toString().toStdString(), "");
                    us->addVisitor(find(usr));
                }
            break;
        }
        s->setVisitCount(obj["visitcount"].toInt());
        QJsonArray outmail = obj["outmail"].toArray();
        QJsonArray inmail = obj["inmail"].toArray();
        QJsonObject in, out;
        // spostare messaggi su heap
        for(int i = 0; i < outmail.size(); ++i) {
            out = outmail[i].toObject();
            Message mex(usr, Username(out["receiver"].toString().toStdString(), ""), out["object"].toString().toStdString(), out["body"].toString().toStdString(), true, QDate::fromString(out["sent"].toString(), "dd.MM.yyyy"), QDate::fromString(out["recv"].toString(), "dd.MM.yyyy"));
            s->loadOutMail(mex);    // add to outmail
            // delete mex;
        }
        for(int i = 0; i < inmail.size(); ++i) {
            in = inmail[i].toObject();
            Message mex(Username(in["sender"].toString().toStdString(), ""), usr, in["object"].toString().toStdString(), in["body"].toString().toStdString(), in["read"].toBool(), QDate::fromString(in["sent"].toString(), "dd.MM.yyyy"), QDate::fromString(in["recv"].toString(), "dd.MM.yyyy"));
            s->loadInMail(mex);// add to inmail
            // delete mex;
        }
        s->resetMail();
        addUser(s);
        delete info;
        // delete acc;
        delete s;
    }
}
void LinqDB::readInfo(Info* inf, const QJsonObject& obj) const {
    QJsonObject info = obj["info"].toObject();
    if(UserInfo* uif = dynamic_cast<UserInfo*> (inf)) {
        uif->setName(info["name"].toString().toStdString());
        uif->setSurname(info["surname"].toString().toStdString());
        uif->setBirthdate(QDate::fromString(info["birthdate"].toString(), "dd.MM.yyyy"));
        uif->setEmail(info["email"].toString().toStdString());
        uif->setAddress(info["address"].toString().toStdString());
        uif->setTelephon(info["telephon"].toString().toStdString());
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
            Experience* expr = new Experience(0, sub["location"].toString().toStdString(), sub["role"].toString().toStdString(), QDate::fromString(sub["from"].toString(), "dd.MM.yyyy"), QDate::fromString(sub["to"].toString(), "dd.MM.yyyy"));
            uif->addExperience(*expr);
        }
        QJsonArray works = obj["jobs"].toArray();
        QJsonObject wrk;
        for(int i = 0; i < works.size(); ++i) {
            wrk = works[i].toObject();
            Experience* expr = new Experience(1, wrk["location"].toString().toStdString(), wrk["role"].toString().toStdString(), QDate::fromString(wrk["from"].toString(), "dd.MM.yyyy"), QDate::fromString(wrk["to"].toString(), "dd.MM.yyyy"));
            uif->addExperience(*expr);
        }
    }
    // if(info.contains("biography"))
        if(Bio* b = dynamic_cast<Bio*> (inf))
            b->setBio(info["biography"].toString().toStdString());
}
void LinqDB::initGroups(const QJsonArray& groups) {
    for(int i = 0; i < groups.size(); ++i) {
        QJsonObject obj = groups[i].toObject();
        Group* grp = new Group(Username(obj["admin"].toString().toStdString(), ""), obj["name"].toString().toStdString(), obj["description"].toString().toStdString());
        QJsonArray pst = obj["posts"].toArray();
        for(int j = 0; j < pst.size(); ++j) {
            QJsonObject ps = pst[j].toObject();
            Post* pst = new Post(Username(ps["author"].toString().toStdString(), ""), ps["content"].toString().toStdString());
            grp->insertPost(*pst);
        }
        QJsonArray mem = obj["members"].toArray();
        for(int k = 0; k < mem.size(); ++k)
            grp->addMember(find(Username(mem[k].toString().toStdString(), "")));
        _grp.push_back(grp);
    }
}
void LinqDB::readGroups(const QJsonArray& a) const {
    list<SmartPtr<User> >::const_iterator it = _db.begin();
    for(; it != _db.end(); ++it) {
        if(BusinessUser* bu = dynamic_cast<BusinessUser*> (&(*(*it)))) {
            for (int i = 0; i < a.size(); ++i) {
                QJsonObject obj = a[i].toObject();
                QJsonArray mem = obj["members"].toArray();
                for(int k = 0; k < mem.size(); ++k) {
                    if(bu->account()->username().login() == mem[k].toString().toStdString()) {
                        QJsonArray posts = obj["posts"].toArray();
                        Group* grp = new Group(Username(obj["admin"].toString().toStdString(), ""), obj["name"].toString().toStdString(), obj["description"].toString().toStdString()); // pesantino
                        for(int j = 0; j < posts.size(); ++j) {
                            QJsonObject ps = posts[j].toObject();
                            Post* pst = new Post(Username(ps["author"].toString().toStdString(), ""), ps["content"].toString().toStdString());
                            grp->insertPost(*pst);
                        }
                        bu->addGroup(*grp);
                    }
                }
            }
        }
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
        QJsonObject jUser, jInf, jFormations, jWork, jPayment, jInMail, jOutMail;
        QJsonArray jArr, jLang, jSkill, jInterest, jForArr, jForWrk, jPay, jKWords, jVis, jInMailArr, jOutMailArr;
        list<Experience*> experience;
        list<SmartPtr<Message> > inMail;
        list<SmartPtr<Message> > outMail;
        vector<SmartPtr<Payment> > payments;
        Info* info = (*it)->account()->info();
        if((uif = dynamic_cast<UserInfo*> (info))) { /*downcast a userinfo*/
            jInf["name"] = QString::fromStdString(uif->name());
            jInf["surname"] = QString::fromStdString(uif->surname());
            jInf["telephon"] = QString::fromStdString(uif->telephon());
            jInf["birthdate"] = (uif->birthdate().toString("dd.MM.yyyy"));
            jInf["email"] = QString::fromStdString(uif->email());
            jInf["address"] = QString::fromStdString(uif->address());
            jInf["website"] = QString::fromStdString(uif->website());
            experience = uif->experiences();
            if((bio = dynamic_cast<Bio*> (info)))
                jInf["biography"] = QString::fromStdString(bio->bio());
        }
        for(list<Experience*>::const_iterator j = experience.begin(); j != experience.end(); ++j) {
            if((*j)->type() == 0) {
                jFormations["location"] = QString::fromStdString((*j)->location());
                jFormations["from"] = ((*j)->from().toString("dd.MM.yyyy"));
                jFormations["to"] = ((*j)->to().toString("dd.MM.yyyy"));
                jFormations["role"] = QString::fromStdString((*j)->role());
                jForArr.append(jFormations);
            }
            else if((*j)->type() == 1) {
                jWork["location"] = QString::fromStdString((*j)->location());
                jWork["from"] = ((*j)->from().toString("dd.MM.yyyy"));
                jWork["to"] = ((*j)->to().toString("dd.MM.yyyy"));
                jWork["role"] = QString::fromStdString((*j)->role());
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
        jUser["avatar"] = QString::fromStdString((*it)->account()->avatar().path());
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
            if((*iter)->billMethod() != NULL) {
                jPayment["code"] = QString::fromStdString((*iter)->billMethod()->code());
                jPayment["nominee"] = QString::fromStdString((*iter)->billMethod()->nominee());
            }
            jPayment["approved"] = (*iter)->approvation();
            jPayment["appdate"] = (*iter)->appDate().toString("dd.MM.yyyy");
            jPay.append(jPayment);
        }
        if(const ExecutiveUser* ex = dynamic_cast<const ExecutiveUser*> (&(*(*it)))) {
            map<string, int> kw = ex->keywords();
            for(map<string, int>::iterator itm = kw.begin(); itm != kw.end(); ++itm) {
                for(int i = 0; i < itm->second; ++i)
                    jKWords.append(QString::fromStdString(itm->first));
            }
            jUser["keywords"] = jKWords;
            list<SmartPtr<User> > v = ex->visitors();
            for(list<SmartPtr<User> >::iterator itr = v.begin(); itr != v.end(); ++itr)
                jVis.append(QString::fromStdString((*itr)->account()->username().login()));
            jUser["visitors"] = jVis;
        }
        inMail = (*it)->inMail();
        outMail = (*it)->outMail();
        list<SmartPtr<Message> >::const_iterator m_it = inMail.begin();
        for(; m_it != inMail.end(); ++m_it) {
            jInMail["receiver"] = QString::fromStdString((*it)->account()->username().login());
            jInMail["sender"] = QString::fromStdString((*m_it)->sender().login());
            jInMail["object"] = QString::fromStdString((*m_it)->object());
            jInMail["body"] = QString::fromStdString((*m_it)->body());
            jInMail["read"] = (*m_it)->isRead();
            jInMail["sent"] = (*m_it)->sent().toString("dd.MM.yyyy");
            jInMail["recv"] = (*m_it)->recv().toString("dd.MM.yyyy");
            jInMailArr.append(jInMail);
        }
        m_it = outMail.begin();
        for(; m_it != outMail.end(); ++m_it) {
            jOutMail["receiver"] = QString::fromStdString((*m_it)->receiver().login());
            jOutMail["sender"] = QString::fromStdString((*it)->account()->username().login());
            jOutMail["object"] = QString::fromStdString((*m_it)->object());
            jOutMail["body"] = QString::fromStdString((*m_it)->body());
            jOutMail["read"] = (*m_it)->isRead();
            jOutMail["sent"] = (*m_it)->sent().toString("dd.MM.yyyy");
            jOutMail["recv"] = (*m_it)->recv().toString("dd.MM.yyyy");
            jOutMailArr.append(jOutMail);
        }
        jUser["net"] = jArr;
        jUser["info"] = jInf;
        jUser["languages"] = jLang;
        jUser["skills"] = jSkill;
        jUser["interests"] = jInterest;
        jUser["formations"] = jForArr;
        jUser["jobs"] = jForWrk;
        jUser["payments"] = jPay;
        jUser["inmail"] = jInMailArr;
        jUser["outmail"] = jOutMailArr;
        vjs.push_back(jUser);
    }
    return vjs;
}
vector<QJsonObject> LinqDB::writeGroups() const {
    vector<QJsonObject> vjs;
    list<SmartPtr<User> >::const_iterator i = _db.begin();
    for(; i != _db.end(); ++i) {
        if(BusinessUser* bu = dynamic_cast<BusinessUser*> (&(**i))) {
            list<Group*> lg = bu->groups();
            for(list<Group*>::const_iterator itr = lg.begin(); itr != lg.end(); ++itr) {
                list<Group*>::const_iterator k = _grp.begin();
                for(; k != _grp.end(); ++k)
                    if((**k) == (**itr)) {
                        list<SmartPtr<User> > lu = (*itr)->members();
                        for(list<SmartPtr<User> >::const_iterator j = lu.begin(); j != lu.end(); ++j)
                            (*k)->addMember(&(**j));
                    }
            }
        }
    }
    list<Group*>::const_iterator it = _grp.begin();
    for(; it != _grp.end(); ++it) {
        QJsonObject jGrp, jPst;
        QJsonArray jMemArr, jPstArr;
        jGrp["name"] = QString::fromStdString((*it)->name());
        jGrp["description"] = QString::fromStdString((*it)->description());
        jGrp["admin"] = QString::fromStdString((*it)->admin().login());
        list<Post*> p = (*it)->posts();
        for(list<Post*>::const_iterator i = p.begin(); i != p.end(); ++i) {
            jPst["author"] = QString::fromStdString((*i)->author().login());
            jPst["content"] = QString::fromStdString((*i)->content());
            jPstArr.append(jPst);
        }
        list<SmartPtr<User> > m = (*it)->members();
        for(list<SmartPtr<User> >::const_iterator itr = m.begin(); itr != m.end(); ++itr)
            jMemArr.append(QString::fromStdString((*itr)->account()->username().login()));
        jGrp["posts"] = jPstArr;
        jGrp["members"] = jMemArr;
        vjs.push_back(jGrp);
    }
    return vjs;
}
void LinqDB::write(const vector<QJsonObject>& json, const vector<QJsonObject>& jg) const throw(Error) {
    QFile saveDB(QStringLiteral("database.json"));
    if (!saveDB.open(QIODevice::WriteOnly))
        throw Error(IO, "Database not found");
    QJsonObject db;
    QJsonArray jarr;
    QJsonArray jgrp;
    QJsonObject jadm;
    for(unsigned int i = 0; i < json.size(); ++i)
        jarr.append(json[i]);
    for(unsigned int i = 0; i < jg.size(); ++i)
        jgrp.append(jg[i]);
    jadm["username"] = QString("root");
    jadm["password"] = QString("toor");
    db["admin"] = jadm;
    db["users"] = jarr;
    db["groups"] = jgrp;
    QJsonDocument doc(db);
    saveDB.write(doc.toJson());
    saveDB.close();
}
void LinqDB::save() const {
    write(writeJson(), writeGroups());
}
void LinqDB::load() {
    bool s = readJson();
    if(!s) std::cout << "Errore connessione DB" << std::endl;
    else std::cout<<"Connessione DB ok" << std::endl;
}
int LinqDB::size() const {
    return _db.size();
}
void LinqDB::deleteGroup(const Group& g) throw(Error) {
    bool found = false;
    list<Group*>::iterator it = _grp.begin();
    for(; it != _grp.end() && !found; ++it)
        if((**it) == g) {
            delete *it;
            _grp.erase(it);
            found = true;
        }
    if(!found) throw Error(groupNotFound, "Requested group not found");
}
void LinqDB::addGroup(const Group& g) throw(Error) {
    bool found = false;
    for(list<Group*>::iterator it = _grp.begin(); it != _grp.end() && !found; ++it)
        if((**it) == g) found = true;
    if(!found) {
        Group& gg = const_cast<Group&> (g);
        gg.addMember(this->find(g.admin()));
        _grp.push_back(static_cast<Group*> (&gg));
    }
    else throw Error(dupGroup, "A group with the same name already exists");
}
void LinqDB::addMemberToGroup(const Group& g, const Username& u) {
    bool found = false;
    list<Group*>::iterator it = _grp.begin();
    for(; it != _grp.end() && !found; ++it)
        if((**it) == g) found = true;
    if(found) (*it)->addMember(find(u));
}
void LinqDB::addPostToGroup(const Group& g, const Post& p) {
    list<Group*>::iterator it = _grp.begin();
    for(; it != _grp.end(); ++it)
        if((**it) == g)
            (*it)->insertPost(p);
}
void LinqDB::addUser(User* u) throw(Error) {
    list<SmartPtr<User> >::iterator it = _db.begin();
    bool alreadyIn = false;
    for(; it != _db.end() && !alreadyIn; ++it) {
        if(((*it)->account()->username()) == (u->account()->username()))
            alreadyIn = true;
    }
    if(!alreadyIn) _db.push_back(SmartPtr<User>(u));
    else throw Error(dupUser, "An user with that username already exists in Linqedin");
}
void LinqDB::removeUser(const Username& usr) throw(Error) {
    list<SmartPtr<User> >::iterator it = _db.begin();
    bool found = false;
    for(; it != _db.end() && !found; ++it)
        if(((*it)->account()->username().login()) == usr.login()) {
            found = true;
            _db.erase(it);
        }
    if(!found) throw Error(userNotFound, "Requested user not found");
}
User* LinqDB::find(const Username& usr) const {
    User* ret = NULL;
    list<SmartPtr<User> >::const_iterator it = _db.begin();
    for(; it != _db.end(); ++it)
        if(((*it)->account()->username().login()) == usr.login())
            // ret = (*it)->clone();
            ret = &(*(*it));
    return ret;
}
Group LinqDB::findGroubByName(const string& n) const throw(Error) {
    bool found = false;
    list<Group*>::const_iterator it = _grp.begin();
    for(; it != _grp.end() && !found; ++it)
        if((*it)->name() == n) {
            found = true;
            return **it;
        }
    throw Error(groupNotFound, "Requested group not found");
}
list<SmartPtr<User> > LinqDB::db() const {
    return _db;
}
list<SmartPtr<User> >::const_iterator LinqDB::begin() const{
    return _db.begin();
}
list<SmartPtr<User> >::const_iterator LinqDB::end() const{
    return _db.end();
}
list<Group*> LinqDB::allGroups() const {
    return _grp;
}
list<Post*> LinqDB::postsFromGroup(const Group& g) const {
    list<Group*>::const_iterator i;
    for(i = _grp.begin(); i != _grp.end(); ++i)
        if((**i) == g)
            return (*i)->posts();
}
int LinqDB::postNumberFromGroup(const Group& g) const {
    list<Group*>::const_iterator i;
    for(i = _grp.begin(); i != _grp.end(); ++i)
        if((**i) == g)
            return (*i)->postNumber();
    return 0;
}
Username LinqDB::getAdmin() const throw(Error) {
    QFile loadDB("database.json");
    if (!loadDB.open(QIODevice::ReadOnly))
        throw Error(IO, "Database not found");
    QByteArray saveData = loadDB.readAll();
    loadDB.close();

    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    QJsonObject db = doc.object();
    QJsonObject adm = db["admin"].toObject();
    Username u(adm["username"].toString().toStdString(), adm["password"].toString().toStdString());
    return u;
}