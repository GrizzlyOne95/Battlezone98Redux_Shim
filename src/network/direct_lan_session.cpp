#include "direct_lan_session.h"
#include <algorithm>
#include <cstring>
#include <limits>
#include <utility>

namespace BZROpenShim::DirectLan
{
    namespace
    {
        bool Text(const std::string& text, size_t maximum)
        {
            return !text.empty() && text.size() <= maximum &&
                std::all_of(text.begin(), text.end(), [](unsigned char c) { return c >= 32 && c <= 126; }) &&
                text.find_first_not_of(' ') != std::string::npos;
        }
        bool LocalAddress(uint32_t ip)
        {
            return (ip >> 24) == 10 || (ip >> 24) == 127 || (ip >> 20) == 0xAC1 ||
                (ip >> 16) == 0xC0A8 || (ip >> 16) == 0xA9FE;
        }
        bool Valid(const Compatibility& c)
        {
            return Text(c.gameBuild, 32) && std::any_of(c.content.begin(), c.content.end(),
                [](uint8_t byte) { return byte != 0; });
        }
        bool Valid(const Config& c)
        {
            return Valid(c.compatibility) && Text(c.name, 63) && Text(c.map, 63) &&
                c.capacity >= 2 && c.capacity <= kMaxMembers && c.settings.size() <= 512;
        }
        struct Writer
        {
            std::vector<uint8_t> data;
            void N(uint64_t value, size_t bytes)
            { for (size_t i = bytes; i; --i) data.push_back(uint8_t(value >> ((i - 1) * 8))); }
            void ID(const Id& id) { data.insert(data.end(), id.bytes.begin(), id.bytes.end()); }
            void S(const std::string& s) { N(s.size(), 1); data.insert(data.end(), s.begin(), s.end()); }
            void C(const Compatibility& c)
            { S(c.gameBuild); data.insert(data.end(), c.content.begin(), c.content.end()); }
            void CFG(const Config& c)
            {
                C(c.compatibility); S(c.name); S(c.map); N(c.capacity, 1); N(c.settings.size(), 2);
                data.insert(data.end(), c.settings.begin(), c.settings.end());
            }
        };
        struct Reader
        {
            const std::vector<uint8_t>& data;
            size_t cursor = 0;
            bool ok = true;
            uint64_t N(size_t bytes)
            {
                if (bytes > data.size() - cursor) { ok = false; return 0; }
                uint64_t value = 0;
                while (bytes--) value = (value << 8) | data[cursor++];
                return value;
            }
            Id ID() { Id id; for (auto& byte : id.bytes) byte = uint8_t(N(1)); return id; }
            std::string S(size_t maximum)
            {
                const size_t count = size_t(N(1));
                if (count > maximum || count > data.size() - cursor) { ok = false; return {}; }
                std::string value(data.begin() + cursor, data.begin() + cursor + count); cursor += count;
                if (!Text(value, maximum)) ok = false;
                return value;
            }
            Compatibility C()
            {
                Compatibility c; c.gameBuild = S(32);
                for (auto& byte : c.content) byte = uint8_t(N(1));
                if (!Valid(c)) ok = false;
                return c;
            }
            Config CFG()
            {
                Config c; c.compatibility = C(); c.name = S(63); c.map = S(63); c.capacity = uint8_t(N(1));
                const size_t count = size_t(N(2));
                if (count > 512 || count > data.size() - cursor) { ok = false; return c; }
                c.settings.assign(data.begin() + cursor, data.begin() + cursor + count); cursor += count;
                if (!Valid(c)) ok = false;
                return c;
            }
            bool Done() const { return ok && cursor == data.size(); }
        };
        std::vector<uint8_t> Snapshot(const View& view)
        {
            Writer w; w.ID(view.owner); w.N(view.revision, 8); w.N(uint8_t(view.phase), 1);
            w.N(view.launch, 8); w.CFG(view.config); w.N(view.members.size(), 1);
            for (const auto& m : view.members)
            {
                w.ID(m.id); w.N(m.slot, 1); w.S(m.name); w.N(m.endpoint.ipv4, 4);
                w.N(m.endpoint.gamePort, 2); w.N(m.ready, 1); w.N(m.prepared, 1);
            }
            return w.data;
        }
        bool ReadSnapshot(const Packet& packet, View& view)
        {
            Reader r{packet.payload}; View candidate;
            candidate.session = packet.session; candidate.owner = r.ID(); candidate.revision = r.N(8);
            candidate.phase = Phase(r.N(1)); candidate.launch = r.N(8); candidate.config = r.CFG();
            const auto count = r.N(1);
            if (!r.ok || !candidate.revision || candidate.owner.Empty() || count == 0 ||
                count > candidate.config.capacity ||
                (candidate.phase != Phase::Lobby && candidate.phase != Phase::Running)) return false;
            for (size_t i = 0; i < count; ++i)
            {
                Member m; m.id = r.ID(); m.slot = uint8_t(r.N(1)); m.name = r.S(31);
                m.endpoint.ipv4 = uint32_t(r.N(4)); m.endpoint.gamePort = uint16_t(r.N(2));
                const auto ready = r.N(1), prepared = r.N(1);
                m.ready = ready != 0; m.prepared = prepared != 0;
                if (!r.ok || m.id.Empty() || m.slot >= kMaxMembers || !LocalAddress(m.endpoint.ipv4) ||
                    !m.endpoint.gamePort || ready > 1 || prepared > 1 ||
                    (candidate.phase == Phase::Lobby && prepared != 0) ||
                    std::any_of(candidate.members.begin(), candidate.members.end(), [&](const Member& old)
                    { return old.id == m.id || old.slot == m.slot ||
                        (old.endpoint.ipv4 == m.endpoint.ipv4 && old.endpoint.gamePort == m.endpoint.gamePort); })) return false;
                candidate.members.push_back(std::move(m));
            }
            if (!r.Done() || candidate.members[0].id != candidate.owner || candidate.members[0].slot != 0 ||
                ((candidate.phase == Phase::Lobby) != (candidate.launch == 0))) return false;
            view = std::move(candidate); return true;
        }
        std::vector<uint8_t> Launch(const View& view)
        { Writer w; w.N(view.revision, 8); w.N(view.launch, 8); return w.data; }
        bool MatchesLaunch(const View& view, const std::vector<uint8_t>& data)
        { Reader r{data}; const auto revision = r.N(8), launch = r.N(8); return r.Done() && revision == view.revision && launch == view.launch; }
    }

    bool Id::Empty() const
    { return std::all_of(bytes.begin(), bytes.end(), [](uint8_t value) { return value == 0; }); }

    bool Encode(const Packet& packet, std::vector<uint8_t>& frame)
    {
        frame.clear();
        if (uint8_t(packet.type) < 1 || uint8_t(packet.type) > uint8_t(Type::Pong) ||
            packet.payload.size() > kMaxFrame - 52 || packet.sender.Empty() || !packet.serial) return false;
        Writer w; w.N(52 + packet.payload.size(), 4);
        const std::string magic = "BZLANP02"; w.data.insert(w.data.end(), magic.begin(), magic.end());
        w.N(uint8_t(packet.type), 1); w.N(0, 3); w.ID(packet.session); w.ID(packet.sender); w.N(packet.serial, 8);
        w.data.insert(w.data.end(), packet.payload.begin(), packet.payload.end());
        frame = std::move(w.data); return true;
    }

    bool Decoder::Feed(const uint8_t* bytes, size_t count, std::vector<Packet>& packets)
    {
        if (failed_) return false;
        // At most one bounded incomplete frame is retained. Process large
        // coalesced reads incrementally rather than allocating the input size.
        for (size_t offset = 0; offset < count;)
        {
            size_t wanted = 4;
            if (pending_.size() >= 4)
            {
                Reader header{pending_}; wanted = size_t(header.N(4)) + 4;
                if (wanted < 56 || wanted > kMaxFrame + 4) { failed_ = true; return false; }
            }
            const auto take = (std::min)(count - offset, wanted - pending_.size());
            pending_.insert(pending_.end(), bytes + offset, bytes + offset + take); offset += take;
            if (pending_.size() == 4)
            {
                Reader header{pending_}; const auto length = header.N(4);
                if (length < 52 || length > kMaxFrame) { failed_ = true; return false; }
            }
            if (pending_.size() < 4 || pending_.size() != wanted || wanted == 4) continue;
            Reader r{pending_}; r.N(4);
            std::string magic; for (size_t i = 0; i < 8; ++i) magic += char(r.N(1));
            Packet packet; packet.type = Type(r.N(1)); const auto reserved = r.N(3);
            packet.session = r.ID(); packet.sender = r.ID(); packet.serial = r.N(8);
            if (magic != "BZLANP02" || reserved || uint8_t(packet.type) < 1 ||
                uint8_t(packet.type) > uint8_t(Type::Pong) || packet.sender.Empty() || !packet.serial)
            { failed_ = true; return false; }
            packet.payload.assign(pending_.begin() + r.cursor, pending_.end());
            packets.push_back(std::move(packet)); pending_.clear();
        }
        return true;
    }

    Session::Session(Id local, std::string name, Compatibility compatibility, uint16_t port)
        : local_(local), name_(std::move(name)), compatibility_(std::move(compatibility)), gamePort_(port)
    { valid_ = !local_.Empty() && Text(name_, 31) && Valid(compatibility_) && port != 0; }

    bool Session::Host(Config config, Id session, uint32_t address, Time now)
    {
        if (!valid_ || view_.phase != Phase::Idle || session.Empty() || !Valid(config) ||
            !(config.compatibility == compatibility_) || !LocalAddress(address)) return false;
        host_ = true; view_ = {session, local_, std::move(config), 1, 0, Phase::Lobby, {}, ""};
        view_.members.push_back({local_, 0, name_, {address, gamePort_}, false, false});
        lastHeard_ = lastPing_ = now; EventOut(EventType::Changed); return true;
    }
    bool Session::Join(Connection connection, Id advertised, Time now)
    {
        if (!valid_ || !connection || view_.phase != Phase::Idle) return false;
        hostConnection_ = connection; view_.phase = Phase::Joining; view_.session = advertised;
        lastHeard_ = lastPing_ = now;
        Writer w; w.C(compatibility_); w.S(name_); w.N(gamePort_, 2);
        Send(connection, Type::Hello, w.data); return true;
    }
    void Session::Send(Connection connection, Type type, std::vector<uint8_t> payload, bool close)
    {
        if (view_.phase == Phase::Closed) return;
        if (outbound_.size() >= 256) { End("Control output queue exhausted"); return; }
        if (serial_ == (std::numeric_limits<uint64_t>::max)()) { End("Control sequence exhausted"); return; }
        outbound_.push_back({connection, {type, view_.session, local_, ++serial_, std::move(payload)}, close});
    }
    void Session::Broadcast(Type type, const std::vector<uint8_t>& payload)
    { for (const auto& link : links_) Send(link.connection, type, payload); }
    void Session::EventOut(EventType type, const std::string& reason)
    {
        if (type == EventType::Changed)
        {
            auto existing = std::find_if(events_.begin(), events_.end(), [](const Event& e) { return e.type == EventType::Changed; });
            if (existing != events_.end()) { existing->state = view_; return; }
        }
        if (events_.size() < 64) events_.push_back({type, reason, view_});
    }
    void Session::Publish()
    { Broadcast(Type::Snapshot, Snapshot(view_)); EventOut(EventType::Changed); }
    void Session::Changed(bool invalidate)
    {
        if (invalidate)
        {
            ++view_.revision; view_.launch = 0;
            for (auto& member : view_.members) member.ready = member.prepared = false;
            if (view_.phase == Phase::Preparing) view_.phase = Phase::Lobby;
        }
        Publish();
    }
    void Session::End(const std::string& reason, bool rejected)
    {
        if (view_.phase == Phase::Closed) return;
        view_.phase = Phase::Closed; view_.reason = reason;
        EventOut(rejected ? EventType::Rejected : EventType::Ended, reason);
    }

    void Session::Receive(Connection connection, uint32_t observed, const Packet& packet, Time now)
    {
        if (view_.phase == Phase::Closed || view_.phase == Phase::Idle || !connection ||
            packet.sender.Empty() || !packet.serial || packet.payload.size() > kMaxFrame - 52) return;
        if (host_)
        {
            auto link = std::find_if(links_.begin(), links_.end(), [&](const Link& l) { return l.connection == connection; });
            if (link == links_.end())
            {
                auto reject = [&](const std::string& reason) { Writer w; w.S(reason); Send(connection, Type::Reject, w.data, true); };
                if (packet.type != Type::Hello) { reject("Expected session greeting"); return; }
                Reader r{packet.payload}; const auto compatibility = r.C(); const auto name = r.S(31);
                const auto port = uint16_t(r.N(2));
                if (!r.Done() || !port || !LocalAddress(observed)) { reject("Invalid LAN greeting"); return; }
                if (view_.phase != Phase::Lobby) { reject("Session is launching or running"); return; }
                if (!packet.session.Empty() && packet.session != view_.session) { reject("Session changed"); return; }
                if (!(compatibility == view_.config.compatibility)) { reject("Game build or content differs"); return; }
                if (view_.members.size() >= view_.config.capacity) { reject("Session is full"); return; }
                if (std::any_of(view_.members.begin(), view_.members.end(), [&](const Member& m) { return m.id == packet.sender; }))
                { reject("Duplicate local identity"); return; }
                if (std::any_of(view_.members.begin(), view_.members.end(), [&](const Member& m)
                    { return m.endpoint.ipv4 == observed && m.endpoint.gamePort == port; }))
                { reject("Gameplay endpoint already in use"); return; }
                uint8_t slot = 1;
                while (std::any_of(view_.members.begin(), view_.members.end(), [&](const Member& m) { return m.slot == slot; })) ++slot;
                links_.push_back({connection, packet.sender, now, packet.serial});
                view_.members.push_back({packet.sender, slot, name, {observed, port}, false, false});
                Changed(true); return;
            }
            if (packet.sender != link->id || packet.session != view_.session || packet.serial <= link->serial) return;
            link->serial = packet.serial; link->heard = now;
            auto member = std::find_if(view_.members.begin(), view_.members.end(), [&](const Member& m) { return m.id == link->id; });
            if (packet.type == Type::Ready && view_.phase == Phase::Lobby)
            {
                Reader r{packet.payload}; const auto revision = r.N(8), ready = r.N(1);
                if (r.Done() && ready <= 1 && revision == view_.revision)
                { if (member->ready != (ready != 0)) { member->ready = ready != 0; Publish(); } }
            }
            else if (packet.type == Type::Prepared && view_.phase == Phase::Preparing && MatchesLaunch(view_, packet.payload))
            { member->prepared = true; CommitIfPrepared(); }
            else if (packet.type == Type::Leave) Disconnected(connection, "Player left");
            else if (packet.type == Type::Ping && packet.payload.empty()) Send(connection, Type::Pong);
        }
        else
        {
            if (connection != hostConnection_ || packet.serial <= receivedSerial_ ||
                (!view_.session.Empty() && packet.session != view_.session &&
                    !(view_.phase == Phase::Joining && packet.type == Type::Reject)) ||
                (!view_.owner.Empty() && packet.sender != view_.owner)) return;
            if (packet.type == Type::Reject || packet.type == Type::Close)
            {
                Reader r{packet.payload}; const auto reason = r.S(127);
                if (r.Done()) End(reason, packet.type == Type::Reject);
                return;
            }
            if (packet.session.Empty()) return;
            if (packet.type == Type::Snapshot && (view_.phase == Phase::Joining || view_.phase == Phase::Lobby ||
                    view_.phase == Phase::Preparing || view_.phase == Phase::Running))
            {
                View candidate;
                if (!ReadSnapshot(packet, candidate) || candidate.owner != packet.sender ||
                    !(candidate.config.compatibility == compatibility_) || candidate.revision < view_.revision ||
                    (view_.phase == Phase::Running && (candidate.phase != Phase::Running || candidate.launch != view_.launch)) ||
                    (view_.phase != Phase::Running && candidate.phase != Phase::Lobby) ||
                    (view_.phase == Phase::Preparing && candidate.revision == view_.revision) ||
                    std::none_of(candidate.members.begin(), candidate.members.end(), [&](const Member& m) { return m.id == local_; })) return;
                view_ = std::move(candidate); EventOut(EventType::Changed);
            }
            else if (packet.type == Type::Prepare && view_.phase == Phase::Lobby)
            {
                Reader r{packet.payload}; const auto revision = r.N(8), launch = r.N(8);
                if (!r.Done() || revision != view_.revision || !launch ||
                    !std::all_of(view_.members.begin(), view_.members.end(), [](const Member& m) { return m.ready; })) return;
                view_.launch = launch; view_.phase = Phase::Preparing; EventOut(EventType::Prepare);
            }
            else if (packet.type == Type::Commit && view_.phase == Phase::Preparing && MatchesLaunch(view_, packet.payload))
            {
                const auto self = std::find_if(view_.members.begin(), view_.members.end(), [&](const Member& m) { return m.id == local_; });
                if (!self->prepared) return;
                view_.phase = Phase::Running; EventOut(EventType::Started);
            }
            else if (packet.type == Type::Ping && packet.payload.empty()) Send(connection, Type::Pong);
            else if (packet.type != Type::Pong) return;
            receivedSerial_ = packet.serial; lastHeard_ = now;
        }
    }

    bool Session::SetReady(bool ready)
    {
        if (view_.phase != Phase::Lobby) return false;
        if (host_)
        {
            view_.members[0].ready = ready; Publish();
        }
        else { Writer w; w.N(view_.revision, 8); w.N(ready, 1); Send(hostConnection_, Type::Ready, w.data); }
        return true;
    }
    bool Session::SetConfig(Config config)
    {
        if (!host_ || view_.phase != Phase::Lobby || !Valid(config) ||
            !(config.compatibility == compatibility_) || config.capacity < view_.members.size()) return false;
        view_.config = std::move(config); Changed(true); return true;
    }
    bool Session::RequestStart(Time now)
    {
        if (!host_ || view_.phase != Phase::Lobby || view_.members.size() < 2 ||
            !std::all_of(view_.members.begin(), view_.members.end(), [](const Member& m) { return m.ready; })) return false;
        view_.phase = Phase::Preparing; view_.launch = serial_ + 1; prepareSince_ = now;
        for (auto& member : view_.members) member.prepared = false;
        Broadcast(Type::Prepare, Launch(view_)); EventOut(EventType::Prepare); return true;
    }
    void Session::CommitIfPrepared()
    {
        if (view_.phase == Phase::Preparing && std::all_of(view_.members.begin(), view_.members.end(),
                [](const Member& m) { return m.prepared; }))
        { Broadcast(Type::Commit, Launch(view_)); view_.phase = Phase::Running; EventOut(EventType::Started); }
    }
    bool Session::Prepared()
    {
        if (view_.phase != Phase::Preparing) return false;
        auto self = std::find_if(view_.members.begin(), view_.members.end(), [&](const Member& m) { return m.id == local_; });
        if (self == view_.members.end()) return false;
        self->prepared = true;
        if (host_) CommitIfPrepared(); else Send(hostConnection_, Type::Prepared, Launch(view_));
        return true;
    }
    void Session::Disconnected(Connection connection, const std::string& reason)
    {
        if (view_.phase == Phase::Closed || view_.phase == Phase::Idle) return;
        if (!host_) { if (connection == hostConnection_) End("Host disconnected: " + reason); return; }
        auto link = std::find_if(links_.begin(), links_.end(), [&](const Link& l) { return l.connection == connection; });
        if (link == links_.end()) return;
        const Id id = link->id; links_.erase(link);
        view_.members.erase(std::remove_if(view_.members.begin(), view_.members.end(), [&](const Member& m) { return m.id == id; }), view_.members.end());
        if (view_.phase == Phase::Running) { ++view_.revision; Publish(); }
        else Changed(true);
    }
    void Session::Leave()
    {
        if (view_.phase == Phase::Idle || view_.phase == Phase::Closed) return;
        if (host_) { Writer w; w.S("Host ended the session"); Broadcast(Type::Close, w.data); }
        else Send(hostConnection_, Type::Leave);
        End("Session left");
    }
    void Session::Tick(Time now)
    {
        if (view_.phase == Phase::Idle || view_.phase == Phase::Closed) return;
        if (host_)
        {
            std::vector<Connection> expired;
            for (const auto& link : links_) if (now >= link.heard && now - link.heard >= 5000) expired.push_back(link.connection);
            for (auto connection : expired) Disconnected(connection, "Connection timed out");
            if (view_.phase == Phase::Preparing && now >= prepareSince_ && now - prepareSince_ >= 10000)
                Changed(true);
        }
        else if (now >= lastHeard_ && now - lastHeard_ >= 5000)
        { End("Host connection timed out"); return; }
        if (now >= lastPing_ && now - lastPing_ >= 1000)
        {
            if (host_) Broadcast(Type::Ping); else Send(hostConnection_, Type::Ping);
            lastPing_ = now;
        }
    }
    std::vector<Outbound> Session::TakeOutbound() { auto out = std::move(outbound_); outbound_.clear(); return out; }
    std::vector<Event> Session::TakeEvents() { auto out = std::move(events_); events_.clear(); return out; }
    bool Session::HasConnection(Connection connection) const
    { return host_ ? std::any_of(links_.begin(), links_.end(), [&](const Link& l) { return l.connection == connection; }) : connection == hostConnection_; }
}
