# CLogger - Zero-Std C Logger

A minimal, low-level logging utility written in **pure C** with **no standard library dependencies**. Designed for bare-metal environments, OS kernels, or projects that need complete control over I/O.

---

## Features

- **No libc / stdlib dependencies** – works in environments where the standard C library is unavailable or undesirable.
- **Custom low-level printing** – logs are output using your own low-level print mechanism (e.g., direct `syscall`, `write`, `putchar`, etc.).
- **Three log levels**:
  - `LOG_LEVEL_INFO` (0) – shown in **green**
  - `LOG_LEVEL_WARNING` (1) – shown in **yellow**
  - `LOG_LEVEL_ERROR` (2) – shown in **red**
- **Lightweight and portable** – perfect for embedded or kernel-level projects.
- **MIT Licensed** – free to use and modify.

---

## Usage

```c
log("System initialized.", LOG_LEVEL_INFO);
log("Could not find config file, using defaults.", LOG_LEVEL_WARNING);
log("Fatal error: device not responding.", LOG_LEVEL_ERROR);
