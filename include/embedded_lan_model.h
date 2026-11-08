#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

namespace BZROpenShim::EmbeddedLan
{
    using Json = nlohmann::json;
    struct Delivery { uint64_t connection; Json message; };
    // False when brackets outside strings nest deeper than maxDepth.
    bool JsonDepthWithin(const std::string& text, unsigned maxDepth);
    // Parse a client frame; returns a discarded value if malformed or nested deeper than 32.
    Json ParseBounded(const std::string& text);
    // Who a connection may log in as, decided outside the model from its
    // source address. steamId ("S<steamid64>") is an identity the Steam
    // bridge already authenticated: the connection may log in as exactly that
    // Steam id (its ticket is ignored, never stored). lan allows a local
    // "B<n>" no-auth login as before.
    struct Admission { std::string steamId; bool lan = true; };
    class Model
    {
    public:
        Model();
        void Connect(uint64_t connection, const std::string& sourceIPv4, const Admission& admission = {});
        std::vector<Delivery> Receive(uint64_t connection, const Json& message);
        std::vector<Delivery> Disconnect(uint64_t connection);
        bool Admitted(uint64_t connection) const;
        // Emits at most one coalesced lobby refresh for updates since the last flush.
        std::vector<Delivery> Flush();
    private:
        struct Player
        {
            std::string ip, id, name, wan, authType = "lan";
            Admission admission;
            Json addresses = Json::array(), metadata = Json::object();
            int lobby = -1;
        };
        struct Lobby
        {
            int id = 0, limit = 16;
            std::string owner, password;
            std::string created;
            bool locked = false, chat = false, privateRoom = false;
            Json metadata = Json::object();
        };
        std::map<uint64_t, Player> players;
        std::map<int, Lobby> lobbies;
        int nextLobby = 2;
        bool refreshPending = false;
        Json User(const Player&) const;
        Json Room(const Lobby&) const;
        Json List() const;
        void Send(std::vector<Delivery>&, uint64_t, const std::string&, Json) const;
        void Broadcast(std::vector<Delivery>&, const std::string&, const Json&) const;
        void Refresh(std::vector<Delivery>&);
        void Leave(std::vector<Delivery>&, Player&);
    };
}
