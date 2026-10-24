// lobby_team_commands.cpp -- host-only /team, /swap and /host for the pre-game
// multiplayer lobby. See include/lobby_team_commands.h for the syntax and why
// these exist.
//
// Engine side (GOG exe, static analysis; the names are ours):
//
//   GetBzrNetLobby            0x00764760  return [0x00945470] -- the live lobby
//                                         interface, a CNetGameLobby subclass
//   CNetGameLobby::IsOwner    0x00742CF0  __thiscall; GetLobbyOwner(+0x68) of
//                                         this+0x28 (current lobby id) == GetMyID(+0x38)
//   CNetGameLobby::FindRecord 0x007470B0  __thiscall(const LobbyId*, bool create);
//                                         walks the record list at this+4
//   CNetGameLobby::AssignTeam 0x007468B0  __thiscall(cUser*, int team); owner
//                                         only, 1 <= team < 16. Self -> SetPlayerData
//                                         "team"/"miniid"; anyone else -> lobby chat
//                                         "AT~<id>~<team>~<miniid>", which that
//                                         client turns into its own metadata.
//   lobby vtable +0x6C        SetLobbyOwner(const LobbyId*, const UserId*) -> bool;
//                                         BZRNetLobby 0x0074B9F0 sends the websocket
//                                         message DoSetLobbyOwner. The stock caller
//                                         is PopulateLobbyFromData (0x0074423F).
//
//   record + 0x10             lobby id (the SetLobbyOwner argument)
//   record + 0xB8             std::list<cUser>; the element sits at node + 8
//   cUser  + 0x08             user id (the SetLobbyOwner argument)
//   cUser  + 0x28             miniid (uint16) -- the lobby player id the command
//                             hook receives for the selected row
//   cUser  + 0x2C             display name, std::string
//   cUser  + 0x80             team (int)
//
// Each offset is pinned by an engine_addresses row on an instruction that uses
// it, so a build where any of them moved stands the whole feature down and the
// command reports that instead of calling into a layout it does not know.
//
// Live behaviour is UNVERIFIED: whether the BZRNet server honours a
// DoSetLobbyOwner from a client, and whether every peer accepts an AT~ message
// for a player that already has a team, are what the two-client test in
// Docs/LOBBY_TEAM_HOST_COMMANDS.md is for.

#include "lobby_team_commands.h"

#include "bzr_hooks_internal.h"
#include "game_state.h"
#include "hook_engine.h"
#include "patcher.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr size_t kLobbyIdOffset = 0x28;      // lobby interface: current lobby id
        constexpr size_t kRecordIdOffset = 0x10;     // lobby record: its id
        constexpr size_t kRecordMembersOffset = 0xB8;
        constexpr size_t kListNodeValueOffset = 8;
        constexpr size_t kUserIdOffset = 0x08;
        constexpr size_t kUserMiniIdOffset = 0x28;
        constexpr size_t kUserNameOffset = 0x2C;
        constexpr size_t kUserTeamOffset = 0x80;
        constexpr size_t kSetLobbyOwnerSlot = 0x6C / 4;
        constexpr int kMaxMembers = 64;  // a corrupt list must not spin forever

        using FnIsOwner = bool(__thiscall*)(void* lobby);
        using FnFindRecord = void*(__thiscall*)(void* lobby, const void* lobbyId, int create);
        using FnAssignTeam = void(__thiscall*)(void* lobby, void* user, int team);
        using FnSetLobbyOwner = bool(__thiscall*)(void* lobby, const void* lobbyId, const void* userId);

        struct Bindings
        {
            uint32_t lobbyGlobal = 0;    // &[0x00945470], from GetBzrNetLobby's operand
            uint32_t lobbyVtable = 0;
            FnIsOwner isOwner = nullptr;
            FnFindRecord findRecord = nullptr;
            FnAssignTeam assignTeam = nullptr;
            uint32_t setLobbyOwner = 0;  // what the vtable slot must hold
        };

        // Binds once; a failure is retried on the next command (the rows can
        // read as Mismatch while SteamStub is still unpacking).
        bool Bind(Bindings& out)
        {
            static Bindings bound;
            static bool ok = false;
            if (ok)
            {
                out = bound;
                return true;
            }

            uint32_t getLobby = 0, vtable = 0, isOwner = 0, findRecord = 0, assignTeam = 0;
            uint32_t setOwner = 0, teamRange = 0, memberList = 0, memberTeam = 0, memberLog = 0;
            uint32_t ownerRestore = 0, recordIdCompare = 0;
            const HookEngine::EngineRow rows[] = {
                { "BzrNetGetLobby", &getLobby },
                { "BzrNetLobbyVtable", &vtable },
                { "BzrNetLobbySetLobbyOwner", &setOwner },
                { "NetGameLobbyIsOwner", &isOwner },
                { "NetGameLobbyFindRecord", &findRecord },
                { "NetGameLobbyFindRecordIdCompare", &recordIdCompare },
                { "NetGameLobbyAssignTeam", &assignTeam },
                { "NetGameLobbyAssignTeamRange", &teamRange },
                { "NetGameLobbyMemberListRead", &memberList },
                { "NetGameLobbyMemberTeamRead", &memberTeam },
                { "NetGameLobbyMemberLog", &memberLog },
                { "NetGameLobbyOwnerRestore", &ownerRestore },
            };
            if (!HookEngine::BindEngineRows("Lobby team commands", rows))
                return false;

            bound.lobbyGlobal = *reinterpret_cast<const uint32_t*>(static_cast<uintptr_t>(getLobby) + 4);
            bound.lobbyVtable = vtable;
            bound.isOwner = reinterpret_cast<FnIsOwner>(static_cast<uintptr_t>(isOwner));
            bound.findRecord = reinterpret_cast<FnFindRecord>(static_cast<uintptr_t>(findRecord));
            bound.assignTeam = reinterpret_cast<FnAssignTeam>(static_cast<uintptr_t>(assignTeam));
            bound.setLobbyOwner = setOwner;
            ok = true;
            out = bound;
            return true;
        }

        // ---- guarded engine access ---------------------------------------
        //
        // Every __try function is kept free of unwindable objects (C2712).

        struct Member
        {
            void* user = nullptr;
            uint16_t miniId = 0;
            int team = 0;
            char name[128] = {};
        };

        struct Roster
        {
            void* lobby = nullptr;
            void* record = nullptr;
            bool owner = false;
            int count = 0;
            Member members[kMaxMembers];
        };

        // MSVC 2013 std::string: 16-byte SSO buffer or pointer, size at +0x10,
        // capacity at +0x14.
        void CopyStdString(uintptr_t str, char* out, size_t capacity)
        {
            const uint32_t size = *reinterpret_cast<const uint32_t*>(str + 0x10);
            const uint32_t reserved = *reinterpret_cast<const uint32_t*>(str + 0x14);
            const char* text = reserved >= 16 ? *reinterpret_cast<const char* const*>(str)
                                              : reinterpret_cast<const char*>(str);
            size_t n = size < capacity - 1 ? size : capacity - 1;
            std::memcpy(out, text, n);
            out[n] = '\0';
        }

        // 0 = ok, otherwise a static reason.
        const char* ReadRoster(const Bindings& b, Roster& roster)
        {
            __try
            {
                void* const lobby = *reinterpret_cast<void* const*>(static_cast<uintptr_t>(b.lobbyGlobal));
                if (!lobby)
                    return "no multiplayer lobby is open";
                const uint32_t* const vptr = *reinterpret_cast<const uint32_t* const*>(lobby);
                if (reinterpret_cast<uintptr_t>(vptr) != b.lobbyVtable)
                    return "the lobby backend is not BZRNet";
                if (vptr[kSetLobbyOwnerSlot] != b.setLobbyOwner)
                    return "the lobby vtable does not match this build";

                roster.lobby = lobby;
                roster.owner = b.isOwner(lobby);
                const uintptr_t lobbyId = reinterpret_cast<uintptr_t>(lobby) + kLobbyIdOffset;
                roster.record = b.findRecord(lobby, reinterpret_cast<const void*>(lobbyId), 0);
                if (!roster.record)
                    return "not in a lobby";

                const uintptr_t head = *reinterpret_cast<const uintptr_t*>(
                    reinterpret_cast<uintptr_t>(roster.record) + kRecordMembersOffset);
                uintptr_t node = *reinterpret_cast<const uintptr_t*>(head);
                while (node != head)
                {
                    if (roster.count >= kMaxMembers)
                        return "the lobby member list is not readable";
                    const uintptr_t user = node + kListNodeValueOffset;
                    Member& m = roster.members[roster.count++];
                    m.user = reinterpret_cast<void*>(user);
                    m.miniId = *reinterpret_cast<const uint16_t*>(user + kUserMiniIdOffset);
                    m.team = *reinterpret_cast<const int*>(user + kUserTeamOffset);
                    CopyStdString(user + kUserNameOffset, m.name, sizeof(m.name));
                    node = *reinterpret_cast<const uintptr_t*>(node);
                }
                return nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return "the lobby could not be read";
        }

        bool CallAssignTeam(const Bindings& b, void* lobby, void* user, int team)
        {
            __try
            {
                b.assignTeam(lobby, user, team);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        // 1 = accepted, 0 = refused by the backend, -1 = faulted.
        int CallSetLobbyOwner(void* lobby, void* record, void* user)
        {
            __try
            {
                const uint32_t* const vptr = *reinterpret_cast<const uint32_t* const*>(lobby);
                const auto setOwner = reinterpret_cast<FnSetLobbyOwner>(
                    static_cast<uintptr_t>(vptr[kSetLobbyOwnerSlot]));
                const void* lobbyId = reinterpret_cast<const char*>(record) + kRecordIdOffset;
                const void* userId = reinterpret_cast<const char*>(user) + kUserIdOffset;
                return setOwner(lobby, lobbyId, userId) ? 1 : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return -1;
        }

        // ---- command plumbing ----------------------------------------------

        void Report(const char* line)
        {
            void* helpObj = (g_BzrPtr_920168 && *g_BzrPtr_920168) ? *g_BzrPtr_920168 : nullptr;
            if (g_BzrFn_HelpLog && helpObj)
                g_BzrFn_HelpLog(helpObj, line);
            if (g_BzrFn_HelpUi)
                g_BzrFn_HelpUi(0, line);
            Log(L"[LOBBY] %hs\n", line);
        }

        const Member* FindByMiniId(const Roster& roster, uint16_t id)
        {
            if (id == 0)
                return nullptr;
            for (int i = 0; i < roster.count; ++i)
                if (roster.members[i].miniId == id)
                    return &roster.members[i];
            return nullptr;
        }

        const Member* FindByTeam(const Roster& roster, int team)
        {
            for (int i = 0; i < roster.count; ++i)
                if (roster.members[i].team == team)
                    return &roster.members[i];
            return nullptr;
        }

        // Exact (case-insensitive) name first, then a unique prefix.
        const Member* FindByName(const Roster& roster, const std::string& name, bool& ambiguous)
        {
            ambiguous = false;
            for (int i = 0; i < roster.count; ++i)
                if (_stricmp(roster.members[i].name, name.c_str()) == 0)
                    return &roster.members[i];
            const Member* match = nullptr;
            for (int i = 0; i < roster.count; ++i)
            {
                if (_strnicmp(roster.members[i].name, name.c_str(), name.size()) != 0)
                    continue;
                if (match)
                {
                    ambiguous = true;
                    return nullptr;
                }
                match = &roster.members[i];
            }
            return match;
        }

        const Member* ResolveTarget(const Roster& roster, const LobbyCommandRequest& request, uint16_t selectedId)
        {
            char message[192] = {};
            if (!request.name.empty())
            {
                bool ambiguous = false;
                const Member* member = FindByName(roster, request.name, ambiguous);
                if (!member)
                {
                    std::snprintf(message, sizeof(message), "%s: %s \"%s\"", request.command,
                                  ambiguous ? "more than one player starts with" : "no player named",
                                  request.name.c_str());
                    Report(message);
                }
                return member;
            }
            const Member* member = FindByMiniId(roster, selectedId);
            if (!member)
            {
                std::snprintf(message, sizeof(message),
                              "%s: select a player in the list, or name one", request.command);
                Report(message);
            }
            return member;
        }

        void Usage(const char* command)
        {
            if (std::strcmp(command, "/team") == 0)
                Report("Usage: /team <1-15> (selected player) or /team <name> <1-15>");
            else if (std::strcmp(command, "/swap") == 0)
                Report("Usage: /swap <team> <team> - swaps the players on two teams");
            else
                Report("Usage: /host (selected player) or /host <name>");
        }

        bool Assign(const Bindings& b, const Roster& roster, const Member& member, int team)
        {
            if (!CallAssignTeam(b, roster.lobby, member.user, team))
                return false;
            Log(L"[LOBBY] AssignTeam name=%hs miniid=%u team %d -> %d\n",
                member.name, member.miniId, member.team, team);
            return true;
        }
    }

    bool HandleLobbyTeamCommand(uint16_t selectedId, const char* cmd)
    {
        const LobbyCommandRequest request = ParseLobbyTeamCommand(cmd);
        if (request.kind == LobbyCommandKind::None)
            return false;
        if (request.kind == LobbyCommandKind::Usage)
        {
            Usage(request.command);
            return true;
        }

        char message[256] = {};
        const ShellUiState shell = ReadShellUiState();
        if (!shell.readable || !shell.wrapperActive || shell.screenType == kScreenTypePause)
        {
            std::snprintf(message, sizeof(message), "%s works only in the pre-game lobby", request.command);
            Report(message);
            return true;
        }

        Bindings b;
        if (!Bind(b))
        {
            std::snprintf(message, sizeof(message), "%s is unavailable on this game build", request.command);
            Report(message);
            return true;
        }

        static Roster roster;  // ~9 KB; commands run on the UI thread only
        roster = Roster{};
        if (const char* why = ReadRoster(b, roster))
        {
            std::snprintf(message, sizeof(message), "%s: %s", request.command, why);
            Report(message);
            return true;
        }
        if (!roster.owner)
        {
            std::snprintf(message, sizeof(message), "%s: only the lobby host can do that", request.command);
            Report(message);
            return true;
        }

        if (request.kind == LobbyCommandKind::Team)
        {
            const Member* member = ResolveTarget(roster, request, selectedId);
            if (!member)
                return true;
            if (member->team == request.teamA)
            {
                std::snprintf(message, sizeof(message), "%s is already on team %d", member->name, member->team);
                Report(message);
                return true;
            }
            const Member* holder = FindByTeam(roster, request.teamA);
            if (holder && holder != member)
            {
                std::snprintf(message, sizeof(message), "Team %d belongs to %s - use /swap",
                              request.teamA, holder->name);
                Report(message);
                return true;
            }
            if (!Assign(b, roster, *member, request.teamA))
            {
                Report("/team: the engine rejected the request");
                return true;
            }
            std::snprintf(message, sizeof(message), "Moved %s to team %d", member->name, request.teamA);
            Report(message);
            return true;
        }

        if (request.kind == LobbyCommandKind::Swap)
        {
            const Member* first = FindByTeam(roster, request.teamA);
            const Member* second = FindByTeam(roster, request.teamB);
            if (!first && !second)
            {
                std::snprintf(message, sizeof(message), "/swap: nobody is on team %d or %d",
                              request.teamA, request.teamB);
                Report(message);
                return true;
            }
            const bool ok = (!first || Assign(b, roster, *first, request.teamB)) &&
                            (!second || Assign(b, roster, *second, request.teamA));
            if (!ok)
            {
                Report("/swap: the engine rejected the request");
                return true;
            }
            if (first && second)
                std::snprintf(message, sizeof(message), "Swapped %s (now team %d) and %s (now team %d)",
                              first->name, request.teamB, second->name, request.teamA);
            else
                std::snprintf(message, sizeof(message), "Moved %s to team %d",
                              first ? first->name : second->name, first ? request.teamB : request.teamA);
            Report(message);
            return true;
        }

        // LobbyCommandKind::Host
        const Member* member = ResolveTarget(roster, request, selectedId);
        if (!member)
            return true;
        const int result = CallSetLobbyOwner(roster.lobby, roster.record, member->user);
        Log(L"[LOBBY] SetLobbyOwner name=%hs miniid=%u result=%d\n", member->name, member->miniId, result);
        if (result == 1)
            std::snprintf(message, sizeof(message), "Asked the server to make %s the host", member->name);
        else if (result == 0)
            std::snprintf(message, sizeof(message), "/host: the lobby service refused the transfer");
        else
            std::snprintf(message, sizeof(message), "/host: the engine faulted; nothing was sent");
        Report(message);
        return true;
    }
}
