# Turn-based battle simulation

Рефакторинг тестового задания: пошаговая боевая симуляция на клеточной карте с расширяемой архитектурой и новым юнитом — **Охотником**.

Набок классов из Core задает механизм декомпозиции  (entity / ability / effect / composition), основанный на отделении состояния иот операций. Реализация очень грубая, очень медленная, схематическая.

Исходное ТЗ и правила симуляции — в [`docs/initialREADME.md`](docs/initialREADME.md).
Внешний контракт (команды, события, ограничения) — в [`docs/contract.md`](docs/contract.md).
Архитектурные заметки и принятые/отклонённые решения — в [`docs/ideas.md`](docs/ideas.md).

## Что реализовано

- **Мечник** — ближняя атака, способность «Рваные раны», движение по приказу `MARCH`.
- **Охотник** — дальняя/ближняя атака, отравленные стрелы, движение.
- **Эффекты** — `Poisoned`, `Rended`, `OrderedToMove`; мировые фазы `updateEffects` / `applyEffects`.
- **Контракт IO** сохранён: те же команды сценария и тот же формат событий на выходе.

Симуляция завершается, когда за ход не осталось осмысленных действий (атака, движение, тик эффекта и т.п.).

## Сборка

Требования: **CMake 3.27+**, **C++20**, **Clang** (presets рассчитаны на LLVM из Visual Studio / standalone LLVM).

```powershell
cmake --preset debug
cmake --build --preset debug
```

Бинарники появляются в `build/ninja-clang-debug/Debug/`:

| Target | Назначение |
|--------|------------|
| `sw_battle_test` | Основной исполняемый файл — прогон сценария из файла |
| `scenario_runner` | Встроенные регрессионные сценарии (без внешних файлов) |

Release-сборка:

```powershell
cmake --preset release
cmake --build --preset release
```

## Запуск

### Сценарий из файла

```powershell
.\build\ninja-clang-debug\Debug\sw_battle_test.exe .\scenario_1.txt
```

Пример входа (`scenario_1.txt`):

```
CREATE_MAP 10 10
SPAWN_SWORDSMAN 1 5 2 10 1 100 5
MARCH 1 5 7
SPAWN_SWORDSMAN 2 7 5 10 1 100 5
MARCH 2 2 5
```

На stdout печатается поток событий: `MAP_CREATED`, `UNIT_SPAWNED`, `MARCH_STARTED`, `UNIT_MOVED`, `UNIT_ATTACKED`, `UNIT_ABILITY_USED`, `UNIT_DIED`, …

### Встроенные тесты

```powershell
.\build\ninja-clang-debug\Debug\scenario_runner.exe
```

В репозитории есть baseline-сценарии (`scenario_1` … `scenario_4`) и дополнительные сценарии для охотника (дистанция, мили-блок дальнего, яд после смерти).

## Структура репозитория

```
src/
├── IO/                 # Внешний контракт: парсер команд, EventSystem, форматы событий
├── Game/               # Baseline-реализация из исходного прототипа (reference, не в shipping)
├── NewGame/            # Целевая архитектура
│   ├── Core/           # Движок: state-модель, транзакции, категории фич, нормализация
│   ├── Features/       # Конкретные механики: Entities, Abilities, Effects, Compositions
│   ├── World.cpp       # Оркестратор симуляции (step, spawn, march, фазы эффектов)
│   └── interface.include.h
├── Main/               # sw_battle_test — точка входа для сценария из argv
└── Test/               # scenario_runner — встроенный harness

docs/                   # ТЗ, контракт, архитектурные заметки
scenario_*.txt          # Примеры входных сценариев
```

### `Game/` vs `NewGame/`

- **`src/Game`** — исходный монолитный прототип, оставлен для сравнения и регрессии. Shipping-сборка его **не** линкует.
- **`src/NewGame`** — новая архитектура по разделению **Core / Features** из ТЗ:
  - **Core** — типобезопасный контейнер состояния, schema, patch-транзакции, reactions/emitters;
  - **Features** — мечник, охотник, атаки, яд, рваные раны, карта, юниты.

`World` остаётся тонким фасадом: принимает команды IO, дергает composition/ability/effect actions, ведёт turn loop.

## Архитектура (кратко)

Фича описывается как тип с осями **State / Actions / Reactions / Emitters** и попадает в schema через `Intertype::SchemaData::build<...>()`.

Категории (по смыслу, не по списку типов):

- **Entity** — то, что умеет существовать само по себе: карта, юнит. Это «носители» мира; без entity ни ability, ни effect жить не могут.
- **Ability** — постоянная способность, навсегда собранная с entity: ближняя атака, дальняя, рваные раны, отравленные стрелы. Это не «состояние на время», а часть того, кем юнит является.
- **Effect** — временное состояние, которое навешивают и снимают: яд, рваные раны как debuff, приказ идти. Тоже живёт только на entity, но имеет свой lifecycle (тики, apply, снятие).
- **Composition** — «мозги-сборщик» сущности: `Swordsman`, `Hunter`. Не ability и не effect, а дирижёр — при spawn собирает нужный набор компонентов, при turn задаёт стратегию (что проверять первым, кого бить, когда двигаться). Именно composition связывает entity с его поведением в игре.

Примеры: `Map`, `Unit` · `MeleeAttack`, `PoisonArrows` · `Poisoned`, `OrderedToMove` · `Swordsman`, `Hunter`.

Изменения состояния идут через **ScopedTransaction**: normalize → reactions → emit diff-событий. Runtime-события (`UNIT_ATTACKED`, `UNIT_MOVED`, …) эмитятся из Actions там, где факт известен в момент действия.

### Turn loop (`World::step`)

1. **updateEffects** — старение эффектов (`remainingTurns`, без урона)
2. **unit turns** — каждый живой юнит по порядку регистрации
3. **applyEffects** — применение DoT (яд; учёт `Rended` для удвоения)

## Охотник (по ТЗ)

| Механика | Поведение |
|----------|-----------|
| Дальняя атака | Случайная цель на расстоянии 2…`Range`, урон = `Agility`; только если **нет** соседних юнитов |
| Ближняя атака | Если рядом есть цель — бьёт на `Strength` вместо выстрела |
| Poison arrows | С шансом `Chance/1000` вместо выстрела — DoT на `Poison` урона за 5 ходов |
| Яд + Rending | Тик яда удваивается, если на цели в этот ход висит `Rended` |
| Атрибуция урона | Тики яда идут как `UNIT_ATTACKED` от охотника-наложителя |

## Отладка (VS Code / Cursor)

В репозитории настроены CMake presets и launch-конфиги для `scenario_runner` и активного CMake target. Preset: `ninja-clang-debug`, startup project: `scenario_runner`.

## Что сознательно упрощено

- Порядок фаз в `World::step()` захардкожен (см. `docs/ideas.md`).
- Turn strategy хранится в `Unit::State` как `std::function`, а не отдельная entity.
- Baseline `Game/` не удалён — удобен для diff с новой моделью.

Для проверки перед сдачей: собрать `debug`, прогнать `scenario_runner`, при необходимости — `sw_battle_test` на `scenario_*.txt`.
