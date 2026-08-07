#include "bzrnet_protocol.h"

#include <algorithm>
#include <array>
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
                if(!ParseString(json,p,strEnd,&decoded)||strEnd>end)break;if(!first)replacement+=',';
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
}
