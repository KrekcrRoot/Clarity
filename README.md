
# Clarity

Static library for writing c++ console programs


## Usage/Examples

**Commands**
is user input that start from prefix "/" or another

Initialization of clarity library
```cpp
#include <Clarity/Console.h>

using namespace clarity;

int main() {

    Console console{};
    console.init();

    return 0;
}
```

To create command you can use Executor class and push it into Console

```cpp
#include <Clarity/Console.h>
#include <Clarity/Executor.h>

using namespace clarity;

int main() {

    Console console{};

    auto hello = Executor::make("hello", [](){
        std::cout << "Hello, World!" << std::endl;
    });

    console.push(hello);

    console.init();

    return 0;
}

```

After that command "/hello" will be available

```
>> /hello
Hello, World!
```

**Interrupts** is user input that start from any character, they don't need to prefix

just change function to "pushInterrupt"
```cpp 
console.pushInterrupt(hello);
```
The result:
```
>> hello
Hello, World!
```

Another way to declare commands into Console.\
You don't need to push it into Console.

```cpp
console.make("hello", [](){
    std::cout << "Hello, World!" << std::endl;
}, CommandType::Default);

console.make("test", [](){
    std::cout << "Interrupt test" << std::endl;
}, CommandType::Interrupt);
```

**Example of getting arguments from user input**
```cpp
auto calc = Executor::make("calc", [](const Command& command) {

    auto arguments = command.getArguments();

    if(arguments.size() < 2) {
        std::cerr << "Wrong number of arguments\n";
        return;
    }

    int res = 0;
    for (const auto &el: arguments) {
        res += std::stoi(el);
    }

    std::cout << res << "\n";

});
```

```
>> /calc 12
Wrong number of arguments

>> /calc 75 25
100
```

## Installation

CMakeLists.txt
```CMake
cmake_minimum_required(VERSION 3.28)
project(example)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib/clarity/include)
add_subdirectory(lib/clarity)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} clarity)
```
## Authors

- [KrekcrRoot](https://github.com/KrekcrRoot)

