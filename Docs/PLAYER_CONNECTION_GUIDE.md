# How to play multiplayer with OpenShim

Battlezone 98 Redux with OpenShim (the Open Community Patch) now has several
ways to get players into the same game. Pick the row that fits, then read its
section.

| You want to... | Use | Steam | GOG | Setup |
|---|---|---|---|---|
| Join or host a normal public game | [Rebellion lobby](#1-rebellion-lobby-stock) | yes | yes | none |
| Play with a Steam friend, no port forwarding | [Steam host + invite / Join Game](#2-host-for-steam-players-from-your-own-pc) | yes | no | one click |
| Let any Steam player find your home-hosted game | [Steam list](#3-public-steam-listing) | yes | no | one click |
| Keep strangers out | [Lobby password, bans](#4-passwords-and-bans) | yes | yes | optional |
| Join a server by address (VPN, Tailscale, a friend's server) | [Custom server](#5-custom-server-by-address) | yes | yes | type an address |
| Play on a home network with nobody signed in | [LAN, no sign-in](#6-lan-with-no-sign-in-experimental) | yes | yes | edit `openshim.ini` (experimental) |

**Everyone needs OpenShim** for anything past row 1. Steam players get it
from the Campaign Reimagined Workshop item or `OpenShimSetup.exe`; GOG players
use `OpenShimSetup.exe`.

**Steam and GOG cannot play together.** Their lobby networks are separate, and
the Steam host tools below use Steam's relay, which GOG copies cannot reach.

## Where the choices are

Click **Multiplayer**. OpenShim shows a **SERVER** box before the lobby:

- **Rebellion**: the stock lobby browser, the default.
- **Custom**: a server address you type.
- **Local**: a server running on this PC.
- **Local host tools**: the LAN screen (the button is named **LAN (no
  sign-in)** when `NoAuthLan=1`), with **Start host**, **Steam list** (Steam copies only), **Refresh** and the list of
  games found.

Your choice is saved in `openshim.ini` (`[Network] Server=` and
`CustomServer=`). To skip the box, set `[Network] PreLobby=0`.

## 1. Rebellion lobby (stock)

Leave the SERVER box on **Rebellion** and use the lobby browser as before.
Steam players see Steam games and GOG players see GOG games. Hosting a public
game this way needs nothing extra.

## 2. Host for Steam players from your own PC

No port forwarding and no INI edits. Traffic goes over Steam's relay network.

Host:

1. Multiplayer > **Local host tools**.
2. Set **Steam list: On**, then click **Start host**. The status line reads
   "Hosting in this game on 127.0.0.2 (Steam players only, via the Steam
   bridge)" and your game joins it.
3. Create your game in the lobby as usual.

Friends (game running, in the menus, not in a mission):

- Accept your Steam invite, or use **Join Game** on you in the Steam friends
  list. Their game switches to your server by itself.

Notes:

- A game hosted this way is for Steam players only. Players on your home
  network cannot reach it; for them, turn the Steam list off and use
  [section 6](#6-lan-with-no-sign-in-experimental).
- Hosting for Steam needs **Steam list: On**, so the game is also listed
  publicly ([section 3](#3-public-steam-listing)). A lobby password is the
  only way to keep it to friends.
- Tested on two PCs with two Steam accounts (2026-11-08): the friend joined
  and was authorized. A full match through this one-click host, joining from
  inside a mission, and Linux/Steam Deck (Proton) are not tested yet. Please
  report what you see.

## 3. Public Steam listing

Host: as in [section 2](#2-host-for-steam-players-from-your-own-pc),
**Steam list: On** then **Start host**. The setting is saved as
`[Network] SteamPublicListing=1` (default off).

Anyone else on Steam with OpenShim: Multiplayer > **Local host tools** >
**Refresh**. Steam-listed games show as `[Steam]` rows (up to 50, worldwide).
Pick one to join.

Your lobby password and your ban list are the only gate, so set a password if
you don't want strangers.

## 4. Passwords and bans

- **Password invites:** a friend invited to a private, passworded lobby joins
  with no password prompt; the invite carries it (`[Fixes] InvitePassword=1`,
  on by default). Before this fix, such invites stalled on "gathering
  information from the server". A passworded lobby hides **Join Game**, so
  friends join it by invite.
- **Bans:** the host's `/ban` command (and the optional lobby Ban button,
  `[Network] LobbyBanButton=1`) writes `bans.cfg` in the game folder. A banned
  Steam player is dropped from a Steam-hosted game within about a second and
  cannot rejoin. Delete their line from `bans.cfg` to lift the ban.

## 5. Custom server by address

Multiplayer > **Custom**, then type the server's host name or IP address
(optionally `:port`; the default is 1337). Use this for a dedicated server, a
friend's server over Tailscale or another VPN, or a port-forwarded host.
Custom servers never receive your Steam or GOG sign-in ticket.

The same thing as a Steam or GOG launch option: `/bzrserver=ws://IP:1337/`.

A server reached from the internet needs TCP 1337 and UDP 1338 (or the
server's own ports) open on the host's router. A VPN such as Tailscale avoids that.

## 6. LAN with no sign-in (experimental)

For a home network or LAN party, with nobody signed in to Steam or GOG.
Turn it on in `openshim.ini`: `[Network] NoAuthLan=1` (default off), on every
PC.

- Host: Multiplayer > **LAN (no sign-in)** > **Start host**, then create the
  game in the lobby.
- Others: the same screen lists games found on the network (UDP 21337), or
  type the host's private IP address.
- The host's firewall must allow TCP 1337, UDP 1338 and UDP 21337 on the
  private network.

This is still being qualified and is not ready for general play.

## Kill switches

If one of these causes trouble, turn it off and report it:

| Feature | Off switch |
|---|---|
| SERVER box | `openshim.ini [Network] PreLobby=0` |
| Steam invite / Join Game redirect | environment variable `OPENSHIM_DISABLE_STEAM_TUNNEL_JOIN=1` |
| Public Steam listing | **Steam list: Off**, or `OPENSHIM_DISABLE_STEAM_PUBLIC_LISTING=1` |
| Password in invites | `openshim.ini [Fixes] InvitePassword=0` |
| In-game Steam bridge | `net.ini [OpenShimSocket] SteamTunnelBridge=` (empty) |

Technical details: [STEAM_TUNNEL.md](STEAM_TUNNEL.md),
[LAN_MULTIPLAYER.md](LAN_MULTIPLAYER.md), [NO_AUTH_LAN.md](NO_AUTH_LAN.md).
