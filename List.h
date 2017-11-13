#ifndef LIST_H
#define LIST_H

#include<stddef.h>
#include<iostream>
#include <iterator>
#include <typeinfo>
namespace cop3530 {

template <typename E> 
class List {
public:
    virtual ~List() {};
    
    virtual void insert( E element, size_t position ) = 0;
    virtual void push_back( E element ) = 0;
    virtual void push_front( E element ) = 0;
    virtual void replace( E element, size_t position ) = 0;
    
    virtual E pop_back() = 0;
    virtual E pop_front() = 0;
    virtual E item_at( size_t position ) = 0;
    virtual E peek_back() = 0;
    virtual E peek_front() = 0;
    virtual void remove( size_t position ) = 0;
    
    virtual bool is_empty() = 0;
    virtual bool is_full() = 0;
    virtual bool contains( E element, bool (*equals_function)(E,E)) = 0;

    virtual size_t length() = 0;
    virtual void clear() = 0;
    virtual void print( std::ostream stream ) = 0;
    virtual E* contents() = 0;
/*
public:
    class Iter : public std::iterator<std::forward_iterator_tag, E> {
    public:

        using _self_type = Iter;
        using _self_reference = Iter&;

        virtual _self_reference operator++() = 0;
        //virtual _self_type operator++(int) = 0;
        
        virtual bool operator==( _self_type const& iter) const = 0;
        virtual bool operator!=( _self_type const& iter) const = 0;

        virtual E& operator*() const = 0;
        virtual E* operator->() const = 0;

    };

    virtual Iter* begin() = 0;
    virtual Iter* end() = 0;*/
};

}

#endif
