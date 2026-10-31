/*
 * Problem 4: Integrated
 *
 * 학번:
 * 이름:
 *
 * ─────────────────────────────────────────────────────────────
 * Character Interface Class 를 상속받아 Knight, Wizard, Archer 를 구현하세요.
 * Character 클래스는 이미 제공되어 있습니다. 수정하지 마세요.
 *
 * [출력 형식]
 *   Knight::attack()  → "Knight <name> attacks with sword! Deals <damage> damage."
 *   Knight::status()  → "Knight | Name: <name> | HP: <hp>"
 *   Knight::getType() → "Knight"
 *   Knight 소멸 시    → "[Knight] destructor: <name>"
 *
 *   Wizard::attack()  → "Wizard <name> casts a spell! Deals <damage> damage."
 *   Wizard::status()  → "Wizard | Name: <name> | HP: <hp>"
 *   Wizard::getType() → "Wizard"
 *   Wizard 소멸 시    → "[Wizard] destructor: <name>"
 *
 *   Archer::attack()  → "Archer <name> shoots an arrow! Deals <damage> damage."
 *   Archer::status()  → "Archer | Name: <name> | HP: <hp>"
 *   Archer::getType() → "Archer"
 *   Archer 소멸 시    → "[Archer] destructor: <name>"
 *
 * [동작 특성]
 *   - Character* 배열로 관리하더라도 실제 객체 타입에 따라
 *     서로 다른 attack(), status(), getType() 이 호출되어야 합니다.
 *   - Character 의 순수 가상 함수를 모두 구현해야 하며,
 *     함수 Signature 가 Interface 와 정확히 일치함을 컴파일러가 검증할 수 있어야 합니다.
 *   - Character* 로 delete 했을 때 각 Derived Class 의 소멸자가 먼저 호출된 후
 *     Character 의 소멸자가 호출되어야 합니다.
 *
 * runner 함수(runProblem4)는 수정하지 마세요.
 * ─────────────────────────────────────────────────────────────
 */
#include <iostream>
#include <string>
using namespace std;

namespace {

// ── Character Interface (수정하지 마세요) ──────────────────────
class Character {
protected:
    string name;
    int hp;
    int damage;
public:
    Character(const string& name, int hp, int damage)
        : name(name), hp(hp), damage(damage) {}
    virtual void attack() const = 0;
    virtual void status() const = 0;
    virtual string getType() const = 0;
    virtual ~Character() {
        cout << "[Character] destructor: " << name << "\n";
    }
    string getName() const { return name; }
};

// ── Knight 를 구현하세요 ────────────────────────────────────────
class Knight /* : public Character */ {
    // TODO
};

// ── Wizard 를 구현하세요 ────────────────────────────────────────
class Wizard /* : public Character */ {
    // TODO
};

// ── Archer 를 구현하세요 ────────────────────────────────────────
class Archer /* : public Character */ {
    // TODO
};

} // namespace

// ── runner (수정하지 마세요) ───────────────────────────────────
void runProblem4(istream& in) {
    string kName, wName, aName;
    int kHP, kDmg, wHP, wDmg, aHP, aDmg;
    in >> kName >> kHP >> kDmg >> wName >> wHP >> wDmg >> aName >> aHP >> aDmg;

    cout << "=== Problem 4: Integrated ===" << "\n";

    Character* party[3];
    party[0] = new Knight(kName, kHP, kDmg);
    party[1] = new Wizard(wName, wHP, wDmg);
    party[2] = new Archer(aName, aHP, aDmg);

    cout << "[Part 1] Status" << "\n";
    for (int i = 0; i < 3; i++) party[i]->status();

    cout << "[Part 2] Attack (Dynamic Dispatch)" << "\n";
    for (int i = 0; i < 3; i++) party[i]->attack();

    cout << "[Part 3] Type" << "\n";
    for (int i = 0; i < 3; i++) {
        cout << "[" << party[i]->getType() << "] " << party[i]->getName() << "\n";
    }

    cout << "[Part 4] Destroy" << "\n";
    for (int i = 0; i < 3; i++) delete party[i];
}
// ─────────────────────────────────────────────────────────────
