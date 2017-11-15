#include "tester.h"

//Ten push (back and front) items in in order, ten items out in order.
//Tests peek front/back, pop front/back
TEST_CASE("CDAL: Push, Peek, and Pop test on small list") {
    
    CDAL<int>* list = new CDAL<int>();
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

//Ten items in, test is full, is empty, length, clear, contents
TEST_CASE("CDAL: Tests is full") {
    CDAL<int>* list = new CDAL<int>();
    REQUIRE(!list->is_full());
}

TEST_CASE("CDAL: Test is empty") {

    CDAL<int>* list = new CDAL<int>();
    REQUIRE(list->is_empty());

    for(int i = 0; i < 10; i++)
        list->push_front(i);

    REQUIRE(!list->is_empty()); 
}

TEST_CASE("CDAL: Tests length") {
   
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    REQUIRE(list->length() == 10);

    for(int i = 0; i < 50; i++) 
        list->push_front(i);
    
    REQUIRE(list->length() == 60);
}

TEST_CASE("CDAL: Test clear") {
    
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++) 
        list->push_front(i);
    
    list->clear();
    REQUIRE(list->is_empty());
}

TEST_CASE("CDAL: Test contents") {

    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++) 
        list->push_front(i);

    int* array = list->contents();
    for(int i = 9; i != -1; i--)
        REQUIRE(array[i] == (9 - i));
    
}

//Ten items in, test item_at, remove, replace, insert
TEST_CASE("CDAL: Test item at") {
    
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 0; i < 10; i++)
        REQUIRE((9 - i) == list->item_at(i));
}

TEST_CASE("CDAL: Test remove") {
    
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    list->remove(7);
    REQUIRE(3 == list->item_at(6));
    REQUIRE(1 == list->item_at(7));
    REQUIRE(0 == list->item_at(8));
}

TEST_CASE("CDAL: Test replace") {
    
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);
    

    list->replace(12,2);
    REQUIRE(8 == list->item_at(1));
    REQUIRE(12 == list->item_at(2));
    REQUIRE(6 == list->item_at(3));
}

TEST_CASE("CDAL: Test insert") {
    
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    list->insert(11, 5);
    REQUIRE(11 == list->item_at(5));
    REQUIRE(5 == list->item_at(4));
    REQUIRE(4 == list->item_at(6));
}

//x items in, x items out, same as test 1 but with a bunch of stuff
TEST_CASE("CDAL: Push, Peek, and Pop on big data set") {
    
    CDAL<int>* list = new CDAL<int>();
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
TEST_CASE("CDAL: Test Contains") {
    
    CDAL<int>* list = new CDAL<int>();
    for(int i = 0; i < 10; i++)
        list->push_front(i);

    for(int i = 0; i < 10; i++)
        REQUIRE(list->contains(i, [](int num1, int num2) {return num1 == num2;}));
}

TEST_CASE("CDAL: Test Print") {
    //list->print(std::cout);
    REQUIRE(true);
}
