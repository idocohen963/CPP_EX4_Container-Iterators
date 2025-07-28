# MyContainer - Dynamic Container Implementation with Advanced Iterators

## 📋 Project Summary

This project implements a dynamic container for comparable types, with support for various iterators that enable scanning in different and creative ways. The container is based on templates and supports all comparable data types.

## 🏗️ Project Structure

```
├── MyContainer.hpp    # Header file with class and iterator implementation
├── Demo.cpp          # Demonstration file of container functionality
├── Test.cpp          # Comprehensive unit tests
├── Makefile          # Build file for compilation and execution
├── doctest.h         # Testing library
└── README.md         # Project documentation
```

## 🚀 Main Features

### The `MyContainer<T>` Class

- **Generic Template**: Supports any comparable type (int, double, string, etc.)
- **Automatic Memory Management**: Using RAII and std::vector
- **Basic Operations**:
  - `add(element)` - Add an element
  - `remove(element)` - Remove all instances of an element
  - `size()` - Return number of elements
  - `operator<<` - Print in format `[elem1, elem2, ...]`

### Special Iterators

#### 1. **OrderIterator** 
Scan in regular insertion order
```cpp
[7,15,6,1,2] → 7,15,6,1,2
```

#### 2. **ReverseOrderIterator**
Scan in reverse insertion order
```cpp
[7,15,6,1,2] → 2,1,6,15,7
```

#### 3. **AscendingIterator**
Scan in ascending order (sorted)
```cpp
[7,15,6,1,2] → 1,2,6,7,15
```

#### 4. **DescendingOrder**
Scan in descending order
```cpp
[7,15,6,1,2] → 15,7,6,2,1
```

#### 5. **SideCrossIterator**
Scan from edges inward - alternating small/large
```cpp
[7,15,6,1,2] → 1,15,2,7,6
```

#### 6. **MiddleOutIterator**
Scan from center outward - from middle then alternating left/right
```cpp
[7,15,6,1,2] → 6,15,1,7,2
```

## 💻 Usage Example

```cpp
#include "MyContainer.hpp"
using namespace ex4;

int main() {
    MyContainer<int> container;
    
    // Add elements
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    std::cout << "Container: " << container << std::endl;
    
    // Ascending scan
    std::cout << "Ascending: ";
    for (auto it = container.begin_ascending_order(); 
         it != container.end_ascending_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Remove element
    container.remove(15);
    std::cout << "After removal: " << container << std::endl;
    
    return 0;
}
```

## 🔧 Compilation and Execution

### Build Demo
```bash
make Main
```

### Run Unit Tests
```bash
make test
```

### Check Memory Leaks
```bash
make valgrind
```

### Clean Temporary Files
```bash
make clean
```

## 🧪 Unit Tests

The project includes comprehensive tests covering:
- **Basic Functionality**: Addition, removal, size
- **Error Handling**: Removing non-existent element, accessing beyond bounds
- **Iterators**: All different scan types
- **Different Types**: int, double, string
- **Edge Cases**: Empty container, container with single element

## 🔍 Technical Details

### Solution Design
- **RAII**: Automatic memory management without leaks
- **Exception Safety**: Throwing exceptions in error cases
- **Iterator Pattern**: Standard C++ iterator implementation
- **Template Programming**: Generic support for any type

### Special Algorithms
- **SideCross**: Sort + scan from edges with O(n) logic
- **MiddleOut**: Center calculation + bi-directional expansion
- **Memory Efficiency**: Vector copying only when creating iterator

### Performance
- **Addition**: O(1) amortized
- **Removal**: O(n) - removes all instances
- **Sorted Iterators**: O(n log n) creation, O(1) scanning
- **Simple Iterators**: O(n) creation, O(1) scanning

---
**Author**: [idocohen963@gmail.com]