"""Tests for the Greeter class."""

import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from src.greeter import Greeter


def test_greet_default():
    g = Greeter()
    assert g.greet("World") == "Hello, World!"


def test_greet_english():
    g = Greeter("en")
    assert g.greet("World") == "Hello, World!"


def test_greet_spanish():
    g = Greeter("es")
    assert g.greet("Mundo") == "¡Hola, Mundo!"


def test_greet_french():
    g = Greeter("fr")
    assert g.greet("Monde") == "Bonjour, Monde!"


def test_greet_german():
    g = Greeter("de")
    assert g.greet("Welt") == "Hallo, Welt!"


def test_unknown_language_falls_back_to_english():
    g = Greeter("jp")
    assert g.greet("World") == "Hello, World!"


def test_language_attribute():
    g = Greeter("fr")
    assert g.language == "fr"
