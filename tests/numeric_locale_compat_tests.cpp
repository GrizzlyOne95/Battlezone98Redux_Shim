#include "numeric_locale_compat.h"

#include <clocale>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

namespace
{
    bool SelectFirstLocale(const char* const* candidates, size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (std::setlocale(LC_ALL, candidates[i]))
                return true;
        }
        return false;
    }

    bool DotDecimalParsesFully()
    {
        char* end = nullptr;
        const float value = std::strtof("0.8", &end);
        return end && *end == '\0' && std::fabs(value - 0.8f) < 0.00001f;
    }
}

int main()
{
    const char* originalPointer = std::setlocale(LC_ALL, nullptr);
    const std::string original = originalPointer ? originalPointer : "C";

    const char* const englishCandidates[] = { "English", "English_United States.1252", "C" };
    if (!SelectFirstLocale(englishCandidates, std::size(englishCandidates)) ||
        !BZROpenShim::EnforceCNumericLocale(std::setlocale) || !DotDecimalParsesFully())
    {
        std::cerr << "English/C dot-decimal compatibility probe failed\n";
        std::setlocale(LC_ALL, original.c_str());
        return EXIT_FAILURE;
    }
    std::cout << "English probe: LC_NUMERIC=C parses 0.8 exactly\n";

    const char* const germanCandidates[] = {
        "German", "German_Germany.1252", "de-DE", "de_DE.UTF-8", "de_DE"
    };
    if (!SelectFirstLocale(germanCandidates, std::size(germanCandidates)))
    {
        // No German locale installed (common on minimal Linux CI images).
        // The German compatibility probe cannot run without one, so report a
        // clean SKIP rather than failing the whole suite: the English/C probe
        // above is the primary compatibility target and always runs, and the
        // German path is still fully validated on any system that does have a
        // German locale installed.
        std::cout << "SKIP: no German locale installed; German compatibility probe not run\n";
        std::setlocale(LC_ALL, original.c_str());
        return EXIT_SUCCESS;
    }

    const char* ctypePointer = std::setlocale(LC_CTYPE, nullptr);
    const char* timePointer = std::setlocale(LC_TIME, nullptr);
    const std::string ctypeBefore = ctypePointer ? ctypePointer : "";
    const std::string timeBefore = timePointer ? timePointer : "";
    const char decimalBefore = std::localeconv() && std::localeconv()->decimal_point
        ? std::localeconv()->decimal_point[0] : '\0';

    const bool applied = BZROpenShim::EnforceCNumericLocale(std::setlocale);
    const char* ctypeAfterPointer = std::setlocale(LC_CTYPE, nullptr);
    const char* timeAfterPointer = std::setlocale(LC_TIME, nullptr);
    const bool presentationPreserved = ctypeBefore == (ctypeAfterPointer ? ctypeAfterPointer : "") &&
        timeBefore == (timeAfterPointer ? timeAfterPointer : "");
    const bool passed = decimalBefore == ',' && applied && presentationPreserved && DotDecimalParsesFully();

    const char* numericAfter = std::setlocale(LC_NUMERIC, nullptr);
    std::cout << "German probe: decimal-before=" << decimalBefore
              << " LC_NUMERIC=" << (numericAfter ? numericAfter : "<null>")
              << " presentation-categories-preserved=" << (presentationPreserved ? "yes" : "no")
              << '\n';
    std::setlocale(LC_ALL, original.c_str());
    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
