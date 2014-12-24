template <class T>
void SmartPtr<T>::RefCounter::addRef() {
    count++;
}
template <class T>
int SmartPtr<T>::RefCounter::release() {
    return --count;
}
template <class T>
SmartPtr<T>::SmartPtr() : _ptr(0), ref(0) {
    ref = new RefCounter();
    ref->addRef();
}
template <class T>
SmartPtr<T>::SmartPtr(T* usr) : _ptr(usr), ref(0) {
    ref = new RefCounter();
    ref->addRef();
}
template <class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& spusr) : _ptr(spusr._ptr), ref(spusr.ref) {
    ref->addRef();
}
template <class T>
SmartPtr<T>::~SmartPtr() {
    if(ref->release() == 0) {
        delete _ptr;
        delete ref;
    }
}
template <class T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& spusr) {
    if (this != &spusr) {
        if(ref->release() == 0) {
            delete _ptr;
            delete ref;
        }
        _ptr = spusr._ptr;
        // spusr._ptr = NULL;
        ref = spusr.ref;
        ref->addRef();
    }
    return *this;
}
template <class T>
T& SmartPtr<T>::operator*() const {
    return *_ptr;
}
template <class T>
T* SmartPtr<T>::operator->() const {
    return _ptr;
}
template <class T>
bool SmartPtr<T>::operator==(const SmartPtr<T>& spu) const{
    return(_ptr == spu._ptr);
}
template <class T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& spu) const{
    return(_ptr != spu._ptr);
}