//idocohen963@gmail.com

/**
 * @file MyContainer.hpp
 * @brief Defines a template container class with multiple iterator types
 */
#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>


namespace ex4{

    /**
     * @brief A template container class that stores elements and provides various iterators
     * @tparam T The type of elements stored in the container (defaults to int)
     */
    template<typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> elements; ///< Internal storage for container elements

    public:
        /**
         * @brief Default constructor for MyContainer
         */
        MyContainer() = default;

        /**
         * @brief Copy constructor
         * @param other The MyContainer to copy from
         */
        MyContainer(const MyContainer& other) : elements(other.elements){}
        
        /**
         * @brief Assignment operator
         * @param other The MyContainer to assign from
         * @return Reference to this MyContainer
         */
        MyContainer& operator=(const MyContainer& other){
            if(this != &other) elements = other.elements;
            return *this;
        }

        /**
         * @brief Default destructor
         */
        ~MyContainer() = default;

        /**
         * @brief Add an element to the container
         * @param element The element to add
         */
        void add(const T& element){
            elements.push_back(element);
        }

        /**
         * @brief Remove an element from the container
         * @param element The element to remove
         * @throws std::runtime_error if the element is not found in the container
         * @details Uses the erase-remove idiom to efficiently remove all instances 
         * of the specified element from the container
         */
        void remove(const T& element){
            if(std::find(elements.begin(), elements.end(), element) == elements.end()){
                throw std::runtime_error("Element was not found in the container");
            }
            elements.erase(std::remove(elements.begin(), elements.end(), element),elements.end());
        }

        /**
         * @brief Get the number of elements in the container
         * @return The number of elements as size_t
         */
        size_t size() const{return elements.size();}

        /**
         * @brief Stream insertion operator for MyContainer
         * @param os The output stream
         * @param container The container to output
         * @return Reference to the output stream
         * @details Formats the container as a comma-separated list of elements enclosed in square brackets
         */
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container){
            os<< "[" ;
            if (container.elements.empty()) {
                os << "]";
                return os;
            }
            for (size_t i = 0; i < container.elements.size(); ++i) {
                os << container.elements[i];
                if (i < container.elements.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }

        /**
         * @brief Iterator that traverses elements in their original order
         */
        class OrderIterator{

            private:
            std::vector<T> _elements;      ///< Copy of container elements
            size_t current_index;          ///< Current position in the iteration
            const MyContainer<T>* owner;   ///< Pointer to the container being iterated

            public:
            /**
             * @brief Constructor for OrderIterator
             * @param elements Vector of elements to iterate
             * @param index Starting position for iteration
             * @param container Pointer to the owner container
             */
            OrderIterator(const std::vector<T>& elements, size_t index, const MyContainer<T>* container)
                : _elements(elements), current_index(index), owner(container){}

            /**
             * @brief Dereference operator
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is out of bounds
             */
            const T& operator*() const{
                if(current_index >= _elements.size()) throw std::out_of_range("Iterator out of bounds");
                return _elements[current_index];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after advancement
             */
            OrderIterator& operator++(){++current_index; return *this; }

            /**
             * @brief Post-increment operator
             * @return Copy of the iterator before advancement
             */
            OrderIterator operator++(int){
                OrderIterator tmp = *this;
                ++current_index;
                return tmp;
            }

            /**
             * @brief Equality comparison operator
             * @param other The iterator to compare with
             * @return True if both iterators belong to the same container and point to the same index
             */
            bool operator==(const OrderIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }

            /**
             * @brief Inequality comparison operator
             * @param other The iterator to compare with
             * @return True if iterators are not equal
             */
            bool operator!=(const OrderIterator& other) const { return !(*this == other); }
        };

        /**
         * @brief Get an iterator to the beginning of the container in original order
         * @return OrderIterator pointing to the first element
         */
        OrderIterator begin_order() { return OrderIterator(elements, 0, this); }
        
        /**
         * @brief Get an iterator to the end of the container in original order
         * @return OrderIterator pointing past the last element
         */
        OrderIterator end_order() { return OrderIterator(elements, elements.size(), this); }

        /**
         * @brief Iterator that traverses elements in reverse order
         */
        class ReverseOrderIterator{

            private:
            std::vector<T> reverse_elements; ///< Reversed copy of container elements
            size_t current_index;           ///< Current position in the iteration
            const MyContainer<T>* owner;    ///< Pointer to the container being iterated

            public:
            /**
             * @brief Constructor for ReverseOrderIterator
             * @param elements Vector of elements to iterate in reverse
             * @param index Starting position for iteration
             * @param container Pointer to the owner container
             */
            ReverseOrderIterator(const std::vector<T>& elements, size_t index, const MyContainer<T>* container)
                : reverse_elements(elements), current_index(index), owner(container){
                    std::reverse(reverse_elements.begin(), reverse_elements.end());
                }

            /**
             * @brief Dereference operator
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is out of bounds
             */
            const T& operator*() const{
                if(current_index >= reverse_elements.size()) throw std::out_of_range("Iterator out of bounds");
                return reverse_elements[current_index];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after advancement
             */
            ReverseOrderIterator& operator++(){++current_index; return *this; }

            /**
             * @brief Post-increment operator
             * @return Copy of the iterator before advancement
             */
            ReverseOrderIterator operator++(int){
                ReverseOrderIterator tmp = *this;
                ++current_index;
                return tmp;
            }

            /**
             * @brief Equality comparison operator
             * @param other The iterator to compare with
             * @return True if both iterators belong to the same container and point to the same index
             */
            bool operator==(const ReverseOrderIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }

            /**
             * @brief Inequality comparison operator
             * @param other The iterator to compare with
             * @return True if iterators are not equal
             */
            bool operator!=(const ReverseOrderIterator& other) const { return !(*this == other); }
        };

        /**
         * @brief Get an iterator to the beginning of the container in reverse order
         * @return ReverseOrderIterator pointing to the first element (last in original order)
         */
        ReverseOrderIterator begin_reverse_order() { return ReverseOrderIterator(elements, 0, this); }
        
        /**
         * @brief Get an iterator to the end of the container in reverse order
         * @return ReverseOrderIterator pointing past the last element
         */
        ReverseOrderIterator end_reverse_order() { return ReverseOrderIterator(elements, elements.size(), this); }

        /**
         * @brief Iterator that traverses elements in ascending order
         */
        class AscendingIterator{

            private:
            std::vector<T> sorted_elements; ///< Sorted copy of container elements
            size_t current_index;          ///< Current position in the iteration
            const MyContainer<T>* owner;   ///< Pointer to the container being iterated

            public:
            /**
             * @brief Constructor for AscendingIterator
             * @param elements Vector of elements to iterate in ascending order
             * @param index Starting position for iteration
             * @param container Pointer to the owner container
             */
            AscendingIterator(const std::vector<T>& elements, size_t index, const MyContainer<T>* container)
                : sorted_elements(elements), current_index(index), owner(container){
                std::sort(sorted_elements.begin(), sorted_elements.end());
            }

            /**
             * @brief Dereference operator
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is out of bounds
             */
            const T& operator*() const{
                if(current_index >= sorted_elements.size()) throw std::out_of_range("Iterator out of bounds");
                return sorted_elements[current_index];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after advancement
             */
            AscendingIterator& operator++(){++current_index; return *this; }

            /**
             * @brief Post-increment operator
             * @return Copy of the iterator before advancement
             */
            AscendingIterator operator++(int){
                AscendingIterator tmp = *this;
                ++current_index;
                return tmp;
            }

            /**
             * @brief Equality comparison operator
             * @param other The iterator to compare with
             * @return True if both iterators belong to the same container and point to the same index
             */
            bool operator==(const AscendingIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }

            /**
             * @brief Inequality comparison operator
             * @param other The iterator to compare with
             * @return True if iterators are not equal
             */
            bool operator!=(const AscendingIterator& other) const { return !(*this == other); }

        };

        /**
         * @brief Get an iterator to the beginning of the container in ascending order
         * @return AscendingIterator pointing to the smallest element
         */
        AscendingIterator begin_ascending_order() { return AscendingIterator(elements, 0, this); }
        
        /**
         * @brief Get an iterator to the end of the container in ascending order
         * @return AscendingIterator pointing past the last element
         */
        AscendingIterator end_ascending_order() { return AscendingIterator(elements, elements.size(), this); }

        /**
         * @brief Iterator that traverses elements in descending order
         */
        class DescendingOrder {

            private:
            std::vector<T> reverse_sorted_elements; ///< Sorted copy of container elements in descending order
            size_t current_index;                  ///< Current position in the iteration
            const MyContainer<T>* owner;           ///< Pointer to the container being iterated

            public:
            /**
             * @brief Constructor for DescendingOrder iterator
             * @param elements Vector of elements to iterate in descending order
             * @param index Starting position for iteration
             * @param container Pointer to the owner container
             */
            DescendingOrder(const std::vector<T>& elements, size_t index, const MyContainer<T>* container)
                : reverse_sorted_elements(elements), current_index(index), owner(container){
                std::sort(reverse_sorted_elements.begin(), reverse_sorted_elements.end(), std::greater<T>());
            }

            /**
             * @brief Dereference operator
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is out of bounds
             */
            const T& operator*() const{
                if(current_index >= reverse_sorted_elements.size()) throw std::out_of_range("Iterator out of bounds");
                return reverse_sorted_elements[current_index];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after advancement
             */
            DescendingOrder& operator++(){++current_index; return *this; }

            /**
             * @brief Post-increment operator
             * @return Copy of the iterator before advancement
             */
            DescendingOrder operator++(int){
                DescendingOrder tmp = *this;
                ++current_index;
                return tmp;
            }

            /**
             * @brief Equality comparison operator
             * @param other The iterator to compare with
             * @return True if both iterators belong to the same container and point to the same index
             */
            bool operator==(const DescendingOrder& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }

            /**
             * @brief Inequality comparison operator
             * @param other The iterator to compare with
             * @return True if iterators are not equal
             */
            bool operator!=(const DescendingOrder& other) const { return !(*this == other); }

        };

        /**
         * @brief Get an iterator to the beginning of the container in descending order
         * @return DescendingOrder pointing to the largest element
         */
        DescendingOrder begin_descending_order() { return DescendingOrder(elements, 0, this); }
        
        /**
         * @brief Get an iterator to the end of the container in descending order
         * @return DescendingOrder pointing past the last element
         */
        DescendingOrder end_descending_order() { return DescendingOrder(elements, elements.size(), this); }

        /**
         * @brief Iterator that traverses elements in a side-cross pattern
         * @details Traverses from both ends toward the middle: smallest element, 
         * largest element, second smallest, second largest, etc.
         */
        class SideCrossIterator {
            private:
            std::vector<T> sorted_elements;       ///< Sorted copy of container elements
            std::vector<T> side_cross_order;      ///< Elements arranged in side-cross order
            size_t current_index;                ///< Current position in the iteration
            const MyContainer<T>* owner;         ///< Pointer to the container being iterated

            public:
            /**
             * @brief Constructor for SideCrossIterator
             * @param elements Vector of elements to iterate
             * @param index Starting position for iteration
             * @param container Pointer to the owner container
             * @details Arranges elements in side-cross pattern: smallest, largest, 
             * second smallest, second largest, etc.
             */
            SideCrossIterator(const std::vector<T>& elements, size_t index, const MyContainer<T>* container)
                : sorted_elements(elements), current_index(index), owner(container) {
                
                if (elements.empty()) return;
                
                std::sort(sorted_elements.begin(), sorted_elements.end());

                size_t left = 0, right = sorted_elements.size() - 1;
                while (left <= right) {
                    side_cross_order.push_back(sorted_elements[left++]);
                    if (left <= right) {
                        side_cross_order.push_back(sorted_elements[right--]);
                    }
                }
            }

            /**
             * @brief Dereference operator
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is out of bounds
             */
            const T& operator*() const {
                if(current_index >= side_cross_order.size()) throw std::out_of_range("Iterator out of bounds");
                return side_cross_order[current_index];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after advancement
             */
            SideCrossIterator& operator++() {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator
             * @return Copy of the iterator before advancement
             */
            SideCrossIterator operator++(int) {
                SideCrossIterator tmp = *this;
                ++current_index;
                return tmp;
            }

            /**
             * @brief Equality comparison operator
             * @param other The iterator to compare with
             * @return True if both iterators belong to the same container and point to the same index
             */
            bool operator==(const SideCrossIterator& other) const {
                return owner == other.owner && current_index == other.current_index;
            }

            /**
             * @brief Inequality comparison operator
             * @param other The iterator to compare with
             * @return True if iterators are not equal
             */
            bool operator!=(const SideCrossIterator& other) const {
                return !(*this == other);
            }
        };

        /**
         * @brief Get an iterator to the beginning of the container in side-cross order
         * @return SideCrossIterator pointing to the first element in side-cross order
         */
        SideCrossIterator begin_side_cross_order() { return SideCrossIterator(elements, 0, this); }
        
        /**
         * @brief Get an iterator to the end of the container in side-cross order
         * @return SideCrossIterator pointing past the last element
         */
        SideCrossIterator end_side_cross_order() { return SideCrossIterator(elements, elements.size(), this); }

        /**
         * @brief Iterator that traverses elements from the middle outward
         * @details Starts from the middle element and then alternates left and right
         */
        class MiddleOutIterator {
            private:
            std::vector<T> middle_out_order;     ///< Elements arranged in middle-out order
            size_t current_index;               ///< Current position in the iteration
            const MyContainer<T>* owner;        ///< Pointer to the container being iterated

            public:
            /**
             * @brief Constructor for MiddleOutIterator
             * @param elements Vector of elements to iterate
             * @param index Starting position for iteration
             * @param container Pointer to the owner container
             * @details Arranges elements in middle-out pattern starting from the middle element,
             * then alternating left and right outward
             */
            MiddleOutIterator(const std::vector<T>& elements, size_t index, const MyContainer<T>* container)
                : current_index(index), owner(container) {

                if (elements.empty()) return;

                size_t n = elements.size();
                size_t mid = n / 2;

                // Add the middle element
                middle_out_order.push_back(elements[mid]);

                // Then scan alternately left and right, moving toward the edges
                for (size_t offset = 1; offset <= mid; ++offset) {
                    if (mid >= offset)
                        middle_out_order.push_back(elements[mid - offset]);  // Left
                    if (mid + offset < n)
                        middle_out_order.push_back(elements[mid + offset]);  // Right
                }
            }

            /**
             * @brief Dereference operator
             * @return Reference to the current element
             * @throws std::out_of_range if iterator is out of bounds
             */
            const T& operator*() const {
                if(current_index >= middle_out_order.size()) throw std::out_of_range("Iterator out of bounds");
                return middle_out_order[current_index];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after advancement
             */
            MiddleOutIterator& operator++() {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator
             * @return Copy of the iterator before advancement
             */
            MiddleOutIterator operator++(int) {
                MiddleOutIterator tmp = *this;
                ++current_index;
                return tmp;
            }

            /**
             * @brief Equality comparison operator
             * @param other The iterator to compare with
             * @return True if both iterators belong to the same container and point to the same index
             */
            bool operator==(const MiddleOutIterator& other) const {
                return owner == other.owner && current_index == other.current_index;
            }

            /**
             * @brief Inequality comparison operator
             * @param other The iterator to compare with
             * @return True if iterators are not equal
             */
            bool operator!=(const MiddleOutIterator& other) const {
                return !(*this == other);
            }
        };

        /**
         * @brief Get an iterator to the beginning of the container in middle-out order
         * @return MiddleOutIterator pointing to the first element in middle-out order (middle element)
         */
        MiddleOutIterator begin_middle_out_order() { return MiddleOutIterator(elements, 0, this); }
        
        /**
         * @brief Get an iterator to the end of the container in middle-out order
         * @return MiddleOutIterator pointing past the last element
         */
        MiddleOutIterator end_middle_out_order() { return MiddleOutIterator(elements, elements.size(), this); }

    };    
}

#endif
