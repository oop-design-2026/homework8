## 개요

C++의 Namespace, Virtual Function, Virtual Destructor, Interface Class 를 실습합니다.  
총 4문제로 구성되어 있으며, 각 `problem*.cpp` 파일에 있는 클래스를 구현하세요.  
`main.cpp` 는 수정하지 않습니다.

---

## 개발 환경 준비

g++ 컴파일러가 필요합니다. 이미 설치되어 있다면 다음 단계로 넘어가세요.

| 운영체제 | 설치 방법 |
|---|---|
| Windows | [MSYS2](https://www.msys2.org/) 설치 후 `pacman -S mingw-w64-ucrt-x86_64-gcc` |
| macOS | 터미널에서 `xcode-select --install` |
| Linux (Ubuntu) | `sudo apt install build-essential` |

설치 확인:
```bash
g++ --version
```

---

## 파일 구조

```
homework8/
├── main.cpp              ← 수정 금지. 테스트 실행 로직.
├── problem1.cpp          ← Problem 1 구현 (Namespace)
├── problem2.cpp          ← Problem 2 구현 (Upcasting & Virtual Function)
├── problem3.cpp          ← Problem 3 구현 (Virtual Destructor)
├── problem4.cpp          ← Problem 4 구현 (Integrated)
├── test8.sh              ← 채점 스크립트 (macOS / Linux)
├── test8.bat             ← 채점 스크립트 (Windows)
└── Test/
    ├── case1.txt         ← 테스트 케이스 1 입력 데이터
    ├── case2.txt         ← 테스트 케이스 2 입력 데이터
    ├── case3.txt         ← 테스트 케이스 3 입력 데이터
    ├── expected1.txt     ← 테스트 케이스 1 기대 출력
    ├── expected2.txt     ← 테스트 케이스 2 기대 출력
    └── expected3.txt     ← 테스트 케이스 3 기대 출력
```

---

## 문제 1 — Namespace (`problem1.cpp`)

runner 함수가 올바르게 동작하도록 Namespace 와 함수를 직접 설계하고 구현하세요.

**활용 개념**

- Namespace 정의 및 Scope Resolution Operator(`::`)
- Nested Namespace
- Namespace Alias — `M` 은 `Math` 의 Alias 입니다
- using Declaration — 특정 이름 하나만 가져옴
- using namespace Directive — Namespace 전체를 가져옴

**구현할 Namespace 구조**

| Namespace | 함수 | 동작 |
|---|---|---|
| `Math` | `add(a, b)` | `a + b` |
| `Math` | `mul(a, b)` | `a * b` |
| `Logic` | `add(a, b)` | `a + b + b` (= a + 2b) |
| `Logic::Sub` (Nested) | `add(a, b)` | `a - b` |

**구현할 wrapper 함수**

| 함수 | 요구 사항 |
|---|---|
| `callWithAlias(a, b)` | 함수 내부에서 Namespace Alias 를 선언하고 `M::add(a, b)` 를 반환 |
| `callWithDeclaration(a, b)` | 함수 내부에서 using Declaration 을 선언하고 `add(a, b)` 를 반환 |
| `callWithDirective(a, b)` | 함수 내부에서 using namespace Directive 를 선언하고 `add(a, b)` 를 반환 |

**기대 출력 — a=5, b=3 기준**

```
[Part 1] Math::add(5, 3) = 8
[Part 2] Math::mul(5, 3) = 15
[Part 3] Logic::add(5, 3) = 11
[Part 4] Logic::Sub::add(5, 3) = 2
[Part 5] Alias M = Math: M::add(5, 3) = 8
[Part 6] using Declaration: add(5, 3) = 8
[Part 7] using namespace Directive: add(5, 3) = 11
```

---

## 문제 2 — Upcasting & Virtual Function (`problem2.cpp`)

`Animal`, `Dog`, `Cat` 클래스를 구현하세요.  
runner 코드를 분석하여 각 함수에 필요한 특성을 스스로 판단하세요.

**출력 형식**

| 함수 | 출력 |
|---|---|
| `Animal::describe()` | `I am an Animal named <name>.` |
| `Dog::describe()` | `I am a Dog named <name>.` |
| `Cat::describe()` | `I am a Cat named <name>.` |
| `Dog::speak()` | `Woof! I am <name>.` |
| `Cat::speak()` | `Meow! I am <name>.` |

**동작 특성**

- `describe()` : `Animal*` 로 호출하면 실제 객체 타입과 관계없이 항상 `Animal` 의 버전이 호출됩니다.
- `speak()` : `Animal*` 로 호출하더라도 실제 객체 타입(`Dog`/`Cat`)에 따라 서로 다른 버전이 호출됩니다.
- `Dog::speak()`, `Cat::speak()` 은 Base Class 의 `speak()` 와 함수 Signature 가 정확히 일치함을 컴파일러가 검증할 수 있어야 합니다.
- `Animal*` 로 `Dog` / `Cat` 객체를 안전하게 가리킬 수 있어야 합니다.

---

## 문제 3 — Virtual Destructor (`problem3.cpp`)

`Base`, `Derived` 클래스를 구현하세요.  
runner 코드를 분석하여 각 클래스에 필요한 특성을 스스로 판단하세요.

**출력 형식**

| 시점 | 출력 |
|---|---|
| `Base` 생성 시 | `[Base] constructor: <name>` |
| `Derived` 생성 시 | `[Derived] constructor: <name> (size=<size>)` |
| `Derived` 소멸 시 | `[Derived] destructor: <name>` |
| `Base` 소멸 시 | `[Base] destructor: <name>` |

**동작 특성**

- `Derived` 는 생성 시 크기 `size` 의 `int` 배열을 동적 할당하고, 소멸 시 메모리 누수 없이 해제해야 합니다.
- `Base*` 로 `delete` 했을 때 `Derived` 의 소멸자가 반드시 먼저 호출된 후 `Base` 의 소멸자가 호출되어야 합니다.
- `Derived` 의 소멸자는 `Base` 의 소멸자와 함수 Signature 가 정확히 일치함을 컴파일러가 검증할 수 있어야 합니다.
- 생성과 소멸의 순서는 반대여야 합니다 — 생성: `Base` → `Derived` / 소멸: `Derived` → `Base`

---

## 문제 4 — Integrated (`problem4.cpp`)

`Character` Interface Class 는 이미 제공되어 있습니다. `Knight`, `Wizard`, `Archer` 를 구현하세요.

**출력 형식**

| 클래스 | `attack()` 출력 | `status()` 출력 | `getType()` | 소멸 시 출력 |
|---|---|---|---|---|
| `Knight` | `Knight <name> attacks with sword! Deals <damage> damage.` | `Knight \| Name: <name> \| HP: <hp>` | `"Knight"` | `[Knight] destructor: <name>` |
| `Wizard` | `Wizard <name> casts a spell! Deals <damage> damage.` | `Wizard \| Name: <name> \| HP: <hp>` | `"Wizard"` | `[Wizard] destructor: <name>` |
| `Archer` | `Archer <name> shoots an arrow! Deals <damage> damage.` | `Archer \| Name: <name> \| HP: <hp>` | `"Archer"` | `[Archer] destructor: <name>` |

**동작 특성**

- `Character*` 배열로 관리하더라도 실제 객체 타입에 따라 서로 다른 `attack()`, `status()`, `getType()` 이 호출되어야 합니다.
- `Character` 의 순수 가상 함수를 모두 구현해야 하며, 함수 Signature 가 Interface 와 정확히 일치함을 컴파일러가 검증할 수 있어야 합니다.
- `Character*` 로 `delete` 했을 때 각 Derived Class 의 소멸자가 먼저 호출된 후 `Character` 의 소멸자가 호출되어야 합니다.

---

## 테스트 방법

```bash
# macOS / Linux
bash test8.sh

# Windows
test8.bat
```

테스트 케이스 3개를 순서대로 실행하며 각 문제별로 `PASS` / `FAIL` 을 출력합니다.  
`FAIL` 인 경우 기대 출력과 실제 출력의 차이를 함께 확인하세요.

---

## 제출 방법 (git)

```bash
git add problem1.cpp problem2.cpp problem3.cpp problem4.cpp
git commit -m "학번 이름"
git push
```

- push 후 저장소의 **Actions 탭** 에서 자동 채점 결과를 확인할 수 있습니다.
- 마감 전까지 몇 번이든 다시 제출할 수 있습니다.
