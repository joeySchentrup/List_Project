#ifndef CIRCULAR_BUFFER_LIST_H
#define CIRCULAR_BUFFER_LIST_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>
namespace cop3530 {

template < typename E >
class Circular_Buffer_List : public List<E> {
public:
    Circular_Buffer_List(size_t size);
    ~Circular_Buffer_List() override;
    Circular_Buffer_List(Circular_Buffer_List<E>& cbal); //copy constructor
    Circular_Buffer_List(Circular_Buffer_List<E>&& cbal); //move constructor
    Circular_Buffer_List<E>& operator=(Circular_Buffer_List<E>& cbal); // copy assignment operator
    Circular_Buffer_List<E>& operator=(Circular_Buffer_List<E>&& cbal); // move assignment

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
    size_t head;
    size_t tail;
    
    size_t next_index(size_t index);
    size_t previous_index(size_t index);
    size_t array_position(size_t position);
};

//Public functions

template <typename E>
Circular_Buffer_List<E>::Circular_Buffer_List(size_t size = 50) {
    if(size < 2)
        throw std::runtime_error( "CBAL:In constructor: size needs to be at least 2." );
    
    array = new E[size];
    tail = 0;
    head = 0;
    length_of_array = size;
};

template <typename E>
Circular_Buffer_List<E>::~Circular_Buffer_List() {
    delete array;
};

//copy constructor
template <typename E>
Circular_Buffer_List<E>::Circular_Buffer_List(Circular_Buffer_List<E>& cbal) { 
    tail = cbal.tail;
    head = cbal.head;
    length_of_array = cbal.length_of_array;
    array = new E[length_of_array];
    for(int i = 0; i < length_of_array; ++i )
        this.array[i] = cbal.array[i];
};

//move constructor
template <typename E>
Circular_Buffer_List<E>::Circular_Buffer_List(Circular_Buffer_List<E>&& cbal) {
    tail = cbal.tail;
    head = cbal.head;
    length_of_array = cbal.length_of_array;
    array = cbal.array;
    cbal.head = nullptr;
};

// copy assignment operator
template <typename E>
Circular_Buffer_List<E>& Circular_Buffer_List<E>::operator=(Circular_Buffer_List<E>& cbal) {
    delete array;

    tail = cbal.tail;
    head = cbal.head;
    length_of_array = cbal.length_of_array;
    for(int i = 0; i < length_of_array; ++i )
        this.array[i] = cbal.array[i];
    
    return *this;
};

// move assignment
template <typename E>
Circular_Buffer_List<E>& Circular_Buffer_List<E>::operator=(Circular_Buffer_List<E>&& cbal) {
    
    if(this!=&cbal) // prevent self-move
    {
        delete this.array;
        tail = cbal.tail;
        head = cbal.head;
        length_of_array = cbal.length_of_array;
        this.array = cbal.array;
        cbal.array = nullptr;
    }
    return *this;
};

template <typename E>
void Circular_Buffer_List<E>::insert( E element, size_t position ) {

    if(is_empty())
        throw std::runtime_error( "CBAL:In insert(): list is empty." );
    if(position >= length() || position < 0)
        throw std::runtime_error( "CBAL:In insert(): invalid position." );
    
    position = array_position(position);
    for(int i = tail; i !=  position ; i = previous_index(i)) 
        array[next_index(i)] = array[i];
    
    tail = next_index(tail);
    array[position] = element;
};

template <typename E>
void Circular_Buffer_List<E>::push_back( E element ) {
    array[tail] = element;
    tail = next_index(tail);
};

template <typename E>
void Circular_Buffer_List<E>::push_front( E element ) {    
    array[head] = element;
    head = previous_index(head);
};

template <typename E>
void Circular_Buffer_List<E>::replace( E element, size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CBAL:In replace(): list is empty." );
    if(position >= length() || position < 0)
        throw std::runtime_error( "CBAL:In replace(): invalid position" );

    position = array_position(position);
    array[position] = element;
};


template <typename E>
E Circular_Buffer_List<E>::pop_back() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In pop_back(): list is empty." );
    
    tail = previous_index(tail);
    return array[tail];
};

template <typename E>
E Circular_Buffer_List<E>::pop_front() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In pop_front(): list is empty." );

    head = previous_index(head);
    E data = array[head];  
    return data;
};

template <typename E>
E Circular_Buffer_List<E>::item_at(size_t position) {
    if(is_empty()) 
        throw std::runtime_error( "CBAL:In item_at(): list is empty." );
    if(position >= length()  || position < 0) 
        throw std::runtime_error( "CBAL:In item_at(): invalid position: " + std::to_string(position) + ".");
    
    position = array_position(position);
    return array[position];
};

template <typename E>
E Circular_Buffer_List<E>::peek_back() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In peek_back(): list is empty." );
    return array[previous_index(tail)];
};

template <typename E>
E Circular_Buffer_List<E>::peek_front() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In peek_front(): list is empty." );
    return array[next_index(head)];
};

template <typename E>
void Circular_Buffer_List<E>::remove( size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CBAL:In remove(): list is empty." );
    if(position >= length()  || position < 0)
        throw std::runtime_error( "CBAL:In remove(): invalid position." );

    //Cant do i < tail e
    position = array_position(position);
    for(int i = position; i != tail; i = next_index(i)) 
        array[i] = array[next_index(i)];
    
    tail = previous_index(tail);
};

template <typename E>
bool Circular_Buffer_List<E>::is_empty() {
    return tail == head;
};

template <typename E>
bool Circular_Buffer_List<E>::is_full() {
    return false;
};

template <typename E>
bool Circular_Buffer_List<E>::contains( E element, bool (*equals_function)(E,E)) {
    E temp;
    for(int i = head; i != tail; i = next_index(i)) {
        if(equals_function(array[i], element)) return true;
    }
    return false;
};


template <typename E>
size_t Circular_Buffer_List<E>::length() {
    if(is_empty()) 
        return 0;
    else if(head < tail) 
        return tail-head;
    else
        return (length_of_array - head) + tail;
};

template <typename E>
void Circular_Buffer_List<E>::clear() {
    tail = 0;
    head = 1;
    head = previous_index(head);
};

template <typename E>
void Circular_Buffer_List<E>::print( std::ostream stream ) {
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
E* Circular_Buffer_List<E>::contents() {
    E* new_array = new E[length()];
    
    int counter = 0;
    for(int i = head; i != tail; i = next_index(i)) {
        new_array[counter++] = item_at(i);
    }

    return new_array;
};

//Private functions

template <typename E>
size_t Circular_Buffer_List<E>::next_index(size_t index) {

    if(length() + 1 >= length_of_array) {
        size_t new_length = length_of_array + (3)*(length_of_array/4);
        E* new_array = new E[new_length];
        
        for(int i = 0; i < length_of_array; i++)
            new_array[i] = array[i];

        array = new_array;
        length_of_array = new_length;
    }

    if(++index == length_of_array) 
        return 0;
    else
        return ++index;
};

template <typename E>
size_t Circular_Buffer_List<E>::previous_index(size_t index) {
    
    if(tail > length_of_array/2 && tail > 101) {
        size_t new_length = length_of_array - length_of_array/4;
        E* new_array = new E[new_length];
        
        for(int i = 0; i < new_length; i++)
            new_array[i] = array[i];

        array = new_array;
        length_of_array = new_length;
    }

    if(index == 0) 
        return length_of_array - 1;
    else
        return --index;
};

template <typename E>
size_t Circular_Buffer_List<E>::array_position(size_t position) {
    position = head + position;
    if(position >= length_of_array) 
        return head - length_of_array;
    else 
        return position;
};

}

#endif