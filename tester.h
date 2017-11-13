#ifndef TESTER_H 
#define TESTER_H

#include<iostream>
#include<string>
#include "catch.hpp"

#include "Singly_Linked_List.h"
#include "Pooled_Singly_Linked_List.h"
#include "Simple_Dynamic_Array_List.h"
#include "Chained_Dynamic_Array_List.h" 
#include "Circular_Buffer_List.h" 

using namespace cop3530;

bool test1(List<int>* list);
bool test2(List<int>* list);
bool test3(List<int>* list);
bool test4(List<int>* list, int x);
bool test5(List<int>* list, int x);
bool test6(List<int>* list);

void debug(List<int>* list);

#endif
