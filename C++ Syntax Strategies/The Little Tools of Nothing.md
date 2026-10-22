![The Little Tools of Nothing: 0, NULL, nullptr, void(), '\0', nullopt and npos glowing and flickering](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/27.%20Hook_Tools_of_Nothing.svg)

# The Little Tools of Nothing

*Written on 18 October 2026.*

**Contents:** [0](#0-the-overloaded-zero) · [NULL](#null-the-macro-that-looked-like-a-pointer) · [nullptr](#nullptr-nothing-with-a-pointers-type) · [void()](#void-nothing-as-a-type) · [Ternary puzzle](#the-ternary-puzzle) · [`'\0'`](#0-the-nothing-that-ends-a-string) · [nullopt](#nullopt-nothing-that-says-so) · [npos](#npos-nothing-as-the-biggest-number) · [Cheat sheet](#cheat-sheet)

C++ has at least seven different ways to say "there is nothing here". They look alike, but the compiler treats each one differently. Every section below has one small, complete program: copy it into `main.cpp`, run it, and compare your output with the one shown.

> [!NOTE]
> **How to run.** `g++ -std=c++23 main.cpp -o main && ./main`. This article is about **C++23**, the language standard, not about one compiler. As of this writing (18 October 2026), Codeforces offers GNU G++23 14.2 (64 bit, msys2), which builds in C++23 mode, so everything here runs there. C++26 is deliberately **not** covered. All programs were compiled with GCC 14.2 (`-std=c++23 -O2 -Wall -Wextra -Wconversion`) without errors or warnings, and sizes assume a 64-bit platform. (`<bits/stdc++.h>` ships with GCC's standard library; with another one, include the specific headers instead.)

---

## `0`: the overloaded zero

Zero is the oldest nothing, and it does three jobs at once. It is a null pointer constant, a neutral element (`x + 0`, `x ^ 0`), and an ordinary `int`. Each output line starts with the input, then `->` and the result:

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    // Job 1: 0 as a null pointer
    int* emptyPointer = 0;
    if (emptyPointer == nullptr) {
        cout << "int* emptyPointer = 0;  -> it is a null pointer\n";
    }

    // Job 2: 0 as a neutral value
    int number = 42;
    cout << "42 + 0                  -> " << number + 0 << '\n';
    cout << "42 ^ 0                  -> " << (number ^ 0) << '\n';

    // Job 3: 0 as a "do nothing" branch of a ternary
    int counter = 0;
    true ? ++counter : 0;
    cout << "true  ? ++counter : 0   -> counter is " << counter << " (++counter ran)\n";
    false ? ++counter : 0;
    cout << "false ? ++counter : 0   -> counter is " << counter << " (0 did nothing)\n";
}
```

```text
int* emptyPointer = 0;  -> it is a null pointer
42 + 0                  -> 42
42 ^ 0                  -> 42
true  ? ++counter : 0   -> counter is 1 (++counter ran)
false ? ++counter : 0   -> counter is 1 (0 did nothing)
```

The last two lines are the seed of the [ternary puzzle](#the-ternary-puzzle): in a conditional expression the two branches must have compatible types, and `0` is a perfectly ordinary `int`.

## `NULL`: the macro that looked like a pointer

`NULL` is a macro that C++ inherited from C. It must be a null pointer constant, and in practice it is often an integer (GCC uses a built-in token, `__null`, of integer type). It works as a null pointer, but it is really a number in disguise, and overloads expose the difference.

![Animated overload resolution: describe(0) picks the int overload, describe(NULL) is ambiguous, describe(nullptr) picks the pointer overload](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/28.%20fig-overload.svg)

```cpp
#include<bits/stdc++.h>
using namespace std;

void describe(int)   { cout << "the int overload ran\n"; }
void describe(char*) { cout << "the pointer overload ran\n"; }

int main() {
    cout << boolalpha;

    int* pointer = NULL;
    cout << "int* pointer = NULL;           -> pointer is null? " << (pointer == nullptr) << '\n';
    cout << "NULL has an integer type       -> " << is_integral_v<decltype(NULL)> << "  (on GCC)\n";
    cout << "describe(0)                    -> "; describe(0);

    // describe(NULL);   // GCC: compile error. NULL fits both overloads equally well.
}
```

```text
int* pointer = NULL;           -> pointer is null? true
NULL has an integer type       -> true  (on GCC)
describe(0)                    -> the int overload ran
```

The commented-out `describe(NULL)` is the problem: `NULL` matches the `int` overload and the pointer overload equally well, so GCC refuses to guess and reports an ambiguity error.

## `nullptr`: nothing, with a pointer's type

`nullptr` fixes that. It has its own type, `std::nullptr_t`, which converts to any pointer type and never silently to an integer. It also gives us a tidy way to "take a pointer out and leave nothing behind" with `std::exchange`.

```cpp
#include<bits/stdc++.h>
using namespace std;

void describe(int)   { cout << "the int overload ran\n"; }
void describe(char*) { cout << "the pointer overload ran\n"; }

int main() {
    cout << boolalpha;

    cout << "describe(nullptr)              -> "; describe(nullptr);
    cout << "nullptr has an integer type    -> " << is_integral_v<decltype(nullptr)> << '\n';
    cout << "nullptr has its own type       -> " << is_null_pointer_v<decltype(nullptr)> << '\n';
    // int number = nullptr;   // compile error: nullptr never turns into an integer

    int value = 5;
    int* pointer = &value;
    int* oldPointer = exchange(pointer, nullptr);   // take the pointer out, leave nullptr behind
    cout << "exchange(pointer, nullptr)     -> old pointer still sees " << *oldPointer
         << ", pointer is null now? " << (pointer == nullptr) << '\n';
}
```

```text
describe(nullptr)              -> the pointer overload ran
nullptr has an integer type    -> false
nullptr has its own type       -> true
exchange(pointer, nullptr)     -> old pointer still sees 5, pointer is null now? true
```

## `void()`: nothing, as a type

`void()` is an expression of type `void`: it has no value at all. That makes it the right tool for throwing a result away on purpose, and `std::ignore` does the same for one element of a tuple. Both programs below keep nothing.

```cpp
#include<bits/stdc++.h>
using namespace std;

int callCount = 0;
int loadConfig() { ++callCount; return 42; }

int main() {
    static_cast<void>(loadConfig());   // run it, throw the result away
    cout << "static_cast<void>(loadConfig())       -> calls made: " << callCount << ", the 42 was discarded\n";

    int firstValue{}, thirdValue{};
    tie(firstValue, ignore, thirdValue) = make_tuple(1, 2, 3);
    cout << "tie(first, ignore, third) = (1, 2, 3) -> first = " << firstValue
         << ", third = " << thirdValue << " (the 2 was skipped)\n";
}
```

```text
static_cast<void>(loadConfig())       -> calls made: 1, the 42 was discarded
tie(first, ignore, third) = (1, 2, 3) -> first = 1, third = 3 (the 2 was skipped)
```

## The ternary puzzle

This article started with a contest trick: replacing an `if` with a ternary. We want "push the position if the character is `'1'`, otherwise do nothing". There are three ways to write the "otherwise do nothing" part:

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    const string bits = "0101";
    vector<int> foundWithZero, foundWithCast;

    for (int position = 0; position < ssize(bits); ++position) {
        // Attempt 1 does not compile in C++23, so it stays commented out:
        // bits[position] != '0' ? foundWithZero.emplace_back(position) : void();

        // Attempt 2: the do-nothing branch is 0 (an int)
        bits[position] != '0' ? foundWithZero.emplace_back(position) : 0;

        // Attempt 3: both branches are void
        bits[position] != '0' ? static_cast<void>(foundWithCast.emplace_back(position)) : void();
    }

    cout << "bits = \"" << bits << "\", collect the positions of '1'\n";
    cout << "attempt 2 (: 0)                          -> " << foundWithZero[0] << " and " << foundWithZero[1] << '\n';
    cout << "attempt 3 (static_cast<void>, : void())  -> " << foundWithCast[0] << " and " << foundWithCast[1] << '\n';
}
```

```text
bits = "0101", collect the positions of '1'
attempt 2 (: 0)                          -> 1 and 3
attempt 3 (static_cast<void>, : void())  -> 1 and 3
```

Attempt 1 fails in C++23: when one branch is `void` and the other is neither `void` nor a `throw`, the conditional operator has no valid type, and compilers report exactly that. The clue is that `emplace_back` returned something. It returns a reference to the new element, `T&` (it returned `void` before C++17).

![Table of three ternary attempts in C++23 showing branch types and whether each compiles](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/29.%20fig-ternary.svg)

The rule is simple: a `void` branch can only pair with another `void` branch (or a `throw`), while `int&` and `0` unify into an `int`. Attempt 2 works because `0` is an `int`, but it depends on `emplace_back` returning a value. The robust choice is attempt 3: `static_cast<void>(...)` is always `void`, whatever the call returns, so it pairs with `void()`.

## `'\0'`: the nothing that ends a string

`'\0'` is a `char` with value zero. C strings use it as a terminator, so a string literal is always one byte longer than it looks, and `strlen` stops at the first one it meets. A `std::string` is different: it knows its own length, so it can hold a `'\0'` in the middle.

![A cursor scanning the characters of a C string and stopping at the NUL terminator](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/30.%20fig-nul.svg)

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    char word[] = "hi";
    cout << "sizeof(word) of \"hi\"                 -> " << sizeof word << "  (h, i and a hidden '\\0')\n";
    cout << "strlen(word)                         -> " << strlen(word) << "  (counting stops at '\\0')\n";

    string withHole("a\0b", 3);
    cout << "std::string(\"a\\0b\", 3).size()        -> " << withHole.size() << "  (std::string keeps the '\\0' inside)\n";
    cout << "strlen(withHole.c_str())             -> " << strlen(withHole.c_str()) << "  (C functions stop at the first '\\0')\n";
}
```

```text
sizeof(word) of "hi"                 -> 3  (h, i and a hidden '\0')
strlen(word)                         -> 2  (counting stops at '\0')
std::string("a\0b", 3).size()        -> 3  (std::string keeps the '\0' inside)
strlen(withHole.c_str())             -> 1  (C functions stop at the first '\0')
```

## `nullopt`: nothing that says so

Before `std::optional`, "no result" was a sentinel: `-1`, `INT_MIN`, an empty string. A sentinel is a real value that you must remember to exclude. `std::nullopt` makes the absence part of the type. C++23 also lets you chain on it with `transform`, so "nothing in" simply means "nothing out":

![Animation of two values moving through an optional chain, one with a value and one with nullopt](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/31.%20fig-optional.svg)

```cpp
#include<bits/stdc++.h>
using namespace std;

optional<int> findFirstOne(const string& bits) {
    auto position = bits.find('1');
    if (position == string::npos) return nullopt;
    return static_cast<int>(position);
}

struct Settings { explicit Settings(int) {} };   // has no default constructor

int main() {
    for (const string bits : {"0100", "000"}) {
        optional<int> position = findFirstOne(bits);
        cout << left << setw(31) << ("findFirstOne(\"" + bits + "\")") << "-> ";
        if (position) cout << "found at index " << *position << '\n';
        else          cout << "nullopt, no '1' in this string\n";

        int oneBased = position.transform([](int index) { return index + 1; }).value_or(-1);
        cout << left << setw(31) << "  .transform(+1).value_or(-1)" << "-> " << oneBased << '\n';
    }

    variant<monostate, Settings> choice;   // monostate lets the variant start out empty
    cout << "variant<monostate, Settings> starts at index " << choice.index() << "  (monostate = nothing yet)\n";
}
```

```text
findFirstOne("0100")           -> found at index 1
  .transform(+1).value_or(-1)  -> 2
findFirstOne("000")            -> nullopt, no '1' in this string
  .transform(+1).value_or(-1)  -> -1
variant<monostate, Settings> starts at index 0  (monostate = nothing yet)
```

The last two lines of the program show `std::monostate`, a cousin of `nullopt`: an empty type that lets a `std::variant` start out empty when none of its other types can be default-constructed.

## `npos`: nothing as the biggest number

`std::string::npos` is `static_cast<size_t>(-1)`, the largest possible unsigned value. `find` returns it to mean "not found". The same unsigned wrap-around bites when you subtract from a `size()`, because `size()` is unsigned too:

![Bar chart showing values.size() - 1 wrapping to 18446744073709551615 for an empty vector](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/32.%20fig-npos.svg)

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    const string letters = "abc";
    cout << boolalpha;
    cout << "\"abc\".find('b')                 -> " << letters.find('b') << "  (found at index 1)\n";
    cout << "\"abc\".find('x') == string::npos -> " << (letters.find('x') == string::npos) << "  (not found)\n";
    cout << "string::npos                    -> " << string::npos << "  (the biggest size_t)\n";
    cout << "\"abc\".contains('b')             -> " << letters.contains('b') << "  (C++23: plain yes or no)\n";

    vector<int> values;   // empty
    cout << "values.size() - 1               -> " << values.size() - 1 << "  (unsigned wrap-around)\n";
    cout << "ssize(values) - 1               -> " << ssize(values) - 1 << "  (signed size, correct)\n";
}
```

```text
"abc".find('b')                 -> 1  (found at index 1)
"abc".find('x') == string::npos -> true  (not found)
string::npos                    -> 18446744073709551615  (the biggest size_t)
"abc".contains('b')             -> true  (C++23: plain yes or no)
values.size() - 1               -> 18446744073709551615  (unsigned wrap-around)
ssize(values) - 1               -> -1  (signed size, correct)
```

## Cheat sheet

| Term | Type | Use it for |
|---|---|---|
| `0` | `int` | Neutral value, dummy ternary branch |
| `NULL` | macro (integer-like on GCC) | Legacy C code only |
| `nullptr` | `std::nullptr_t` | Any null pointer |
| `void()` | `void` | Discarding a result, matching a `void` branch |
| `'\0'` | `char` | Ending a C string |
| `nullopt` | `std::nullopt_t` | "No value" without a sentinel |
| `npos` | `size_t` | "Not found" from string searches |

Pick the nothing whose **type** matches what the code around it expects. That is the whole trick.
