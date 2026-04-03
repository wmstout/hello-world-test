"""Greeter module providing localized greeting messages."""


SUPPORTED_LANGUAGES = ("en", "es", "fr", "de")


class Greeter:
    """Produces greeting strings for a given language."""

    def __init__(self, language: str = "en") -> None:
        self.language = language if language in SUPPORTED_LANGUAGES else "en"

    def greet(self, name: str) -> str:
        """Return a greeting for *name* in the configured language."""
        greetings = {
            "es": f"¡Hola, {name}!",
            "fr": f"Bonjour, {name}!",
            "de": f"Hallo, {name}!",
        }
        return greetings.get(self.language, f"Hello, {name}!")
