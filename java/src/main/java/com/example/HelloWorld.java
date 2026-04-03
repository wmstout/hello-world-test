package com.example;

/**
 * Simple Hello World application demonstrating a multi-class Java project.
 *
 * <p>Usage: java -jar hello-world.jar [language] [name]
 *   language: en (default), es, fr, de
 *   name: World (default)
 */
public class HelloWorld {

    public static void main(String[] args) {
        String language = args.length > 0 ? args[0] : "en";
        String name = args.length > 1 ? args[1] : "World";

        Greeter greeter = new Greeter(language);
        System.out.println(greeter.greet(name));
        System.out.printf("Language: %s%n", greeter.getLanguage());
    }
}
