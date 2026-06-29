# Baseline `game` (reference)

Original prototype from the assignment, kept **as-is** on purpose.

- **CMake target:** `game` (static library, links `io`)
- **Not used** by `sw_battle_test` — the shipping executable links `NewGame` instead

Why it stays here:

- side‑by‑side diff with `NewGame` while refactoring (behavior, events, structure)
- optional experiments: link `game` instead of `NewGame` in a target and compare output on the same `scenario_*.txt`

To try the baseline in code, point your executable at `target_link_libraries(... PRIVATE game io)` and use `sw::game::World` / headers under `Game/`.
