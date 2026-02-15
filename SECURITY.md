# Security Policy

## 1. Purpose

The purpose of this document is to define the security standards, expectations, and practices followed in this repository.  
This policy establishes minimum requirements for secure coding, vulnerability prevention, and responsible disclosure.

This repository is maintained primarily for educational and development use. It is not intended for direct production deployment without additional security validation and review.

---

## 2. Scope

This policy applies to:

- All source code in the repository
- Build configurations and scripts
- Documentation containing executable or sample code
- Future integrations such as CI/CD pipelines, testing frameworks, or tooling

---

## 3. Security Principles

Development within this repository follows these core security principles:

### 3.1 Memory Safety
- All dynamic memory allocations must be validated before use.
- Memory must be released using appropriate deallocation functions.
- Double free, use-after-free, and memory leak conditions must be prevented.
- NULL pointer checks must be performed before dereferencing.

### 3.2 Input and Buffer Safety
- Unsafe input functions must not be used.
- All external or user-provided input must be treated as untrusted.
- Input length must be validated before storage or processing.
- Buffer boundaries must be strictly enforced.

### 3.3 Pointer Safety
- Pointer arithmetic must remain within allocated memory boundaries.
- Double pointer and function pointer usage must be validated and documented.
- Uninitialized pointer usage is strictly prohibited.

---

## 4. Prohibited Functions and Patterns

The following are explicitly disallowed:

- `gets()`
- Unbounded `scanf("%s")`
- Writing beyond allocated buffer boundaries
- Dereferencing unchecked pointers
- Ignoring compiler warnings

Preferred safer alternatives include:

- `fgets()`
- Length-restricted input parsing
- Explicit bounds validation

---

## 5. Compiler Security Requirements

All code must compile without warnings under strict compiler settings.

Minimum required flags:

```bash
gcc -Wall -Wextra -Werror filename.c
