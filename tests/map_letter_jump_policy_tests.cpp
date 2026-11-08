#include "map_letter_jump_policy.h"
#include "test_check.h"

using namespace BZROpenShim::MapLetterJump;
using OpenShimTest::Check;
using OpenShimTest::ExitCode;

int main()
{
    const char* const titles[] = { "Achilles", "Bravo", "alpine", "Crater", "Arena", "delta" };
    const size_t count = sizeof(titles) / sizeof(titles[0]);

    Check(LetterFromControlCode(0x01) == 'a' && LetterFromControlCode(0x1A) == 'z' &&
              LetterFromControlCode(0x03) == 'c',
          "control codes map to letters");
    Check(LetterFromControlCode(0x00) == 0 && LetterFromControlCode(0x1B) == 0 &&
              LetterFromControlCode('a') == 0 && LetterFromControlCode(0x7F) == 0,
          "other characters map to nothing");

    Check(FindNextByLetter(titles, count, 0, 'a') == 2, "next match starts after the current row");
    Check(FindNextByLetter(titles, count, 2, 'a') == 4, "continues down the list");
    Check(FindNextByLetter(titles, count, 4, 'a') == 0, "wraps past the end to the top");
    Check(FindNextByLetter(titles, count, 5, 'b') == 1, "wraps from the last row");
    Check(FindNextByLetter(titles, count, 1, 'b') == 1, "the current row is the sole match");

    Check(FindNextByLetter(titles, count, 0, 'A') == 2, "an upper-case letter matches");
    Check(FindNextByLetter(titles, count, 3, 'D') == 5, "an upper-case letter matches lower-case titles");
    Check(FindNextByLetter(titles, count, 0, 'c') == 3, "a lower-case letter matches upper-case titles");

    Check(FindNextByLetter(titles, count, 0, 'z') == -1, "no match");
    Check(FindNextByLetter(titles, count, 0, 0) == -1, "no letter");
    Check(FindNextByLetter(titles, 0, -1, 'a') == -1, "empty list");
    Check(FindNextByLetter(nullptr, 3, 0, 'a') == -1, "null list");

    Check(FindNextByLetter(titles, count, -1, 'a') == 0, "no selection starts at the top");
    Check(FindNextByLetter(titles, count, 99, 'a') == 0, "a selection past the end starts at the top");
    Check(FindNextByLetter(titles, count, static_cast<int>(count), 'b') == 1,
          "a selection at count starts at the top");

    const char* const holes[] = { nullptr, "", "Echo", "echo2" };
    Check(FindNextByLetter(holes, 4, 0, 'e') == 2, "null and empty titles are skipped");
    Check(FindNextByLetter(holes, 4, 3, 'e') == 2, "wraps over skipped titles");

    return ExitCode();
}
