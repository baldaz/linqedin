#include "dispatcher.h"
#include "info.h"
#include <iostream>

Dispatcher::~Dispatcher() {}
string DispatcherHtml::dispatch(const UserInfo& info) const {
    std::ostringstream o;
    o << info.age();
    string html = "";
    html = "<html><body>";
    html += "<h2>" + info.name() + " " + info.surname() + "</h2>";
    if(info.age() > -1)
        html += "<p style='font-weight: 400; font-size:14px;'> " + o.str() + " years old<br>";
    html += info.address() + "</p>";
    vector<string>::const_iterator it;
    vector<string> _interests = info.interests();
    if(!_interests.empty()) {
        html += "<h4><img src='img/rugby100.png'>  Interests</h4><p style='font-weight: 400; font-size:14px;line-height:26px'>";
        it = _interests.begin();
        for(; it < _interests.end(); ++it)
            html += "<span style='background-color:rgba(102,102,156,.5);'>&nbsp;" + *it + "&nbsp;</span>&nbsp;&nbsp;";
        html += "</p>";
    }
    vector<string> _skills = info.skills();
    if(!_skills.empty()) {
        html += "<h4><img src='img/atom2.png'>  Skills</h4><p style='font-weight: 400; font-size:14px; line-height:26px;'>";
        it = _skills.begin();
        for(; it < _skills.end(); ++it)
            html += "<span style='background-color:rgba(102,102,102,.5);'>&nbsp;"  + *it + "&nbsp;</span>&nbsp;&nbsp;";
        html += "</p>";
    }
    vector<string> _languages = info.languages();
    if(!_languages.empty()) {
        html += "<h4><img src='img/flag27.png'>  Languages</h4><p style='font-weight: 400; font-size:14px;'>";
        it = _languages.begin();
        for(; it < _languages.end(); ++it)
            html += *it + " ";
        html += "</p>";
    }
    list<Experience*> _exp = info.experiences();
    if(!_exp.empty()) {
        html += "<h4><img src='img/graduate34.png'>  Educations</h4><ul style='font-weight: 400; font-size:14px;'>";
        list<Experience*>::const_iterator itr = _exp.begin();
        string jobs = "";
        bool job = false;
        for(; itr != _exp.end(); ++itr) {
            if((*itr)->type() == 0)
                if(itr == _exp.end())
                    html += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
                else
                    html += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
            else if((*itr)->type() == 1) {
                job = true;
                if(itr == _exp.end())
                    jobs += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
                else
                    jobs += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
            }
        }
        if(job) {
            html += "</ul><h4><img src='img/work3.png'>  Job Experiences</h4><ul style='font-weight: 400; font-size:14px;'>";
            html += jobs;
        }
    }
    html += "</ul>";
    if(!info.email().empty() || !info.telephon().empty() || !info.address().empty())
        html += "<h4><img src='img/business133.png'>  Contacts</h4><p style='font-weight: 400; font-size:14px'>E-mail: " + info.email() + " &nbsp;&nbsp;<br>Website: <a style='color:#4782EC;' href='#'>" + info.website() + "</a><br> Telephon: " + info.telephon() + "</p>";
    return html;
}

string DispatcherHtml::dispatch(const Bio& bio) const {
    std::ostringstream o;
    o << bio.age();
    string html = "";
    html = "<html><body>";
    html += "<h2>" + bio.name() + " " + bio.surname() + "</h2>";
    if(bio.age() > -1)
        html += "<p style='font-weight: 400; font-size:14px;'> " + o.str() + " years old<br>";
    html += bio.address() + "</p>";
    vector<string>::const_iterator it;
    vector<string> _interests = bio.interests();
    if(!_interests.empty()) {
        html += "<h4><img src='img/rugby100.png'>  Interests</h4><p style='font-weight: 400; font-size:14px;line-height:26px'>";
        it = _interests.begin();
        for(; it < _interests.end(); ++it)
            html += "<span style='background-color:rgba(102,102,156,.5);'>&nbsp;" + *it + "&nbsp;</span>&nbsp;&nbsp;";
        html += "</p>";
    }
    vector<string> _skills = bio.skills();
    if(!_skills.empty()) {
        html += "<h4><img src='img/atom2.png'>  Skills</h4><p style='font-weight: 400; font-size:14px; line-height:26px;'>";
        it = _skills.begin();
        for(; it < _skills.end(); ++it)
            html += "<span style='background-color:rgba(102,102,102,.5);'>&nbsp;"  + *it + "&nbsp;</span>&nbsp;&nbsp;";
        html += "</p>";
    }
    vector<string> _languages = bio.languages();
    if(!_languages.empty()) {
        html += "<h4><img src='img/flag27.png'>  Languages</h4><p style='font-weight: 400; font-size:14px;'>";
        it = _languages.begin();
        for(; it < _languages.end(); ++it)
            html += *it + " ";
        html += "</p>";
    }
    list<Experience*> _exp = bio.experiences();
    if(!_exp.empty()) {
        html += "<h4><img src='img/graduate34.png'>  Educations</h4><ul style='font-weight: 400; font-size:14px;'>";
        list<Experience*>::const_iterator itr = _exp.begin();
        string jobs = "";
        bool job = false;
        for(; itr != _exp.end(); ++itr) {
            if((*itr)->type() == 0)
                if(itr == _exp.end())
                    html += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
                else
                    html += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
            else if((*itr)->type() == 1) {
                job = true;
                if(itr == _exp.end())
                    jobs += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
                else
                    jobs += "<li>" + (*itr)->role() + " at " + (*itr)->location() + " from " + (*itr)->from().toString("dd.MM.yyyy").toStdString() + " to " + (*itr)->to().toString("dd.MM.yyyy").toStdString() + "</li>";
            }
        }
        if(job) {
            html += "</ul><h4><img src='img/work3.png'>  Job Experiences</h4><ul style='font-weight: 400; font-size:14px;'>";
            html += jobs;
        }
    }
    html += "</ul>";
    if(!bio.email().empty() || !bio.telephon().empty() || !bio.address().empty())
        html += "<h4><img src='img/business133.png'>  Contacts</h4><p style='font-weight: 400; font-size:14px'>E-mail: " + bio.email() + " &nbsp;&nbsp;<br>Website: <a style='color:#4782EC;' href='#'>" + bio.website() + "</a><br> Telephon: " + bio.telephon() + "</p>";
    if(!(bio.bio()).empty()) {
        html += "<h4><img src='img/user91.png'> Short Summary</h4>";
        html += "<p style='font-weight:400'>" + bio.bio() + "</p>";
    }
    return html;
}