// The published SDK contract, checked as text.
//
// docs/OPENSHIM_SDK_V2.md tells companion DLLs to find OpenShim through
// GetModuleHandleA("winmm.dll") + GetProcAddress, so the set of OpenShim*
// names winmm.dll exports is a public ABI. Three artefacts have to agree
// about it forever:
//
//   src/winmm.def                    what the linker exports
//   include/openshim_sdk_exports.inc what the thunks and provider table define
//   tests/winmm_export_baseline.txt  what a shipped winmm.dll actually exported
//
// This runs on the Linux lane -- it reads the repository, not a binary. The
// Windows workflow additionally dumpbins the built DLL against the same
// baseline, which is what catches a decoration or calling-convention change
// that text alone cannot see.

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const std::string& what)
    {
        if (condition) return;
        std::printf("FAIL: %s\n", what.c_str());
        ++g_Failures;
    }

    std::string Slurp(const char* path)
    {
        std::ifstream in(path, std::ios::binary);
        if (!in)
        {
            std::printf("FAIL: could not open %s\n", path);
            ++g_Failures;
            return {};
        }
        std::ostringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

    std::string Trim(const std::string& s)
    {
        const size_t b = s.find_first_not_of(" \t\r\n");
        if (b == std::string::npos) return {};
        const size_t e = s.find_last_not_of(" \t\r\n");
        return s.substr(b, e - b + 1);
    }

    // Names the .def exports, restricted to the OpenShim* surface. An alias
    // line ("PlaySound = PlaySoundA") exports the left-hand name.
    std::set<std::string> DefExports(const std::string& text)
    {
        std::set<std::string> out;
        std::istringstream in(text);
        std::string line;
        while (std::getline(in, line))
        {
            const std::string t = Trim(line);
            if (t.rfind("OpenShim", 0) != 0) continue;
            std::string name = t.substr(0, t.find_first_of(" \t="));
            out.insert(name);
        }
        return out;
    }

    // Third macro argument of each OPENSHIM_SDK_EXPORT[_NS] entry.
    std::set<std::string> IncExports(const std::string& text)
    {
        std::set<std::string> out;
        std::istringstream in(text);
        std::string line;
        while (std::getline(in, line))
        {
            const std::string t = Trim(line);
            if (t.rfind("OPENSHIM_SDK_EXPORT", 0) != 0) continue;
            const size_t open = t.find('(');
            if (open == std::string::npos) continue;
            // ret, callconv, name, ...
            std::vector<std::string> fields;
            size_t start = open + 1;
            int depth = 0;
            for (size_t i = open + 1; i < t.size() && fields.size() < 3; ++i)
            {
                const char c = t[i];
                if (c == '(') ++depth;
                else if (c == ')') --depth;
                if (c == ',' && depth == 0)
                {
                    fields.push_back(Trim(t.substr(start, i - start)));
                    start = i + 1;
                }
            }
            if (fields.size() >= 3) out.insert(fields[2]);
        }
        return out;
    }

    // OpenShim*-shaped exports that deliberately have no winmm.def entry and
    // no thunk, because they are not part of the published SDK:
    //
    //   OpenShimSetWalkerCase / OpenShimWalkerTraceSummary
    //       __declspec(dllexport) debug hooks in walker_cockpit_trace.cpp.
    //       They leave the export table when that file moves to the plugin.
    //   OpenShimSdkProvider_GetTable
    //       the bridge's own plumbing -- how the bootstrap fetches the
    //       provider table from plugins/openshim.dll. It is infrastructure,
    //       not API, and it must never be thunked through itself.
    bool IsNotDefExported(const std::string& name)
    {
        return name == "OpenShimSetWalkerCase" ||
               name == "OpenShimWalkerTraceSummary" ||
               name == "OpenShimSdkProvider_GetTable" ||
               name == "OpenShimBootstrap_GetApi";
    }

    std::set<std::string> BaselineOpenShimExports(const std::string& text)
    {
        std::set<std::string> out;
        std::istringstream in(text);
        std::string line;
        while (std::getline(in, line))
        {
            std::string t = Trim(line);
            if (t.rfind("OpenShim", 0) != 0) continue;
            // Baseline entries carry the __stdcall stack size ("name@4").
            // Names are what the .def can be compared against; the stack
            // sizes are checked against the real binary on the Windows lane.
            const size_t at = t.find('@');
            if (at != std::string::npos) t = t.substr(0, at);
            if (IsNotDefExported(t)) continue;
            out.insert(t);
        }
        return out;
    }

    void ReportDifference(const char* label,
                          const std::set<std::string>& a,
                          const std::set<std::string>& b)
    {
        std::vector<std::string> only;
        std::set_difference(a.begin(), a.end(), b.begin(), b.end(),
                            std::back_inserter(only));
        for (const auto& n : only)
        {
            std::printf("FAIL: %s: %s\n", label, n.c_str());
            ++g_Failures;
        }
    }
}

int main()
{
    const std::set<std::string> def = DefExports(Slurp(BZR_WINMM_DEF));
    const std::set<std::string> inc = IncExports(Slurp(BZR_SDK_EXPORTS_INC));
    const std::set<std::string> baseline =
        BaselineOpenShimExports(Slurp(BZR_EXPORT_BASELINE));

    Check(!def.empty(), "winmm.def lists OpenShim exports");
    Check(!inc.empty(), "openshim_sdk_exports.inc lists exports");
    Check(!baseline.empty(), "the export baseline lists OpenShim exports");

    // Every exported name must have exactly one thunk, and every thunk must
    // correspond to an exported name. A thunk without a .def entry is dead
    // code; a .def entry without a thunk is an unresolved external.
    ReportDifference("exported in winmm.def but no thunk in openshim_sdk_exports.inc",
                     def, inc);
    ReportDifference("thunk in openshim_sdk_exports.inc but not exported by winmm.def",
                     inc, def);

    // The baseline is what a built winmm.dll really exported before the
    // implementations moved behind the bridge. Losing one of these breaks
    // Extra Utilities and anything else resolving against winmm.dll.
    ReportDifference("present in the shipped export baseline but dropped from winmm.def",
                     baseline, def);

    if (g_Failures != 0)
    {
        std::printf("openshim sdk export contract tests FAILED (%d)\n", g_Failures);
        return 1;
    }
    std::printf("openshim sdk export contract tests passed (%zu exports)\n",
                def.size());
    return 0;
}
