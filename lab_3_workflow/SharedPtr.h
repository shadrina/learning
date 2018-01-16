#ifndef LAB_3_WORKFLOW_SHAREDPTR_H
#define LAB_3_WORKFLOW_SHAREDPTR_H


template <typename T>
class SharedPtr {
private:
    T *obj;
    int *ref_counter;
public:
    SharedPtr();
    explicit SharedPtr(T *);
    SharedPtr(const SharedPtr<T> &);
    ~SharedPtr();
    T * operator->();
    T & operator*();
    SharedPtr<T> & operator=(const SharedPtr<T> &);
    bool operator==(T *);
    bool operator!=(T *);
};

template<typename T>
SharedPtr<T>::SharedPtr() : obj(nullptr) {
    ref_counter = new int(0);
}

template<typename T>
SharedPtr<T>::SharedPtr(T *obj_) : obj(obj_) {
    ref_counter = new int(1);
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &ptr) {
    obj = ptr.obj;
    ref_counter = ptr.ref_counter;
    (*(this->ref_counter))++;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    (*ref_counter)--;
    if (*ref_counter == 0) {
        delete obj;
        delete ref_counter;
        obj = nullptr;
        ref_counter = nullptr;
    }
}

template<typename T>
T * SharedPtr<T>::operator->() {
    return obj;
}

template<typename T>
T & SharedPtr<T>::operator*() {
    return *obj;
}

template<typename T>
SharedPtr<T> & SharedPtr<T>::operator=(const SharedPtr & ptr) {
    if (ptr.obj != this->obj && this != &ptr) {
        (*ref_counter)--;
        if (*ref_counter == 0) {
            delete obj;
            delete ref_counter;
        }
        ref_counter = ptr.ref_counter;
        (*ref_counter)++;
        obj = ptr.obj;
    }
    return *this;
}

template<typename T>
bool SharedPtr<T>::operator==(T *ptr) {
    return obj == ptr;
}

template<typename T>
bool SharedPtr<T>::operator!=(T *ptr) {
    return obj != ptr;
}


#endif //LAB_3_WORKFLOW_SHAREDPTR_H
