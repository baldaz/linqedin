#include "post.h"

Post::Post(const Username& u, const string& c) : _author(u), _content(c) {}
// Post::~Post() {}
Username Post::author() const {
    return _author;
}
string Post::content() const {
    return _content;
}