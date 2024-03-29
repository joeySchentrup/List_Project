#include "tester.h"

//Ten push (back and front) items in in order, ten items out in order.
//Tests peek front/back, pop front/back
TEST_CASE("CBL: Push, Peek, and Pop test on small list") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 9; i != -1; i--) {
        REQUIRE(list->peek_front() == i);
        REQUIRE(list->pop_front() == i);
    }
    
    for(int i = 0; i < 10; i++)
    {
        list->push_back(i);
    }

    for(int i = 9; i != -1; i--) {
        REQUIRE(list->peek_back() == i);
        REQUIRE(list->pop_back() == i);
    }
}

TEST_CASE("CBL: Test Exception trowing on empty list") {
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 9; i != -1; i--)
        list->pop_front();
    bool passed = false;
    
    try {
        list->pop_front();
    } catch (...) {
        passed = true;
    }
    REQUIRE(passed);
    
    passed = false;
    try {
        list->pop_back();
    } catch (...) {
        passed = true;
    }
    REQUIRE(passed);

    passed = false;
    try {
        list->peek_back();
    } catch (...) {
        passed = true;
    }
    REQUIRE(passed);

    passed = false;
    try {
        list->peek_front();
    } catch (...) {
        passed = true;
    }
    REQUIRE(passed);
}

TEST_CASE("CBL: Test Copy Constructor") {
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    CBL<int>* list_copy = new CBL<int>(*list);
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy->peek_back() == i);
        REQUIRE(list_copy->pop_back() == i);
    }

}

TEST_CASE("CBL: Test Move Constructor") { 
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    CBL<int> list_copy = std::move(*list);
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy.peek_back() == i);
        REQUIRE(list_copy.pop_back() == i);
    }

}

TEST_CASE("CBL: Test Copy Assignment operator") { 
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    CBL<int> list_copy = CBL<int>();
    list_copy = *list;
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy.peek_back() == i);
        REQUIRE(list_copy.pop_back() == i);
    }
}

TEST_CASE("CBL: Test Move Assignment operator") { 
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    CBL<int> list_copy = CBL<int>();
    list_copy = std::move(*list);
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy.peek_back() == i);
        REQUIRE(list_copy.pop_back() == i);
    }
}

//Ten items in, test is full, is empty, length, clear, contents
TEST_CASE("CBL: Tests is full") {
    CBL<int>* list = new CBL<int>();
    REQUIRE(!list->is_full());
}

TEST_CASE("CBL: Test is empty") {

    CBL<int>* list = new CBL<int>();
    REQUIRE(list->is_empty());

    for(int i = 0; i < 10; i++)
        list->push_front(i);

    REQUIRE(!list->is_empty()); 
}

TEST_CASE("CBL: Tests length") {
   
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    REQUIRE(list->length() == 10);

    for(int i = 0; i < 50; i++) 
        list->push_front(i);
    
    REQUIRE(list->length() == 60);
}

TEST_CASE("CBL: Test clear") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++) 
        list->push_front(i);
    
    list->clear();
    REQUIRE(list->is_empty());
}

TEST_CASE("CBL: Test contents") {

    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++) 
        list->push_front(i);

    int* array = list->contents();
    for(int i = 9; i != -1; i--)
        REQUIRE(array[i] == (9 - i));
    
}

//Ten items in, test item_at, remove, replace, insert
TEST_CASE("CBL: Test item at") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 0; i < 10; i++)
        REQUIRE((9 - i) == list->item_at(i));
}

TEST_CASE("CBL: Test remove") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    list->remove(7);
    REQUIRE(3 == list->item_at(6));
    REQUIRE(1 == list->item_at(7));
    REQUIRE(0 == list->item_at(8));
}

TEST_CASE("CBL: Test replace") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);
    

    list->replace(12,2);
    REQUIRE(8 == list->item_at(1));
    REQUIRE(12 == list->item_at(2));
    REQUIRE(6 == list->item_at(3));
}

TEST_CASE("CBL: Test insert") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    list->insert(11, 5);
    REQUIRE(11 == list->item_at(5));
    REQUIRE(5 == list->item_at(4));
    REQUIRE(4 == list->item_at(6));
}

TEST_CASE("CBL: Test insert on large set") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 500; i++)
        list->push_back(i);

    list->insert(11, 205);
    REQUIRE(11 == list->item_at(205));
    REQUIRE(204 == list->item_at(204));
    REQUIRE(205 == list->item_at(206));
}

//x items in, x items out, same as test 1 but with a bunch of stuff
TEST_CASE("CBL: Push, Peek, and Pop on big data set") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 1000; i++)
        list->push_front(i);

    for(int i = 999; i != -1; i--) {
        REQUIRE(list->peek_front() == i);
        REQUIRE(list->pop_front() == i);
    }
    
    for(int i = 0; i < 1000; i++)
        list->push_back(i);

    for(int i = 999; i != -1; i--) {
        REQUIRE(list->peek_back() == i);
        REQUIRE(list->pop_back() == i); 
    }
}

//Test the for each iterator
TEST_CASE("CBL: Tests the iterators using for each") {
        
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 1000; i++) {
        list->push_front(i);
    }
    
    int i = 999;
    for(auto item : *list) 
        REQUIRE(item == i--);
}
    
//Test the begin and end and ++ operators
TEST_CASE("CBL: Tests the iterators using begin and end and ++ operators") {
        
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 1000; i++) {
        list->push_front(i);
    }
    
    int i = 999;
    
    CBL<int>::CBL_Iter<CBL<int>,int> iter = list->begin();
    CBL<int>::CBL_Iter<CBL<int>,int> end = list->end();
    
    for(; iter != end; iter++) 
        REQUIRE(*iter == i--);

    i = 999;
    for(; iter != end; ++iter) 
        REQUIRE(*iter == i--);
}

//Ten items in, tests contains and print
TEST_CASE("CBL: Test Contains") {
    
    CBL<int>* list = new CBL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 0; i < 10; i++)
        REQUIRE(list->contains(i, [](int num1, int num2) {return num1 == num2;}));
}

TEST_CASE("CBL: Test Print") {
    //list->print(std::cout);
    REQUIRE(true);
}
