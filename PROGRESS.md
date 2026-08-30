# Progress tracker — C++ mentorship

*Single source of truth for where we are. Claude updates it every session; tick boxes yourself freely.*
*To resume any time: open a Cowork session on this folder and say "continue C++ coaching".*

> **Now (2026-08-30):** Phase 1 · **Assignment 1 PASSED** · **Milestone M1 `templog` issued** — spec below, data file `sensors.csv` in the repo.
> Epilogue owed with the next commit: actual outcomes + the one-sentence trust-model conclusion as comments in `predictions.cpp`.

---

## Assignment 1 — "First contact" *(Phase 0 wrap-up + Phase 1 kickoff, ~3–4 h)*

**Part A — housekeeping (~30 min)**

- [x] `git init` + `.gitignore` (`cmake-build-*/`, `*.exe`) + real commit history *(2026-08-30, 5 commits)*
- [x] Terminal compile without the IDE (incl. PATH lesson: CLion's bundled MinGW isn't on PATH) *(2026-08-30)*
- [x] Compiler error vs linker error — both provoked and witnessed, incl. `undefined reference to f()` *(confirmed 2026-08-30)*

**Part B — `01_sensor_stats.cpp` (~2 h)**

Create the file and add a **second** `add_executable` target to CMakeLists.txt (first taste of multi-target builds).

Spec (amended 2026-08-30: **median** added — it's the reason the vector must exist; streaming version lives in git history):

- [x] Read readings until end-of-input into a `std::vector<double>` (stretch adopted as the main path)
- [x] Median — correct for odd/even/single/negatives/empty (verified in sandbox 2026-08-30)
- [x] Empty-input guard; `static_cast<double>` for size conversion
- [x] **Revision:** count printed + all output lines labeled *(2026-08-30)*
- [x] **Revision:** out-of-range warning names value and position (0-based) *(2026-08-30)*
- [x] **Revision:** two functions extracted — `calculateMedian(const std::vector<double>&)` with documented sorted-precondition, `printResults` fixed to const-ref after the "your own rule" nudge *(2026-08-30)*
- [x] **Open question answered:** stream mechanics explained (failbit is sticky, parse ≠ cast, unconsumed buffer); detection implemented as `if (cin.fail() && !cin.eof())` → error message. Witnessed the fail-on-clean-end surprise live. *(2026-08-30)*

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
- [x] Predictions transcribed as comments; `#include <string>` added (include-what-you-use) *(2026-08-30)*
- [ ] **Epilogue (non-blocking):** add actual outcomes next to each prediction + the one-sentence trust-model conclusion

**Part D — warnings (~15 min)**

- [x] `add_compile_options(-Wall -Wextra)` added before all targets — correct placement *(2026-08-30)*. Observed: №1 (`-Wuninitialized`) and №4 (`-Wparentheses`) warn; №2 and №3 stay silent even with these flags.

Reading alongside: learncpp.com — the intro chapters, *fundamental data types*, and *intro to std::vector*.

**Done =** everything committed → tell Claude *"review assignment 1"*.

**VERDICT: PASSED 2026-08-30.** Build clean under `-Wall -Wextra`; garbage detection, labels, positions, const-correct functions all verified in sandbox.

---

## Milestone M1 — `templog` *(issued 2026-08-30)*

The scenario: three days of temperature logs from five home sensors landed in **`sensors.csv`** (in the repo — supplied by Claude, with deliberate damage inside: corrupt lines *and* impossible readings, locations undisclosed). Build the tool that turns it into a report you can trust.

Run as: `templog sensors.csv` — the path comes from the **command line**, not stdin (new topic: `argc`/`argv`).

- [ ] **First multi-file program:** `stats.h` + `stats.cpp` (min/max/mean/median over `std::vector<double>`) used by `02_templog.cpp`; one CMake target, two .cpp files. This closes the Phase 0 gate — be ready to explain .h vs .cpp and what `#pragma once` protects against.
- [ ] Read **line by line** (`std::getline`), skip the header row, split on commas into a `Reading` struct (your first struct): timestamp, sensor, value. Parsing strategy is your choice (`std::stringstream`, or `find`+`substr`).
- [ ] A line that doesn't parse cleanly → **report it with its line number, skip it, keep going.** Note what you've gained over `cin >> double`: per-line reading contains the damage. Be ready to say why.
- [ ] Group readings per sensor. Recommended discovery: `std::map<std::string, std::vector<double>>` — the standard library's answer to `Dictionary` (sorted, no hashing). Rolling your own grouping with vectors is also acceptable.
- [ ] Out-of-range readings (outside **[-40, 85] °C**): **excluded from the statistics**, listed separately as anomalies (sensor, value, line number). Note this is a different policy than `sensor_stats`, which included them — in M1 they're presumed sensor faults.
- [ ] Report: per sensor — count, min, max, mean, median; then the anomaly list; then the corrupt-line list; totals at the end.
- [ ] Rules: const-correct signatures everywhere; no `new`/`delete`; range-for where natural.
- [ ] Stretch: exit code 1 if any corrupt lines were found (what `return` from `main` is for); `--sensor <name>` filter argument.

**Gate:** clean build with warnings on; numbers match Claude's independently computed answer key; every sabotaged line caught with the right line number; the .h/.cpp explanation delivered.

Reading alongside: learncpp — `std::string` & `std::getline`, structs, command-line arguments; cppreference: `std::map`.

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
- [x] Assignment 1 reviewed & passed *(2026-08-30)*
- [x] Parameter-passing contract understood: cheap by value / `const T&` default / naked `T&` = mutation intent; found the by-value copy in his own `printResults` *(2026-08-30)*
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
| 2026-08-30 | **Assignment 1 final** | **PASSED** | Revision complete: labels+count, position+value warnings, `calculateMedian` (const-ref, documented precondition) + `printResults` (const-ref after nudge), `fail() && !eof()` detection with error message. Sandbox: clean build, correct behavior on garbage & clean runs. Epilogue open: outcomes + trust-model sentence in predictions.cpp. |
| 2026-08-30 | **M1 `templog` issued** | — | `sensors.csv` (64 data lines, 5 sensors) committed to repo with undisclosed sabotage; answer key held by Claude. |

## Session log

- **2026-08-27** — Kickoff: profiled background (10y C#/.NET), confirmed hardware (2× TTGO LoRa32, 1× LuaNode32), 3–5 h/week, mixed style. Roadmap written. Assignment 1 issued.
- **2026-08-30** — Big session. Covered along the way: PATH & how shells find programs; compile→link pipeline (-c, symbol tables, lazy linker); read-until-EOF idiom (`while (cin >> v)`) + the `!eof()` trap; streaming vs storing (median amendment); narrowing conversions & first `static_cast`; `std::sort` / algorithms-as-free-functions (STL vs LINQ shape); UB masterclass — deterministic garbage, optimizer as-if rule, -O levels ↔ Debug/Release. Median verified correct. A1 nearly closed: Part B revision + predictions transcription outstanding.
- **2026-08-30 (cont.)** — Stream state machine closed out: sticky failbit, fail-on-clean-end witnessed via his own experiment, `fail() && !eof()` detection shipped. Parameter-passing contract taught off his own theory (const-ref default; he found the by-value copy in `printResults` himself). **Assignment 1 PASSED.** **M1 `templog` issued** with sabotaged `sensors.csv`; new ground ahead: argc/argv, getline+splitting, first struct, first header split, std::map.
