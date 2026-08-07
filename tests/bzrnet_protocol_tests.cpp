#include "bzrnet_protocol.h"

#include <cstdio>
#include <string>

using namespace BZROpenShim;

namespace
{
    int g_Checks = 0;
    int g_Failures = 0;
    void Check(bool value, const char* name)
    {
        ++g_Checks;
        if (value) return;
        ++g_Failures;
        std::printf("FAIL %s\n", name);
    }
}

int main()
{
    std::string type;
    Check(ExtractBzrNetMessageType(R"({"type":"Authorization","content":{"x":1}})", type) && type == "Authorization", "type extraction");
    Check(LookupBzrNetMessage("OnP2PRoute") && LookupBzrNetMessage("OnP2PRoute")->evidence == BzrNetEvidence::BinaryConfirmed, "registry evidence");

    int64_t reason = -1;
    Check(TryExtractBzrNetJsonInt(R"({"data":{"reasonCode":5}})", "reasonCode", reason) && reason == 5, "nested integer");
    bool success = true;
    Check(TryExtractBzrNetJsonBool(R"({"data":{"success":false}})", "success", success) && !success, "nested bool");

    ResetBzrNetSanitizationAliases();
    auto safe = SanitizeBzrNetJson(
        R"({"type":"Authorization","content":{"steamAppTicket":"SECRET","password":"pw","userId":"abc","name":"Alice","wanAddress":"1.2.3.4","lanAddresses":["10.0.0.1","10.0.0.2"]}})",
        false);
    Check(safe.authTicketRedacted && safe.authTicketLength == 6 && safe.json.find("SECRET") == std::string::npos, "auth ticket redaction");
    Check(safe.passwordRedacted && safe.passwordLength == 2 && safe.json.find("\"pw\"") == std::string::npos, "password redaction");
    Check(safe.json.find("abc") == std::string::npos && safe.json.find("Alice") == std::string::npos, "identity redaction");
    Check(safe.json.find("1.2.3.4") == std::string::npos && safe.json.find("10.0.0.2") == std::string::npos, "endpoint redaction");

    auto repeated = SanitizeBzrNetJson(
        R"({"users":[{"userId":"A","wanAddress":"8.8.8.8","lanAddresses":["10.1.1.1"]},{"userId":"B","wanAddress":"9.9.9.9","lanAddresses":["10.2.2.2"]}]})",
        false);
    Check(repeated.json.find("\"A\"") == std::string::npos && repeated.json.find("\"B\"") == std::string::npos, "all repeated identities redacted");
    Check(repeated.json.find("8.8.8.8") == std::string::npos && repeated.json.find("10.2.2.2") == std::string::npos, "all repeated endpoints redacted");

    auto repeatedSecrets = SanitizeBzrNetJson(
        R"({"type":"Unknown","content":{"steamAppTicket":"FIRST","nested":{"steamAppTicket":"SECOND","password":"one"},"password":"two"}})",
        true);
    Check(
        repeatedSecrets.authTicketRedacted &&
        repeatedSecrets.passwordRedacted &&
        repeatedSecrets.json.find("FIRST") == std::string::npos &&
        repeatedSecrets.json.find("SECOND") == std::string::npos &&
        repeatedSecrets.json.find("\"one\"") == std::string::npos &&
        repeatedSecrets.json.find("\"two\"") == std::string::npos,
        "all repeated secrets redacted");

    const uint8_t pp[] = {'P','P',1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,5,0,0,0};
    const auto udp = DecodeBzrUdpControl(pp, sizeof(pp));
    Check(udp.recognized && udp.marker == "PP" && udp.fieldCount == 5 && udp.field4 == 5, "PP decoder");

    std::printf("%d checks, %d failures\n", g_Checks, g_Failures);
    return g_Failures ? 1 : 0;
}
