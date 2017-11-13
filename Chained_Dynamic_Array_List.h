#ifndef CHAINED_DYNAMIC_ARRAY_LIST_H
#define CHAINED_DYNAMIC_ARRAY_LIST_H

#include "List.h"
#include<iostream>
#include <stdexcept>
namespace cop3530 {

const int ARRAY_SIZE = 50;

template < typename E >
class Chained_Dynamic_Array_List : public List<E> {
public:
    Chained_Dynamic_Array_List();
    ~Chained_Dynamic_Array_List() override;
    Chained_Dynamic_Array_List(Chained_Dynamic_Array_List<E>& cdal); //copy constructor
    Chained_Dynamic_Array_List(Chained_Dynamic_Array_List<E>&& cdal); //move constructor
    Chained_Dynamic_Array_List<E>& operator=(Chained_Dynamic_Array_List<E>& cdal); // copy assignment operator
    Chained_Dynamic_Array_List<E>& operator=(Chained_Dynamic_Array_List<E>&& cdal); // move assignment

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
        Node(Node * n,Node * p, E d);
        ~Node();
        
        Node * next;
        Node * previous;

        E* data;
    };

    Node* head;
    size_t tail;
};

//Public functions

template <typename E>
Chained_Dynamic_Array_List<E>::Node::Node(Node * next_node, Node * previous_node, E first_element) {
    next = next_node;
    previous = previous_node;


    data = new E[ARRAY_SIZE ];
    data[0] = first_element;
}

template <typename E>
Chained_Dynamic_Array_List<E>::Node::~Node() {
    delete data;
}

template <typename E>
Chained_Dynamic_Array_List<E>::Chained_Dynamic_Array_List() {
    head = nullptr; 
    tail = 0;
};

template <typename E>
Chained_Dynamic_Array_List<E>::~Chained_Dynamic_Array_List() {
    Node* n = nullptr;
    while(head) {
        n = head;
        head = head->next;
        delete n;
    }
};

//-----------------------------------------------------------------------------------------------------------

//copy constructor
template <typename E>
Chained_Dynamic_Array_List<E>::Chained_Dynamic_Array_List(Chained_Dynamic_Array_List<E>& cdal) { 
    head = nullptr;
    size_t size = cdal.length();
    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < size; ++i )
        this.push_back(cdal.item_at(i));
};

//move constructor
template <typename E>
Chained_Dynamic_Array_List<E>::Chained_Dynamic_Array_List(Chained_Dynamic_Array_List<E>&& cdal) {
    head = cdal.head;
    cdal.head = nullptr;
};

// copy assignment operator
template <typename E>
Chained_Dynamic_Array_List<E>& Chained_Dynamic_Array_List<E>::operator=(Chained_Dynamic_Array_List<E>& cdal) {
    Node* temp;
    while(head) {
        temp = head;
        head = head->next;
        delete temp;
    }

    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    size_t size = cdal.length();
    for(int i = 0; i < size; ++i )
        this.push_back(cdal.item_at(i));

    
    return *this;
};

// move assignment
template <typename E>
Chained_Dynamic_Array_List<E>& Chained_Dynamic_Array_List<E>::operator=(Chained_Dynamic_Array_List<E>&& cdal) {
    
    if(this!=&cdal) // prevent self-move
    {
        Node* temp;
        while(head) {
            temp = head;
            head = head->next;
            delete temp;
        }

        head = cdal.head;
        cdal.head = nullptr;
    }
    return *this;
};

//-------------------------------------------------------------------------------------------------------

//untested. Done?
template <typename E>
void Chained_Dynamic_Array_List<E>::insert( E element, size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CDAL:In insert(): list is empty." );
    if(position >= tail || position < 0)
        throw std::runtime_error( "CDAL:In insert(): invalid position" );

    Node* temp = head;
    size_t node_counter = 0;

    while((1 + node_counter)*ARRAY_SIZE <= position) {
        ++node_counter;
        temp = temp->next;
    }

    if((ARRAY_SIZE - 1) == tail%ARRAY_SIZE && !temp->next) { //if tail is pointing to the next node and a next node DNE.
        temp->next = new Node(nullptr, temp, element); //element is going in here but only as a place holder
        temp = temp->next;
    }

    for(int i = tail; i > (position - 1); i--) {
        if(i%ARRAY_SIZE  == 0) {
            temp->data[i%ARRAY_SIZE] = temp->previous->data[(--i)%ARRAY_SIZE ];
            temp = temp->previous;
        }
        temp->data[i%ARRAY_SIZE] = temp->data[i%ARRAY_SIZE  - 1];
    }

    if(temp != head)
        throw std::runtime_error( "Expecting head to be temp. It was not." );
     
    temp->data[position%ARRAY_SIZE] = element;

    ++tail;
};

template <typename E>
void Chained_Dynamic_Array_List<E>::push_back( E element ) {
    if(is_empty() && !head) {
        head = new Node(nullptr, nullptr, element);        
    } else if (is_empty()) {
        head->data[tail] = element;
    } else {
        Node* temp = head;
        int counter = -1;

        while(++counter != tail/ARRAY_SIZE) 
            temp = temp->next;
        
        if((ARRAY_SIZE - 1) == tail%ARRAY_SIZE && !temp->next) {
            temp->next = new Node(nullptr, temp, element); 
        } else {
            temp->data[tail%ARRAY_SIZE] = element;
        }
    }
    ++tail;
};

template <typename E>
void Chained_Dynamic_Array_List<E>::push_front( E element ) {
    if(is_empty() && !head) {
        head = new Node(nullptr, nullptr, element);        
    } else if (is_empty()) {
        head->data[tail] = element;
    } else {
        Node* temp = head;
        int counter = -1;

        while(++counter != tail/ARRAY_SIZE) 
            temp = temp->next;
        
        if((ARRAY_SIZE - 1) == tail%ARRAY_SIZE && !temp->next) 
            temp->next = new Node(nullptr, temp, element); //element is going in here but it is just a place holder

        for(int i = tail; i > 0; i--) {
            if(i%ARRAY_SIZE  == 0) {
                temp->data[i%ARRAY_SIZE ] = temp->previous->data[(--i)%ARRAY_SIZE ];
                temp = temp->previous;
            }
            temp->data[i%ARRAY_SIZE] = temp->data[i%ARRAY_SIZE  - 1];
        }

        //if(temp != head)
        //  throw std::runtime_error( "Expecting head to be temp. It was not." );
        
        temp->data[0] = element;
    }

    ++tail;
};

template <typename E>
void Chained_Dynamic_Array_List<E>::replace( E element, size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CDAL:In insert(): list is empty." );
    if(position >= tail || position < 0)
        throw std::runtime_error( "CDAL:In insert(): invalid position" );

    Node* temp = head;
    size_t node_counter = 0;

    while((1 + node_counter)*ARRAY_SIZE <= position) {
        ++node_counter;
        temp = temp->next;
    }

    if(temp != head)
        throw std::runtime_error( "Expecting head to be temp. It was not." );
 
    temp->data[position%ARRAY_SIZE] = element;
};


template <typename E>
E Chained_Dynamic_Array_List<E>::pop_back() {
    if( is_empty())
        throw std::runtime_error( "Chained_Dynamic_Array_List<E>::pop_back(): empty list" );
    
    Node* temp = head;
    int counter = -1;
    
    while(++counter != (tail-1)/ARRAY_SIZE) 
        temp = temp->next;

    if((ARRAY_SIZE - 1) == (tail - 1)%ARRAY_SIZE && temp->next) { //if tail will be pointing to the previous node and the next node of the soon to be empty array exists
        delete temp->next;
        temp->next = nullptr;
    }
    
    return temp->data[(--tail)%ARRAY_SIZE];
};

template <typename E>
E Chained_Dynamic_Array_List<E>::pop_front() {
    if(is_empty()) {
        throw std::runtime_error( "Chained_Dynamic_Array_List<E>::pop_front(): empty list" );
    } else {
        Node* temp = head;
        E element = head->data[0];
    
        for(int i = 0; i < tail; ++i) {
            if(i%ARRAY_SIZE  == ARRAY_SIZE - 1) {
                temp->data[i%ARRAY_SIZE ] = temp->next->data[(++i)%ARRAY_SIZE ];
                temp = temp->next;
            }
            temp->data[i%ARRAY_SIZE ] = temp->data[i%ARRAY_SIZE  + 1];
        }
        if((ARRAY_SIZE - 1) == (--tail)%ARRAY_SIZE && temp->next) { //if tail will be pointing to the previous node and the next node of the now empty array exists
            delete temp->next;
            temp->next = nullptr;
        }
        return element;
    }
};

template <typename E>
E Chained_Dynamic_Array_List<E>::item_at( size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CDAL:In insert(): list is empty." );
    if(position >= tail || position < 0)
        throw std::runtime_error( "CDAL:In insert(): invalid position" );

    Node* temp = head;
    size_t node_counter = 0;

    while((1 + node_counter)*ARRAY_SIZE <= position) {
       ++node_counter;
       temp = temp->next;
    }

    if(temp != head)
        throw std::runtime_error( "Expecting head to be temp. It was not." );

    return temp->data[position%ARRAY_SIZE];
};

template <typename E>
E Chained_Dynamic_Array_List<E>::peek_back() {
    if( is_empty())
        throw std::runtime_error( "Chained_Dynamic_Array_List<E>::peek_back(): empty list" );

    Node* temp = head;
    int counter = -1;

    while(++counter != (tail-1)/ARRAY_SIZE) 
        temp = temp->next;

    return temp->data[(tail-1)%ARRAY_SIZE];
};

template <typename E>
E Chained_Dynamic_Array_List<E>::peek_front() {
    if( is_empty())
        throw std::runtime_error( "Chained_Dynamic_Array_List<E>::peek_front(): empty list" );
    return head->data[0];
};

template <typename E>
void Chained_Dynamic_Array_List<E>::remove( size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CDAL:In insert(): list is empty." );
    if(position >= tail || position < 0)
        throw std::runtime_error( "CDAL:In insert(): invalid position" );

    Node* temp = head;
    size_t node_counter = 0;

    while((1 + node_counter)*ARRAY_SIZE <= position) {
        ++node_counter;
        temp = temp->next;
    }

    for(int i = position; i < tail; i++) {
        if(i%ARRAY_SIZE  == 0) {
            temp->data[i%ARRAY_SIZE ] = temp->previous->data[(--i)%ARRAY_SIZE ];
            temp = temp->previous;
        }
        temp->data[i%ARRAY_SIZE] = temp->data[i%ARRAY_SIZE  + 1];
    }

    if((ARRAY_SIZE - 1) == (tail - 1)%ARRAY_SIZE && temp->next) { //if tail will be pointing to the previous node and the next node of the soon to be empty array exists
        int counter = 0;
        while(++counter != (tail-1)/ARRAY_SIZE) 
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }

    if(temp != head)
        throw std::runtime_error( "Expecting head to be temp. It was not." );
};

template <typename E>
bool Chained_Dynamic_Array_List<E>::is_empty() {
    return tail == 0;
};

template <typename E>
bool Chained_Dynamic_Array_List<E>::is_full() {
    return false;
};

template <typename E>
bool Chained_Dynamic_Array_List<E>::contains( E element, bool (*equals_function)(E,E)) {
    Node* temp = head;
    int counter = -1;

    while(++counter <= tail/ARRAY_SIZE) {
        for(int i = 0; i < ARRAY_SIZE; i++) {
            if(equals_function(temp->data[i], element)) return true;
        }
        temp = temp->next;
    }
    return false;
};


template <typename E>
size_t Chained_Dynamic_Array_List<E>::length() {
    return tail;
};

template <typename E>
void Chained_Dynamic_Array_List<E>::clear() {
    tail = 0;
};

template <typename E>
void Chained_Dynamic_Array_List<E>::print( std::ostream stream ) {
    /*Node* temp = head;
    
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
E* Chained_Dynamic_Array_List<E>::contents() {
    size_t size = length();
    E* array = new E[size];
    Node* temp = head;
    
    for(int node_counter = 0; node_counter <= size/50; node_counter++) {
        for(int i = 0; i < ARRAY_SIZE ; ) {
            array[node_counter*ARRAY_SIZE  + i] = temp->data[i];
            if(node_counter*ARRAY_SIZE + ++i == size) return array;
        }
        temp = temp->next;
    }
    return array;
};

//Private functions


}

#endif