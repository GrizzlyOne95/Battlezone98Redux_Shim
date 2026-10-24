#pragma once

// Host-only pre-game lobby commands: /team, /swap and /host.
//
// Stock Redux numbers lobby teams itself: the owner hands each new member the
// lowest team number nobody holds, so join order decides teams and the first
// player in is always host. The engine already has the two operations a host
// needs to change that -- CNetGameLobby::AssignTeam and the lobby interface's
// SetLobbyOwner (vtable +0x6C) -- but no command reaches them. These commands
// call those natives through guarded engine_addresses rows; nothing here
// writes team or owner state directly.
//
// Syntax (the "selected player" is the row selected in the lobby player list,
// the same target the stock K/M buttons and OpenShim's /ban use):
//   /team <n>            move the selected player to team n (1-15)
//   /team <name> <n>     move the named player to team n
//   /swap <a> <b>        swap whoever holds team a with whoever holds team b
//                        (an empty side is just a move)
//   /host                make the selected player the lobby owner
//   /host <name>         make the named player the lobby owner
//
// The parser below is pure so tests/lobby_team_commands_tests.cpp can pin it.

#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    enum class LobbyCommandKind
    {
        None,   // not one of these commands; let the next handler see it
        Usage,  // one of these commands, but malformed; print usage
        Team,
        Swap,
        Host,
    };

    struct LobbyCommandRequest
    {
        LobbyCommandKind kind = LobbyCommandKind::None;
        const char* command = "";  // "/team", "/swap" or "/host"
        std::string name;          // empty = use the selected player
        int teamA = 0;             // /team target team; /swap first team
        int teamB = 0;             // /swap second team
    };

    constexpr int kLobbyMinTeam = 1;
    constexpr int kLobbyMaxTeam = 15;  // AssignTeam rejects team < 1 or team >= 16

    namespace LobbyCommandDetail
    {
        inline bool MatchVerb(const char* cmd, const char* verb, const char*& args)
        {
            // Portable on purpose: the Linux CTest lane compiles this header.
            const size_t length = std::strlen(verb);
            for (size_t i = 0; i < length; ++i)
                if (std::tolower(static_cast<unsigned char>(cmd[i])) != verb[i])
                    return false;
            if (cmd[length] != '\0' && cmd[length] != ' ' && cmd[length] != '\t')
                return false;
            args = cmd + length;
            return true;
        }

        inline std::string Trim(const char* text)
        {
            const char* begin = text;
            while (*begin == ' ' || *begin == '\t')
                ++begin;
            const char* end = begin + std::strlen(begin);
            while (end > begin && (end[-1] == ' ' || end[-1] == '\t'))
                --end;
            return std::string(begin, end);
        }

        // A whole token of 1-2 digits naming a team in range; anything else
        // (signs, "07x", "16") is not a team.
        inline bool ParseTeam(const std::string& token, int& team)
        {
            if (token.empty() || token.size() > 2)
                return false;
            for (const char c : token)
                if (!std::isdigit(static_cast<unsigned char>(c)))
                    return false;
            const int value = std::atoi(token.c_str());
            if (value < kLobbyMinTeam || value > kLobbyMaxTeam)
                return false;
            team = value;
            return true;
        }

        // Splits "<rest> <last>" at the final run of blanks.
        inline void SplitLast(const std::string& text, std::string& rest, std::string& last)
        {
            const size_t space = text.find_last_of(" \t");
            if (space == std::string::npos)
            {
                rest.clear();
                last = text;
                return;
            }
            last = text.substr(space + 1);
            rest = Trim(text.substr(0, space).c_str());
        }
    }

    inline LobbyCommandRequest ParseLobbyTeamCommand(const char* cmd)
    {
        using namespace LobbyCommandDetail;
        LobbyCommandRequest request;
        if (!cmd)
            return request;

        const char* args = nullptr;
        if (MatchVerb(cmd, "/team", args))
        {
            request.command = "/team";
            request.kind = LobbyCommandKind::Usage;
            std::string rest, last;
            SplitLast(Trim(args), rest, last);
            if (ParseTeam(last, request.teamA))
            {
                request.kind = LobbyCommandKind::Team;
                request.name = rest;
            }
        }
        else if (MatchVerb(cmd, "/swap", args))
        {
            request.command = "/swap";
            request.kind = LobbyCommandKind::Usage;
            std::string rest, last;
            SplitLast(Trim(args), rest, last);
            if (ParseTeam(rest, request.teamA) && ParseTeam(last, request.teamB) &&
                request.teamA != request.teamB)
                request.kind = LobbyCommandKind::Swap;
        }
        else if (MatchVerb(cmd, "/host", args))
        {
            request.command = "/host";
            request.kind = LobbyCommandKind::Host;
            request.name = Trim(args);
        }
        return request;
    }

    // Handles /team, /swap and /host from the multiplayer command hook.
    // Returns true when the command was one of these (handled or refused,
    // with a chat-log line either way); false lets the next handler run.
    // `selectedId` is the lobby player id (cUser miniid) of the selected row.
    bool HandleLobbyTeamCommand(uint16_t selectedId, const char* cmd);
}
