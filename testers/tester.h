#ifndef TESTER_H 
#define TESTER_H

#include<iostream>
#include<string>
#include "catch.hpp"

#include "../SSLL.h"
#include "../PSLL.h"
#include "../SDAL.h"
#include "../CDAL.h" 
#include "../CBL.h" 

using namespace cop3530;

template <typename T>
class Debugger {
public:
    static void debug(List<T>* list) {
        int l = list->length();
        T* a = list->contents();

        for(int i = 0; i < l; i++) 
            std::cout << a[i] << " ";
    
       std::cout << std::endl;
    }
};




#endif
