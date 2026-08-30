# Progress tracker — C++ mentorship

*Single source of truth for where we are. Claude updates it every session; tick boxes yourself freely.*
*To resume any time: open a Cowork session on this folder and say "continue C++ coaching".*

> **Now (2026-08-30):** Phase 1 · Assignment 1 reviewed — **Parts A, C, D accepted**; Part B revision outstanding (see below). Then: **Milestone M1 `templog`**.

---

## Assignment 1 — "First contact" *(Phase 0 wrap-up + Phase 1 kickoff, ~3–4 h)*

**Part A — housekeeping (~30 min)**

- [x] `git init` + `.gitignore` (`cmake-build-*/`, `*.exe`) + real commit history *(2026-08-30, 5 commits)*
- [x] Terminal compile without the IDE (incl. PATH lesson: CLion's bundled MinGW isn't on PATH) *(2026-08-30)*
- [ ] Compiler error vs linker error — compiler side seen; linker side: `f()` was orphaned by the CMake target swap, since restored & deleted — **confirm you actually saw `undefined reference to f()` before deleting it** (one line in chat closes this)

**Part B — `01_sensor_stats.cpp` (~2 h)**

Create the file and add a **second** `add_executable` target to CMakeLists.txt (first taste of multi-target builds).

Spec (amended 2026-08-30: **median** added — it's the reason the vector must exist; streaming version lives in git history):

- [x] Read readings until end-of-input into a `std::vector<double>` (stretch adopted as the main path)
- [x] Median — correct for odd/even/single/negatives/empty (verified in sandbox 2026-08-30)
- [x] Empty-input guard; `static_cast<double>` for size conversion
- [ ] **Revision:** print **count** + label every output line (empty input currently prints four bare zeros — indistinguishable from real data)
- [ ] **Revision:** out-of-range warning must name the offender's **position and value**
- [ ] **Revision:** extract **≥2 functions** besides `main` — and state your parameter choice (by value / by reference) and why
- [ ] **Open question to answer in chat:** feed `1 2 abc 3` — explain what the stream did at `abc`, and how the program can *detect* the early stop (eof vs fail). This becomes M1's corrupt-line defense.

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

- [x] Predictions made *before* running — graded **3.5/4** in chat (2026-08-30): №1 garbage ✓ (terminology: the variable *is* the slot, nothing "points"; and it's UB — deterministic 1 at -O0, 0 at -O2/-O3 on his machine), №2 pointer arithmetic ✓ (correction: literal is null-terminated → exactly `"bc"`, no trailing garbage), №3 truncation ✓ (C++ allows with `=`, braces `{}` would refuse), №4 outcome ✓ (assignment is an expression, int→bool conversion)
- [ ] Transcribe predictions + actual outcomes as comments into `predictions.cpp`, plus the one-sentence trust-model conclusion (currently the file still says "prediction?")
- [ ] Add missing `#include <string>` to predictions.cpp (it compiles via iostream's transitive includes — a portability accident, not a guarantee; include what you use)

**Part D — warnings (~15 min)**

- [x] `add_compile_options(-Wall -Wextra)` added before all targets — correct placement *(2026-08-30)*. Observed: №1 (`-Wuninitialized`) and №4 (`-Wparentheses`) warn; №2 and №3 stay silent even with these flags.

Reading alongside: learncpp.com — the intro chapters, *fundamental data types*, and *intro to std::vector*.

**Done =** everything committed → tell Claude *"review assignment 1"*.

---

## Phase gates

### Phase 0 — Toolchain & mental model
- [x] CLion + MinGW GCC 13.1 + CMake 4.2 + ninja working, C++20 set *(2026-08-27)*
- [x] First IDE build & run *(2026-08-27)*
- [x] Terminal build without IDE *(2026-08-30)*
- [x] Compile→link pipeline understood (demonstrated in conversation: stages, -c vs link, symbol resolution, lazy linker) *(2026-08-30)*
- [x] Warnings enabled *(2026-08-30)*
- [ ] **Gate:** ~~what the linker does~~ ✓ conversationally · .h vs .cpp explanation — lands naturally in M1 when the code first splits into files

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
| 2026-08-30 | Median (Part B core) | ✓ correct | Sandbox-verified: odd/even/single/negatives/empty all right; min/max init sound. Punch list issued: count+labels, offender positions, function extraction. |
| 2026-08-30 | Parts A, C, D | ✓ accepted | Git history real; CMake 3 targets + `-Wall -Wextra` correctly placed; predictions 3.5/4; UB determinism explored hands-on (-O0 → 1, -O2/-O3 → 0). Pending: prediction comments in file, linker-error confirmation. |

## Session log

- **2026-08-27** — Kickoff: profiled background (10y C#/.NET), confirmed hardware (2× TTGO LoRa32, 1× LuaNode32), 3–5 h/week, mixed style. Roadmap written. Assignment 1 issued.
- **2026-08-30** — Big session. Covered along the way: PATH & how shells find programs; compile→link pipeline (-c, symbol tables, lazy linker); read-until-EOF idiom (`while (cin >> v)`) + the `!eof()` trap; streaming vs storing (median amendment); narrowing conversions & first `static_cast`; `std::sort` / algorithms-as-free-functions (STL vs LINQ shape); UB masterclass — deterministic garbage, optimizer as-if rule, -O levels ↔ Debug/Release. Median verified correct. A1 nearly closed: Part B revision + predictions transcription outstanding.
