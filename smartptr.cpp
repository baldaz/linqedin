template <typename T>
void SmartPtr<T>::RefCounter::addRef() {
    count++;
}
template <typename T>
int SmartPtr<T>::RefCounter::release() {
    return --count;
}
template <typename T>
SmartPtr<T>::SmartPtr(T* usr) : _ptr(usr), ref(0) {
    ref = new RefCounter();
    ref->addRef();
}
template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& spusr) : _ptr(spusr._ptr), ref(spusr.ref) {
    ref->addRef();
}
template <typename T>
SmartPtr<T>::~SmartPtr() {
    if(!ref->release()) {
        delete _ptr;
        delete ref;
    }
}
template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& spusr) {
    if (this != &spusr) {
        if(ref->release() == 0) {
            delete _ptr;
            delete ref;
        }
        _ptr = spusr._ptr;
        ref = spusr.ref;
        ref->addRef();
    }
    return *this;
}
template <typename T>
T& SmartPtr<T>::operator*() const {
    return *_ptr;
}
template <typename T>
T* SmartPtr<T>::operator->() const {
    return _ptr;
}
template <typename T>
bool SmartPtr<T>::operator==(const SmartPtr& spu) const{
    return(_ptr == spu._ptr);
}
template <typename T>
bool SmartPtr<T>::operator!=(const SmartPtr& spu) const{
    return(_ptr != spu._ptr);
}