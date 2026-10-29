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
    class Model
    {
    public:
        Model();
        void Connect(uint64_t connection, const std::string& sourceIPv4);
        std::vector<Delivery> Receive(uint64_t connection, const Json& message);
        std::vector<Delivery> Disconnect(uint64_t connection);
        bool Admitted(uint64_t connection) const;
    private:
        struct Player
        {
            std::string ip, id, name, wan;
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
        Json User(const Player&) const;
        Json Room(const Lobby&) const;
        Json List() const;
        void Send(std::vector<Delivery>&, uint64_t, const std::string&, Json) const;
        void Broadcast(std::vector<Delivery>&, const std::string&, const Json&) const;
        void Refresh(std::vector<Delivery>&) const;
        void Leave(std::vector<Delivery>&, Player&);
    };
}
