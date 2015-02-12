#ifndef ADS_H
#define ADS_H

#include <string>
#include <list>

using std::string;
using std::list;

class Username;

class Ads {
private:
    string _title, _description;
    list<Username*> _candidates;
public:
    Ads(const string&, const string&);
    // Ads(const Ads&);
    string title() const;
    string description() const;
    list<Username*> candidates() const;
    bool operator==(const Ads&) const;
    void addCandidate(const Username&);
};
#endif