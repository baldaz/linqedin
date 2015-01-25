#include "portrait.h"

Portrait::Portrait(const string& p, int s) : _path(p) {
	// throw exception if image size exceed 300 kb
	std::ifstream file(_path, ios::binary | ios:ate);
	if((file.tellg() / 1000) > 300) throw Error();
	else s = file.tellg(); 
}
string Portrait::size() const {
	return _size;
}
