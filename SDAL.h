#ifndef SDAL_H
#define SDAL_H

#include "List.h"
#include <iostream>
#include <stdexcept>
namespace cop3530 {

template < typename E >
class SDAL : public List<E> {
public:
    SDAL(size_t size);
    ~SDAL() override;
    SDAL(SDAL<E>& sdal); //copy constructor
    SDAL(SDAL<E>&& sdal); //move constructor
    SDAL<E>& operator=(SDAL<E>& sdal); // copy assignment operator
    SDAL<E>& operator=(SDAL<E>&& sdal); // move assignment

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
    E* array;
    size_t length_of_array;
    size_t tail;
    
    void  next_index();
    void  previous_index();
};

//Public functions

template <typename E>
SDAL<E>::SDAL(size_t size = 50) {
    if(size < 2)
        throw std::runtime_error( "SDAL:In constructor: size needs to be at least 2." );
    
    array = new E[size];
    tail = 0;
    length_of_array = size;
};

template <typename E>
SDAL<E>::~SDAL() {
    delete array;
};

//copy constructor
template <typename E>
SDAL<E>::SDAL(SDAL<E>& sdal) { 
    tail = sdal.length();
    length_of_array = tail;
    array = new E[tail];
    for(int i = 0; i < tail; ++i )
        this.array[i] = sdal.array[i];
};

//move constructor
template <typename E>
SDAL<E>::SDAL(SDAL<E>&& sdal) {
    tail = sdal.tail;
    length_of_array = sdal.length_of_array;
    array = sdal.array;
    sdal.head = nullptr;
};

// copy assignment operator
template <typename E>
SDAL<E>& SDAL<E>::operator=(SDAL<E>& sdal) {
    delete array;

    tail = sdal.tail;
    length_of_array = sdal.length_of_array;
    array = new E[length_of_array];
    for(int i = 0; i < tail; ++i )
        this.array[i] = sdal.array[i];
    
    return *this;
};

// move assignment
template <typename E>
SDAL<E>& SDAL<E>::operator=(SDAL<E>&& sdal) {
    
    if(this!=&sdal) // prevent self-move
    {
        delete this.array;
        tail = sdal.tail;
        length_of_array = sdal.length_of_array;
        this.array = sdal.array;
        sdal.array = nullptr;
    }
    return *this;
};


template <typename E>
void SDAL<E>::insert( E element, size_t position ) {

    if(is_empty())
        throw std::runtime_error( "SDAL:In insert(): list is empty." );
    if(position >= tail || position < 0)
        throw std::runtime_error( "SDAL:In insert(): invalid postition." );
    
    for(int i = tail-1; i > (position - 1); i--) 
        array[i + 1] = array[i];
    
    array[position] = element;
    next_index();
};

template <typename E>
void SDAL<E>::push_back( E element ) {
    array[tail] = element;
    next_index();
};

template <typename E>
void SDAL<E>::push_front( E element ) {
    for(int i = tail; i > 0; i--)
        array[i] = array[i-1];
    array[0] = element;
    next_index();
};

template <typename E>
void SDAL<E>::replace( E element, size_t position ) {
    if(is_empty())
        throw std::runtime_error( "SDAL:In replace(): list is empty." );
    if(position >= tail || position < 0)
        throw std::runtime_error( "SDAL:In replace(): invalid position" );

    array[position] = element;
};


template <typename E>
E SDAL<E>::pop_back() {
    if(is_empty())
        throw std::runtime_error( "SDAL:In pop_back(): list is empty." );
    
    previous_index();
    return array[tail];
};

template <typename E>
E SDAL<E>::pop_front() {
    if(is_empty())
        throw std::runtime_error( "SDAL:In pop_front(): list is empty." );

    E data = array[0];

    previous_index();
    for(int i = 0; i < tail; i ++) 
        array[i] = array[i + 1];
    
    return data;
};

template <typename E>
E SDAL<E>::item_at( size_t position) {
    if(is_empty())
        throw std::runtime_error( "SDAL:In item_at(): list is empty." );
    if(position >= tail  || position < 0) 
        throw std::runtime_error( "SDAL:In item_at(): invalid postition." );
    
    return array[position];
};

template <typename E>
E SDAL<E>::peek_back() {
    if(is_empty())
        throw std::runtime_error( "SDAL:In peek_back(): list is empty." );

    return array[tail-1];
};

template <typename E>
E SDAL<E>::peek_front() {
    if(is_empty())
        throw std::runtime_error( "SDAL:In peek_front(): list is empty." );

    return array[0];
};

template <typename E>
void SDAL<E>::remove( size_t position ) {
    if(is_empty())
        throw std::runtime_error( "SDAL:In remove(): list is empty." );
    if(position >= tail  || position < 0)
        throw std::runtime_error( "SDAL:In remove(): invalid postition." );

    previous_index();
    for(int i = position; i < tail; i++) 
        array[i] = array[i + 1];
    
};

template <typename E>
bool SDAL<E>::is_empty() {
    return tail == 0;
};

template <typename E>
bool SDAL<E>::is_full() {
    return false;
};

template <typename E>
bool SDAL<E>::contains( E element, bool (*equals_function)(E,E)) {
    E temp;
    for(int i = 0; i < tail; i++) {
        if(equals_function(array[i], element)) return true;
    }
    return false;
};


template <typename E>
size_t SDAL<E>::length() {
    return tail;
};

template <typename E>
void SDAL<E>::clear() {
    tail = 0;
};

template <typename E>
void SDAL<E>::print( std::ostream stream ) {
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
E* SDAL<E>::contents() {
    E* new_array = new E[length()];
    
    for(int i = 0; i < length(); i++) {
        new_array[i] = item_at(i);
    }

    return new_array;
};

//Private functions

template <typename E>
void SDAL<E>::next_index() {
    ++tail;

    if(tail >= length_of_array) {
        size_t new_length = length_of_array + length_of_array/2;
        E* new_array = new E[new_length];
        
        for(int i = 0; i < length_of_array; i++)
            new_array[i] = array[i];

        array = new_array;
        length_of_array = new_length;
    }
};

template <typename E>
void SDAL<E>::previous_index() {
    --tail;
    
    if(tail < length_of_array/2 && tail > 100) {
        size_t new_length = length_of_array - length_of_array/4;
        E* new_array = new E[new_length];
        
        for(int i = 0; i < new_length; i++)
            new_array[i] = array[i];

        array = new_array;
        length_of_array = new_length;
    }
    
};

}

#endif