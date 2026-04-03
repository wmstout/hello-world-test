# hello-world-test

A polyglot Hello World repository used to test mirror/sync workflows.  
Each application supports multiple greeting languages (`en`, `es`, `fr`, `de`) and accepts optional CLI arguments so that behavioural changes can be verified end-to-end.

---

## Structure

```
.
├── java/       # Maven project (Java 11)
├── cpp/        # CMake project (C++17)
├── rust/       # Cargo project (Rust edition 2021)
└── python/     # Plain Python 3 package
```

---

## Build & Run

### Java (requires JDK 11+ and Maven)

```bash
cd java
mvn package -q
java -jar target/hello-world-1.0.0.jar          # Hello, World!
java -jar target/hello-world-1.0.0.jar es Mundo  # ¡Hola, Mundo!
mvn test
```

### C++ (requires CMake 3.15+ and a C++17 compiler)

```bash
cd cpp
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/hello_world          # Hello, World!
./build/hello_world fr Monde # Bonjour, Monde!
```

### Rust (requires Cargo / Rust 2021 edition)

```bash
cd rust
cargo run                    # Hello, World!
cargo run -- de Welt         # Hallo, Welt!
cargo test
```

### Python (requires Python 3.8+)

```bash
cd python
python hello_world.py              # Hello, World!
python hello_world.py es Mundo     # ¡Hola, Mundo!
python -m pytest tests/
```

---

## Supported Languages

| Code | Language |
|------|----------|
| `en` | English (default) |
| `es` | Spanish |
| `fr` | French |
| `de` | German |
