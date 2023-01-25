// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

using namespace std;
TEST(test_one) {
    BinarySearchTree<int> tree;
    
    tree.insert(3);

    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(*tree.max_element() == 3);
    ASSERT_TRUE(*tree.min_element() == 3);
    ASSERT_TRUE(*tree.min_greater_than(2) == 3);
    ASSERT_EQUAL(tree.min_greater_than(5), tree.end());
    ASSERT_EQUAL(*tree.find(3), 3);
    ASSERT_EQUAL(tree.find(4), tree.end());
    ASSERT_EQUAL(tree.find(5), tree.end());
    ostringstream correct;
    ostringstream s;
    ostringstream w;
    correct << "3 ";
    tree.traverse_inorder(s);
    tree.traverse_preorder(w);
    ASSERT_EQUAL(s.str(), correct.str());
    ASSERT_EQUAL(w.str(), correct.str());
    
}
TEST(tree_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.min_element(), tree.end());
    ASSERT_EQUAL(tree.max_element(), tree.end());
    ASSERT_EQUAL(tree.min_greater_than(2), tree.end());
    ASSERT_EQUAL(tree.find(3), tree.end());
    ostringstream correct;
    ostringstream s;
    ostringstream w;
    correct << "";
    tree.traverse_inorder(s);
    tree.traverse_preorder(w);
    ASSERT_EQUAL(s.str(), correct.str());
    ASSERT_EQUAL(w.str(), correct.str());
}
TEST(tree_changed_invariant) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    ASSERT_EQUAL(tree.size(), 3);
    ASSERT_EQUAL(tree.height(), 2);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(*tree.max_element(), 6);
    ASSERT_EQUAL(*tree.min_element(), 2);
    ASSERT_EQUAL(*tree.min_greater_than(3), 4);
    ostringstream correct_s;
    ostringstream correct_w;
    ostringstream s;
    ostringstream w;
    correct_s << "4 2 6 ";
    correct_w << "2 4 6 ";
    tree.traverse_inorder(w);
    tree.traverse_preorder(s);
    ASSERT_EQUAL(correct_s.str(), s.str());
    ASSERT_EQUAL(correct_w.str(), w.str());
    *tree.find(2) = 7;
    ASSERT_FALSE(tree.check_sorting_invariant());
}
TEST(min_greater_than_back_up) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(7);
    tree.insert(5);
    ASSERT_NOT_EQUAL(tree.min_greater_than(6), tree.end());
    ASSERT_EQUAL(*tree.min_greater_than(6), 7); //may consider not using - if it fails and returns nullptr creates seg fault
}
TEST(tree_unbalanced) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(4);
    tree.insert(3);
    tree.insert(5);
    tree.insert(10);
    tree.insert(8);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(*tree.min_element(), 3);
    ASSERT_EQUAL(*tree.max_element(), 10);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(*tree.find(10), 10);
    ASSERT_EQUAL(tree.size(), 6);
    ASSERT_EQUAL(tree.height(), 3);
    ASSERT_EQUAL(*tree.min_greater_than(6), 7);
    ASSERT_EQUAL(*tree.min_greater_than(9), 10);
    ostringstream p;
    ostringstream i;
    ostringstream correct_p;
    ostringstream correct_i;
    cout << tree;
    correct_p << "7 4 3 5 10 8 ";
    correct_i << "3 4 5 7 8 10 ";
    tree.traverse_inorder(i);
    tree.traverse_preorder(p);
    ASSERT_EQUAL(correct_p.str(), p.str());
    ASSERT_EQUAL(correct_i.str(), i.str()); 
}
TEST(copy_nodes) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(4);
    tree.insert(3);
    tree.insert(5);
    tree.insert(10);
    tree.insert(8);
    BinarySearchTree<int> tree_two(tree);
    ASSERT_NOT_EQUAL(tree.find(7), tree_two.find(7));
    ASSERT_NOT_EQUAL(tree.find(4), tree_two.find(4));
    ASSERT_NOT_EQUAL(tree.find(3), tree_two.find(3));
    ASSERT_NOT_EQUAL(tree.find(5), tree_two.find(5));
    ASSERT_NOT_EQUAL(tree.find(10), tree_two.find(10));
    ASSERT_NOT_EQUAL(tree.find(8), tree_two.find(8));
    ASSERT_EQUAL(*tree.find(7), *tree_two.find(7));
    ASSERT_EQUAL(*tree.find(4), *tree_two.find(4));
    ASSERT_EQUAL(*tree.find(3), *tree_two.find(3));
    ASSERT_EQUAL(*tree.find(5), *tree_two.find(5));
    ASSERT_EQUAL(*tree.find(10), *tree_two.find(10));
    ASSERT_EQUAL(*tree.find(8), *tree_two.find(8));
}
TEST(tree_assign){
    BinarySearchTree<int> tree_three;
    BinarySearchTree<int> tree_four;
    tree_three.insert(4);
    tree_three.insert(2);
    tree_three.insert(5);
    tree_four.insert(6);
    tree_four.insert(3);
    ASSERT_TRUE(tree_four.size() == 2);
    tree_four = tree_three;
    ASSERT_EQUAL(*tree_four.find(4), 4);
    ASSERT_NOT_EQUAL(tree_four.find(4), tree_three.find(4));
    ASSERT_NOT_EQUAL(tree_four.find(2), tree_three.find(2));
    ASSERT_NOT_EQUAL(tree_four.find(5), tree_three.find(5));
    ASSERT_EQUAL(*tree_four.find(4), *tree_three.find(4));
    ASSERT_EQUAL(*tree_four.find(2), *tree_three.find(2));
    ASSERT_EQUAL(*tree_four.find(5), *tree_three.find(5));
}
TEST(tree_out) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    ostringstream p;
    ostringstream i;
    ostringstream correct_p;
    ostringstream correct_i;
    cout << tree;
    correct_p << "7 6 5 ";
    correct_i << "5 6 7 ";
    tree.traverse_inorder(i);
    tree.traverse_preorder(p);
    ASSERT_EQUAL(correct_p.str(), p.str());
    ASSERT_EQUAL(correct_i.str(), i.str());
}

TEST_MAIN()
