# C++ Reflection Demo

This project demonstrates different approaches to reflection in C++ using:
- Boost.PFR (Precise Field Reflection) library
- Macro-based reflection techniques

## Prerequisites

- C++ compiler with C++20 support
- CMake 3.25 or higher
- Boost library

## Building the Project

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## Examples

### Using Boost.PFR

The [reflection_boost_pfr.cpp](reflection_boost_pfr.cpp) example shows how to use Boost.PFR for struct reflection:

```cpp
struct Person {
    int age;
    std::string name;
    double salary;
};

// Print all fields and their values
boost::pfr::for_each_field(person, [](const auto& field, std::size_t index) {
    std::cout << "Field " << index << ": " << field << "\n";
});

// Print fields with their names
boost::pfr::for_each_field_with_name(person, [](auto fieldname, auto value) {
    std::cout << fieldname << ": " << value << "\n";
});
```

### Using Macro-based Reflection

The [reflection_macro.cpp](reflection_macro.cpp) demonstrates an alternative approach using macro-based reflection techniques.

## Building and Running

After building, you can run the examples:

```sh
./build/reflection_demo
```

## License

This project is open source and available under the MIT License.