#include "shell_casing_policy.h"
#include "test_check.h"
using namespace BZROpenShim::ShellCasings;
using OpenShimTest::Check;
int main()
{
    char mesh[128] = {};
    Check(ParseCasingMesh(" \"MyPack/Brass.mesh\" ", mesh) && std::string_view(mesh) == "MyPack/Brass.mesh",
        "explicit resource preserves case");
    Check(ParseCasingMesh("\"\"", mesh) && !mesh[0], "empty selects normal mesh convention");
    for (auto value : {"../brass.mesh", "C:/brass.mesh", "/brass.mesh", "a\\brass.mesh", "brass.sdf", "\"unterminated.mesh", "a.mesh|b"})
        Check(!ParseCasingMesh(value, mesh) && !mesh[0], "reject unsafe/malformed resource");
    char longName[130] = {};
    for (int i = 0; i < 124; ++i) longName[i] = 'a';
    Check(!ParseCasingMesh(longName, mesh), "never truncate an explicit resource");
    Check(ParseCasingType(" \"small\"\r\n") == CasingType::Small, "quoted small");
    Check(ParseCasingType("medium") == CasingType::Medium, "medium");
    Check(ParseCasingType("large") == CasingType::Large, "large");
    for (auto value : {"none", "", "plasma", "auto", "small garbage", "\"small", "LARGE"})
        Check(ParseCasingType(value) == CasingType::None, "invalid/none is disabled");
    Check(StockCasingType("gminigun") == CasingType::Small, "minigun ballistic");
    Check(StockCasingType("GMINIGUN.ODF") == CasingType::Small, "filename normalization");
    Check(StockCasingType("gatstab") == CasingType::Medium, "AT ballistic");
    Check(StockCasingType("gspstab") == CasingType::Large, "SP ballistic");
    for (auto odf : {"gblast", "gbolt", "asplsmg", "gtechno", "ghornet", "newmod"})
        Check(StockCasingType(odf) == CasingType::None, "no energy/missile/unknown brass");
    Check(CasingTypeLength(CasingType::None) == 0, "disabled length");
    Check(CasingTypeLength(CasingType::Small) < CasingTypeLength(CasingType::Medium) &&
        CasingTypeLength(CasingType::Medium) < CasingTypeLength(CasingType::Large), "ordered sizes");
}
