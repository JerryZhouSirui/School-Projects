// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

// Add your test cases here

TEST(test_default_ctor) {
    List<int> test;
    ASSERT_TRUE(test.size() == 0);
    ASSERT_TRUE(test.begin() == test.end());
}

TEST(simple_empty_push_front) {    
    List<int> test;
    test.push_front(1);
    ASSERT_TRUE(!test.empty());
    test.clear();
    ASSERT_TRUE(test.empty());
}

TEST(test_simple_push_char) {
    List<char> test;
    test.push_front('a');
    test.push_back('b');

    ASSERT_TRUE(test.front() == 'a');
    ASSERT_TRUE(test.back() == 'b');
}

TEST(simple_empty_push_back) {
    List<int> test;
    test.push_back(1);
    ASSERT_TRUE(!test.empty());
    test.clear();
    ASSERT_TRUE(test.empty());
}

TEST(test_simple_push_back) {
    List<int> test;
    test.push_back(10);
    test.push_back(9);
    ASSERT_TRUE(test.front() == 10);
    ASSERT_TRUE(test.back() == 9);
}

TEST(test_simple_push_front) {
    List<int> test;
    test.push_front(2);
    test.push_front(1);
    ASSERT_TRUE(test.front() == 1);
    ASSERT_TRUE(test.back() == 2);
}

TEST(test_simple_pop) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    test.pop_back();
    ASSERT_TRUE(test.back() == 2);
    
    test.pop_front();
    ASSERT_TRUE(test.front() == 2);
}

TEST(test_size) {
    List<int> test;
    test.push_front(3);
    test.push_front(4);
    test.push_front(5);
    test.push_front(6);
    ASSERT_EQUAL(test.size(), 4);

    test.pop_back();
    ASSERT_EQUAL(test.size(), 3);
}

TEST(test_copy_ctor_size){
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int> test1(test);
    ASSERT_EQUAL(test1.size(), test.size());
    ASSERT_EQUAL(test1.size(), 3);
}

TEST(test_copy_ctor_first_last) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int> test1(test);
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    ASSERT_TRUE(test1.front() == test.front());
    ASSERT_TRUE(test1.back() == test.back());
}

TEST(test_copy_ctor_push) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int> test1(test);
    test1.push_back(4);
    ASSERT_TRUE(test1.back() == 4);
    ASSERT_FALSE(test.back() == 4);

    test.push_back(5);
    ASSERT_TRUE(test.back() == 5);
    ASSERT_FALSE(test1.back() == 5);
}

TEST(test_iterator_dereference) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int>::Iterator it(test.begin());
    ASSERT_EQUAL(*it, 1);
}

TEST(test_iterator_increment) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int>::Iterator it(test.begin());
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}

TEST(test_iterator_decrement) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    // cout << test.size() << endl;

    ASSERT_TRUE(test.size() == 3);  
    List<int>::Iterator it(test.begin());

    ++it;
    ++it;

    ASSERT_EQUAL(*it, 3);
    --it;
    ASSERT_EQUAL(*it, 2);
    --it;
    ASSERT_EQUAL(*it, 1); 
}

TEST(test_iterator_equivalence) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int>::Iterator it(test.begin());
    ++it;
    List<int>::Iterator it1(test.begin());
    ++it1;
    ASSERT_TRUE(it == it1);

    --it1;
    ASSERT_TRUE(it != it1);
}

TEST(test_list_insert) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);

    List<int>::Iterator it(test.begin());
    ++it;
    ++it;
    test.insert(it, 0);

    ASSERT_TRUE(test.size() == 5);

    ASSERT_TRUE(*it == 3);
    --it;
    ASSERT_TRUE(*it == 0);
}

TEST(test_list_insert_empty) {
    List<int> test;
    List<int>::Iterator it(test.begin());
    test.insert(it, 1);

    ASSERT_TRUE(test.back() == 1);
    ASSERT_TRUE(test.front() == 1);
}

TEST(test_list_insert_back) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    
    List<int>::Iterator it(test.end());
    test.insert(it, 4);
    cout << test.size() << endl;
    ASSERT_TRUE(test.back() == 4);
    ASSERT_TRUE(test.front() == 1);
    ASSERT_TRUE(test.size() == 4);
}

TEST(test_list_insert_front) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int>::Iterator it(test.begin());
    test.insert(it, 0);

    ASSERT_TRUE(test.front() == 0);
    ASSERT_TRUE(test.size() == 4);
}

TEST(test_list_erase){
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);

    List<int>::Iterator it(test.begin());
    ++it;
    ASSERT_TRUE(*it == 2);
    test.erase(it);
    List<int>::Iterator it1(test.begin());
    ++it1;
    ASSERT_TRUE(*it1 == 3);
}

TEST(test_list_erase_single) {
    List<int> test;
    test.push_back(1);

    List<int>::Iterator it(test.begin());
    test.erase(it);

    ASSERT_TRUE(test.empty());
}

TEST(test_list_erase_front) {
    List<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    List<int>::Iterator it(test.begin());
    test.erase(it);
    ASSERT_TRUE(test.front() == 2);
    ASSERT_TRUE(test.size() == 2);
}

TEST(test_simple_pops) {
    List<int> test;
    test.push_front(1);
    test.pop_back();
    ASSERT_TRUE(test.empty());
    
    test.push_front(1);
    test.pop_front();
    ASSERT_TRUE(test.empty());

    test.push_back(1);
    test.pop_front();
    ASSERT_TRUE(test.empty());
}

TEST(test_assignment_op) {
    List<int> test;
    List<int> test1;

    test1.push_back(97);
    test1.push_back(98);
    test1.push_back(99);

    test = test1;

    ASSERT_TRUE(test.size() == 3);
    ASSERT_TRUE(test.front() == 97);
    ASSERT_TRUE(test.back() == 99);
}

TEST(test_assignment_deep) {
    List<int> test;
    List<int> test1;

    test1.push_back(97);
    test1.push_back(98);
    test1.push_back(99);

    test = test1;

    test1.push_back(100);
    ASSERT_TRUE(test1.back() == 100);
    ASSERT_TRUE(test1.size() == 4);
    ASSERT_FALSE(test.back() == 100);
    ASSERT_TRUE(test.size() == 3);
}

TEST(test_copy_ctor_empty) {
    List<int> test;
    List<int> test1(test);

    ASSERT_TRUE(test1.size() == 0);
    ASSERT_TRUE(test1.begin() == test1.end());

    test1.push_front(44);
    
    ASSERT_TRUE(test1.front() == 44);
    ASSERT_TRUE(test1.back() == 44);
    ASSERT_TRUE(test.size() == 0);
}

TEST(test_ass_op_empty) {
    List<int> test;
    List<int> test1;

    test1 = test;

    ASSERT_TRUE(test.size() == test1.size());
    ASSERT_TRUE(test.size() == 0);
    test.push_front(3);

    ASSERT_TRUE(test1.size() == 0);
    ASSERT_TRUE(test.front() == test.back());
    ASSERT_TRUE(test.front() == 3);
}

TEST(iterator_frenzy) {
    List<double> test;
    test.push_back(1.1);
    test.push_back(2.1);
    test.push_back(3.1);
    test.push_back(4.1);

    List<double> test1(test);
    List<double> test2 = test;

    List<double>::Iterator it(test.begin());
    List<double>::Iterator it1(test1.begin());
    List<double>::Iterator it2(test2.begin());
    List<double>::Iterator ite(test.end());
    List<double>::Iterator it1e(test1.end());
    List<double>::Iterator it2e(test2.end());

    ASSERT_TRUE(it != it1 && it != it2);
    ASSERT_TRUE(ite == it1e && ite == it2e);
    ASSERT_TRUE(*it == 1.1 && *it1 == 1.1 && *it2 == 1.1);
    ++it;
    ++it1;
    ++it2;
    ASSERT_TRUE(*it == 2.1 && *it1 == 2.1 && *it2 == 2.1);
    ASSERT_TRUE(it != it1 && it != it2);
    ++it;
    ++it1;
    ++it2;
    ASSERT_TRUE(it != it1 && it != it2);
    ASSERT_TRUE(*it == 3.1 && *it1 == 3.1 && *it2 == 3.1);
    ++it;
    ++it1;
    ++it2;
    ASSERT_TRUE(it != it1 && it != it2);
    ASSERT_TRUE(*it == 4.1 && *it1 == 4.1 && *it2 == 4.1);
}

TEST(list_string) {
    List<string> test;
    test.push_back("pen");
    test.push_back("ball");
    test.push_back("stick");

    ASSERT_TRUE(test.front() == "pen");
    ASSERT_TRUE(test.back() == "stick");
    test.pop_back();
    ASSERT_TRUE(test.back() == "ball");
}





TEST_MAIN()