# C++ Programming Guide

This guide consolidates several key concepts in C++, from vector manipulation and loop control to error handling and data types.

## 1\. Understanding Expressions: Value vs. Side Effect

Every operation, function, and expression in C++ has two potential outcomes:

1.  **A return value:** This is the result of the computation, which can be stored in a variable or passed to another function.
2.  **A side effect:** This refers to any change in the state of the computer after the expression is evaluated.

For example, the assignment operator (`=`) has a **side effect** of changing a variable's value. Its **return value** is the value that was assigned.

Standard arithmetic operations like `+`, `-`, `*`, `/`, and `%` have **no side effects**. They only compute and return a result without changing any existing state.

## 2\. Working with `std::vector`

The `std::vector` is a dynamic array that is a fundamental part of the C++ Standard Library.

### Vector Initialization

There are several ways to initialize a `std::vector`, and the syntax can lead to different results.

```c++
#include <iostream>
#include <vector>

// A vector of five elements, each initialized to 0.
std::vector<int> numbers1(5);

// A vector with a single element with the value 5.
std::vector<int> numbers2{5};

// A vector of five elements, each with the value 10.
std::vector<int> numbers3(5, 10);

// A vector of two elements with the values 5 and 10.
std::vector<int> numbers4{5, 10};

// Accessing an element
std::cout << numbers3[2] << std::endl; // Prints 10
```

### Iterating with a Range-Based `for` Loop

When you need to access elements in a container without needing their index, a range-based `for` loop is a clean and expressive option.

```c++
#include <iostream>
#include <vector>

std::vector<int> magic_numbers{4, 8, 15, 16, 23, 42};

// To the left of the colon: the type and name of the temporary variable.
// To the right of the colon: the name of the container to iterate over.
for (int item : magic_numbers) {
    std::cout << item << std::endl;
}
```

This loop is more readable as it clearly states the intent: "for each item in `magic_numbers`". While you lose direct access to the index, the code is much shorter and less error-prone.

### Modifying Elements in a Loop

To modify the elements of a vector within a range-based `for` loop, you must use a **reference** (`&`).

```c++
#include <vector>

std::vector<int> magic_numbers{4, 8, 15, 16, 23, 42};

// Use an ampersand (&) to modify the vector's values.
for (int& item : magic_numbers) {
    // Divide even elements by two.
    if (item % 2 == 0) {
        item /= 2;
    }
}

// The vector now contains: {2, 4, 15, 8, 23, 21}
```

By declaring `int& item`, `item` becomes a reference to the actual element in the vector. Any changes made to `item` directly affect the vector itself.

## 3\. Mastering Loops

The standard `for` loop in C++ is incredibly flexible.

### Advanced `for` Loop Techniques

* **Multiple Counters:** You can initialize and update multiple counters in a single loop.

  ```c++
  #include <iostream>

  // This loop has two counters: i and j.
  for (int i = 5, j = 1; i + j < 20; i++, j *= 2) {
      std::cout << "i + j = " << (i + j) << std::endl;
  }
  ```

* **Infinite Loops:** A `for` loop can be made infinite by omitting the condition or providing a condition that is always true.

  ```c++
  #include <iostream>

  // This loop has no counters, and its condition is always true.
  // It will endlessly print "Dig!".
  int a = 1;
  for (; a > 0; ) {
      std::cout << "Dig!" << std::endl;
  }

  // All four of the following loops are functionally identical infinite loops:
  for (; 1; ) {
      std::cout << "Dig! Dig!" << std::endl;
  }

  for (; true; ) {
      std::cout << "Dig! Dig! Dig!" << std::endl;
  }

  // If the condition is omitted, the compiler assumes it's true.
  for (;;) {
      std::cout << "Dig! Dig! Dig! Dig!" << std::endl;
  }
  ```

* **The Comma Operator:** The comma operator allows you to evaluate multiple expressions where only one is expected.

  ```c++
  #include <iostream>

  // This surprising construct works!
  // It prints numbers from 0 to 4.
  for (int i = 0; i < 5; std::cout << i << std::endl, i++) {
      // The body of the loop is empty.
  }
  ```

  Here, the comma operator ensures that `std::cout << i << std::endl` is executed before `i++` in each iteration's post-expression.

### Modern C++ Loops with Ranges

Modern C++ (C++20 and later) provides a more convenient way to loop over a sequence of numbers using `std::views::iota`.

```c++
#include <iostream>
#include <ranges>

// Prints numbers from 1 to 100
for (int i : std::views::iota(1, 101)) {
    std::cout << i << std::endl;
}
```

`iota` takes a starting number (inclusive) and an ending number (exclusive). This requires the `<ranges>` header and a modern compiler.

### A Warning About `size_t`

Be careful when counting down in a loop using an unsigned type like `size_t`. The condition `i >= 0` will always be true for an unsigned type.

When an unsigned variable `i` is 0 and you decrement it (`i--`), it doesn't become -1. Instead, it "wraps around" to the largest possible value for that unsigned type, leading to an infinite loop.

## 4\. The `auto` Keyword

The `auto` keyword instructs the compiler to automatically deduce the type of a variable from its initializer.

```c++
// The compiler automatically deduces the type as int
// from the assigned value.
auto i = 100;

// This will not work, as the type cannot be deduced.
// auto j; // Compilation Error!
```

## 5\. Handling Input Streams and Errors

Properly handling user input is crucial for robust programs.

### Checking for Input Failure

You can check if a read operation from a stream like `std::cin` was successful. The `fail()` method returns `true` if the last read operation failed.

It is common practice to use `std::cerr` for error messages, which is a separate stream specifically for errors. This helps separate normal program output from error diagnostics.

```c++
#include <iostream>

int n;
std::cin >> n;

if (!std::cin.fail()) {
    std::cout << "You entered the number " << n << std::endl;
} else {
    // Use std::cerr for error messages.
    std::cerr << "Error while reading a number." << std::endl;
}
```

### Simplifying Error Checks

The stream object itself can be evaluated as a boolean, providing a more concise way to check for errors.

```c++
#include <iostream>

int n;
std::cin >> n;

if (std::cin) { // This is equivalent to !std::cin.fail()
    std::cout << "You entered the number " << n << std::endl;
} else {
    std::cerr << "Error while reading a number." << std::endl;
}
```

Even more compactly, you can perform the read operation directly inside the `if` condition, since the `>>` operator returns the stream itself.

```c++
#include <iostream>

int n;

if (std::cin >> n) {
    std::cout << "You entered the number " << n << std::endl;
} else {
    std::cerr << "Error while reading a number." << std::endl;
}
```

### Resetting the Stream State

After a failed read, the stream enters an error state and will not accept further input until the state is cleared. Use the `clear()` method to reset it.

```c++
#include <iostream>
#include <string>

int n;

if (std::cin >> n) {
    std::cout << "You entered the number " << n << std::endl;
} else {
    std::cerr << "That was not a number." << std::endl;

    // Must call clear() to resume reading from the stream.
    std::cin.clear();

    std::string word;
    if (std::cin >> word) {
        std::cerr << "You entered '" << word << "' instead." << std::endl;
    } else {
        std::cerr << "Failed to read anything from the stream." << std::endl;
    }
}
```

## 6\. Control Flow and Data Types

### The `switch` Statement

The condition for a `switch` statement must be an integer-like type (e.g., `int`, `uint64_t`, `char`, or an `enum`). Using other types like strings or floating-point numbers will result in a compilation error.

### Enumerations (`enum class`)

An `enum class` provides a type-safe way to represent a set of named constants. Internally, these are represented by integers. You can explicitly convert between an enum and an integer type using `static_cast`.

```c++
#include <vector>

enum class Month {
    Jan, Feb, Mar, Apr, May, Jun,
    Jul, Aug, Sep, Oct, Nov, Dec
};

int main() {
    // Convert an integer to a Month
    int n = 4;
    Month m = static_cast<Month>(n); // m is now Month::May

    bool isMay = (m == Month::May); // isMay is true
    // Note: May is the 4th month because numbering starts from 0.

    // Convert a Month to an integer
    int k = static_cast<int>(Month::Jan); // k is 0

    return 0;
}
```

## 7\. Full Code Example: Bubble Sort

This program demonstrates reading input, storing it in a vector, sorting the vector with a function, and printing the middle element.

```c++
#include <iostream>
#include <vector>

// Function prototype
std::vector<int> bubble_sort(std::vector<int> v);

int main() {
    int n, m, k;
    // Read three numbers from the user
    std::cin >> n >> m >> k;
    // Initialize a vector with the input
    const std::vector digits = {n, m, k};
    // Call the sorting function
    const std::vector<int> sorted_vector = bubble_sort(digits);
    // Calculate and print the middle element
    const int middle_index = sorted_vector.size() / 2;
    std::cout << sorted_vector.at(middle_index) << std::endl;

    return 0;
}

/**
 * @brief Sorts a vector of integers using the bubble sort algorithm.
 * @param v The vector to be sorted.
 * @return A new vector containing the sorted elements.
 */
std::vector<int> bubble_sort(std::vector<int> v) {
    // Note: The vector is passed by value, so we are working on a copy.
    for (int step = 0; step < v.size(); step++) {
        for (int pos = 0; pos < v.size() - step - 1; pos++) {
            // Swap adjacent elements if they are in the wrong order
            if (v[pos] > v.at(pos + 1)) {
                int tmp = v[pos];
                v[pos] = v[pos + 1];
                v[pos + 1] = tmp;
            }
        }
    }
    return v;
}
```


Функция `std::getline` использует другой способ передачи аргумента — передачу по ссылке. Чтобы использовать его, нужно между типом параметра и его именем поставить знак `&`. В этом случае копия переданной переменной создаваться не будет, и изменение аргумента скажется на значении переменной из вызывающей функции.
Покажем пользу от передачи по ссылке на примере функции `RemoveSpaces`. Она получает ссылку на строку, из которой удаляет все пробельные символы.

```c++
#include <string>

// Удаляет все пробелы из строки. Параметр str принимается по ссылке.
void RemoveSpaces(std::string& str) {
    size_t dst_index = 0;
    // Копируем только непробельные символы.
    for (size_t src_index = 0; src_index < str.length(); ++src_index) {
        char ch = str[src_index];
        if (ch != ' ') { // Копируем символ, только если это не пробел.
            str[dst_index] = ch;
            ++dst_index;
        }
    }
    // Теперь dst_index хранит позицию в строке, следующую
    // за последним скопированным символом.
    str.resize(dst_index); // Отрезаем всё лишнее.
}

using namespace std::literals;
int main() {
    std::string text = "Hello! How are you?"s;
    RemoveSpaces(text);
    // Теперь text хранит строку "Hello!Howareyou?"
}
```
Аргумент, переданный по ссылке, можно использовать, чтобы вернуть из функции дополнительное значение, помимо основного. Аргумент, который функция принимает по ссылке и использует только для записи, называется выходным аргументом (*output argument*).

У передачи параметров по ссылке есть ряд ограничений:
- По ссылке можно передать только реально существующий объект, такой как переменная или элемент вектора. Временный объект, который образуется в ходе вычислений выражения, передать по ссылке нельзя.
- Нельзя передать константную переменную. Значение константной переменной изменять нельзя, поэтому попытка передать константу в функцию, которая попытается её изменить, завершится ошибкой.