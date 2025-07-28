//idocohen963@gmail.com
#include <iostream>
#include "MyContainer.hpp"
using namespace ex4;
int main() {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    std::cout << "Size of container: " << container.size() << std::endl;
    std::cout << "Container contents: " << container << std::endl;

    std::cout << "Ascending order: ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // 1 2 6 7 15
    }
    std::cout << std::endl;

    std::cout << "Descending order: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // 15 7 6 2 1
    }
    std::cout << std::endl;

    std::cout << "Side cross order: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // 1 15 2 7 6
    }
    std::cout << std::endl;

    std::cout << "Reverse order: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // 2 1 6 15 7
    }
    std::cout << std::endl;

    std::cout << "Regular order: ";
    for (auto it = container.begin_order(); it != container.end_order(); ++it) {
        std::cout << *it << ' ';  // 7 15 6 1 2
    }
    std::cout << std::endl;

    std::cout << "Middle out order: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // 6 15 1 7 2
    }
    std::cout << std::endl;

    // Example with std::string
    MyContainer<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("C++");
    stringContainer.add("Programming");
    stringContainer.add("Is");
    stringContainer.add("Fun");

    std::cout << "String container contents: " << stringContainer << std::endl;

    std::cout << "String container in ascending order: ";
    for (auto it = stringContainer.begin_ascending_order(); it != stringContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "String container in reverse order: ";
    for (auto it = stringContainer.begin_reverse_order(); it != stringContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "String container in side cross order: ";
    for (auto it = stringContainer.begin_side_cross_order(); it != stringContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Example with double
    MyContainer<double> doubleContainer;
    doubleContainer.add(3.14);
    doubleContainer.add(2.71);
    doubleContainer.add(1.41);
    doubleContainer.add(0.577);
    doubleContainer.add(1.618);
    doubleContainer.add(2.302);

    std::cout << "Double container contents: " << doubleContainer << std::endl;

    std::cout << "Double container in ascending order: ";
    for (auto it = doubleContainer.begin_ascending_order(); it != doubleContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Double container in reverse order: ";
    for (auto it = doubleContainer.begin_reverse_order(); it != doubleContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Double container in side cross order: ";
    for (auto it = doubleContainer.begin_side_cross_order(); it != doubleContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}
