#include <gtest/gtest.h>

#include <list>

#include "mylist.h"

TEST(constuctor, default_constructor) { List<int> test; }

TEST(constuctor, size_n) {
List<int> test(5);
}

TEST(constuctor, init_list) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
}

TEST(func, begin) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
GTEST_ASSERT_EQ(*test.begin(), 5);
}

TEST(foreach, foreach) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
for (auto &&el : test) {
}
}

TEST(constuctor, copy) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
List<int> result(test);
GTEST_ASSERT_EQ(*result.begin(), 5);
GTEST_ASSERT_EQ(*result.end(), 0);
}

TEST(constuctor, move) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
List<int> result(std::move(test));
GTEST_ASSERT_EQ(*result.begin(), 5);
GTEST_ASSERT_EQ(*result.end(), 0);
}

TEST(operator, equals) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
List<int> result;
result = test;
GTEST_ASSERT_EQ(*result.begin(), 5);
GTEST_ASSERT_EQ(*result.end(), 0);
}

TEST(push_front, ex_1) {
List<int> test;
test.push_front(5);
test.push_front(5);
test.push_front(5);
GTEST_ASSERT_EQ(test.size(), 3);
}

TEST(pop_back, ex_1) {
List<int> test;
test.push_front(5);
test.push_front(5);
test.push_front(5);
test.pop_back();
test.pop_back();
GTEST_ASSERT_EQ(test.size(), 1);
}

TEST(pop_back, ex_2) {
List<int> test;
test.push_front(5);
test.push_front(5);
test.push_front(5);
test.pop_back();
test.pop_back();
test.pop_back();
GTEST_ASSERT_EQ(test.size(), 0);
}

TEST(pop_front, ex_1) {
List<int> test;
test.push_front(5);
test.push_front(5);
test.push_front(5);
test.pop_front();
test.pop_front();
test.pop_front();
GTEST_ASSERT_EQ(test.size(), 0);
}

TEST(pop_front, ex_2) {
List<int> test;
test.push_front(5);
test.push_front(5);
test.push_front(5);
test.pop_front();
test.pop_front();
GTEST_ASSERT_EQ(test.size(), 1);
}

TEST(clear, ex_1) {
List<int> test;
test.push_front(5);
test.push_front(4);
test.push_front(10);
test.clear();
GTEST_ASSERT_EQ(test.size(), 0);
}

TEST(iterator, begin) {
List<int> test;
test.push_front(5);
test.push_front(4);
test.push_front(10);
GTEST_ASSERT_EQ(*test.begin(), 10);
}

TEST(iterator, not_equals) {
List<int> test;
test.push_front(5);
test.push_front(4);
test.push_front(10);
GTEST_ASSERT_EQ(test.begin() != test.end(), 1);
}

TEST(iterator, increment) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
auto it = test.begin();
GTEST_ASSERT_EQ(*it, 5);
++it;
GTEST_ASSERT_EQ(*it, 4);
++it;
GTEST_ASSERT_EQ(*it, 22);
}

TEST(iterator, decrement) {
List<int> test{5, 4, 22, 156, 3, 2, 1, 0};
auto it = test.end();
GTEST_ASSERT_EQ(*it, 0);
--it;
GTEST_ASSERT_EQ(*it, 0);
--it;
GTEST_ASSERT_EQ(*it, 1);
--it;
GTEST_ASSERT_EQ(*it, 2);
}

TEST(find, ex_1) {
List<int> test;
test.push_back(5);
test.push_back(6);
test.push_back(1);
auto search = test.find(5);
GTEST_ASSERT_EQ(*search, 5);
}


TEST(List_Constructors, default_constructor) {
List<int> my_list_int;
ASSERT_TRUE(my_list_int.empty());
ASSERT_EQ(my_list_int.size(), 0);

List<size_t> my_list_size_t;
ASSERT_TRUE(my_list_size_t.empty());
ASSERT_EQ(my_list_size_t.size(), 0);

List<double> my_list_double;
ASSERT_TRUE(my_list_double.empty());
ASSERT_EQ(my_list_double.size(), 0);

List<char> my_list_char;
ASSERT_TRUE(my_list_char.empty());
ASSERT_EQ(my_list_char.size(), 0);

List<std::string> my_list_string;
ASSERT_TRUE(my_list_string.empty());
ASSERT_EQ(my_list_string.size(), 0);
}

TEST(List_Constructors, parameterized_constructor) {
List<int> my_list_int(3);
ASSERT_FALSE(my_list_int.empty());
ASSERT_EQ(my_list_int.size(), 3);

List<size_t> my_list_size_t(100);
ASSERT_FALSE(my_list_size_t.empty());
ASSERT_EQ(my_list_size_t.size(), 100);

List<double> my_list_double(78);
ASSERT_FALSE(my_list_double.empty());
ASSERT_EQ(my_list_double.size(), 78);

List<char> my_list_char(0);
ASSERT_TRUE(my_list_char.empty());
ASSERT_EQ(my_list_char.size(), 0);

List<std::string> my_list_string(205);
ASSERT_FALSE(my_list_string.empty());
ASSERT_EQ(my_list_string.size(), 205);
}

TEST(List_Constructors, initializer_list_constructor) {
List<int> my_list_int{777, -3, 1, 2, 2};
ASSERT_EQ(my_list_int.size(), 5);
ASSERT_EQ(my_list_int.front(), 777);
ASSERT_EQ(my_list_int.back(), 2);

List<std::string> my_list_string{"Hello", "I'm", "Human"};
ASSERT_EQ(my_list_string.size(), 3);
ASSERT_EQ(my_list_string.front(), "Hello");
ASSERT_EQ(my_list_string.back(), "Human");
}

TEST(List_Constructors, copy_constructor_iterators) {
List<int> my_list_int{777, -3, 1, 2, 5};
List<int> my_list_int2(my_list_int);
ASSERT_EQ(my_list_int.size(), 5);
ASSERT_EQ(my_list_int.front(), 777);
ASSERT_EQ(my_list_int.back(), 5);
ASSERT_EQ(my_list_int2.size(), 5);
ASSERT_EQ(my_list_int2.front(), 777);
ASSERT_EQ(my_list_int2.back(), 5);

List<std::string> my_list_string{"Hello", "I'm", "Human"};
List<std::string> my_list_string2(my_list_string);
ASSERT_EQ(my_list_string.size(), 3);
ASSERT_EQ(my_list_string.front(), "Hello");
ASSERT_EQ(my_list_string.back(), "Human");
auto it = my_list_string2.begin();
auto it_end = my_list_string2.end();
--it_end;
ASSERT_EQ(*it, "Hello");
ASSERT_EQ(*it_end, "Human");
}

TEST(List_Constructors, move_constructor_iterators) {
List<int> my_list_int{777, -3, 1, 2, 5};
List<int> my_list_int2(std::move(my_list_int));
ASSERT_EQ(my_list_int.size(), 0);
ASSERT_EQ(my_list_int2.size(), 5);
ASSERT_EQ(my_list_int2.front(), 777);
ASSERT_EQ(my_list_int2.back(), 5);

List<std::string> my_list_string{"Hello", "I'm", "Human"};
List<std::string> my_list_string2(std::move(my_list_string));
ASSERT_EQ(my_list_string.size(), 0);
ASSERT_EQ(my_list_string2.size(), 3);
auto it = my_list_string2.begin();
auto it_end = my_list_string2.end();
--it_end;
ASSERT_EQ(*it, "Hello");
ASSERT_EQ(*it_end, "Human");
}

TEST(List_Overload, assignment_operator_swap) {
List<int> my_list_int{777, -3, 1, 2, 5};
List<int> my_list_int2(3);
my_list_int2 = my_list_int;
ASSERT_EQ(my_list_int.size(), 5);
ASSERT_EQ(my_list_int.front(), 777);
ASSERT_EQ(my_list_int.back(), 5);
ASSERT_EQ(my_list_int2.size(), 5);
ASSERT_EQ(my_list_int2.front(), 777);
ASSERT_EQ(my_list_int2.back(), 5);

List<double> my_list_double{0.5, -3.9, 1.5, 2.3};
List<double> my_list_double2{100.1, 100.2};
my_list_double2 = my_list_double;
ASSERT_EQ(my_list_double.size(), 4);
ASSERT_DOUBLE_EQ(my_list_double.front(), 0.5);
ASSERT_DOUBLE_EQ(my_list_double.back(), 2.3);
ASSERT_EQ(my_list_double2.size(), 4);
ASSERT_DOUBLE_EQ(my_list_double2.front(), 0.5);
ASSERT_DOUBLE_EQ(my_list_double2.back(), 2.3);

List<std::string> my_list_string{"Hello", "I'm", "Human"};
List<std::string> my_list_string2{"Nice", "to", "meet", "you"};
my_list_string2 = std::move(my_list_string);
ASSERT_EQ(my_list_string.size(), 0);
ASSERT_EQ(my_list_string2.size(), 3);
auto it = my_list_string2.begin();
auto it_end = my_list_string2.end();
--it_end;
ASSERT_EQ(*it, "Hello");
ASSERT_EQ(*it_end, "Human");
}

TEST(List_Modifiers, test_clear) {
List<int> my_list_int{777, -3, 1, 0, 5};
std::list<int> list_int{777, -3, 1, 0, 5};
my_list_int.clear();
list_int.clear();
ASSERT_EQ(my_list_int.size(), list_int.size());
ASSERT_TRUE(my_list_int.empty());
}

TEST(List_Modifiers, test_insert_push) {
List<int> my_list_int{777, -3, 1, 0, 5};
std::list<int> list_int{777, -3, 1, 0, 5};
auto it_my = my_list_int.begin();
auto it_orig = list_int.begin();
auto it_my_insert = my_list_int.insert(it_my, 111);
auto it_orig_insert = list_int.insert(it_orig, 111);
ASSERT_EQ(*it_my_insert, *it_orig_insert);
++it_my;
++it_orig;
auto it_my_insert2 = my_list_int.insert(it_my, 8);
auto it_orig_insert2 = list_int.insert(it_orig, 8);
ASSERT_EQ(*it_my_insert2, *it_orig_insert2);
}

TEST(List_Modifiers, test_erase_pop) {
List<std::string> my_list_string{"Hello", "I'm", "Human"};
std::list<std::string> list_string{"Hello", "I'm", "Human"};
auto it_my = my_list_string.begin();
auto it_orig = list_string.begin();
++it_my;
++it_orig;
my_list_string.erase(it_my);
list_string.erase(it_orig);
auto it_my_after_erase = my_list_string.begin();
auto it_orig_after_erase = list_string.begin();
++it_my_after_erase;
++it_orig_after_erase;
ASSERT_EQ(*it_my_after_erase, *it_orig_after_erase);

my_list_string.erase(it_my_after_erase);
list_string.erase(it_orig_after_erase);
auto it_my_after_erase2 = my_list_string.begin();
auto it_orig_after_erase2 = list_string.begin();
ASSERT_EQ(*it_my_after_erase2, *it_orig_after_erase2);

my_list_string.erase(it_my_after_erase2);
list_string.erase(it_orig_after_erase2);
ASSERT_TRUE(my_list_string.empty());
ASSERT_TRUE(list_string.empty());
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
