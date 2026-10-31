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

서로 다른 Namespace 에 동일한 이름의 함수가 존재할 때 **이름 충돌을 방지하고 각 함수를 호출하는 방법**을 확인합니다.

**구현할 Namespace 구조**

| Namespace | 함수 | 동작 |
|---|---|---|
| `Math` | `add(a, b)` | `a + b` |
| `Math` | `mul(a, b)` | `a * b` |
| `Logic` | `add(a, b)` | `a + b + b` (= a + 2b) |
| `Logic::Sub` (Nested) | `add(a, b)` | `a - b` |

**요구 사항**

- `Math` 와 `Logic` Namespace 를 각각 정의하세요.
- `Logic::Sub` 는 `Logic` 안에 정의된 Nested Namespace 입니다.
- Namespace Alias `M = Math` 로 `M::add` 를 호출할 수 있어야 합니다.
- `using Math::add;` (Declaration) 와 `using namespace Logic;` (Directive) 의 차이를 확인합니다.

```cpp
// a=5, b=3 기준
Math::add(5, 3)         // 8   (Scope Resolution)
Math::mul(5, 3)         // 15
Logic::add(5, 3)        // 11  (= 5 + 3 + 3)
Logic::Sub::add(5, 3)   // 2   (Nested Namespace)
M::add(5, 3)            // 8   (Alias)
// using Math::add;  → add(5, 3) = 8   (Declaration: Math::add 만 가져옴)
// using namespace Logic; → add(5, 3) = 11 (Directive: Logic 전체)
```

---

## 문제 2 — Upcasting & Virtual Function (`problem2.cpp`)

Derived Class Object 를 Base Class Pointer 로 참조할 때, **Virtual Function 유무에 따라 호출되는 함수가 달라진다는 점**을 확인합니다.

**클래스 구조**

| 클래스 | 멤버 | 접근 지정자 | 설명 |
|---|---|---|---|
| `Animal` (base) | `string name` | protected | 이름 |
| `Dog` (derived) | — | — | `Animal` 을 public 상속 |
| `Cat` (derived) | — | — | `Animal` 을 public 상속 |

**요구 사항**

- `void describe() const` — **Non-virtual**: `Animal*` 로 호출하면 항상 `Animal::describe()` 가 불립니다 (Static Binding).
  - `Animal::describe()` → `"I am an Animal named <name>."` 출력
  - `Dog::describe()` → `"I am a Dog named <name>."` 출력 (직접 호출 시에만)
  - `Cat::describe()` → `"I am a Cat named <name>."` 출력 (직접 호출 시에만)
- `virtual void speak() const` — **Virtual**: `Animal*` 로 호출해도 실제 객체 타입의 함수가 불립니다 (Dynamic Binding).
  - `Dog::speak()` → `"Woof! I am <name>."` 출력, `override` 사용
  - `Cat::speak()` → `"Meow! I am <name>."` 출력, `override` 사용
- `virtual ~Animal()` 를 선언하세요.

```cpp
Dog dog("Rex");  Cat cat("Whiskers");
Animal* p;
p = &dog;  p->describe(); // "I am an Animal named Rex."   (Static Binding)
p = &dog;  p->speak();    // "Woof! I am Rex."             (Dynamic Binding)
p = &cat;  p->speak();    // "Meow! I am Whiskers."        (Dynamic Binding)
```

`Dog` / `Cat` 이 `Animal` 을 public 상속하지 않으면 `static_assert` 에 의해 빌드가 실패합니다.

---

## 문제 3 — Virtual Destructor (`problem3.cpp`)

Base Class Pointer 를 통해 Derived Class Object 를 삭제할 때 **Virtual Destructor 가 필요한 이유**를 확인합니다.

**클래스 구조**

| 클래스 | 멤버 | 접근 지정자 | 설명 |
|---|---|---|---|
| `Base` (base) | `string name` | protected | 이름 |
| `Derived` (derived) | `int* data`, `int size` | private | 동적 할당 배열 |

**요구 사항**

- `Base(const string& name)` → `"[Base] constructor: <name>"` 출력
- `virtual ~Base()` → `"[Base] destructor: <name>"` 출력
- `Derived(const string& name, int size)` → `new int[size]` 로 메모리 할당, `"[Derived] constructor: <name> (size=<size>)"` 출력
- `~Derived() override` → `"[Derived] destructor: <name>"` 출력, `delete[] data` 로 메모리 해제
- Virtual Destructor 가 없으면 `Base*` 로 `delete` 시 `Derived::~Derived()` 가 호출되지 않아 메모리 누수가 발생합니다.

```cpp
Base* p = new Derived("Hero", 3);
// [Base] constructor: Hero
// [Derived] constructor: Hero (size=3)
delete p;
// [Derived] destructor: Hero   ← virtual 덕분에 올바르게 호출됨
// [Base] destructor: Hero
```

---

## 문제 4 — Integrated (`problem4.cpp`)

**Interface Class, Pure Virtual Function, Function Overriding, Dynamic Dispatch** 를 함께 활용합니다.

`Character` Interface Class 는 이미 제공되어 있습니다. `Knight`, `Wizard`, `Archer` 를 구현하세요.

**제공되는 Character Interface**

```cpp
class Character {
protected:
    string name;
    int hp;
    int damage;
public:
    Character(const string& name, int hp, int damage);
    virtual void attack() const = 0;       // Pure Virtual
    virtual void status() const = 0;       // Pure Virtual
    virtual string getType() const = 0;    // Pure Virtual
    virtual ~Character();                  // "[Character] destructor: <name>" 출력
    string getName() const;
};
```

**구현할 Derived Class**

| 클래스 | `attack()` 출력 | `status()` 출력 | `getType()` |
|---|---|---|---|
| `Knight` | `"Knight <name> attacks with sword! Deals <damage> damage."` | `"Knight \| Name: <name> \| HP: <hp>"` | `"Knight"` |
| `Wizard` | `"Wizard <name> casts a spell! Deals <damage> damage."` | `"Wizard \| Name: <name> \| HP: <hp>"` | `"Wizard"` |
| `Archer` | `"Archer <name> shoots an arrow! Deals <damage> damage."` | `"Archer \| Name: <name> \| HP: <hp>"` | `"Archer"` |

**요구 사항**

- 모든 Pure Virtual Function 을 구현하고 `override` keyword 를 사용하세요.
- 각 Destructor(`~Knight()` 등) 는 `"[Knight] destructor: <name>"` 을 출력하세요.
- `Character*` 배열에서 `attack()` 을 호출하면 실제 객체 타입에 따라 서로 다른 함수가 불려야 합니다 (Dynamic Dispatch).
- `delete` 시 Derived Destructor → `Character` Destructor 순서로 호출되어야 합니다.

```cpp
Character* c = new Knight("Arthur", 100, 30);
c->status();   // "Knight | Name: Arthur | HP: 100"
c->attack();   // "Knight Arthur attacks with sword! Deals 30 damage."
delete c;
// "[Knight] destructor: Arthur"
// "[Character] destructor: Arthur"
```

`Knight`, `Wizard`, `Archer` 가 `Character` 를 public 상속하지 않으면 `static_assert` 에 의해 빌드가 실패합니다.

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
