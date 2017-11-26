#ifndef SSLL_H
#define SSLL_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <iterator>

namespace cop3530 {
//Look to see f there are any functions I am not overriding.
template < typename E >
class SSLL : public List<E> {
public:
    SSLL(); //constructor
    ~SSLL() override; //destructor
    SSLL(SSLL<E>& ssl); //copy constructor
    SSLL(SSLL<E>&& ssl); //move constructor
    SSLL<E>& operator=(SSLL<E>& ssl); // copy assignment operator
    SSLL<E>& operator=(SSLL<E>&& ssl); // move assignment

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
    Node* head;


    /*All the functions in this iterator are defined in the iterator. I am unsure if there
    is another way to get them further downt the file and out of the implamentation, but
    this is the only way I found to get it to compile.*/
public:
    template < typename SSLLT, typename T >
    class SSLL_Iter {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*; 
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        using self_type = SSLL_Iter;
        using self_reference = SSLL_Iter&;

        // iterators over a non-const List
        static self_type make_begin( SSLL<value_type>& s) {
            SSLL_Iter i( s, s.head );
            return i;
        };

        static self_type make_end( SSLL<value_type>& s) {            
            SSLL_Iter i( s, nullptr );
            return i;
        };

        //referencing ops-------------------------------------------------

        reference operator*() const { return here->data; };
        pointer operator->() const { return &(operator*()); };

        //incramentors----------------------------------------------------

        self_reference operator++() { // preincrement
            here = here->next;
            return *this;
        };

        self_type operator++(int) { // postincrement
            self_type temp = *this;
            here = here->next;
            return temp;
        };

        //equivalence ops--------------------------------------------------

        bool operator==( self_type const& iter ) const {
            return iter.here == this->here;
        };

        bool operator!=( self_type const& iter ) const {
            return iter.here != this->here;
        };

        //-------------------------------------------------------------------
        
    private:
        SSLLT ssl;
        Node* here;

        SSLL_Iter( SSLLT &list, Node* start ) {
            here = start;
            ssl = list;
        };
    };

public:
    // type aliases for prettier code
    using iterator = SSLL_Iter<SSLL, E>;
    using const_iterator = SSLL_Iter<SSLL const, E const>;
    
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

template <typename E>
SSLL<E>::Node::Node(Node * n, E d) {
    next = n;
    data = d;
}

template <typename E>
SSLL<E>::Node::~Node() {
    //delete
}

//Construtor
template <typename E>
SSLL<E>::SSLL() {
    head = nullptr; 
};

//Destructor
template <typename E>
SSLL<E>::~SSLL() {
    Node* temp;
    while(head) {
        temp = head;
        head = head->next;
        delete temp;
    }
};

//copy constructor
template <typename E>
SSLL<E>::SSLL(SSLL<E>& ssl) { 
    head = nullptr;
    size_t size = ssl.length();
    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < size; ++i )
        this->push_back(ssl.item_at(i));
};

//move constructor
template <typename E>
SSLL<E>::SSLL(SSLL<E>&& ssl) {
    head = ssl.head;
    ssl.head = nullptr;
};

// copy assignment operator
template <typename E>
SSLL<E>& SSLL<E>::operator=(SSLL<E>& ssl) {
    Node* temp;
    while(head) {
        temp = head;
        head = head->next;
        delete temp;
    }

    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    size_t size = ssl.length();
    for(int i = 0; i < size; ++i )
        this->push_back(ssl.item_at(i));

    
    return *this;
};

// move assignment
template <typename E>
SSLL<E>& SSLL<E>::operator=(SSLL<E>&& ssl) {
    
    if(this!=&ssl) // prevent self-move
    {
        Node* temp;
        while(head) {
            temp = head;
            head = head->next;
            delete temp;
        }

        head = ssl.head;
        ssl.head = nullptr;
    }
    return *this;
};

template <typename E>
void SSLL<E>::insert( E element, size_t position ) {
    Node* temp = head;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = new Node(temp->next, element);
};

template <typename E>
void SSLL<E>::push_back( E element ) {
    if(is_empty())  {
        head = new Node(nullptr, element);
    }
    else {
        Node* temp = head;
        Node* val = nullptr;
        while(temp) {
            val = temp;
            temp = temp->next;
        }
        val->next = new Node(nullptr, element);
    }
};

template <typename E>
void SSLL<E>::push_front( E element ) {
    head = new Node(head, element);
};

template <typename E>
void SSLL<E>::replace( E element, size_t position ) {
    Node* temp = head;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = new Node(temp->next->next, element);
};


template <typename E>
E SSLL<E>::pop_back() {
    if(is_empty())
        throw std::runtime_error( "SSLL<E>::pop_back(): empty list" );

    Node* temp = head;
    Node* further = nullptr;
    Node* shorter = nullptr;

    while(temp) {
        shorter = further;
        further = temp;
        temp = temp->next;
    }

    if(shorter) {
        shorter->next = nullptr;
    }
    else {
        head = nullptr;
    }
    return further->data;
};

template <typename E>
E SSLL<E>::pop_front() {
    if(is_empty())
        throw std::runtime_error( "SSLL<E>::pop_front(): empty list" );

    Node* temp = head;
    head = temp->next;
    return temp->data;
};

template <typename E>
E SSLL<E>::item_at( size_t position ) {
    Node* temp = head;
    for(int i = 0; i < position; i++)
        temp = temp->next;
    return temp->data;
};

template <typename E>
E SSLL<E>::peek_back() {
    if(is_empty())
        throw std::runtime_error( "SSLL<E>::peek_back(): empty list" );

    Node* temp = head;
    Node* val = nullptr;
    while(temp) {
        val = temp;
        temp = temp->next;
    }
    return val->data;
};

template <typename E>
E SSLL<E>::peek_front() {
    if( is_empty())
        throw std::runtime_error( "SSLL<E>::peek_back(): empty list" );
    return head->data;
};

template <typename E>
void SSLL<E>::remove( size_t position ) {
    Node* temp = head;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = temp->next->next;
};


template <typename E>
bool SSLL<E>::is_empty() {
    return !head;
};

template <typename E>
bool SSLL<E>::is_full() {
    return false;
};

template <typename E>
bool SSLL<E>::contains( E element, bool (*equals_function)(E,E)) {
    Node* temp = head;
    while(temp) {
        if(equals_function(temp->data, element)) return true;
        temp = temp->next;
    }
    return false;
};


template <typename E>
size_t SSLL<E>::length() {
    Node* temp = head;
    size_t counter = 0;
    while(temp) {
        temp = temp->next;
        counter++;
    }
    return counter;
};

template <typename E>
void SSLL<E>::clear() {
    head = nullptr;
};

template <typename E>
void SSLL<E>::print( std::ostream stream ) {
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
E* SSLL<E>::contents() {
    size_t length = SSLL<E>::length();
    E* array = new E[length];
    Node* temp = head;
    for(int i = 0; i < length; i++){
        array[i] = temp->data;
        temp = temp->next;
    }
    return array;
};

}

#endif
