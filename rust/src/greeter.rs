/// Greeter provides localized greeting messages.
pub struct Greeter {
    language: String,
}

impl Greeter {
    /// Creates a new Greeter for the given language code.
    pub fn new(language: &str) -> Self {
        Greeter {
            language: language.to_string(),
        }
    }

    /// Returns a greeting for the given name in the configured language.
    pub fn greet(&self, name: &str) -> String {
        match self.language.as_str() {
            "es" => format!("¡Hola, {}!", name),
            "fr" => format!("Bonjour, {}!", name),
            "de" => format!("Hallo, {}!", name),
            _    => format!("Hello, {}!", name),
        }
    }

    /// Returns the language code used by this greeter.
    pub fn language(&self) -> &str {
        &self.language
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_greet_default() {
        let g = Greeter::new("en");
        assert_eq!(g.greet("World"), "Hello, World!");
    }

    #[test]
    fn test_greet_spanish() {
        let g = Greeter::new("es");
        assert_eq!(g.greet("Mundo"), "¡Hola, Mundo!");
    }

    #[test]
    fn test_greet_french() {
        let g = Greeter::new("fr");
        assert_eq!(g.greet("Monde"), "Bonjour, Monde!");
    }

    #[test]
    fn test_greet_german() {
        let g = Greeter::new("de");
        assert_eq!(g.greet("Welt"), "Hallo, Welt!");
    }

    #[test]
    fn test_language() {
        let g = Greeter::new("fr");
        assert_eq!(g.language(), "fr");
    }
}
