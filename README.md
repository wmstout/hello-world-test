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

## Security Testing (SAST / SCA)

This repo is intentionally configured with known-vulnerable dependency versions and insecure code patterns so that SAST and SCA scanners have real findings to report.

### SCA — Vulnerable Dependencies

| Language | Package | Version | Vulnerability |
|----------|---------|---------|---------------|
| Java | `log4j-core` | 2.14.1 | CVE-2021-44228 — Log4Shell RCE |
| Java | `commons-collections` | 3.2.1 | CVE-2015-4852 — Insecure Deserialization |
| Python | `PyYAML` | 5.3.1 | CVE-2020-14343 — Improper Input Validation |
| Python | `requests` | 2.18.0 | CVE-2018-18074 — Insufficiently Protected Credentials |
| Python | `Pillow` | 8.0.0 | Multiple CVEs — RCE / path traversal |
| Python | `urllib3` | 1.24.1 | CVE-2019-11324 — Improper Certificate Validation |
| Rust | `smallvec` | 0.6.12 | RUSTSEC-2019-0009 — Buffer Overflow / Use-of-Uninitialized-Resource |

### SAST — Insecure Code Patterns

| Language | File | Pattern |
|----------|------|---------|
| Java | `DatabaseHelper.java` | SQL injection (string concatenation), OS command injection, hardcoded credentials |
| Python | `src/utils.py` | `eval()` on user input, `subprocess(shell=True)`, `pickle.loads()`, unsafe `yaml.load()`, hardcoded API key |
| C++ | `src/utils.cpp` | `strcpy`/`strcat` (buffer overflow), hardcoded password |
| Rust | `src/utils.rs` | `unsafe` block with raw pointer dereference and `from_utf8_unchecked` |

---

## Supported Languages

| Code | Language |
|------|----------|
| `en` | English (default) |
| `es` | Spanish |
| `fr` | French |
| `de` | German |
