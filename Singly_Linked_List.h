#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <iterator>

namespace cop3530 {
//Look to see f there are any functions I am not overriding.
template < typename E >
class Singly_Linked_List : public List<E> {
public:
    Singly_Linked_List(); //constructor
    ~Singly_Linked_List() override; //destructor
    Singly_Linked_List(Singly_Linked_List<E>& ssl); //copy constructor
    Singly_Linked_List(Singly_Linked_List<E>&& ssl); //move constructor
    Singly_Linked_List<E>& operator=(Singly_Linked_List<E>& ssl); // copy assignment operator
    Singly_Linked_List<E>& operator=(Singly_Linked_List<E>&& ssl); // move assignment

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

/*
    All the functions in this iterator are defined in the iterator. I am unsure if there
    is another way to get them further downt the file and out of the implamentation, but
    this is the only way I found to get it to compile.
public:
    template < typename T >
    class SSL_Iter : public List<T>::Iter {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*; 
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        using self_type = typename List<T>::Iter;
        using self_reference = typename List<T>::Iter&;

        // iterators over a non-const List
        static SSL_Iter make_begin( Singly_Linked_List<value_type>& s) {
            SSL_Iter<T> i( s, s.head );
            return i;
        };

        static SSL_Iter make_end( Singly_Linked_List<value_type>& s) {
            //------------------need to do------------------------
            SSL_Iter<T> i( s, s.head );
            return i;
        };

        SSL_Iter( Singly_Linked_List<value_type>& list, Node* start ) {
            here = start;
            ssl = list;
        };

        //referencing ops-------------------------------------------------

        reference operator*() const override { return here->data; };
        pointer operator->() const override { return &(operator*()); };

        //incramentors----------------------------------------------------

        self_reference operator++() override { // preincrement
            here = here->next;
            return this;
        };

        /*self_type operator++(int) override { // postincrement
            SSL_Iter temp = this;
            here = here->next;
            return temp;
        };

        //equivalence ops--------------------------------------------------

        bool operator==( self_type const& iter ) const override {
            return iter.here == this.here;
        };

        bool operator!=( self_type const& iter ) const override {
            return iter.here != this.here;
        };

        //-------------------------------------------------------------------
        
    private:
        Singly_Linked_List<value_type>& ssl;
        Node* here;
    };

public:
    typename List<E>::Iter* begin() override {
        return SSL_Iter<E>::make_begin( *this ); 
    };
    typename List<E>::Iter* end() override {
        return SSL_Iter<E>::make_end( *this ); 
    };

    */
};

template <typename E>
Singly_Linked_List<E>::Node::Node(Node * n, E d) {
    next = n;
    data = d;
}

template <typename E>
Singly_Linked_List<E>::Node::~Node() {
    //delete
}

//Construtor
template <typename E>
Singly_Linked_List<E>::Singly_Linked_List() {
    head = nullptr; 
};

//Destructor
template <typename E>
Singly_Linked_List<E>::~Singly_Linked_List() {
    Node* temp;
    while(head) {
        temp = head;
        head = head->next;
        delete temp;
    }
};

//copy constructor
template <typename E>
Singly_Linked_List<E>::Singly_Linked_List(Singly_Linked_List<E>& ssl) { 
    head = nullptr;
    size_t size = ssl.length();
    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i = 0; i < size; ++i )
        this.push_back(ssl.item_at(i));
};

//move constructor
template <typename E>
Singly_Linked_List<E>::Singly_Linked_List(Singly_Linked_List<E>&& ssl) {
    head = ssl.head;
    ssl.head = nullptr;
};

// copy assignment operator
template <typename E>
Singly_Linked_List<E>& Singly_Linked_List<E>::operator=(Singly_Linked_List<E>& ssl) {
    Node* temp;
    while(head) {
        temp = head;
        head = head->next;
        delete temp;
    }

    //TODO: replace with iterator!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    size_t size = ssl.length();
    for(int i = 0; i < size; ++i )
        this.push_back(ssl.item_at(i));

    
    return *this;
};

// move assignment
template <typename E>
Singly_Linked_List<E>& Singly_Linked_List<E>::operator=(Singly_Linked_List<E>&& ssl) {
    
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
void Singly_Linked_List<E>::insert( E element, size_t position ) {
    Node* temp = head;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = new Node(temp->next, element);
};

template <typename E>
void Singly_Linked_List<E>::push_back( E element ) {
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
void Singly_Linked_List<E>::push_front( E element ) {
    head = new Node(head, element);
};

template <typename E>
void Singly_Linked_List<E>::replace( E element, size_t position ) {
    Node* temp = head;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = new Node(temp->next->next, element);
};


template <typename E>
E Singly_Linked_List<E>::pop_back() {
    if(is_empty())
        throw std::runtime_error( "Singly_Linked_List<E>::pop_back(): empty list" );

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
E Singly_Linked_List<E>::pop_front() {
    if(is_empty())
        throw std::runtime_error( "Singly_Linked_List<E>::pop_front(): empty list" );

    Node* temp = head;
    head = temp->next;
    return temp->data;
};

template <typename E>
E Singly_Linked_List<E>::item_at( size_t position ) {
    Node* temp = head;
    for(int i = 0; i < position; i++)
        temp = temp->next;
    return temp->data;
};

template <typename E>
E Singly_Linked_List<E>::peek_back() {
    if(is_empty())
        throw std::runtime_error( "Singly_Linked_List<E>::peek_back(): empty list" );

    Node* temp = head;
    Node* val = nullptr;
    while(temp) {
        val = temp;
        temp = temp->next;
    }
    return val->data;
};

template <typename E>
E Singly_Linked_List<E>::peek_front() {
    if( is_empty())
        throw std::runtime_error( "Singly_Linked_List<E>::peek_back(): empty list" );
    return head->data;
};

template <typename E>
void Singly_Linked_List<E>::remove( size_t position ) {
    Node* temp = head;
    for(int i = 0; i < (position - 1); i++)
        temp = temp->next;
    temp->next = temp->next->next;
};


template <typename E>
bool Singly_Linked_List<E>::is_empty() {
    return !head;
};

template <typename E>
bool Singly_Linked_List<E>::is_full() {
    return false;
};

template <typename E>
bool Singly_Linked_List<E>::contains( E element, bool (*equals_function)(E,E)) {
    Node* temp = head;
    while(temp) {
        if(equals_function(temp->data, element)) return true;
        temp = temp->next;
    }
    return false;
};


template <typename E>
size_t Singly_Linked_List<E>::length() {
    Node* temp = head;
    size_t counter = 0;
    while(temp) {
        temp = temp->next;
        counter++;
    }
    return counter;
};

template <typename E>
void Singly_Linked_List<E>::clear() {
    head = nullptr;
};

template <typename E>
void Singly_Linked_List<E>::print( std::ostream stream ) {
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
E* Singly_Linked_List<E>::contents() {
    size_t length = Singly_Linked_List<E>::length();
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
