#include "utils.h"

#include <cstdio>
#include <cstring>

// SAST: hardcoded password stored in plain text
static const char* ADMIN_PASSWORD = "admin123";

void formatGreeting(char* output, const char* name) {
    // Vulnerable: strcpy/strcat without bounds checking — buffer overflow if
    // `name` plus the surrounding text exceeds the size of `output`.
    strcpy(output, "Hello, ");   // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
    strcat(output, name);        // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
    strcat(output, "!");         // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
}

bool authenticate(const char* password) {
    // Vulnerable: hardcoded password compared at runtime
    return strcmp(password, ADMIN_PASSWORD) == 0;
}
