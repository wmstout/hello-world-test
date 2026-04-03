#pragma once

#include <string>

/**
 * Greeter provides localized greeting messages.
 */
class Greeter {
public:
    explicit Greeter(const std::string& language = "en");

    std::string greet(const std::string& name) const;
    std::string getLanguage() const;

private:
    std::string language_;
};
