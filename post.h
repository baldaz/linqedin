#ifndef POST_H
#define POST_H

#include <string>
#include "username.h"

using std::string;

class Post {
private:
    Username _author;
    string _content;
public:
    Post(const Username&, const string& = "");
    Username author() const;
    string content() const;
};
#endif