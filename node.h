#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    int count;

    Node(T value){
        this->data = value;
        next = nullptr;
        count = 0;
    }
    void killSelf();
};

template <typename T>
void Node<T>::killSelf() {
    if (next) {
        next->killSelf();
    }
    delete this;
}
#endif