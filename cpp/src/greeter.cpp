#include "greeter.h"

Greeter::Greeter(const std::string& language) : language_(language) {}

std::string Greeter::greet(const std::string& name) const {
    if (language_ == "es") {
        return "¡Hola, " + name + "!";
    } else if (language_ == "fr") {
        return "Bonjour, " + name + "!";
    } else if (language_ == "de") {
        return "Hallo, " + name + "!";
    } else {
        return "Hello, " + name + "!";
    }
}

std::string Greeter::getLanguage() const {
    return language_;
}
