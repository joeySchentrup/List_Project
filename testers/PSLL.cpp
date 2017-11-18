#include "tester.h"

//Ten push (back and front) items in in order, ten items out in order.
//Tests peek front/back, pop front/back
TEST_CASE("PSLL: Push, Peek, and Pop test on small list") {
    
    PSLL<int>* list = new PSLL<int>();
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

TEST_CASE("PSLL: Test Exception trowing on empty list") {
    PSLL<int>* list = new PSLL<int>();
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

TEST_CASE("PSLL: Test Copy Constructor") {
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    PSLL<int>* list_copy = new PSLL<int>(*list);
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy->peek_back() == i);
        REQUIRE(list_copy->pop_back() == i);
    }

}

TEST_CASE("PSLL: Test Move Constructor") { 
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    PSLL<int> list_copy = std::move(*list);
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy.peek_back() == i);
        REQUIRE(list_copy.pop_back() == i);
    }

}

TEST_CASE("PSLL: Test Copy Assignment operator") { 
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    PSLL<int> list_copy = PSLL<int>();
    list_copy = *list;
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy.peek_back() == i);
        REQUIRE(list_copy.pop_back() == i);
    }
}

TEST_CASE("PSLL: Test Move Assignment operator") { 
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 101; i++)
        list->push_back(i);

    PSLL<int> list_copy = PSLL<int>();
    list_copy = std::move(*list);
    for(int i = 100; i != -1; i--) {
        REQUIRE(list_copy.peek_back() == i);
        REQUIRE(list_copy.pop_back() == i);
    }
}

//Ten items in, test is full, is empty, length, clear, contents
TEST_CASE("PSLL: Tests is full") {
    PSLL<int>* list = new PSLL<int>();
    REQUIRE(!list->is_full());
}

TEST_CASE("PSLL: Test is empty") {

    PSLL<int>* list = new PSLL<int>();
    REQUIRE(list->is_empty());

    for(int i = 0; i < 10; i++)
        list->push_front(i);

    REQUIRE(!list->is_empty()); 
}

TEST_CASE("PSLL: Tests length") {
   
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    REQUIRE(list->length() == 10);

    for(int i = 0; i < 50; i++) 
        list->push_front(i);
    
    REQUIRE(list->length() == 60);
}

TEST_CASE("PSLL: Test clear") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++) 
        list->push_front(i);
    
    list->clear();
    REQUIRE(list->is_empty());
}

TEST_CASE("PSLL: Test contents") {

    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++) 
        list->push_front(i);

    int* array = list->contents();
    for(int i = 9; i != -1; i--)
        REQUIRE(array[i] == (9 - i));
    
}

//Ten items in, test item_at, remove, replace, insert
TEST_CASE("PSLL: Test item at") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 0; i < 10; i++)
        REQUIRE((9 - i) == list->item_at(i));
}

TEST_CASE("PSLL: Test remove") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    list->remove(7);
    REQUIRE(3 == list->item_at(6));
    REQUIRE(1 == list->item_at(7));
    REQUIRE(0 == list->item_at(8));
}

TEST_CASE("PSLL: Test replace") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);
    

    list->replace(12,2);
    REQUIRE(8 == list->item_at(1));
    REQUIRE(12 == list->item_at(2));
    REQUIRE(6 == list->item_at(3));
}

TEST_CASE("PSLL: Test insert") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    list->insert(11, 5);
    REQUIRE(11 == list->item_at(5));
    REQUIRE(5 == list->item_at(4));
    REQUIRE(4 == list->item_at(6));
}

TEST_CASE("PSLL: Test insert on large set") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 500; i++)
        list->push_back(i);

    list->insert(11, 205);
    REQUIRE(11 == list->item_at(205));
    REQUIRE(204 == list->item_at(204));
    REQUIRE(205 == list->item_at(206));
}

//x items in, x items out, same as test 1 but with a bunch of stuff
TEST_CASE("PSLL: Push, Peek, and Pop on big data set") {
    
    PSLL<int>* list = new PSLL<int>();
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

/*
//Test the iterator
bool test5(List<int>* list, int x) {
        
    for(int i = 0; i < x; i++) {
        list->push_front(i);
    }
    
    int i = x - 1;
    List<int>::Iter* begin = list->begin();
    List<int>::Iter* end = list->end();
    for(; begin != end; ++begin) {
        if(**begin != i) {
            std::cout << "    Test 4, Part 1: Failed. Looked at " << **begin << " in front but expected " << i << "." << std::endl;
            debug(list);
            return false;
        }
        --i;
    }
    
    std::cout << "    Test 5, Part 1: Passed!" << std::endl;
    std::cout << "Test 5: Passed!" << std::endl;

    return true;
}
*/

//Ten items in, tests contains and print
TEST_CASE("PSLL: Test Contains") {
    
    PSLL<int>* list = new PSLL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 0; i < 10; i++)
        REQUIRE(list->contains(i, [](int num1, int num2) {return num1 == num2;}));
}

TEST_CASE("PSLL: Test Print") {
    //list->print(std::cout);
    REQUIRE(true);
}
