#include "avatar.h"

Avatar::Avatar(const string& p) {
    if(p == "") _path = STANDARD_AVATAR;
    else _path = p;
}
Avatar::Avatar(const Avatar& a) : _path(a._path) {}
string Avatar::path() const {
    return _path;
}
