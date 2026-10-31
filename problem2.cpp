/*
 * Problem 2: Upcasting & Virtual Function
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * Animal, Dog, Cat 클래스를 구현하세요.
 * runner 코드를 분석하여 각 함수에 필요한 특성을 스스로 판단하세요.
 *
 * [출력 형식]
 *   Animal::describe() → "I am an Animal named <name>."
 *   Dog::describe()    → "I am a Dog named <name>."
 *   Cat::describe()    → "I am a Cat named <name>."
 *   Dog::speak()       → "Woof! I am <name>."
 *   Cat::speak()       → "Meow! I am <name>."
 *
 * [동작 특성]
 *   - describe() : Animal* 로 호출하면 실제 객체 타입과 관계없이
 *                  항상 Animal 의 버전이 호출됩니다.
 *   - speak()    : Animal* 로 호출하더라도 실제 객체 타입(Dog/Cat)에 따라
 *                  서로 다른 버전이 호출됩니다.
 *   - Dog::speak(), Cat::speak() 은 Base Class 의 speak() 와 함수 Signature 가
 *                  정확히 일치함을 컴파일러가 검증할 수 있어야 합니다.
 *   - Animal* 로 Dog / Cat 객체를 안전하게 가리킬 수 있어야 합니다.
 *
 * runner 함수(runProblem2)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
#include <string>
using namespace std;

namespace {

// ── Animal (base class) 를 구현하세요 ───────────────────────────
class Animal {
    // TODO
};

// ── Dog (derived class) 를 구현하세요 ──────────────────────────
class Dog /* : public Animal */ {
    // TODO
};

// ── Cat (derived class) 를 구현하세요 ──────────────────────────
class Cat /* : public Animal */ {
    // TODO
};

} // namespace

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem2(istream& in) {
    string dogName, catName;
    in >> dogName >> catName;

    cout << "=== Problem 2: Upcasting & Virtual Function ===" << "\n";

    Dog dog(dogName);
    Cat cat(catName);
    Animal* p;

    cout << "[Part 1] describe() via Animal* (Static Binding)" << "\n";
    p = &dog;
    p->describe();
    p = &cat;
    p->describe();

    cout << "[Part 2] speak() via Animal* (Dynamic Binding)" << "\n";
    p = &dog;
    p->speak();
    p = &cat;
    p->speak();

    cout << "[Part 3] Polymorphic array" << "\n";
    Animal* animals[2] = {&dog, &cat};
    for (int i = 0; i < 2; i++) {
        animals[i]->speak();
    }
}
// ─────────────────────────────────────────────────────────────
