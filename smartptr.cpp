template <class T>
SmartPtr<T>::SmartPtr() : _ptr(0) {}
template <class T>
SmartPtr<T>::SmartPtr(T* pointer) : _ptr(pointer->clone()) {}
template <class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& smartptr) : _ptr((smartptr._ptr)->clone()) {}
template <class T>
SmartPtr<T>::~SmartPtr() { delete _ptr;}
template <class T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& smartptr) {
    if (this != &smartptr) {
        delete _ptr;
        _ptr = (smartptr._ptr)->clone();
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
bool SmartPtr<T>::operator==(const SmartPtr<T>& smartptr) const{
    return(_ptr == smartptr._ptr);
}
template <class T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& smartptr) const{
    return(_ptr != smartptr._ptr);
}