#ifndef CBL_H
#define CBL_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>
namespace cop3530 {

template < typename E >
class CBL : public List<E> {
public:
    CBL(size_t size = 50);
    ~CBL() override;
    CBL(CBL<E>& cbal); //copy constructor
    CBL(CBL<E>&& cbal); //move constructor
    CBL<E>& operator=(CBL<E>& cbal); // copy assignment operator
    CBL<E>& operator=(CBL<E>&& cbal); // move assignment

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
    size_t start_capacity;
    
    size_t next_index(size_t index);
    size_t previous_index(size_t index);
    size_t array_position(size_t position);
    void resize_check();

public:
    template < typename CBLT, typename T >
    class CBL_Iter {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*; 
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        using self_type = CBL_Iter;
        using self_reference = CBL_Iter&;

        // iterators over a non-const List
        static self_type make_begin( CBL<value_type>& s) {
            CBL_Iter i( s, s.head );
            return i;
        };

        static self_type make_end( CBL<value_type>& s) {            
            CBL_Iter i( s, s.tail );
            return i;
        };

        //referencing ops-------------------------------------------------

        reference operator*() const { return array[here]; };
        pointer operator->() const { return &(operator*()); };

        //incramentors----------------------------------------------------

        self_reference operator++() { // preincrement
            here = iter_next_index(here);
            return *this;
        };

        self_type operator++(int) { // postincrement
            self_type temp = *this;
            here = iter_next_index(here);
            return temp;
        };

        //equivalence ops--------------------------------------------------

        bool operator==( self_type const& iter ) const {
            return iter.here == this->here && iter.array == this->array;
        };

        bool operator!=( self_type const& iter ) const {
            return iter.here != this->here || iter.array != this->array;
        };

        //-------------------------------------------------------------------
        
    private:
        CBLT CBL;
        size_t here;
        T* array;

        CBL_Iter( CBLT &list, size_t start ) {
            CBL = list;
            here = start;
            array = list.array; 
        };

        size_t iter_next_index(size_t index) {
            if(++index == CBL.length_of_array) 
                return 0;
            else
            return index;
        };
    };

public:
    // type aliases for prettier code
    using iterator = CBL_Iter<CBL, E>;
    using const_iterator = CBL_Iter<CBL const, E const>;
    
    // methods to create appropriate iterators
    iterator begin() { 
        return iterator::make_begin(*this); 
    };
    iterator end() { 
        return iterator::make_end(*this); 
    };
    
    const_iterator begin() const { 
        return const_iterator::make_begin(*this); 
    };
    const_iterator end() const {
         return const_iterator::make_end(*this); 
    };
};

//Public functions

template <typename E>
CBL<E>::CBL(size_t size = 50) {
    if(size < 2)
        throw std::runtime_error( "CBAL:In constructor: size needs to be at least 2." );
    
    array = new E[size];
    tail = 0;
    head = 0;
    start_capacity = length_of_array = size;
};

template <typename E>
CBL<E>::~CBL() {
    delete array;
};

//copy constructor
template <typename E>
CBL<E>::CBL(CBL<E>& cbal) { 
    tail = cbal.tail;
    head = cbal.head;
    length_of_array = cbal.length_of_array;
    start_capacity = cbal.start_capacity;
    array = new E[length_of_array];
    for(int i = 0; i < length_of_array; ++i )
        this->array[i] = cbal.array[i];
};

//move constructor
template <typename E>
CBL<E>::CBL(CBL<E>&& cbal) {
    tail = cbal.tail;
    head = cbal.head;
    start_capacity = cbal.start_capacity;
    length_of_array = cbal.length_of_array;
    array = cbal.array;

    cbal.array = nullptr;
};

// copy assignment operator
template <typename E>
CBL<E>& CBL<E>::operator=(CBL<E>& cbal) {

    tail = cbal.tail;
    head = cbal.head;
    start_capacity = cbal.start_capacity;
    length_of_array = cbal.length_of_array;

    E* temp = this->array;
    this->array = new E[length_of_array];
    delete temp;

    for(int i = 0; i < length_of_array; ++i )
        this->array[i] = cbal.array[i];
    
    return *this;
};

// move assignment
template <typename E>
CBL<E>& CBL<E>::operator=(CBL<E>&& cbal) {
    
    if(this!=&cbal) // prevent self-move
    {
        tail = cbal.tail;
        head = cbal.head;
        start_capacity = cbal.start_capacity;
        length_of_array = cbal.length_of_array;
        E* temp = this->array;
        this->array = cbal.array;
        delete temp;
        cbal.array = nullptr;
    }
    return *this;
};

template <typename E>
void CBL<E>::insert( E element, size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CBAL:In insert(): list is empty." );
    if(position >= length() || position < 0)
        throw std::runtime_error( "CBAL:In insert(): invalid position." );
    
    resize_check();
    position = array_position(position);
    for(int i = tail; i !=  previous_index(position) ; i = previous_index(i)) 
        array[next_index(i)] = array[i];
    
    tail = next_index(tail);
    array[position] = element;
};

template <typename E>
void CBL<E>::push_back( E element ) {
    resize_check();
    array[tail] = element;
    tail = next_index(tail);
};

template <typename E>
void CBL<E>::push_front( E element ) {
    resize_check();  
    head = previous_index(head);
    array[head] = element;
};

template <typename E>
void CBL<E>::replace( E element, size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CBAL:In replace(): list is empty." );
    if(position >= length() || position < 0)
        throw std::runtime_error( "CBAL:In replace(): invalid position" );

    position = array_position(position);
    array[position] = element;
};


template <typename E>
E CBL<E>::pop_back() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In pop_back(): list is empty." );
    
    resize_check();
    tail = previous_index(tail);
    return array[tail];
};

template <typename E>
E CBL<E>::pop_front() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In pop_front(): list is empty." );

    E data = array[head]; 
    head = next_index(head); 
    resize_check();
    return data;
};

template <typename E>
E CBL<E>::item_at(size_t position) {
    if(is_empty()) 
        throw std::runtime_error( "CBAL:In item_at(): list is empty." );
    if(position >= length()  || position < 0) 
        throw std::runtime_error( "CBAL:In item_at(): invalid position: " + std::to_string(position) + ".");
    
    position = array_position(position);
    return array[position];
};

template <typename E>
E CBL<E>::peek_back() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In peek_back(): list is empty." );
    return array[previous_index(tail)];
};

template <typename E>
E CBL<E>::peek_front() {
    if(is_empty())
        throw std::runtime_error( "CBAL:In peek_front(): list is empty." );
    return array[head];
};

template <typename E>
void CBL<E>::remove( size_t position ) {
    if(is_empty())
        throw std::runtime_error( "CBAL:In remove(): list is empty." );
    if(position >= length()  || position < 0)
        throw std::runtime_error( "CBAL:In remove(): invalid position." );

    //Cant do i < tail e
    position = array_position(position);
    for(int i = position; i != tail; i = next_index(i)) 
        array[i] = array[next_index(i)];
    
    resize_check();
    tail = previous_index(tail);
};

template <typename E>
bool CBL<E>::is_empty() {
    return tail == head;
};

template <typename E>
bool CBL<E>::is_full() {
    return false;
};

template <typename E>
bool CBL<E>::contains( E element, bool (*equals_function)(E,E)) {
    E temp;
    for(int i = head; i != tail; i = next_index(i)) {
        if(equals_function(array[i], element)) return true;
    }
    return false;
};


template <typename E>
size_t CBL<E>::length() {
    if(is_empty())
        return 0;
    else if(head < tail) 
        return tail-head;
    else
        return (length_of_array - head) + tail;
};

template <typename E>
void CBL<E>::clear() {
    tail = 0;
    head = 0;
    resize_check();
};

template <typename E>
void CBL<E>::print( std::ostream stream ) {
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
E* CBL<E>::contents() {
    E* new_array = new E[length()];
    
    int counter = 0;
    for(int i = head; i != tail; i = next_index(i)) {
        new_array[counter++] = array[i];
    }

    return new_array;
};

//Private functions

template <typename E>
size_t CBL<E>::next_index(size_t index) {
    if(++index == length_of_array) 
        return 0;
    else
        return index;
};

template <typename E>
size_t CBL<E>::previous_index(size_t index) {
    if(index == 0) 
        return length_of_array - 1;
    else
        return --index;
};

template <typename E>
size_t CBL<E>::array_position(size_t position) {
    position = head + position;
    if(position >= length_of_array) 
        return head - length_of_array;
    else 
        return position;
};

template <typename E>
void CBL<E>::resize_check() {
    
    if(length() < length_of_array/2 && length() > start_capacity*2) {
        size_t lost_length = length_of_array/4;
        E* new_array = new E[length_of_array - lost_length];
        
        if(head < tail) {
            if(tail < length_of_array - lost_length) {
                for(int i = head; i != tail; i++)
                    new_array[i] = array[i];
            } else {
                for(int i = head; i != tail; i++)
                    new_array[i - lost_length] = array[i];
            }
        } else {
            for(int i = 0; i != tail; i++)
                new_array[i] = array[i];
            for(int i = head; i != length_of_array; i++)
                new_array[i - lost_length] = array[i];
            head -= lost_length;
        }

        array = new_array;
        length_of_array = length_of_array - lost_length;

    } else if(length() + 1 == length_of_array) {        
        size_t added_length = (length_of_array/2);
        E* new_array = new E[length_of_array + added_length];
        
        if(head < tail) {
            for(int i = head; i < tail; i++)
                new_array[i] = array[i];
        }
        else {
            for(int i = 0; i < tail; i++)
                new_array[i] = array[i];
            for(int i = head; i < length_of_array; i++)
                new_array[i + added_length] = array[i];
            head += added_length;
        }

        array = new_array;
        length_of_array = added_length + length_of_array;
    }
};


}

#endif