mod greeter;

use std::env;

use greeter::Greeter;

/// Simple Hello World application demonstrating a multi-module Rust project.
///
/// Usage: hello_world [language] [name]
///   language: en (default), es, fr, de
///   name: World (default)
fn main() {
    let args: Vec<String> = env::args().collect();
    let language = args.get(1).map(String::as_str).unwrap_or("en");
    let name     = args.get(2).map(String::as_str).unwrap_or("World");

    let greeter = Greeter::new(language);
    println!("{}", greeter.greet(name));
    println!("Language: {}", greeter.language());
}
