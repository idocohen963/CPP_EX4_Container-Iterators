//idocohen963@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <string>
#include <sstream>
#include <vector>

using namespace ex4;

TEST_SUITE("Core Functionality & Constructors") {
    
    // Tests that a newly created container is empty.
    TEST_CASE("Create empty container") {
        MyContainer<int> container;
        CHECK(container.size() == 0);
    }
    
    // Tests adding one element and checks size and content.
    TEST_CASE("Add single element") {
        MyContainer<int> container;
        container.add(5);
        CHECK(container.size() == 1);
        
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[5]");
    }
    
    // Tests adding several elements.
    TEST_CASE("Add multiple elements") {
        MyContainer<int> container;
        container.add(10);
        container.add(20);
        container.add(30);
        CHECK(container.size() == 3);
        
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[10, 20, 30]");
    }
    
    // Tests removing an element that exists in the container.
    TEST_CASE("Remove existing element") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        container.remove(2);
        CHECK(container.size() == 2);
        
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[1, 3]");
    }

    // Tests the copy constructor to ensure a deep copy is made.
    TEST_CASE("Copy constructor") {
        MyContainer<int> original;
        original.add(4);
        original.add(5);
        original.add(6);
        
        MyContainer<int> copy(original);
        CHECK(copy.size() == original.size());
        
        std::stringstream ss1, ss2;
        ss1 << original;
        ss2 << copy;
        CHECK(ss1.str() == ss2.str());
        
        // Test independence by modifying the copy.
        copy.add(7);
        CHECK(copy.size() != original.size());
    }
    
    // Tests the assignment operator for deep copy and independence.
    TEST_CASE("Assignment operator") {
        MyContainer<int> container1;
        container1.add(1);
        container1.add(2);
        
        MyContainer<int> container2;
        container2.add(3);
        container2.add(4);
        
        container2 = container1;
        
        std::stringstream ss1, ss2;
        ss1 << container1;
        ss2 << container2;
        CHECK(ss1.str() == ss2.str());
        
        // Test independence by modifying the original.
        container1.add(5);
        CHECK(container1.size() != container2.size());
    }
    
    // Checks that assigning a container to itself does not corrupt it.
    TEST_CASE("Self assignment") {
        MyContainer<int> container;
        container.add(7);
        container.add(8);
        container.add(9);
        
        container = container;
        CHECK(container.size() == 3);
        
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[7, 8, 9]");
    }

    // Verifies that printing an empty container results in "[]".
    TEST_CASE("Print empty container") {
        MyContainer<int> container;
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[]");
    }
    
    // Verifies correct printing format for a container with one element.
    TEST_CASE("Print container with single element") {
        MyContainer<int> container;
        container.add(42);
        
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[42]");
    }
}

TEST_SUITE("Iterator Functionality") {
    
    // Checks the default order iterator (insertion order).
    TEST_CASE("Regular scan with OrderIterator") {
        MyContainer<int> container;
        container.add(10);
        container.add(30);
        container.add(20);
        
        std::vector<int> result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {10, 30, 20};
        CHECK(result == expected);
    }
    
    // Ensures begin() and end() are the same for an empty container.
    TEST_CASE("OrderIterator on empty container") {
        MyContainer<int> container;
        auto begin_it = container.begin_order();
        auto end_it = container.end_order();
        CHECK(begin_it == end_it);
    }

    // Checks the reverse order iterator.
    TEST_CASE("Reverse scan") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        container.add(4);
        
        std::vector<int> result;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {4, 3, 2, 1};
        CHECK(result == expected);
    }
    
    // Checks the reverse iterator on a single-element container.
    TEST_CASE("ReverseOrderIterator with single element") {
        MyContainer<int> container;
        container.add(99);
        
        std::vector<int> result;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {99};
        CHECK(result == expected);
    }
    
    // Checks the ascending order iterator.
    TEST_CASE("Ascending order scan") {
        MyContainer<int> container;
        container.add(50);
        container.add(10);
        container.add(30);
        container.add(20);
        
        std::vector<int> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {10, 20, 30, 50};
        CHECK(result == expected);
    }
    
    // Checks the ascending iterator with duplicate values.
    TEST_CASE("AscendingIterator with duplicate values") {
        MyContainer<int> container;
        container.add(5);
        container.add(3);
        container.add(5);
        container.add(1);
        container.add(3);
        
        std::vector<int> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {1, 3, 3, 5, 5};
        CHECK(result == expected);
    }

    // Checks the descending order iterator.
    TEST_CASE("Descending order scan") {
        MyContainer<int> container;
        container.add(15);
        container.add(5);
        container.add(25);
        container.add(10);
        
        std::vector<int> result;
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {25, 15, 10, 5};
        CHECK(result == expected);
    }

    // Checks the side-cross iteration pattern (first, last, second, second-to-last...).
    TEST_CASE("SideCross scan - odd number of elements") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(6);
        container.add(7);
        container.add(15);
        
        std::vector<int> result;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {1, 15, 2, 7, 6};
        CHECK(result == expected);
    }
    
    // Checks the side-cross pattern with an even number of elements.
    TEST_CASE("SideCross scan - even number of elements") {
        MyContainer<int> container;
        container.add(3);
        container.add(8);
        container.add(12);
        container.add(18);
        
        std::vector<int> result;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {3, 18, 8, 12};
        CHECK(result == expected);
    }
    
    // Checks the side-cross iterator on a single-element container.
    TEST_CASE("SideCrossIterator with single element") {
        MyContainer<int> container;
        container.add(100);
        
        std::vector<int> result;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {100};
        CHECK(result == expected);
    }

    // Checks the middle-out iteration pattern with an odd number of elements.
    TEST_CASE("MiddleOut scan - odd number of elements") {
        MyContainer<int> container;
        container.add(10);
        container.add(20);
        container.add(30);
        container.add(40);
        container.add(50);
        
        std::vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {30, 20, 40, 10, 50};
        CHECK(result == expected);
    }
    
    // Checks the middle-out pattern with an even number of elements.
    TEST_CASE("MiddleOut scan - even number of elements") {
        MyContainer<int> container;
        container.add(5);
        container.add(15);
        container.add(25);
        container.add(35);
        
        std::vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        
        std::vector<int> expected = {25, 15, 35, 5};
        CHECK(result == expected);
    }

    // Compares iterators from the same container for equality and inequality.
    TEST_CASE("Compare iterators from same container") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_order();
        auto it2 = container.begin_order();
        
        CHECK(it1 == it2);
        CHECK_FALSE(it1 != it2);
        
        ++it1;
        CHECK_FALSE(it1 == it2);
        CHECK(it1 != it2);
    }
    
    // Verifies that iterators from different containers are not equal.
    TEST_CASE("Compare iterators from different containers") {
        MyContainer<int> container1;
        MyContainer<int> container2;
        container1.add(1);
        container2.add(1);
        
        auto it1 = container1.begin_order();
        auto it2 = container2.begin_order();
        
        CHECK_FALSE(it1 == it2);
        CHECK(it1 != it2);
    }
}

TEST_SUITE("Advanced, Edge Cases & Error Handling") {
    
    // Tests that removing an element not in the container throws a runtime_error.
    TEST_CASE("Remove non-existing element") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        CHECK_THROWS_AS(container.remove(5), std::runtime_error);
        CHECK_THROWS_WITH(container.remove(5), "Element was not found in the container");
    }
    
    // Tests that removing from an empty container throws an exception.
    TEST_CASE("Remove from empty container") {
        MyContainer<int> container;
        CHECK_THROWS_AS(container.remove(1), std::runtime_error);
    }

    // Tests that dereferencing an end iterator throws an out_of_range exception.
    TEST_CASE("OrderIterator out of range dereference") {
        MyContainer<int> container;
        container.add(1);
        
        auto end_it = container.end_order();
        CHECK_THROWS_AS(*end_it, std::out_of_range);
    }
    
    // Checks that `remove` deletes all occurrences of a value.
    TEST_CASE("Remove all instances of repeating value") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(2);
        container.add(3);
        container.add(2);
        container.add(4);
        
        container.remove(2);
        CHECK(container.size() == 3);
        
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[1, 3, 4]");
    }
    
    // Verifies that the container and its iterators work with negative integers.
    TEST_CASE("Work with negative values") {
        MyContainer<int> container;
        container.add(-5);
        container.add(-1);
        container.add(-10);
        container.add(3);
        
        std::vector<int> ascending_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            ascending_result.push_back(*it);
        }
        
        std::vector<int> expected = {-10, -5, -1, 3};
        CHECK(ascending_result == expected);
    }

    // Verifies the container works correctly with std::string as the template type.
    TEST_CASE("Work with string") {
        MyContainer<std::string> container;
        container.add("zebra");
        container.add("apple");
        container.add("banana");
        
        std::vector<std::string> ascending_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            ascending_result.push_back(*it);
        }
        
        std::vector<std::string> expected = {"apple", "banana", "zebra"};
        CHECK(ascending_result == expected);
    }
    
    // Verifies the container works correctly with double as the template type.
    TEST_CASE("Work with double") {
        MyContainer<double> container;
        container.add(3.14);
        container.add(2.71);
        container.add(1.41);
        container.add(2.71);
        
        std::vector<double> ascending_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            ascending_result.push_back(*it);
        }
        
        std::vector<double> expected = {1.41, 2.71, 2.71, 3.14};
        CHECK(ascending_result == expected);
    }

    // An integration test checking all iterator types on the same container.
    TEST_CASE("Multiple iterators combination") {
        MyContainer<int> container;
        container.add(4);
        container.add(1);
        container.add(3);
        container.add(2);
        
        // Order Iterator
        std::vector<int> order_result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            order_result.push_back(*it);
        }
        CHECK(order_result == std::vector<int>{4, 1, 3, 2});
        
        // Ascending Iterator
        std::vector<int> ascending_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            ascending_result.push_back(*it);
        }
        CHECK(ascending_result == std::vector<int>{1, 2, 3, 4});
    }

    // Checks that iterators work correctly on a container with only identical elements.
    TEST_CASE("Container with identical elements") {
        MyContainer<int> container;
        container.add(7);
        container.add(7);
        container.add(7);
        container.add(7);
        
        std::vector<int> expected = {7, 7, 7, 7};
        
        std::vector<int> order_result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            order_result.push_back(*it);
        }
        CHECK(order_result == expected);
        
        std::vector<int> asc_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc_result.push_back(*it);
        }
        CHECK(asc_result == expected);
    }

    // Checks that multiple iterators can be created and used independently.
    TEST_CASE("Multiple iterators simultaneously") {
        MyContainer<int> container;
        container.add(3);
        container.add(1);
        container.add(4);
        container.add(1);
        container.add(5);
        
        auto order_it = container.begin_order();
        auto asc_it = container.begin_ascending_order();
        auto desc_it = container.begin_descending_order();
        auto side_it = container.begin_side_cross_order();
        auto middle_it = container.begin_middle_out_order();
        auto reverse_it = container.begin_reverse_order();
        
        // Check that each iterator points to its correct starting element.
        CHECK(*order_it == 3);
        CHECK(*asc_it == 1);
        CHECK(*desc_it == 5);
        CHECK(*side_it == 1);
        CHECK(*middle_it == 4);
        CHECK(*reverse_it == 5);
    }
}