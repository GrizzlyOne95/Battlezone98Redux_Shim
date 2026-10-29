#include "embedded_lan_model.h"
#include "test_check.h"
#include <algorithm>
using namespace BZROpenShim::EmbeddedLan;
Json Message(const char* type,Json content) { return {{"type",type},{"content",content}}; }
bool Has(const std::vector<Delivery>& out,const char* type,bool success=true)
{
    return std::any_of(out.begin(),out.end(),[&](const Delivery& d){return d.message["type"]==type && d.message["data"].value("success",false)==success;});
}
Json Auth(const char* id) { return Message("Authorization",{{"id",id},{"name","Local Player"},{"clientVersion","2.2.301"},{"authtype","lan"}}); }
int main()
{
    Model m; m.Connect(1,"192.168.1.1"); m.Connect(2,"192.168.1.2"); m.Connect(3,"8.8.8.8");
    CHECK(m.Receive(3,Auth("B3")).empty());
    CHECK(m.Receive(1,Message("CreateGame",Json::object())).empty());
    auto wrong=Auth("S76561198000000000"); CHECK(Has(m.Receive(1,wrong),"OnAuthorization",false));
    wrong=Auth("B1"); wrong["content"]["steamAppTicket"]="ticket"; CHECK(Has(m.Receive(1,wrong),"OnAuthorization",false));
    auto initial=Auth("B1");
    initial["content"]["lanAddresses"]={"8.8.8.8:4567","192.168.8.1:4567"};
    initial["content"]["wanAddress"]="9.9.9.9:4567";
    const auto admitted=m.Receive(1,initial);
    CHECK(Has(admitted,"OnAuthorization"));
    for (const auto& event:admitted) if (event.message["type"]=="OnAuthorization")
    {
        CHECK(event.message["data"]["lanAddresses"]==Json::array({"192.168.1.1:4567"}));
        CHECK(event.message["data"]["wanAddress"]=="192.168.1.1:4567");
    }
    for (const auto& event:admitted) if (event.message["type"]=="OnLobbyListChanged")
    {
        const auto& lounge=event.message["data"]["lobbies"]["1"];
        CHECK(lounge["id"]==1); // Redux treats zero as an invalid lobby ID.
        CHECK(lounge["owner"].is_string() && lounge["owner"]=="B1");
    }
    CHECK(Has(m.Receive(2,Auth("B1")),"OnAuthorization",false));
    CHECK(Has(m.Receive(2,Auth("B2")),"OnAuthorization"));
    CHECK(m.Admitted(1) && m.Admitted(2) && !m.Admitted(3));
    const auto created=m.Receive(1,Message("CreateGame",{{"name","Test"},{"password","secret"},{"memberLimit",2}}));
    CHECK(Has(created,"OnLobbyCreated"));
    auto cache=std::find_if(created.begin(),created.end(),[](const Delivery& d){return d.message["type"]=="OnLobbyChanged";});
    auto ack=std::find_if(created.begin(),created.end(),[](const Delivery& d){return d.message["type"]=="OnLobbyCreated";});
    CHECK(cache<ack);
    // Invalid replacement must not destroy the existing room; repeated joins
    // succeed even after the owner's room is full or locked.
    CHECK(m.Receive(1,Message("CreateGame",{{"name",std::string(257,'x')}})).empty());
    CHECK(Has(m.Receive(2,Message("DoJoinLobby",{{"id",2},{"password","wrong"}})),"OnLobbyJoined",false));
    CHECK(Has(m.Receive(2,Message("DoJoinLobby",{{"id",2},{"password","secret"}})),"OnLobbyJoined"));
    CHECK(Has(m.Receive(1,Message("DoJoinLobby",{{"id",2},{"password","secret"}})),"OnLobbyJoined"));
    CHECK(Has(m.Receive(1,Message("LockLobby",true)),"OnLobbyChanged"));
    CHECK(Has(m.Receive(2,Message("DoJoinLobby",{{"id",2}})),"OnLobbyJoined"));
    CHECK(m.Receive(2,Message("SetLobbyData",{{"key","gameSettings"},{"value","forbidden"}})).empty());
    CHECK(Has(m.Receive(1,Message("SetLobbyData",{{"key","gameSettings"},{"value","map-settings"}})),"OnLobbyDataChanged"));
    CHECK(Has(m.Receive(2,Message("SetPlayerData",{{"key","ready"},{"value","map-settings"}})),"OnUserDataChanged"));
    CHECK(Has(m.Receive(2,Message("DoP2PConnect",{{"player","B1"}})),"OnLobbyMemberP2PConnect"));
    CHECK(Has(m.Receive(2,Message("DoP2PRoute",{{"player","B1"}})),"OnLobbyMemberP2PConnect",false));
    CHECK(Has(m.Receive(1,Message("DoSendChat","hello")),"OnChatMessage"));
    // Bounded total metadata, and canonical local IDs cannot alias each other.
    CHECK(Has(m.Receive(2,Message("SetPlayerData",{{"key","large"},{"value",std::string(15000,'x')}})),"OnUserDataChanged"));
    CHECK(m.Receive(2,Message("SetPlayerData",{{"key","overflow"},{"value",std::string(15000,'x')}})).empty());
    m.Connect(4,"192.168.1.4"); CHECK(Has(m.Receive(4,Auth("B01")),"OnAuthorization",false));
    CHECK(Has(m.Disconnect(1),"OnLobbyRemoved"));
    CHECK(m.Receive(2,Message("DoP2PConnect",{{"player","B1"}})).empty());
    CHECK(m.Receive(2,Message("DoJoinLobby",Json::array())).empty());
    return OpenShimTest::ExitCode();
}
