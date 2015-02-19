#ifndef LOADER_H
#define LOADER_H


class Username;
class LinqClient;
class LinqDB;

class Loader {
private:
    LinqDB* _db;
public:
    Loader();
    ~Loader();
    bool isAdmin(const Username&) const;
    LinqClient* getClientHandle(const Username&) const;
};
#endif