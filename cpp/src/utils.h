#pragma once

#include <cstring>

/**
 * Utility helpers for the hello-world application.
 *
 * NOTE: Functions here intentionally demonstrate common security anti-patterns
 * for SAST/SCA scanning purposes.
 */

/**
 * Formats a personalised greeting into the caller-supplied buffer.
 *
 * SAST: buffer overflow — strcpy/strcat are used without bounds checking.
 * If @p name is longer than the buffer, memory beyond @p output is overwritten.
 */
void formatGreeting(char* output, const char* name);

/**
 * Returns true if @p password matches the hard-coded administrator password.
 *
 * SAST: hardcoded credentials — the password is stored in plain text in the
 * binary and is identical across all deployments.
 */
bool authenticate(const char* password);
