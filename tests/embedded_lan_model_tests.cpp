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
    {
        // Updates coalesce: a burst yields exactly one refresh at flush time.
        m.Flush(); // drain earlier pending refreshes
        const auto lock=m.Receive(1,Message("LockLobby",true));
        CHECK(!Has(lock,"OnLobbyChanged"));
        for (int i=0;i<5;++i) m.Receive(2,Message("SetPlayerData",{{"key","ready"},{"value",std::to_string(i)}}));
        const auto flushed=m.Flush();
        const auto lists=std::count_if(flushed.begin(),flushed.end(),[](const Delivery& d){return d.connection==1 && d.message["type"]=="OnLobbyListChanged";});
        CHECK(lists==1);
        CHECK(Has(flushed,"OnLobbyChanged"));
        CHECK(m.Flush().empty());
    }
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
    // Steam bridge admission: only the Steam id the bridge authenticated.
    {
        Model steam;
        const Admission bridged{"S76561198000000001",false}, host{"S76561198000000002",true};
        steam.Connect(1,"127.0.1.1",bridged); steam.Connect(2,"127.0.1.2",bridged);
        steam.Connect(3,"127.0.0.1",host); steam.Connect(4,"127.0.1.4",{"X1",false});
        auto as=[](const char* id,const char* type){ auto a=Auth(id); a["content"]["authtype"]=type; a["content"]["steamAppTicket"]="ticket"; return a; };
        CHECK(Has(steam.Receive(1,as("S76561198000000009","steam")),"OnAuthorization",false)); // another id
        CHECK(Has(steam.Receive(1,Auth("B1")),"OnAuthorization",false)); // bridged: no LAN login
        CHECK(steam.Receive(4,as("S76561198000000001","steam")).empty()); // malformed admission never connects
        const auto ok=steam.Receive(1,as("S76561198000000001","steam"));
        CHECK(Has(ok,"OnAuthorization"));
        CHECK(std::any_of(ok.begin(),ok.end(),[](const Delivery& d){return d.message.dump().find("\"authType\":\"steam\"")!=std::string::npos;}));
        CHECK(std::none_of(ok.begin(),ok.end(),[](const Delivery& d){return d.message.dump().find("ticket")!=std::string::npos;}));
        CHECK(Has(steam.Receive(2,as("S76561198000000001","steam")),"OnAuthorization",false)); // same id twice
        CHECK(Has(steam.Receive(3,as("S76561198000000003","steam")),"OnAuthorization",false)); // host, wrong id
        CHECK(Has(steam.Receive(3,as("S76561198000000002","steam")),"OnAuthorization")); // host's own game
        auto lanTicket=Auth("B3"); lanTicket["content"]["steamAppTicket"]="ticket";
        Model lanHost; lanHost.Connect(1,"127.0.0.1",host);
        CHECK(Has(lanHost.Receive(1,lanTicket),"OnAuthorization",false)); // LAN still refuses tickets
        CHECK(Has(lanHost.Receive(1,Auth("B3")),"OnAuthorization"));
        Model plain; plain.Connect(1,"192.168.1.1"); // no admission: LAN logins only
        CHECK(Has(plain.Receive(1,as("S76561198000000002","steam")),"OnAuthorization",false));
    }
    // Deep nesting is rejected before parsing; ordinary messages still parse.
    CHECK(ParseBounded(std::string(30000,'[')+std::string(30000,']')).is_discarded());
    CHECK(ParseBounded("{\"a\":"+std::string(33,'[')+std::string(33,']')+"}").is_discarded());
    CHECK(!ParseBounded("{\"a\":"+std::string(30,'[')+std::string(30,']')+"}").is_discarded());
    CHECK(!ParseBounded("{\"type\":\"DoSendChat\",\"content\":\"[[[[ \\\" {{{{\"}").is_discarded());
    return OpenShimTest::ExitCode();
}
