#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "node.h"

template <typename T>
class SelfList {
    public: 
        enum Method {
            Move, Count, Transpose
        };

    protected:
        Node<T>* head;
        Node<T>* tail;
        Method method;
        int nodes;

    public:
        SelfList(Method method) : head(nullptr),tail(nullptr),method(method),nodes(0){};

        bool insert(T data) {
            Node<T>* temp = new Node<T>(data);
            if(nodes == 0){
                this->head = temp;
                this->tail = temp;
            }
            else{
                this->tail->next = temp;
                this->tail = temp;
            }
            (this->nodes)++;
        }

        bool inList(T data, Node<T> **&pointer){
            while((*pointer) != nullptr){

                if ((*pointer)->data == data){
                    return true;
                }
                pointer = &((*pointer)->next);
            }
            return false;
        }

        bool remove(T data) {
            Node<T>** tempA = &(this->head);
            bool check = inList(data,tempA);

            if (check){
                Node<T>* tempB = (*tempA)->next;

                //update tail
                if (*tempA == this->tail) {
                    int size = this->nodes-2;
                    Node<T>* prev = this->head;

                    while(size>0){
                        prev = prev->next;
                    }

                    this->tail = prev;
                }

                delete (*tempA);
                (*tempA) = tempB;

                (this->nodes)--;

                return true;
            }

            return false;

        }

        bool find(T data) {

            Node<T>** tempA = &(this->head);
            bool check = inList(data,tempA);
            if (check){
                switch(this->method){
                    case Move: {
                        if(*tempA != this->head) {

                            Node<T>* tempB = this->head;
                            while (tempB->next != *tempA) {
                                tempB = tempB->next;
                            }
                            
                            std::swap(tempB->data, (*tempA)->data);
                        }
                        break;
                    }
                    case Count: {
                        (*tempA)->count++;
                        if(*tempA != this->head) sortCount(tempA);
                        break;
                    }
                    case Transpose: {
                        if(*tempA != this->head) std::swap(this->head->data,(*tempA)->data);
                        break;
                    }
                }
                return true;
            }
            return false;
        }

        void sortCount(Node<T> **&pointer){
            Node<T>* temp = this->head;
            bool sort = false;
            while( !sort ){
                if ((*pointer)->count >= temp->count ){
                    std::swap((*pointer)->data, temp->data);
                    std::swap((*pointer)->count, temp->count);
                    break;
                }
                temp = temp->next;
            }
        }

        T operator [] (int index) {
            if(0 <= index && index < (this->nodes)) {
                Node<T>* temp = this->head;
                while (index--){
                    temp = temp->next;
                }
                return temp->data;
            }
            else return -1;
        }
             
        int size() {
            return this->nodes;
        }

        void print() {
            int length = this->nodes;
            Node<T>* temp = this->head;
            while(length != 0){
                std::cout<<temp->data<<" ";
                temp = temp->next;
                length--;
            }
            std::cout<<"\n";
        }
        void clear() {
            this->tail = nullptr;

            this->head->killSelf();
            this->head = nullptr;

            this->nodes = 0;
        }
        ~SelfList() {
            if(nodes!=0) clear();
        }  
};

#endif