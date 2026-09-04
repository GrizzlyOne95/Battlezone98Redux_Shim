# Automatic session upload

Opt-in tooling for the test crew. It is not part of the player install.
Adding the wrapper to Steam launch options is the consent step: **no wrapper
in the launch options, nothing ever uploads.**

The wrapper runs outside the game process, so it still fires after a crash.
It snapshots `BZLogger.txt` and `openshim.log` *before* launch because both
are overwritten on the next start.

## Setup

The webhook URL is pinned in the private Discord channel the bundles land in.
It is never written to this repo. Discord auto-revokes webhook URLs that
appear on GitHub.

Test-crew job:

1. Paste the pinned install command from the private channel (the normal
   `GrizzlyOne95/Battlezone98Redux_Shim` install plus `OPENSHIM_WEBHOOK`).
2. Copy the **one** launch-option line the installer prints. Don't guess.

Or configure by hand after copying the wrapper:

```bash
# Linux
mkdir -p ~/.local/share/openshim
cp upload/openshim_wrap.sh ~/.local/share/openshim/
~/.local/share/openshim/openshim_wrap.sh --setup
```

```powershell
# Windows
mkdir "$env:LOCALAPPDATA\openshim"
copy upload\openshim_wrap.ps1,upload\openshim_wrap.bat "$env:LOCALAPPDATA\openshim\"
powershell -ExecutionPolicy Bypass -File "$env:LOCALAPPDATA\openshim\openshim_wrap.ps1" -Setup
```

Then set Steam launch options (Steam → Battlezone 98 Redux → Properties →
Launch Options).

```text
Windows:
  cmd /c ""%LOCALAPPDATA%\openshim\openshim_wrap.bat" %command%"

Linux native / Flatpak:
  WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" "${XDG_DATA_HOME:-$HOME/.local/share}/openshim/openshim_wrap.sh" %command%

Linux Snap:
  WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" "$SNAP_USER_COMMON/.local/share/openshim/openshim_wrap.sh" %command%
```

The doubled quotes on the Windows line are load-bearing. A console window
stays open while the game runs — that is the wrapper waiting to bundle on
exit. Closing it kills the upload, not the game.

The Linux native line also covers Flatpak: Steam evaluates launch options
through a shell, and Flatpak remaps `XDG_DATA_HOME` into its sandbox.

Snap needs its own line. Snap remaps `HOME` and cannot read the host's
dot-dirs. `$SNAP_USER_COMMON` is set by snapd inside the sandbox. The Steam
snap runtime has neither curl nor python3, so bundles park in the outbox
and a host-side systemd user path/timer (`openshim-retry`) drains them.

`install_linux.sh` mirrors the wrapper and `upload.conf` into the Snap
(`~/snap/steam/common/.local/share/openshim/`) and Flatpak
(`~/.var/app/com.valvesoftware.Steam/data/openshim/`) dirs whenever those
Steams exist.

## What it sends

On every wrapped exit it zips (Windows) or xz-compresses (Linux) and POSTs:

- `openshim.log` and `openshim_crash.log` (from `logs\`, with a game-root fallback)
- a pre-launch snapshot of `openshim.log` (the previous session)
- `BZLogger.txt` plus its pre-launch snapshot
- `winmm_proxy.log` / `dsound_proxy.log` when present
- `multi.ini`
- session-fresh buffer-capture files and `openshim_crash_*.dmp` minidumps
- `meta.txt` (UTC time, hostname, player name, exit code, wrapper version)

A bundle over the ~10 MB webhook cap is split; reassemble with
`cat *.part* > bundle.tar.xz` or `copy /b` on Windows.

**Menu-only sessions are sent too** so a silent skip cannot be mistaken for
a broken uploader. Set `OPENSHIM_UPLOAD_MENU=0` in `upload.conf` to skip them.

**Upload failed or offline** → the bundle is parked in an outbox and retried
on the next wrapped launch.

## The webhook URL is never committed

`--setup` and the installer write it to `~/.config/openshim/upload.conf`
(mode 600) or `%APPDATA%\openshim\upload.conf`. `OPENSHIM_UPLOAD_WEBHOOK`
overrides it for unattended runs. `OPENSHIM_REPO` / `OPENSHIM_REF` override
where a piped install fetches the wrapper; the default is
`GrizzlyOne95/Battlezone98Redux_Shim` on `main`.

## Privacy

Bundles can contain every peer's public IP. The destination is a private
channel only. Remove the launch-option wrapper and nothing is ever sent again.

## Other commands

```bash
openshim_wrap.sh --status    # configuration and how many bundles are waiting
openshim_wrap.sh --retry     # send the outbox now and exit
```
