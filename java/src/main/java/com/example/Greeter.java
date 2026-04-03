package com.example;

/**
 * Greeter provides localized greeting messages.
 */
public class Greeter {
    private final String language;

    public Greeter(String language) {
        this.language = language;
    }

    public String greet(String name) {
        switch (language) {
            case "es":
                return "¡Hola, " + name + "!";
            case "fr":
                return "Bonjour, " + name + "!";
            case "de":
                return "Hallo, " + name + "!";
            default:
                return "Hello, " + name + "!";
        }
    }

    public String getLanguage() {
        return language;
    }
}
