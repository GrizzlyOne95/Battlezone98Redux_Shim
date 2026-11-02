#include "embedded_lan_model.h"
#include "lan_no_auth_policy.h"
#include <algorithm>
#include <limits>
#include <chrono>
#include <ctime>

namespace BZROpenShim::EmbeddedLan
{
bool JsonDepthWithin(const std::string& text, unsigned maxDepth)
{
    unsigned depth = 0; bool inString = false, escaped = false;
    for (const char ch : text)
    {
        if (inString)
        {
            if (escaped) escaped = false;
            else if (ch == '\\') escaped = true;
            else if (ch == '"') inString = false;
        }
        else if (ch == '"') inString = true;
        else if (ch == '[' || ch == '{') { if (++depth > maxDepth) return false; }
        else if ((ch == ']' || ch == '}') && depth) --depth;
    }
    return true;
}
Json ParseBounded(const std::string& text)
{
    // Later copies and dump() recurse; reject deep nesting before parsing.
    if (!JsonDepthWithin(text,32)) return Json(Json::value_t::discarded);
    return Json::parse(text,nullptr,false);
}
namespace
{
    std::string Timestamp(bool iso)
    {
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm utc{};
#ifdef _WIN32
        gmtime_s(&utc,&now);
#else
        gmtime_r(&now,&utc);
#endif
        char text[32]{};
        std::strftime(text,sizeof(text),iso ? "%Y-%m-%dT%H:%M:%S.000Z" : "%Y-%m-%d %H:%M:%S",&utc);
        return text;
    }
    bool MetadataFits(const Json& metadata,const std::string& key,const Json& value)
    {
        auto candidate=metadata; candidate[key]=value;
        return candidate.size()<=64 && candidate.dump().size()<=24576;
    }
    std::string Text(const Json& value)
    {
        return value.is_string() ? value.get<std::string>() : value.dump();
    }
    bool LocalId(const std::string& id)
    {
        if (id.size() < 2 || id.size() > 21 || id.front() != 'B' || id[1]=='0') return false;
        uint64_t value = 0;
        for (size_t i = 1; i < id.size(); ++i)
        {
            if (id[i] < '0' || id[i] > '9') return false;
            const unsigned digit = unsigned(id[i] - '0');
            if (value > ((std::numeric_limits<uint64_t>::max)() - digit) / 10) return false;
            value = value * 10 + digit;
        }
        return value != 0;
    }
    bool Printable(const std::string& s, size_t max)
    {
        return !s.empty() && s.size() <= max && std::all_of(s.begin(), s.end(),
            [](unsigned char c) { return c >= 32 && c != 127; });
    }
    Json ObservedAddresses(const Json& values,const std::string& ip)
    {
        Json addresses=Json::array();
        if (!values.is_array() || values.size()>32) return addresses;
        for (const auto& item:values)
        {
            if (!item.is_string()) continue;
            const auto value=item.get<std::string>();
            const auto split=value.find_last_of(':');
            std::string canonical;
            if (split==std::string::npos || !LanNoAuth::PrivateEndpoint(ip+value.substr(split),canonical)) continue;
            if (std::find(addresses.begin(),addresses.end(),Json(canonical))==addresses.end()) addresses.push_back(canonical);
        }
        return addresses;
    }
}
Model::Model()
{
    // Redux joins this canonical chat room before showing/creating games.
    // It is owned by the session host, survives empty membership, and has no
    // synthetic player identity or account behind it.
    Lobby lounge; lounge.id=1; lounge.chat=true; lounge.created=Timestamp(true);
    lounge.metadata={{"name","~chat~pub~~default"},{"gameType","1"},
        {"gameSettings","*"},{"GameVersion","2.2.301"},{"userPack",""}};
    lobbies.emplace(1,std::move(lounge));
}
void Model::Connect(uint64_t c, const std::string& ip)
{
    if (players.size() >= 16 || players.count(c)) return;
    std::string endpoint;
    if (!LanNoAuth::PrivateEndpoint(ip, endpoint)) return;
    players[c].ip = ip;
}
bool Model::Admitted(uint64_t c) const
{
    const auto it=players.find(c);
    return it!=players.end() && !it->second.id.empty();
}
Json Model::User(const Player& p) const
{
    return {{"id",p.id},{"userId",p.id},{"name",p.name},{"realname",p.name},
        {"playerName",p.name},{"authType","lan"},{"clientVersion","2.2.301"},
        {"inLounge",p.lobby < 0},{"isInLounge",p.lobby < 0},{"isAdmin",false},
        {"isAuth",true},{"isBB",false},{"lobby",p.lobby},{"ipAddress",p.ip},
        {"wanAddress",p.wan},{"lanAddresses",p.addresses},{"metadata",p.metadata}};
}
Json Model::Room(const Lobby& l) const
{
    Json users = Json::object();
    for (const auto& entry : players)
        if (!entry.second.id.empty() && entry.second.lobby == l.id)
            users[entry.second.id] = User(entry.second);
    Json metadata = l.metadata;
    metadata["userCount"] = std::to_string(users.size());
    return {{"id",l.id},{"lobbyId",l.id},{"owner",l.owner},{"memberLimit",l.limit},
        {"userCount",users.size()},{"isPrivate",l.privateRoom},{"isLocked",l.locked},
        {"isChat",l.chat},{"name",metadata.value("name",std::string{})},
        {"clientVersion","2.2.301"},{"createdTime",l.created},
        {"metadata",metadata},{"users",users}};
}
Json Model::List() const
{
    Json rooms = Json::object();
    for (const auto& entry : lobbies) rooms[std::to_string(entry.first)] = Room(entry.second);
    return {{"lobbies",rooms},{"totalUsers",players.size()}};
}
void Model::Send(std::vector<Delivery>& out, uint64_t c, const std::string& type, Json data) const
{
    if (data.is_object())
    {
        data["type"] = type;
        data["time"] = Timestamp(false);
        if (!data.contains("success")) data["success"] = true;
    }
    out.push_back({c,{{"type",type},{"data",std::move(data)}}});
}
void Model::Broadcast(std::vector<Delivery>& out, const std::string& type, const Json& data) const
{
    for (const auto& entry : players)
        if (!entry.second.id.empty()) Send(out,entry.first,type,data);
}
void Model::Refresh(std::vector<Delivery>& out)
{
    refreshPending = false;
    Broadcast(out,"OnLobbyListChanged",List());
    for (const auto& entry : lobbies)
        Broadcast(out,"OnLobbyChanged",{{"lobbies",{{std::to_string(entry.first),Room(entry.second)}}},
            {"totalUsers",players.size()}});
}
void Model::Leave(std::vector<Delivery>& out, Player& p)
{
    const int id = p.lobby; p.lobby = -1; p.metadata = Json::object();
    auto it = lobbies.find(id);
    if (it == lobbies.end()) return;
    Broadcast(out,"OnLobbyMemberListChanged",{{"lobbyId",id},{"member",p.id},{"id",p.id},{"removed",true}});
    if (id==1) return;
    // No host migration: leaving the owner ends that game room visibly.
    if (it->second.owner == p.id || Room(it->second)["users"].empty())
    {
        for (auto& entry : players) if (entry.second.lobby == id)
        { entry.second.lobby = -1; entry.second.metadata = Json::object(); }
        lobbies.erase(it);
        Broadcast(out,"OnLobbyRemoved",{{"id",id}});
    }
}
std::vector<Delivery> Model::Disconnect(uint64_t c)
{
    std::vector<Delivery> out;
    auto it = players.find(c);
    if (it != players.end())
    {
        const auto id=it->second.id;
        Leave(out,it->second); players.erase(it);
        auto& lounge=lobbies.at(1);
        if (lounge.owner==id)
        {
            lounge.owner.clear();
            for (const auto& peer:players) if (!peer.second.id.empty()) {lounge.owner=peer.second.id;break;}
        }
        refreshPending = true;
    }
    return out;
}
std::vector<Delivery> Model::Flush()
{
    std::vector<Delivery> out;
    if (refreshPending) Refresh(out);
    return out;
}
std::vector<Delivery> Model::Receive(uint64_t c, const Json& message)
{
    std::vector<Delivery> out;
    auto it = players.find(c);
    if (it == players.end() || !message.is_object()) return out;
    try
    {
        auto& p = it->second;
        const auto type = message.value("type",std::string{});
        const Json content = message.value("content",Json::object());
        if (type == "Authorization")
        {
            if (!p.id.empty() || !content.is_object()) return out;
            const auto id = content.value("id",std::string{});
            const auto name = content.value("name",std::string{});
            bool valid = LocalId(id) && Printable(name,127) && content.value("authtype",std::string{}) == "lan" &&
                content.value("clientVersion",std::string{}) == "2.2.301";
            for (const auto& peer : players) if (peer.second.id == id) valid = false;
            for (const char* key : {"steamAppTicket","gogAppTicket","authTicket","platformTicket"})
                if (content.contains(key) && Text(content[key]) != "") valid = false;
            if (!valid) { Send(out,c,"OnAuthorization",{{"success",false}}); return out; }
            // Redux publishes endpoints in the initial Authorization and only
            // sends DoUpdate* when they change. Dropping the initial values
            // leaves an admitted room with no gameplay route indefinitely.
            const auto addresses=ObservedAddresses(content.value("lanAddresses",Json::array()),p.ip);
            const auto wan=ObservedAddresses(Json::array({content.value("wanAddress",Json{})}),p.ip);
            p.id = id; p.name = name;
            p.addresses=addresses;
            if (!wan.empty()) p.wan=wan[0].get<std::string>();
            if (lobbies.at(1).owner.empty()) lobbies.at(1).owner=id;
            auto admission=User(p);
            admission["user"]=User(p);
            admission["member"]=p.name;
            Send(out,c,"OnAuthorization",std::move(admission));
            Send(out,c,"OnWhitelistUpdated",{{"whitelist",{{"list",{"*.wav","*.ogg","*.ini","*.inf","*.jpg","*.txt","*.stb","*.des","*.dds","*.png","*.sta","*mod.material"}},{"major",8},{"minor",0}}}});
            Send(out,c,"OnRelayUpdated",{{"enabled",false}});
            Refresh(out); return out;
        }
        if (p.id.empty()) return out;
        if (type == "DoEnterLounge")
        { Send(out,c,"OnDoEnterLounge",Json::object()); Send(out,c,"OnLobbyListChanged",List()); return out; }
        if (type == "GetLobbyList")
        { Send(out,c,"OnLobbyList",List()); Send(out,c,"OnGetLobbyList",List()); return out; }
        if (type == "CreateGame" || type == "CreateLobby")
        {
            if (!content.is_object() || lobbies.size() >= 17) return out;
            Lobby room; room.owner = p.id; room.chat = type == "CreateLobby";
            room.limit = (std::clamp)(content.value("memberLimit",16),1,16);
            room.password = content.value("password",std::string{});
            room.privateRoom=content.value("isPrivate",false) || !room.password.empty();
            if (room.password.size() > 127) return out;
            auto name = content.value("name",p.name);
            if (!Printable(name,256)) return out;
            Leave(out,p);
            room.id = nextLobby++; room.created=Timestamp(true);
            if (name.front() != '~') name = std::string(room.chat ? "~chat~pub~~" : "~game~pub~~") + name;
            room.metadata = {{"name",name},{"GameVersion","2.2.301"},{"clientVersion","2.2.301"},
                {"gameType","1"},{"gameSettings","*"},{"ready","*"},{"nextmid","1"}};
            p.lobby = room.id; lobbies.emplace(room.id,room);
            Refresh(out); // cache must arrive before OnLobbyCreated (immediate, not coalesced)
            Send(out,c,"OnLobbyCreated",{{"id",room.id}}); return out;
        }
        if (type == "DoJoinLobby")
        {
            const int id = content.value("id",-1);
            auto room = lobbies.find(id);
            if (room!=lobbies.end() && p.lobby==id)
            { Send(out,c,"OnLobbyJoined",{{"id",id},{"reasonCode",0}}); return out; }
            int reason = room == lobbies.end() ? 1 : room->second.locked ? 2 :
                int(Room(room->second)["users"].size()) >= room->second.limit ? 3 :
                room->second.password != content.value("password",std::string{}) ? 4 : 0;
            if (reason) { Send(out,c,"OnLobbyJoined",{{"success",false},{"id",id},{"reasonCode",reason}}); return out; }
            if (p.lobby == id) { Send(out,c,"OnLobbyJoined",{{"id",id},{"reasonCode",0}}); return out; }
            Leave(out,p); p.lobby = id;
            Refresh(out); // immediate: cache precedes the join acknowledgement
            Broadcast(out,"OnLobbyMemberListChanged",{{"lobbyId",id},{"id",p.id},{"member",p.id},{"removed",false},{"user",User(p)}});
            Send(out,c,"OnLobbyJoined",{{"id",id},{"reasonCode",0}}); return out;
        }
        if (type == "DoExitLobby") { Leave(out,p); Refresh(out); Send(out,c,"OnDoExitLobby",Json::object()); return out; }
        auto room = lobbies.find(p.lobby);
        if (type == "DoUpdateLAN" || type == "DoUpdateWAN")
        {
            Json values = content;
            if (content.is_object()) values = content.value(type == "DoUpdateLAN" ? "lanAddresses" : "wanAddress",Json{});
            if (type == "DoUpdateWAN") values = Json::array({values});
            if (!values.is_array() || values.size() > 32) return out;
            const auto addresses=ObservedAddresses(values,p.ip);
            if (type == "DoUpdateLAN") p.addresses = addresses;
            else if (!addresses.empty()) p.wan = addresses[0].get<std::string>();
            const auto user = User(p);
            Broadcast(out,type == "DoUpdateLAN" ? "OnLANUpdated" : "OnWANUpdated",
                {{"id",p.id},{"member",p.id},{"player",p.id},{"lanAddresses",p.addresses},{"wanAddress",p.wan},
                 {"user",user},{"users",{{p.id,user}}}});
            refreshPending = true; return out;
        }
        if (type == "SetPlayerData" && content.is_object())
        {
            const auto key = content.value("key",std::string{});
            const auto value = Text(content.value("value",Json{}));
            if (!Printable(key,64) || value.size() > 16384 || !MetadataFits(p.metadata,key,value)) return out;
            p.metadata[key] = value;
            if ((key == "name" || key == "playerName") && Printable(value,127)) p.name = value;
            refreshPending = true;
            Broadcast(out,"OnUserDataChanged",{{"member",p.id},{"id",p.id},{"lobbyId",p.lobby},{"users",{{p.id,User(p)}}}});
            if (room != lobbies.end()) Broadcast(out,"OnLobbyDataChanged",{{"changedLobby",room->first}});
            return out;
        }
        if (room == lobbies.end()) return out;
        auto& l = room->second;
        if ((type == "SetLobbyData" || type == "DeleteLobbyData") && l.owner == p.id && content.is_object())
        {
            const auto key = content.value("key",std::string{});
            const auto value = Text(content.value("value",Json{}));
            if (!Printable(key,64) || value.size() > 16384 || !MetadataFits(l.metadata,key,value)) return out;
            if (type == "SetLobbyData") l.metadata[key] = value; else l.metadata.erase(key);
            Broadcast(out,"OnLobbyDataChanged",{{"changedLobby",l.id},{"key",key},{"value",value}});
            refreshPending = true;
        }
        else if (type == "LockLobby" && l.owner == p.id && content.is_boolean()) { l.locked = content.get<bool>(); refreshPending = true; }
        else if (type == "SetLobbyMemberLimit" && l.owner == p.id && content.is_number_integer())
        { l.limit = (std::clamp)(content.get<int>(),1,16); refreshPending = true; }
        else if (type == "DoSendChat")
        {
            const auto text = content.is_object() ? content.value("text",std::string{}) : Text(content);
            if (Printable(text,1024))
                for (const auto& peer : players) if (peer.second.lobby == l.id)
                    Send(out,peer.first,"OnChatMessage",{{"speakerId",p.id},{"author",p.name},{"text",text},{"lobbyId",l.id},{"isChat",l.chat}});
        }
        else if (type == "DoP2PRoute")
        {
            const auto target=content.is_object() ? content.value("player",std::string{}) : Text(content);
            Send(out,c,"OnLobbyMemberP2PConnect",{{"success",false},{"connect",false},
                {"reset",false},{"player",target},{"lobbyId",l.id},{"relayEnabled",false}});
        }
        else if (type == "DoP2PConnect")
        {
            const auto target = content.is_object() ? content.value("player",std::string{}) : Text(content);
            for (const auto& peer : players) if (peer.second.id == target && peer.second.lobby == l.id)
            {
                const bool reset = content.is_object() && content.value("reset",false);
                Send(out,peer.first,"OnLobbyMemberP2PConnect",{{"player",p.id},{"member",p.id},{"lobbyId",l.id},{"connect",true},{"reset",reset},{"users",{{p.id,User(p)}}}});
                Send(out,c,"OnLobbyMemberP2PConnect",{{"player",target},{"member",target},{"lobbyId",l.id},{"connect",true},{"reset",reset},{"users",{{target,User(peer.second)}}}});
                break;
            }
            // No relay is advertised. Gameplay must use the direct LAN path.
        }
    }
    catch (const Json::exception&) { /* malformed remote input changes no native state */ }
    return out;
}
}
