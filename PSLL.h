#ifndef PSLL_H
#define PSLL_H

#include "List.h"
#include <iostream>
#include <stdexcept>
namespace cop3530 {

template < typename E >
class PSLL : public List<E> {
public:
    PSLL();
    ~PSLL() override;
    PSLL(PSLL<E>& ssl); //copy constructor
    PSLL(PSLL<E>&& ssl); //move constructor
    PSLL<E>& operator=(PSLL<E>& ssl); // copy assignment operator
    PSLL<E>& operator=(PSLL<E>&& ssl); // move assignment


    void insert( E element, size_t position ) override;
    void push_back( E element ) override;
    void push_front( E element ) override;
    void replace( E element, size_t position ) override;
    
    E pop_back() override;
    E pop_front() override;
    E item_at( size_t position ) override;
    E peek_back() override;
    E peek_front() override;
    void remove( size_t position ) override;
    
    bool is_empty() override;
    bool is_full() override;
    bool contains( E element, bool (*equals_function)(E,E)) override;

    size_t length() override;
    void clear() override;
    void print( std::ostream stream ) override;
    E* contents() override;

    
private:
    struct Node {
        Node(Node * n, E d);
        ~Node();
        Node * next;
        E data;
    };

    Node* head_active;

    Node* head_pool;
    int pool_size;

    Node* new_node(Node * n, E d);
    void delete_node(Node * n);
};

//Public functions

template <typename E>
PSLL<E>::Node::Node(Node * n, E d) {
    next = n;
    data = d;
}

template <typename E>
PSLL<E>::Node::~Node() {
    //delete
}

template <typename E>
PSLL<E>::PSLL() {
    head_active = nullptr; 
    head_pool = nullptr;
    pool_size = 0;
};

template <typename E>
PSLL<E>::~PSLL() {
    Node* temp;
    while(head_active) {
        temp = head_active;
        head_active = head_active->next;
        delete temp;
    }
    while(head_pool) {
        temp = head_pool;
        head_pool = head_pool->next;
        delete temp;
    }
};

//--------------------------------------------------------------------------------------------------------------

//copy constructor
template <typename E>
PSLL<E>::PSLL(PSLL<E>& psll) { 
    head_active = nullptr;
    head_pool = nullptr;
    pool_size = 0;
    size_t size = psll.length();
    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < size; ++i )
        this->push_back(psll.item_at(i));
};

//move constructor
template <typename E>
PSLL<E>::PSLL(PSLL<E>&& psll) {
    head_active = psll.head_active;
    head_pool = nullptr;
    pool_size = 0;
    psll.head_active = nullptr;

    while(psll.head_pool) {
        Node* temp = psll.head_pool;
        psll.head_pool = psll.head_pool->next;
        delete temp;
    }
};

// copy assignment operator
template <typename E>
PSLL<E>& PSLL<E>::operator=(PSLL<E>& psll) {
    Node* temp;
    while(head_active) {
        temp = head_active;
        head_active = head_active->next;
        delete temp;
    }

    head_active = nullptr;
    head_pool = nullptr;
    pool_size = 0;

    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    size_t size = psll.length();
    for(int i = 0; i < size; ++i )
        this->push_back(psll.item_at(i));

    
    return *this;
};

// move assignment
template <typename E>
PSLL<E>& PSLL<E>::operator=(PSLL<E>&& psll) {
    
    if(this!=&psll) // prevent self-move
    {
        Node* temp;
        while(head_active) {
            temp = head_active;
            head_active = head_active->next;
            delete temp;
        }
        
        while(psll.head_pool) {
            temp = psll.head_pool;
            psll.head_pool = psll.head_pool->next;
            delete temp;
        }

        head_active = psll.head_active;
        psll.head_active = nullptr;
    }
    return *this;
};

//-----------------------------------------------------------------------------------------------------------------

template <typename E>
void PSLL<E>::insert( E element, size_t position ) {
    Node* temp = head_active;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = new_node(temp->next, element);
};

template <typename E>
void PSLL<E>::push_back( E element ) {
    if(is_empty())  {
        head_active = new_node(nullptr, element);
    }
    else {
        Node* temp = head_active;
        Node* val = nullptr;
        while(temp) {
            val = temp;
            temp = temp->next;
        }
        val->next = new_node(nullptr, element);
    }
};

template <typename E>
void PSLL<E>::push_front( E element ) {
    head_active = new_node(head_active, element);
};

template <typename E>
void PSLL<E>::replace( E element, size_t position ) {
    Node* temp = head_active;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    
    Node* to_be_deleted = temp->next;
    temp->next = new_node(temp->next->next, element);
    
    delete_node(to_be_deleted);
};


template <typename E>
E PSLL<E>::pop_back() {
    if( is_empty())
        throw std::runtime_error( "PSLL<E>::pop_back(): empty list" );
    
    Node* temp = head_active;
    Node* further = nullptr;
    Node* shorter = nullptr;

    while(temp) {
        shorter = further;
        further = temp;
        temp = temp->next;
    }

    if(shorter)  {
        shorter->next = nullptr;
        int tempInt = further->data;
        delete_node(further);
        return tempInt;
    }
    else {
        head_active = nullptr;
        int tempInt = further->data;
        delete_node(further);
        return tempInt;
    }
};

template <typename E>
E PSLL<E>::pop_front() {
    if( is_empty())
        throw std::runtime_error( "PSLL<E>::pop_front(): empty list" );
    
    Node* temp = head_active;
    head_active = temp->next;

    int data = temp->data;
    delete_node(temp);
   
    return data;
};

template <typename E>
E PSLL<E>::item_at( size_t position ) {
    Node* temp = head_active;
    for(int i = 0; i < position; i++)
        temp = temp->next;
    return temp->data;
};

template <typename E>
E PSLL<E>::peek_back() {
    if( is_empty())
        throw std::runtime_error( "PSLL<E>::peek_back(): empty list" );

    Node* temp = head_active;
    Node* val = nullptr;
    while(temp) {
        val = temp;
        temp = temp->next;
    }
    return val->data;
};

template <typename E>
E PSLL<E>::peek_front() {
    if( is_empty())
        throw std::runtime_error( "PSLL<E>::peek_front(): empty list" );

    return head_active->data;
};

template <typename E>
void PSLL<E>::remove( size_t position ) {
    Node* temp = head_active;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    
    Node* to_be_deleted = temp->next;
    temp->next = to_be_deleted->next;
    delete_node(to_be_deleted);
};

template <typename E>
bool PSLL<E>::is_empty() {
    return !head_active;
};

template <typename E>
bool PSLL<E>::is_full() {
    return false;
};

template <typename E>
bool PSLL<E>::contains( E element, bool (*equals_function)(E,E)) {
    Node* temp = head_active;
    while(temp) {
        if(equals_function(temp->data, element)) return true;
        temp = temp->next;
    }
    return false;
};


template <typename E>
size_t PSLL<E>::length() {
    Node* temp = head_active;
    size_t counter = 0;
    while(temp) {
        temp = temp->next;
        counter++;
    }
    return counter;
};

template <typename E>
void PSLL<E>::clear() {
    Node* temp = head_active;
    while(head_active) {
        temp = head_active;
        head_active = head_active->next;
        delete_node(temp);
    }
    head_active = nullptr;
};

template <typename E>
void PSLL<E>::print( std::ostream stream ) {
    /*Node* temp = head_active;
    
    if(!temp) {
        stream << "<empty list>";
    }
    else {
        stream << "[";
        while(temp) {
            if(temp->next) stream << temp->data << ", ";
            else stream << temp->data << "]";
            temp = temp->next;
        }
    }*/
};

template <typename E>
E* PSLL<E>::contents() {
    size_t length = PSLL<E>::length();
    E* array = new E[length];
    Node* temp = head_active;
    for(int i = 0; i < length; i++){
        array[i] = temp->data;
        temp = temp->next;
    }
    return array;
};

//Private functions

template <typename E>
typename PSLL<E>::Node* PSLL<E>::new_node(Node * n, E d) {
    if(head_pool) {
        Node * temp = head_pool;
        head_pool = head_pool->next;
        temp->data = d;
        temp->next = n;
        --pool_size;
        return temp;
    }
    else {
        return new Node( n, d );
    }
};

template <typename E>
void PSLL<E>::delete_node(Node * n) {

    if(pool_size < 50) {
        ++pool_size;
        n->next = head_pool;
        head_pool = n;
    } 
    else {
        delete n;
    }
};

}

#endif