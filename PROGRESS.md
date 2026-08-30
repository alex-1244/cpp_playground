# Progress tracker — C++ mentorship

*Single source of truth for where we are. Claude updates it every session; tick boxes yourself freely.*
*To resume any time: open a Cowork session on this folder and say "continue C++ coaching".*

> **Now:** Phase 1 · **Assignment 1 issued 2026-08-27** · Next step: do the assignment, then say *"review assignment 1"*.

---

## Assignment 1 — "First contact" *(Phase 0 wrap-up + Phase 1 kickoff, ~3–4 h)*

**Part A — housekeeping (~30 min)**

- [ ] `git init`; add a `.gitignore` ignoring `cmake-build-*/` (keep `.idea/` or not — your call; JetBrains already dropped a sensible `.idea/.gitignore`); first commit
- [ ] From a plain terminal, compile without the IDE: `g++ -std=c++20 main.cpp -o scratch.exe`, run it.
      Point: the compiler is just a program; CLion only orchestrates it.
- [ ] Break the build twice on purpose: (1) a syntax error — read the *compiler* error;
      (2) declare a function `int f();`, call it, never define it — read the *linker* error. Note how different they look.

**Part B — `01_sensor_stats.cpp` (~2 h)**

Create the file and add a **second** `add_executable` target to CMakeLists.txt (first taste of multi-target builds).

Spec:

- [ ] Read a count `N`, then `N` temperature readings (doubles) from `std::cin` into a `std::vector<double>`
- [ ] Print count, min, max, and mean (1 decimal place)
- [ ] Warn about any reading outside **[-40, 85] °C** (a DS18B20's limits), listing each offender's position
- [ ] Rules: `std::vector` + range-for; at least two functions besides `main`; **no** `new`/`delete`, no raw arrays
- [ ] Stretch: drop the `N` prefix and read until end-of-input instead (in a Windows terminal, Ctrl+Z then Enter ends stdin)

**Part C — `02_puzzlers.cpp` (~45 min)**

Third target. For each snippet, write your **prediction as a comment above it** *before* running:

```cpp
int x; std::cout << x << "\n";                    // 1. prediction?
std::string s = "abc" + 1; std::cout << s << "\n";// 2. prediction?
int y = 3.9; std::cout << y << "\n";              // 3. prediction?
int z = 0; if (z = 5) std::cout << "yes " << z;   // 4. prediction?
```

Every one of these compiles. In C#, **none** of them would. Afterwards, write one sentence in a
comment: what does this tell you about the C++ compiler's trust model?

**Part D — warnings (~15 min)**

- [ ] Add `add_compile_options(-Wall -Wextra)` to CMakeLists.txt (config, not solution — allowed), rebuild, and note which puzzlers now warn — and which one *still doesn't*.

Reading alongside: learncpp.com — the intro chapters, *fundamental data types*, and *intro to std::vector*.

**Done =** everything committed → tell Claude *"review assignment 1"*.

---

## Phase gates

### Phase 0 — Toolchain & mental model
- [x] CLion + MinGW GCC 13.1 + CMake 4.2 + ninja working, C++20 set *(2026-08-27)*
- [x] First IDE build & run *(2026-08-27)*
- [ ] Terminal build without IDE *(Assignment 1)*
- [ ] One compiler error + one linker error, provoked and understood *(Assignment 1)*
- [ ] Warnings enabled *(Assignment 1)*
- [ ] **Gate:** can explain .h vs .cpp and what the linker does

### Phase 1 — Core syntax & the value model
- [ ] Assignment 1 reviewed
- [ ] Value semantics: predict copy vs reference correctly in review
- [ ] Strings/vectors/range-for fluent; const habit forming
- [ ] **Milestone M1 `templog`** built and reviewed
- [ ] **Gate passed**

### Phase 2 — Ownership & the object model
- [ ] doctest wired into the build
- [ ] `RaiiBuffer` exercise (rule of five, once, by hand)
- [ ] Smart pointers + move semantics exercises
- [ ] **Milestone M2 `geom`** built and reviewed
- [ ] **Field trip:** TTGO LoRa32 blinks + OLED says hello (PlatformIO proven)
- [ ] **Gate passed**

### Phase 3 — The systems layer
- [ ] Bits/bytes/endianness exercises
- [ ] UB + sanitizer session (Claude's sandbox or WSL)
- [ ] **Milestone M3 `framecodec`** built and reviewed
- [ ] **Gate passed:** can hand-decode own hexdump

### Phase 4 — Embedded transition
- [ ] Shopping done (BME280, breadboard, jumpers, data cable)
- [ ] GPIO/PWM/I2C/SPI ladder on real hardware
- [ ] FreeRTOS tasks + queues exercise
- [ ] **Milestone M4** MQTT sensor node survives 24 h unattended
- [ ] **Gate passed**

### Phase 5 — LoRa capstone
- [ ] Board frequencies confirmed matching (433/868/915 MHz)
- [ ] Node A (battery, deep sleep, LoRa TX)
- [ ] Node B (LoRa RX → MQTT bridge, OLED stats)
- [ ] **Gate passed:** one week of unattended telemetry on a dashboard

## Review log

| Date | What | Verdict | Notes |
|---|---|---|---|
| 2026-08-27 | Kickoff | — | Toolchain verified (GCC 13.1, C++20). Roadmap + tracker created. Assignment 1 issued. |

## Session log

- **2026-08-27** — Kickoff: profiled background (10y C#/.NET), confirmed hardware (2× TTGO LoRa32, 1× LuaNode32), 3–5 h/week, mixed style. Roadmap written. Assignment 1 issued.
