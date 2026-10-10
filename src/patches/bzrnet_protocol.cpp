#include "bzrnet_protocol.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <iterator>
#include <charconv>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

namespace BZROpenShim
{
namespace
{
    constexpr std::array<BzrNetMessageInfo, 41> kMessages = {{
        {"Authorization",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoEnterLounge",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoExitLounge",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"CreateLobby",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"CreateGame",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoJoinLobby",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoExitLobby",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoSetLobbyOwner",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"SetLobbyData",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"SetPlayerData",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DeleteLobbyData",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"LockLobby",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"SetLobbyMemberLimit",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoSendChat",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoP2PConnect",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoP2PRoute",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoUpdateWAN",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"DoUpdateLAN",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::BinaryConfirmed,"content"},
        {"Ping",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::Inferred,"content"},
        {"DoPing",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::Inferred,"content"},
        {"DoKickUser",BzrNetMessageDirection::ClientToServer,BzrNetEvidence::Inferred,"content"},
        {"OnAuthorization",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnChatMessage",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnHeartbeat",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnWANUpdated",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLANUpdated",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyMemberListChanged",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyDataChanged",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnUserDataChanged",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyListChanged",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyChanged",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyCreated",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyRemoved",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyJoined",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnDoExitLobby",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnDoExitLounge",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnFailure",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnWhitelistUpdated",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnLobbyMemberP2PConnect",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnP2PRoute",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
        {"OnServerShutdown",BzrNetMessageDirection::ServerToClient,BzrNetEvidence::BinaryConfirmed,"data"},
    }};

    std::mutex g_AliasMutex;
    std::unordered_map<std::string,std::string> g_Identities;
    std::unordered_map<std::string,std::string> g_Endpoints;

    bool Ws(char c) { return c==' '||c=='\t'||c=='\r'||c=='\n'; }
    size_t SkipWs(std::string_view s,size_t p){ while(p<s.size()&&Ws(s[p])) ++p; return p; }

    bool ParseString(std::string_view s,size_t quote,size_t& end,std::string* decoded)
    {
        if(quote>=s.size()||s[quote]!='"') return false;
        std::string out;
        for(size_t i=quote+1;i<s.size();++i)
        {
            char c=s[i];
            if(c=='"'){ end=i+1; if(decoded)*decoded=std::move(out); return true; }
            if(c!='\\'){ out.push_back(c); continue; }
            if(++i>=s.size()) return false;
            switch(s[i])
            {
                case '"':out.push_back('"');break; case '\\':out.push_back('\\');break; case '/':out.push_back('/');break;
                case 'b':out.push_back('\b');break; case 'f':out.push_back('\f');break; case 'n':out.push_back('\n');break;
                case 'r':out.push_back('\r');break; case 't':out.push_back('\t');break;
                case 'u': if(i+4>=s.size())return false; out.append("\\u");out.append(s.substr(i+1,4));i+=4;break;
                default:return false;
            }
        }
        return false;
    }

    std::string Quote(std::string_view value)
    {
        std::string out="\"";
        for(char c:value)
        {
            switch(c){case '"':out+="\\\"";break;case '\\':out+="\\\\";break;case '\n':out+="\\n";break;case '\r':out+="\\r";break;case '\t':out+="\\t";break;default:out.push_back(static_cast<unsigned char>(c)<0x20?'?':c);break;}
        }
        out+='"'; return out;
    }

    bool FindValue(std::string_view json,std::string_view wanted,size_t& start,size_t& end,std::string* decoded=nullptr,size_t from=0)
    {
        size_t pos=from;
        while(pos<json.size())
        {
            pos=json.find('"',pos); if(pos==std::string_view::npos)return false;
            size_t keyEnd=0; std::string key; if(!ParseString(json,pos,keyEnd,&key))return false;
            size_t colon=SkipWs(json,keyEnd); if(colon>=json.size()||json[colon]!=':'){pos=keyEnd;continue;}
            start=SkipWs(json,colon+1); if(start>=json.size())return false; end=start; std::string value;
            if(json[start]=='"'){if(!ParseString(json,start,end,&value))return false;}
            else if(json[start]=='['||json[start]=='{')
            {
                const char open=json[start],close=open=='['?']':'}';int depth=0;bool inString=false,escaped=false;
                for(size_t i=start;i<json.size();++i)
                {
                    char c=json[i];
                    if(inString){if(escaped)escaped=false;else if(c=='\\')escaped=true;else if(c=='"')inString=false;continue;}
                    if(c=='"'){inString=true;continue;} if(c==open)++depth; else if(c==close&&--depth==0){end=i+1;break;}
                }
                if(end==start)return false;
            }
            else
            {
                while(end<json.size()&&json[end]!=','&&json[end]!='}'&&json[end]!=']')++end;
                while(end>start&&Ws(json[end-1]))--end;
            }
            if(key==wanted){if(decoded)*decoded=std::move(value);return true;} pos=keyEnd;
        }
        return false;
    }

    std::string Alias(std::unordered_map<std::string,std::string>& table,std::string_view raw,const char* prefix)
    {
        std::lock_guard<std::mutex> guard(g_AliasMutex); const std::string key(raw);
        auto it=table.find(key); if(it!=table.end())return it->second;
        std::string value=std::string(prefix)+std::to_string(table.size()+1);table.emplace(key,value);return value;
    }

    size_t RedactAll(std::string& json,std::string_view key,size_t* maxOriginalLength=nullptr)
    {
        const std::string replacement=Quote("<REDACTED>");
        size_t scan=0,count=0,maxLength=0;
        while(scan<json.size())
        {
            size_t start=0,end=0;std::string decoded;
            if(!FindValue(json,key,start,end,&decoded,scan))break;
            maxLength=(std::max)(maxLength,decoded.size());
            json.replace(start,end-start,replacement);
            scan=start+replacement.size();
            ++count;
        }
        if(maxOriginalLength)*maxOriginalLength=maxLength;
        return count;
    }

    void AliasAll(std::string& json,std::string_view key,std::unordered_map<std::string,std::string>& table,const char* prefix)
    {
        size_t scan=0;
        while(scan<json.size())
        {
            size_t start=0,end=0;std::string decoded;if(!FindValue(json,key,start,end,&decoded,scan))break;
            if(start<json.size()&&json[start]=='"'&&!decoded.empty())
            {std::string replacement=Quote(Alias(table,decoded,prefix));json.replace(start,end-start,replacement);scan=start+replacement.size();}
            else scan=(std::max)(end,start+1);
        }
    }

    void AliasLanArrays(std::string& json)
    {
        size_t scan=0;
        while(scan<json.size())
        {
            size_t start=0,end=0;if(!FindValue(json,"lanAddresses",start,end,nullptr,scan))break;
            if(start>=end||json[start]!='['){scan=(std::max)(end,start+1);continue;}
            std::string replacement="[";size_t p=start+1;bool first=true;
            while(p<end)
            {
                p=json.find('"',p);if(p==std::string::npos||p>=end)break;size_t strEnd=0;std::string decoded;
                if (!ParseString(json, p, strEnd, &decoded) || strEnd > end) break;
                if (!first) replacement += ',';
                replacement+=Quote(Alias(g_Endpoints,decoded,"endpoint_"));first=false;p=strEnd;
            }
            replacement+=']';json.replace(start,end-start,replacement);scan=start+replacement.size();
        }
    }

    uint32_t U32(const uint8_t* p){return uint32_t(p[0])|(uint32_t(p[1])<<8)|(uint32_t(p[2])<<16)|(uint32_t(p[3])<<24);}
}

const BzrNetMessageInfo* LookupBzrNetMessage(std::string_view type){for(const auto& m:kMessages)if(type==m.name)return &m;return nullptr;}
bool ExtractBzrNetMessageType(std::string_view json,std::string& out){size_t s=0,e=0;std::string v;if(!FindValue(json,"type",s,e,&v)||v.empty())return false;out=std::move(v);return true;}

bool TryExtractBzrNetJsonInt(std::string_view json,std::string_view key,int64_t& out)
{
    size_t s=0,e=0;if(!FindValue(json,key,s,e)||s>=e||json[s]=='"')return false;auto token=json.substr(s,e-s);int64_t value=0;
    auto result=std::from_chars(token.data(),token.data()+token.size(),value);if(result.ec!=std::errc{}||result.ptr!=token.data()+token.size())return false;out=value;return true;
}

bool TryExtractBzrNetJsonBool(std::string_view json,std::string_view key,bool& out)
{
    size_t s=0,e=0;if(!FindValue(json,key,s,e))return false;auto token=json.substr(s,e-s);if(token=="true"){out=true;return true;}if(token=="false"){out=false;return true;}return false;
}

const char* BzrNetEvidenceName(BzrNetEvidence e)
{
    switch(e){case BzrNetEvidence::BinaryConfirmed:return "binary_confirmed";case BzrNetEvidence::CaptureConfirmed:return "capture_confirmed";case BzrNetEvidence::HighConfidence:return "high_confidence";case BzrNetEvidence::Inferred:return "inferred";case BzrNetEvidence::ReplacementOnly:return "replacement_only";default:return "unknown";}
}
const char* BzrNetDirectionName(BzrNetMessageDirection d){return d==BzrNetMessageDirection::ClientToServer?"outbound":d==BzrNetMessageDirection::ServerToClient?"inbound":"unknown";}

BzrNetSanitizedMessage SanitizeBzrNetJson(std::string_view json,bool privateForensic)
{
    BzrNetSanitizedMessage result;result.json.assign(json.begin(),json.end());
    for(const char* key:{"steamAppTicket","gogAppTicket","authTicket","platformTicket"})
    {
        size_t n=0;
        if(RedactAll(result.json,key,&n)>0)
        {
            result.authTicketRedacted=true;
            result.authTicketLength=(std::max)(result.authTicketLength,n);
        }
    }
    size_t passwordLength=0;
    if(RedactAll(result.json,"password",&passwordLength)>0)
    {
        result.passwordRedacted=true;
        result.passwordLength=passwordLength;
    }
    if(!privateForensic)
    {
        for(const char* key:{"userId","player","speakerId","owner","member"})AliasAll(result.json,key,g_Identities,"player_");
        // Shareable traces prefer privacy over retaining human-readable labels;
        // this also aliases lobby names when they use the generic `name` key.
        for(const char* key:{"name","realname"})AliasAll(result.json,key,g_Identities,"identity_");
        AliasAll(result.json,"wanAddress",g_Endpoints,"endpoint_");AliasLanArrays(result.json);
    }
    return result;
}

void ResetBzrNetSanitizationAliases(){std::lock_guard<std::mutex> guard(g_AliasMutex);g_Identities.clear();g_Endpoints.clear();}
std::string SanitizeBzrNetEndpoint(std::string_view v,bool privateForensic){return privateForensic||v.empty()?std::string(v):Alias(g_Endpoints,v,"endpoint_");}
std::string SanitizeBzrNetIdentity(std::string_view v,bool privateForensic){return privateForensic||v.empty()?std::string(v):Alias(g_Identities,v,"player_");}

BzrUdpControlInfo DecodeBzrUdpControl(const uint8_t* data,size_t length)
{
    BzrUdpControlInfo info;if(!data||length<2)return info;info.marker.assign(reinterpret_cast<const char*>(data),2);
    if(info.marker=="PP")
    {info.recognized=true;info.likelyMeaning="peer_ping_request";info.evidence=BzrNetEvidence::HighConfidence;if(length>=22){info.field0=U32(data+2);info.field1=U32(data+6);info.field2=U32(data+10);info.field3=U32(data+14);info.field4=U32(data+18);info.fieldCount=5;}}
    else if(info.marker=="PR")
    {info.recognized=true;info.likelyMeaning="peer_ping_response";info.evidence=BzrNetEvidence::HighConfidence;if(length>=14){info.field0=U32(data+2);info.field1=U32(data+6);info.field2=U32(data+10);info.fieldCount=3;}}
    else if(info.marker=="PB")
    {info.recognized=true;info.likelyMeaning="peer_timing_sideband";info.evidence=BzrNetEvidence::Inferred;if(length>=10){info.field0=U32(data+2);info.field1=U32(data+6);info.fieldCount=2;}}
    else if(info.marker=="SS"){info.recognized=true;info.likelyMeaning="peer_session_sync";info.evidence=BzrNetEvidence::HighConfidence;}
    else if(info.marker=="KA"){info.recognized=true;info.likelyMeaning="peer_keepalive";info.evidence=BzrNetEvidence::HighConfidence;}
    else if(info.marker=="PO"||info.marker=="PZ"){info.recognized=true;info.likelyMeaning=info.marker=="PO"?"peer_control_unknown_po":"peer_control_unknown_pz";info.evidence=BzrNetEvidence::Inferred;}
    return info;
}

size_t FindHttpHeaderEnd(const std::vector<uint8_t>& data)
{
    static const uint8_t delimiter[] = { '\r', '\n', '\r', '\n' };
    const auto it = std::search(data.begin(), data.end(), std::begin(delimiter), std::end(delimiter));
    return it == data.end() ? std::string::npos : static_cast<size_t>(it - data.begin()) + sizeof(delimiter);
}

void FeedWebSocketStream(
    WebSocketStreamState& state,
    const uint8_t* bytes,
    size_t length,
    size_t maxBytes,
    std::vector<WebSocketMessage>& out)
{
    if (!bytes || length == 0)
        return;
    if (state.pending.size() + length > maxBytes)
    {
        state.pending.clear();
        state.fragmented.clear();
        state.fragmentedOpcode = 0;
        return;
    }

    state.pending.insert(state.pending.end(), bytes, bytes + length);
    if (!state.handshakeComplete)
    {
        const size_t headerEnd = FindHttpHeaderEnd(state.pending);
        if (headerEnd == std::string::npos)
        {
            if (state.pending.size() > 64 * 1024)
                state.pending.clear();
            return;
        }
        state.pending.erase(state.pending.begin(), state.pending.begin() + headerEnd);
        state.handshakeComplete = true;
    }

    while (state.pending.size() >= 2)
    {
        const uint8_t first = state.pending[0];
        const uint8_t second = state.pending[1];
        const bool fin = (first & 0x80u) != 0;
        const uint8_t opcode = first & 0x0Fu;
        const bool masked = (second & 0x80u) != 0;
        uint64_t payloadLength = second & 0x7Fu;
        size_t headerLength = 2;

        if (payloadLength == 126)
        {
            if (state.pending.size() < 4)
                return;
            payloadLength = (static_cast<uint64_t>(state.pending[2]) << 8) |
                static_cast<uint64_t>(state.pending[3]);
            headerLength = 4;
        }
        else if (payloadLength == 127)
        {
            if (state.pending.size() < 10)
                return;
            payloadLength = 0;
            for (size_t i = 2; i < 10; ++i)
                payloadLength = (payloadLength << 8) | state.pending[i];
            headerLength = 10;
        }

        if (payloadLength > maxBytes)
        {
            state.pending.clear();
            state.fragmented.clear();
            state.fragmentedOpcode = 0;
            return;
        }

        uint8_t mask[4] = {};
        if (masked)
        {
            if (state.pending.size() < headerLength + sizeof(mask))
                return;
            std::memcpy(mask, state.pending.data() + headerLength, sizeof(mask));
            headerLength += sizeof(mask);
        }

        if (state.pending.size() < headerLength + static_cast<size_t>(payloadLength))
            return;

        std::vector<uint8_t> payload(static_cast<size_t>(payloadLength));
        for (size_t i = 0; i < payload.size(); ++i)
        {
            payload[i] = state.pending[headerLength + i];
            if (masked)
                payload[i] ^= mask[i % 4];
        }
        state.pending.erase(
            state.pending.begin(),
            state.pending.begin() + headerLength + static_cast<size_t>(payloadLength));

        if (opcode == 0x0)
        {
            if (state.fragmentedOpcode == 0 ||
                state.fragmented.size() + payload.size() > maxBytes)
            {
                state.fragmented.clear();
                state.fragmentedOpcode = 0;
                continue;
            }
            state.fragmented.insert(state.fragmented.end(), payload.begin(), payload.end());
            if (fin)
            {
                out.push_back({ state.fragmentedOpcode, std::move(state.fragmented) });
                state.fragmented.clear();
                state.fragmentedOpcode = 0;
            }
        }
        else if (opcode == 0x1 || opcode == 0x2)
        {
            if (fin)
            {
                out.push_back({ opcode, std::move(payload) });
            }
            else
            {
                state.fragmentedOpcode = opcode;
                state.fragmented = std::move(payload);
            }
        }
    }
}

namespace
{
    constexpr const char* kTicketKeys[] = { "steamAppTicket", "gogAppTicket", "authTicket", "platformTicket" };
    constexpr char kWithheldMarker[] = "withheld";
    constexpr size_t kWithheldLength = sizeof(kWithheldMarker) - 1;

    bool IsJsonSpace(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }

    // Rewrites every ticket value in `json` in place. False = a ticket key was
    // found whose value could not be rewritten safely.
    bool WithholdTicketsInJson(std::string& json, std::vector<WebSocketTicketRewrite>& rewrites)
    {
        for (const char* key : kTicketKeys)
        {
            const std::string quoted = std::string("\"") + key + "\"";
            size_t pos = 0;
            while ((pos = json.find(quoted, pos)) != std::string::npos)
            {
                size_t p = pos + quoted.size();
                const size_t keyEnd = p;
                while (p < json.size() && IsJsonSpace(json[p])) ++p;
                if (p >= json.size() || json[p] != ':')
                {
                    pos = keyEnd;   // the name used as a value, not a key
                    continue;
                }
                ++p;
                while (p < json.size() && IsJsonSpace(json[p])) ++p;
                if (json.compare(p, 4, "null") == 0)
                {
                    pos = p + 4;
                    continue;
                }
                if (p >= json.size() || json[p] != '"')
                    return false;

                const size_t open = p;
                size_t close = open + 1;
                while (close < json.size() && json[close] != '"')
                    close += (json[close] == '\\') ? 2 : 1;
                if (close >= json.size())
                    return false;

                const size_t valueLength = close - open - 1;
                if (valueLength > 0)
                {
                    std::string replacement(valueLength + 2, ' ');
                    replacement[0] = '"';
                    if (valueLength >= kWithheldLength)
                    {
                        std::memcpy(&replacement[1], kWithheldMarker, kWithheldLength);
                        replacement[1 + kWithheldLength] = '"';
                    }
                    else
                    {
                        replacement[1] = '"';
                    }
                    json.replace(open, valueLength + 2, replacement);
                    WebSocketTicketRewrite rewrite;
                    rewrite.key = key;
                    rewrite.length = valueLength;
                    rewrites.push_back(rewrite);
                }
                pos = close + 1;
            }
        }
        return true;
    }

    bool ContainsNoCase(const std::vector<uint8_t>& data, const char* needle)
    {
        const size_t n = std::strlen(needle);
        if (data.size() < n) return false;
        for (size_t i = 0; i + n <= data.size(); ++i)
        {
            size_t j = 0;
            while (j < n && std::tolower(data[i + j]) == std::tolower(static_cast<unsigned char>(needle[j]))) ++j;
            if (j == n) return true;
        }
        return false;
    }
}

WebSocketScrubStatus ScrubWebSocketTickets(
    WebSocketTicketScrubState& state,
    uint8_t* data,
    size_t length,
    std::vector<WebSocketTicketRewrite>& rewrites,
    const char** rejectReason)
{
    using Phase = WebSocketTicketScrubState::Phase;
    auto reject = [&](const char* reason)
    {
        state.rejected = true;
        if (rejectReason) *rejectReason = reason;
        return WebSocketScrubStatus::Rejected;
    };
    if (state.rejected)
        return reject("connection previously rejected");
    if (length > 0 && !data)
        return reject("null buffer");

    bool changed = false;
    size_t i = 0;
    while (i < length)
    {
        switch (state.phase)
        {
        case Phase::Passthrough:
            i = length;
            break;

        case Phase::Handshake:
        {
            const size_t before = state.handshake.size();
            if (before + (length - i) > 16 * 1024)
                return reject("handshake header too large");
            state.handshake.insert(state.handshake.end(), data + i, data + length);
            const size_t end = FindHttpHeaderEnd(state.handshake);
            if (end == std::string::npos)
            {
                i = length;
                break;
            }
            i += end - before;
            const bool isWs = state.handshake.size() >= 4 &&
                std::memcmp(state.handshake.data(), "GET ", 4) == 0 &&
                ContainsNoCase(state.handshake, "websocket");
            state.handshake.clear();
            state.handshake.shrink_to_fit();
            state.phase = isWs ? Phase::FrameHeader : Phase::Passthrough;
            state.headerLength = 0;
            break;
        }

        case Phase::FrameHeader:
        {
            state.header[state.headerLength++] = data[i++];
            if (state.headerLength < 2)
                break;
            const uint8_t lenCode = state.header[1] & 0x7Fu;
            const bool masked = (state.header[1] & 0x80u) != 0;
            const size_t extra = lenCode == 126 ? 2 : (lenCode == 127 ? 8 : 0);
            const size_t needed = 2 + extra + (masked ? 4 : 0);
            if (state.headerLength < needed)
                break;

            const uint8_t first = state.header[0];
            const uint8_t opcode = first & 0x0Fu;
            if ((first & 0x70u) != 0)
                return reject("RSV bits set (compressed or extended frame)");
            uint64_t payloadLength = lenCode;
            if (extra)
            {
                payloadLength = 0;
                for (size_t b = 0; b < extra; ++b)
                    payloadLength = (payloadLength << 8) | state.header[2 + b];
            }
            std::memset(state.mask, 0, sizeof(state.mask));
            if (masked)
                std::memcpy(state.mask, state.header + 2 + extra, 4);
            state.opcode = opcode;
            state.payloadRemaining = payloadLength;
            state.headerLength = 0;

            if (opcode == 0)
                return reject("continuation frame");
            if (opcode == 1 && (first & 0x80u) == 0)
                return reject("fragmented text message");
            if ((opcode >= 3 && opcode <= 7) || opcode >= 11)
                return reject("reserved opcode");
            if (opcode == 1 && payloadLength > kTicketScrubMaxPayload)
                return reject("text frame too large");
            if (payloadLength > 0)
                state.phase = Phase::FramePayload;
            break;
        }

        case Phase::FramePayload:
        {
            const size_t avail = length - i;
            if (state.opcode != 1)
            {
                const size_t take = static_cast<size_t>((std::min<uint64_t>)(avail, state.payloadRemaining));
                state.payloadRemaining -= take;
                i += take;
            }
            else
            {
                if (avail < state.payloadRemaining)
                    return reject("text frame split across sends");
                const size_t n = static_cast<size_t>(state.payloadRemaining);
                std::string json(n, '\0');
                for (size_t b = 0; b < n; ++b)
                    json[b] = static_cast<char>(data[i + b] ^ state.mask[b % 4]);
                std::vector<WebSocketTicketRewrite> local;
                if (!WithholdTicketsInJson(json, local))
                    return reject("ticket value could not be rewritten");
                if (!local.empty())
                {
                    for (size_t b = 0; b < n; ++b)
                        data[i + b] = static_cast<uint8_t>(static_cast<uint8_t>(json[b]) ^ state.mask[b % 4]);
                    rewrites.insert(rewrites.end(), local.begin(), local.end());
                    changed = true;
                }
                i += n;
                state.payloadRemaining = 0;
            }
            if (state.payloadRemaining == 0)
                state.phase = Phase::FrameHeader;
            break;
        }
        }
    }
    return changed ? WebSocketScrubStatus::Rewritten : WebSocketScrubStatus::Unchanged;
}

WebSocketScrubStatus ScrubWebSocketTicketsPerCall(
    const ByteSpan* spans,
    size_t count,
    std::vector<WebSocketTicketRewrite>& rewrites,
    const char** rejectReason)
{
    auto reject = [&](const char* reason)
    {
        if (rejectReason) *rejectReason = reason;
        return WebSocketScrubStatus::Rejected;
    };

    size_t total = 0;
    for (size_t i = 0; i < count; ++i)
    {
        if (spans[i].length > 0 && !spans[i].data)
            return reject("null buffer");
        total += spans[i].length;
        if (total > kTicketScrubMaxCallBytes)
            return reject("send too large");
    }
    if (total == 0)
        return WebSocketScrubStatus::Unchanged;

    std::vector<uint8_t> flat;
    flat.reserve(total);
    for (size_t i = 0; i < count; ++i)
        if (spans[i].length > 0)
            flat.insert(flat.end(), spans[i].data, spans[i].data + spans[i].length);

    static const uint8_t crlf2[4] = { '\r', '\n', '\r', '\n' };
    if (total >= 8 && std::memcmp(flat.data(), "GET ", 4) == 0 &&
        std::memcmp(flat.data() + total - 4, crlf2, 4) == 0)
        return WebSocketScrubStatus::Unchanged;

    WebSocketTicketScrubState state;
    state.phase = WebSocketTicketScrubState::Phase::FrameHeader;
    std::vector<WebSocketTicketRewrite> local;
    const WebSocketScrubStatus status = ScrubWebSocketTickets(state, flat.data(), flat.size(), local, rejectReason);
    if (status == WebSocketScrubStatus::Rejected)
        return status;
    if (state.phase != WebSocketTicketScrubState::Phase::FrameHeader || state.headerLength != 0)
        return reject("call does not end on a frame boundary");
    if (status == WebSocketScrubStatus::Unchanged)
        return status;

    size_t offset = 0;
    for (size_t i = 0; i < count; ++i)
    {
        if (spans[i].length == 0)
            continue;
        std::memcpy(spans[i].data, flat.data() + offset, spans[i].length);
        offset += spans[i].length;
    }
    rewrites.insert(rewrites.end(), local.begin(), local.end());
    return WebSocketScrubStatus::Rewritten;
}
}
