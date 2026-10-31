/*
 * Problem 3: Virtual Destructor
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * Base, Derived 클래스를 구현하세요.
 * runner 코드를 분석하여 각 클래스에 필요한 특성을 스스로 판단하세요.
 *
 * [출력 형식]
 *   Base 생성 시      → "[Base] constructor: <name>"
 *   Derived 생성 시   → "[Derived] constructor: <name> (size=<size>)"
 *   Derived 소멸 시   → "[Derived] destructor: <name>"
 *   Base 소멸 시      → "[Base] destructor: <name>"
 *
 * [동작 특성]
 *   - Derived 는 생성 시 크기 size 의 int 배열을 동적 할당하고,
 *     소멸 시 메모리 누수 없이 해제해야 합니다.
 *   - Base* 로 delete 했을 때 Derived 의 소멸자가 반드시 먼저 호출된 후
 *     Base 의 소멸자가 호출되어야 합니다.
 *   - Derived 의 소멸자는 Base 의 소멸자와 함수 Signature 가 정확히
 *     일치함을 컴파일러가 검증할 수 있어야 합니다.
 *   - 생성과 소멸의 순서는 반대여야 합니다.
 *       생성: Base → Derived
 *       소멸: Derived → Base
 *
 * runner 함수(runProblem3)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
#include <string>
using namespace std;

namespace {

// ── Base (base class) 를 구현하세요 ─────────────────────────────
class Base {
    // TODO
};

// ── Derived (derived class) 를 구현하세요 ────────────────────────
class Derived /* : public Base */ {
    // TODO
};

} // namespace

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem3(istream& in) {
    string name;
    int size;
    in >> name >> size;

    cout << "=== Problem 3: Virtual Destructor ===" << "\n";

    cout << "[Part 1] Create Derived object" << "\n";
    Base* p = new Derived(name, size);

    cout << "[Part 2] Delete via Base pointer" << "\n";
    delete p;

    cout << "[Part 3] Object deleted" << "\n";
}
// ─────────────────────────────────────────────────────────────
