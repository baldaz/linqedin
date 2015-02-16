#ifndef AVATAR_H
#define AVATAR_H

#include <string>

using std::string;
const string STANDARD_AVATAR = "img/port2.jpg";

class Avatar {
private:
	string _path;
public:
	Avatar(const string& = STANDARD_AVATAR);
    Avatar(const Avatar&);
	string path() const;
};

#endif