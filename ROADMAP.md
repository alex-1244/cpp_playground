# C++ Roadmap — from C# to embedded & IoT

*Created 2026-08-27. Learner: Aleksey (10+ years C#/.NET web). Mentor: Claude.*
*Companion file: [PROGRESS.md](PROGRESS.md) — the living tracker, updated every session.*

## The goal

Go from senior C#/.NET developer to a confident C++ developer shipping real embedded/IoT
projects: first a LoRa-linked wireless sensor system for the smart home (built on hardware
you already own), then robotics fundamentals (motor control, PID) as the next horizon.

## How we work — the contract

- **You write every line of code.** Claude never writes solutions — only reviews, hints
  (escalating, gentlest first), explanations with C# contrasts, build configuration, and test data.
- Rhythm per phase: short exercises per topic → one **milestone project** → **mentor review gate**.
- **Gates, not dates.** The calendar below is a sanity check, not a deadline. A phase ends
  when its gate is passed, never because a week ended.
- To get a review: open a Cowork session on this folder and say *"review my code"* /
  *"continue C++ coaching"*. Claude reads this repo, reviews like a PR reviewer, and can
  compile and run your code in its Linux sandbox — including under sanitizers MinGW doesn't have.

## Starting point (verified 2026-08-27)

- Toolchain working: CLion + bundled MinGW (**GCC 13.1**) + CMake 4.2 + ninja, `CMAKE_CXX_STANDARD 20`.
  GCC 13 covers C++20 well (including `std::format`); if we ever hit a missing C++23 feature, we upgrade then.
- You already know from C#: OOP, generics, LINQ-thinking, async, exceptions, and GC-world memory concepts.
  The roadmap spends your time only on what's *different*.
- Hardware on hand: **2× LILYGO TTGO LoRa32** (ESP32 + SX127x LoRa radio + SSD1306 OLED),
  **1× LuaNode32** (plain ESP32). No purchases needed until Phase 4 (~$15 of sensors).
- Time budget: 3–5 h/week.

---

## Phase 0 — Toolchain & mental model *(mostly done)*

**Goal:** know what actually happens when you press Run — the biggest day-one difference from .NET.

Topics: translation units; preprocessor and `#include` vs `using` + assemblies; the
compile → link pipeline vs Roslyn/MSBuild/JIT; headers vs sources; why C++ builds break
differently (and why linker errors look scary but aren't).

- [x] IDE build & run works
- [ ] Build from a plain terminal with `g++` directly — no IDE (Assignment 1)
- [ ] Provoke and read one *compiler* error and one *linker* error (declare a function, never define it)
- [ ] Warnings on: `-Wall -Wextra` in CMakeLists (Assignment 1)

**Gate:** you can explain `.h` vs `.cpp`, say what the linker does, and read a linker error without fear.

## Phase 1 — Core syntax & the value model *(~6 weeks)*

**Goal:** read and write everyday C++. The one mental shift that matters most:
**C++ defaults to values where C# defaults to references.** Assignment copies. Everything
behaves like a C# `struct` unless you explicitly say otherwise.

Topics (C# anchor in parentheses):

- Fundamental types & fixed-width ints (`int` size is *not* guaranteed like `Int32`), `auto` (`var`),
  brace initialization `{}` and narrowing rules
- References `&` and pointers `*` vs C# `ref` and class references; `nullptr`
- `const` correctness (`readonly`, but everywhere and enforced)
- Functions, overloading, default arguments; the header/source split in practice
- `enum class` (`enum`), `struct` vs `class` (only the default visibility differs!)
- `std::string` — a *value* type (mutable, copied on assignment); `std::string_view`
- `std::vector<T>` (`List<T>`), range-for (`foreach`), basic iterators
- `std::cin`/`std::cout`, reading a file with `std::ifstream`
- Error handling, first pass: exceptions exist, but C++ often prefers other tools — intro only

**Milestone M1 — `templog`:** CLI tool that reads a CSV of timestamped sensor readings
(Claude supplies the data file), then reports per-sensor min/max/mean and flags out-of-range
anomalies. Structs, vectors, strings, functions — no manual memory anywhere.

**Gate:** M1 reviewed. You can predict what copies vs what references. Zero `new`/`delete` used.

Reading: learncpp.com (topics: fundamental data types, constants and strings, operators,
control flow, `std::vector`); *A Tour of C++* ch. 1–3 if you grab the book.

## Phase 2 — Ownership & the object model *(~7 weeks — the heart of C++)*

**Goal:** RAII becomes instinct. This is the thing that replaces the garbage collector in your head.

Topics:

- Constructors/destructors and **RAII** (deterministic `IDisposable`, everywhere, with no `using` ceremony)
- Copy vs **move**, rvalues, `std::move`, and the **rule of zero / three / five**
- **`std::unique_ptr` (your default)**, `shared_ptr`/`weak_ptr` (rarer than you'd think);
  why raw *owning* pointers are banned in modern C++
- Templates vs C# generics (compile-time, monomorphized, duck-typed) + C++20 concepts intro
- Lambdas (delegates/closures), `<algorithm>` and C++20 ranges — your LINQ replacement
- `std::optional` (`Nullable`/nullable refs), `std::variant` (a real discriminated union)
- Operator overloading; inheritance and `virtual` done right — vtables, and **object slicing**
  (where value semantics bites polymorphism; there's no analog in C#)
- Unit testing with **doctest** from the start of this phase; CMake `FetchContent`

Key exercise: build `RaiiBuffer`, your own tiny `unique_ptr`-like owner with the rule of five
by hand — once, to earn the right to never do it again.

**Milestone M2 — `geom`:** header-only Vec2/Vec3/Mat3 template mini-library — operators,
dot/cross, 2D rotations — with a doctest suite. This is robotics math you will reuse.

**Field trip (one weekend, any time after M1):** PlatformIO + the TTGO LoRa32 — blink the
LED and put "Hello" on the OLED. Zero theory. Pure motivation, and it proves the embedded
toolchain early instead of during Phase 4.

**Gate:** M2 reviewed. You can say where every object lives and dies. New classes follow the
rule of zero by default.

Reading: learncpp (classes, move semantics, smart pointers, lambdas); *Effective Modern C++*
items on move semantics and smart pointers.

## Phase 3 — The systems layer *(~6 weeks)*

**Goal:** everything C# hid from you. This phase *is* embedded preparation.

Topics:

- Memory for real: stack/heap/static storage, object lifetime, dangling references, and what
  **undefined behavior** actually means ("the compiler trusts you" has a price)
- Raw arrays, `std::array`, `std::span`, pointer arithmetic, C strings
- **Bits & bytes:** masks, shifts, hex fluency; endianness; alignment and struct packing —
  this is register-manipulation practice
- The four casts: `static_cast`, `reinterpret_cast`, `const_cast`, `dynamic_cast` (vs C# cast/`as`)
- C interop and `extern "C"` — because every embedded SDK API is C
- CMake for real: multiple targets, a library target for your `geom` lib
- Tooling: AddressSanitizer/UBSan (via Claude's sandbox or WSL — MinGW lacks them), clang-tidy in CLion
- `std::chrono`; binary file I/O
- Concurrency intro: `std::thread`, `mutex`, `atomic` (vs `Task`/`lock`) — groundwork for FreeRTOS

**Milestone M3 — `framecodec`:** a binary wire-protocol encoder/decoder you design —
sync byte, node id, message type, payload length, payload, CRC16 — with round-trip doctest
coverage and a little hexdump utility. **This becomes your LoRa protocol in Phase 5.**

**Gate:** M3 reviewed. You can hand-decode a hexdump of your own frames, and UB is no longer a mystery word.

Reading: learncpp (pointers and arrays in depth, bit manipulation); toys: godbolt.org (Compiler Explorer), cppinsights.io.

## Phase 4 — Embedded transition *(~8 weeks)*

**Goal:** same language, different planet — ~520 KB RAM, FreeRTOS instead of Windows, no crash dialogs.

Topics:

- **PlatformIO** with the Arduino framework on ESP32 (ESP-IDF peek later); serial monitor;
  CP210x USB driver on Windows if the board doesn't enumerate
- GPIO, debounced buttons, PWM (LEDC), ADC quirks
- The embedded C++ dialect: why heap, exceptions and RTTI get restricted; static allocation;
  `volatile`; interrupts (ISR + `IRAM_ATTR`)
- UART logging; **I2C** (the TTGO's onboard OLED, then a BME280 sensor); **SPI** (the LoRa radio speaks it)
- Non-blocking patterns and simple state machines instead of `delay()`
- **FreeRTOS** on ESP32: tasks, queues, notifications (vs C# `Task` — preemptive real-time, not a thread pool)
- Wi-Fi + **MQTT** to a local Mosquitto broker; ArduinoJson
- Deep sleep and power basics

**Milestone M4 — sensor node:** one ESP32 reads a BME280 and publishes MQTT to
Mosquitto/Home Assistant every 30 s, with reconnect logic and a status-LED state machine.

**Gate:** the node survives a router reboot and a broker restart, unattended, for 24 hours.

Shopping (~$15): BME280 breakout, breadboard, jumper wires (F-F and M-F), a known-good *data*
USB cable. Optional: 18650 battery for the TTGO.

Reading: Random Nerd Tutorials (ESP32), the free official FreeRTOS book, PlatformIO docs.

## Phase 5 — Capstone: the LoRa sensor link *(~8 weeks)*

**Goal:** a real IoT system, end to end, designed by you — on the boards you already own.

The build:

- **Node A** (TTGO #1, battery): wake → read sensor → encode a `framecodec` frame → LoRa TX → deep sleep
- **Node B** (TTGO #2, powered): LoRa RX → validate CRC → bridge to Wi-Fi/MQTT → Home Assistant;
  OLED shows last packet, RSSI, and packet-loss %
- RadioLib driving the SX127x; *your* Phase-3 protocol on top

First checklist item: confirm both boards' LoRa frequency matches (sticker/marking: 433 vs
868 vs 915 MHz — in Ukraine the license-free choices are 868 MHz or 433 MHz).

Stretch goals: ACK + retry, payload encryption, OTA firmware updates, LuaNode32 as a third
node — a tiny mesh.

**Gate:** a week of unattended telemetry from another room showing up on a dashboard, with a
packet-loss number you can explain.

## Beyond the roadmap — the horizon

Robotics branch: PID control of a DC motor with an encoder (~$20 of parts; the ESP32 is enough),
then a small differential-drive robot. STM32 as a second, industry-grade platform. ROS 2 in C++
on a Raspberry Pi when a bigger robot calls. Language depth: C++23, coroutines, CppCon talks.

## Standing resources

- **cppreference.com** — *the* reference (prefer it over cplusplus.com)
- **learncpp.com** — main structured course companion (chapter numbers drift; follow topics)
- **godbolt.org** — see the assembly; **cppinsights.io** — see what the compiler really generates
- **C++ Core Guidelines** — the "how modern C++ is written" rulebook
- **hackingcpp.com** — excellent cheat sheets
- Books: *A Tour of C++* (3rd ed., Stroustrup — short, written exactly for experienced devs like you),
  *Effective Modern C++* (Meyers) from Phase 2 on

## Rough calendar (at ~4 h/week — gates rule, not dates)

| Phase | Window |
|---|---|
| 0 — Toolchain | done Aug 2026, wrap-up in Assignment 1 |
| 1 — Core syntax | Sep – mid Oct 2026 |
| 2 — Ownership | mid Oct – early Dec 2026 (field trip ~Nov) |
| 3 — Systems | Dec 2026 – late Jan 2027 (holiday buffer built in) |
| 4 — Embedded | Feb – late Mar 2027 |
| 5 — LoRa capstone | Apr – Jun 2027 |
