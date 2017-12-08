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
    static std::string debug(List<T>* list) {
        int l = list->length();
        T* a = list->contents();
        std::string output = "Array: ";

        for(int i = 0; i < l; i++) {
            output.append( std::to_string(a[i]));
            output.append(" ");
        }
    
       return output;
    }
};

#endif
