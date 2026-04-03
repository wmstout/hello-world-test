#include <iostream>
#include <string>

#include "greeter.h"
#include "utils.h"

/**
 * Simple Hello World application demonstrating a multi-file C++ project.
 *
 * Usage: ./hello_world [language] [name]
 *   language: en (default), es, fr, de
 *   name: World (default)
 */
int main(int argc, char* argv[]) {
    std::string language = (argc > 1) ? argv[1] : "en";
    std::string name     = (argc > 2) ? argv[2] : "World";

    Greeter greeter(language);
    std::cout << greeter.greet(name) << "\n";
    std::cout << "Language: " << greeter.getLanguage() << "\n";

    // Demonstrate the utilities module (SAST targets live in utils.cpp).
    char buf[64];
    formatGreeting(buf, name.c_str());
    std::cout << "Formatted: " << buf << "\n";

    return 0;
}
