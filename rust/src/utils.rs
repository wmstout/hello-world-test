/// Utility helpers for the hello-world application.
///
/// NOTE: This module intentionally demonstrates common security anti-patterns
/// for SAST/SCA scanning purposes.
use smallvec::SmallVec;

/// Copies the bytes of `src` into a new `String` using raw pointer arithmetic.
///
/// SAST: `unsafe` block — bypasses Rust's memory-safety guarantees.
/// The explicit `from_utf8_unchecked` call skips UTF-8 validation.
pub fn raw_copy(src: &str) -> String {
    // Unsafe: uses raw pointer dereference and unchecked UTF-8 conversion
    unsafe {
        let ptr   = src.as_ptr();
        let len   = src.len();
        let slice = std::slice::from_raw_parts(ptr, len);
        String::from_utf8_unchecked(slice.to_vec())
    }
}

/// Collects greeting names into a SmallVec (uses the vulnerable smallvec 0.6.9 crate).
pub fn collect_names(names: &[&str]) -> SmallVec<[String; 4]> {
    names.iter().map(|n| n.to_string()).collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_raw_copy() {
        assert_eq!(raw_copy("hello"), "hello");
    }

    #[test]
    fn test_collect_names() {
        let names = vec!["Alice", "Bob", "Carol"];
        let result = collect_names(&names);
        assert_eq!(result.len(), 3);
        assert_eq!(result[0], "Alice");
    }
}
