package com.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class GreeterTest {

    @Test
    void greetDefaultLanguage() {
        Greeter greeter = new Greeter("en");
        assertEquals("Hello, World!", greeter.greet("World"));
    }

    @Test
    void greetSpanish() {
        Greeter greeter = new Greeter("es");
        assertEquals("¡Hola, Mundo!", greeter.greet("Mundo"));
    }

    @Test
    void greetFrench() {
        Greeter greeter = new Greeter("fr");
        assertEquals("Bonjour, Monde!", greeter.greet("Monde"));
    }

    @Test
    void greetGerman() {
        Greeter greeter = new Greeter("de");
        assertEquals("Hallo, Welt!", greeter.greet("Welt"));
    }

    @Test
    void unknownLanguageFallsBackToEnglish() {
        Greeter greeter = new Greeter("jp");
        assertEquals("Hello, World!", greeter.greet("World"));
    }

    @Test
    void getLanguage() {
        Greeter greeter = new Greeter("fr");
        assertEquals("fr", greeter.getLanguage());
    }
}
