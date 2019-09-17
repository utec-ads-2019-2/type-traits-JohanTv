#ifndef TRAITS_LIST_H
#define TRAITS_LIST_H

#include "node.h"

template <typename Tr>
class TraitsList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
      
    private:
        Node<T>* head;
        int nodes;
        Operation cmp;

        bool find(T data, Node<T> **&pointer) {
            while((*pointer) != nullptr){

                if ((*pointer)->data == data){
                    return true;
                }
                else if(cmp(data,(*pointer)->data)){
                    break;
                }
                pointer = &((*pointer)->next);
            }
            return false;

        }
              
    public:
        TraitsList() : head(nullptr),nodes(0){};
             
        bool insert(T data) {
            Node<T>** tempA = &(this->head);
            if(!find(data, tempA)){
                Node<T>* node = new Node<T>(data);
                Node<T>* tempB = (*tempA);

                node->next = tempB;
                (*tempA) = node;

                (this->nodes)++;

                return true;
            }
            return false;
        }
             
        bool remove(T data) {
            Node<T>** tempA = &(this->head);
            if(find(data,tempA)){
                Node<T>* tempB = (*tempA);
                (*tempA) = tempB->next;
                delete tempB;

                (this->nodes)--;
                return true;
            }
            return false;
        }  

        bool find(T data){
            Node<T>** temp = &(this->head);
            return find(data,temp);

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

        void clear(){
            //this->tail = nullptr;

            this->head->killSelf();
            this->head = nullptr;

            this->nodes = 0;
        }

        ~TraitsList() {
            if(nodes != 0) clear();
        }         
};

#endif