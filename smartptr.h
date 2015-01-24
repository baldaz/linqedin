#ifndef SMARTPTR_H
#define SMARTPTR_H

template <class T>
class SmartPtr {
private:
    T* _ptr;
public:
    SmartPtr();
    SmartPtr(T*);
    SmartPtr(const SmartPtr&);
    ~SmartPtr();
    SmartPtr& operator=(const SmartPtr&);
    T& operator*() const;
    T* operator->() const;
    bool operator==(const SmartPtr&) const;
    bool operator!=(const SmartPtr&) const;
};

#include "smartptr.cpp"

// template<typename T>
// class SmartPtr{
//     T* pointer;
//     std::size_t *refs;

//     void clear(){
//         if (!--*refs){
//             delete pointer;
//             delete refs;
//         }
//     }

// public:
//     SmartPtr(T* p = NULL)
//         : pointer(p), refs(new std::size_t(1))
//     {}
//     SmartPtr(const SmartPtr<T>& other)
//         : pointer(other.pointer), refs(other.refs)
//     {
//         ++*refs;
//     }
//     ~SmartPtr(){
//         clear();
//     }

//     SmartPtr<T>& operator=(const SmartPtr<T>& other){
//         if (this != &other){
//             clear();

//             pointer = other.pointer;
//             refs    = other.refs;
//             ++*refs;
//         }
//         return *this;
//     }

//     SmartPtr<T>& operator=(T* p){
//         if (pointer != p){
//             pointer = p;
//             *refs = 1;
//         }
//         return *this;
//     }

//     T& operator*() const{
//         return *pointer;
//     }

//     // const T& operator*() const{
//     //     return *pointer;
//     // }

//     T* operator->() const{
//         return pointer;
//     }

//     // const T* operator->() const{
//     //     return pointer;
//     // }

//     std::size_t getCounts(){
//         return *refs;
//     }
// };
// template <class T>
// class SmartPtr {
//     class U_Ptr {
//     public:
//         friend class HasPtr;
//         T *ip;
//         size_t use;
//         U_Ptr(T *p): ip(p), use(1) { }
//         ~U_Ptr() { delete ip; }
// };
// public:
//     SmartPtr(T *p, int i=0): ptr(new U_Ptr(p)), val(i) { }
//     SmartPtr(const SmartPtr &orig):
//     ptr(orig.ptr), val(orig.val) { ++ptr->use; }
//     SmartPtr& operator=(const SmartPtr&) {}
//     T& operator*() const { return *(ptr->ip);}
//     T* operator->() const { return ptr->ip;}
// private:
//     U_Ptr *ptr;        // points to use-counted U_Ptr class
//     int val;
// };
#endif