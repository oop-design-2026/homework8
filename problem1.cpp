/*
 * Problem 1: Namespace
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * 아래 runner 함수(runProblem1)가 올바르게 동작하도록
 * Namespace 와 함수를 직접 설계하고 구현하세요.
 * 전달 인자와 반환값은 모두 int 타입입니다.
 *
 * [활용 개념]
 *   - Namespace 정의 및 Scope Resolution Operator(::)
 *   - Nested Namespace
 *   - Namespace Alias  (M 은 Math 의 Alias 입니다)
 *   - using Declaration   (특정 이름 하나만 가져옴)
 *   - using namespace Directive  (Namespace 전체를 가져옴)
 *
 * [기대 반환 — a=5, b=3 기준]
 *   [Part 1] Math::add(5, 3) = 8 (5 + 3)
 *   [Part 2] Math::mul(5, 3) = 15 (5 * 3)
 *   [Part 3] Logic::add(5, 3) = 11 (5 + 3 + 3)
 *   [Part 4] Logic::Sub::add(5, 3) = 2 (5 - 2)
 *   [Part 5] Alias M = Math: M::add(5, 3) = 8 (5 + 3)
 *   [Part 6] using Declaration: add(5, 3) = 8 (5 + 3)
 *   [Part 7] using namespace Directive: add(5, 3) = 11 (5 + 3 + 3)
 *
 * runner 함수(runProblem1)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
using namespace std;

// ── Namespace 와 함수를 여기에 정의하고 구현하세요 ────────────────

// TODO: Math, Logic, Logic::Sub Namespace 를 정의하세요.


// Part 5: Namespace Alias 를 사용하여 Math::add 를 호출하세요.
//         함수 내부에서 namespace alias 를 선언하고 M::add(a, b) 를 반환하세요.
int callWithAlias(int a, int b) {
    // TODO
}

// Part 6: using Declaration 을 사용하여 Math::add 를 :: 없이 호출하세요.
//         함수 내부에서 using Declaration 을 선언하고 add(a, b) 를 반환하세요.
int callWithDeclaration(int a, int b) {
    // TODO
}

// Part 7: using namespace Directive 를 사용하여 Logic::add 를 :: 없이 호출하세요.
//         함수 내부에서 using namespace Directive 를 선언하고 add(a, b) 를 반환하세요.
int callWithDirective(int a, int b) {
    // TODO
}

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem1(istream& in) {
    int a, b;
    in >> a >> b;

    cout << "=== Problem 1: Namespace ===" << "\n";

    // Scope Resolution Operator
    cout << "[Part 1] Math::add(" << a << ", " << b << ") = " << Math::add(a, b) << "\n";
    cout << "[Part 2] Math::mul(" << a << ", " << b << ") = " << Math::mul(a, b) << "\n";
    cout << "[Part 3] Logic::add(" << a << ", " << b << ") = " << Logic::add(a, b) << "\n";

    // Nested Namespace
    cout << "[Part 4] Logic::Sub::add(" << a << ", " << b << ") = " << Logic::Sub::add(a, b) << "\n";

    // Namespace Alias
    cout << "[Part 5] Alias M = Math: M::add(" << a << ", " << b << ") = " << callWithAlias(a, b) << "\n";

    // using Declaration
    cout << "[Part 6] using Declaration: add(" << a << ", " << b << ") = " << callWithDeclaration(a, b) << "\n";

    // using namespace Directive
    cout << "[Part 7] using namespace Directive: add(" << a << ", " << b << ") = " << callWithDirective(a, b) << "\n";
}
// ─────────────────────────────────────────────────────────────
