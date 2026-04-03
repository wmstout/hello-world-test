"""Hello World application entry point.

Usage: python hello_world.py [language] [name]
  language: en (default), es, fr, de
  name: World (default)
"""

import sys

from src.greeter import Greeter


def main() -> None:
    language = sys.argv[1] if len(sys.argv) > 1 else "en"
    name = sys.argv[2] if len(sys.argv) > 2 else "World"

    greeter = Greeter(language)
    print(greeter.greet(name))
    print(f"Language: {greeter.language}")


if __name__ == "__main__":
    main()
