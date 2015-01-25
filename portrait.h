#include<iostream>
#include<fstream>
#include<string>

using std::string;
using std::ios;

class Portrait {
private:
	string _path;
	int _size;
public:
	Portrait(const string& = "", int = 0);
	string path() const;
};
