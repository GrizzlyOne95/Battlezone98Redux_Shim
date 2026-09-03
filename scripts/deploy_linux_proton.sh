#!/usr/bin/env bash
#
# deploy_linux_proton.sh — Deploy OpenShim into Battlezone 98 Redux installs
# running under Steam Proton on Linux (native, Flatpak, or Snap Steam).
#
# winmm.dll and scripts/patches.json must move together. OpenShim also ships
# openshim.ini and net.ini beside the game executable; those carry the V5.3-
# aligned networking preset when GovernorTuning = OpenShim.
#
# Build winmm.dll on Windows first (Release | Win32), then deploy from Linux:
#   ./scripts/deploy_linux_proton.sh [GAME_DIR] [DLL_PATH]
#
# With no GAME_DIR, every detected install is patched (native + Flatpak + Snap
# on the same machine). Set BZR_GAME_PATH to force one directory.
#
set -euo pipefail

APPID=301650
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# shellcheck source=scripts/steam_game_paths.sh
source "$SCRIPT_DIR/steam_game_paths.sh"

usage() {
    cat <<EOF
Usage:
  $0 [GAME_DIR] [DLL_PATH]

Environment:
  BZR_GAME_PATH   Deploy to this directory only (overrides auto-detect)
  STEAM_ROOT      Extra Steam root to scan for libraryfolders.vdf entries

Defaults:
  DLL_PATH        $REPO_ROOT/bin/Release/winmm.dll
EOF
}

GAME_DIR="${1:-}"
DLL="${2:-$REPO_ROOT/bin/Release/winmm.dll}"
PATCHES="$SCRIPT_DIR/patches.json"
OPENSHIM_INI="$REPO_ROOT/openshim.ini"
NET_INI="$REPO_ROOT/net.ini"
RENDER_SOURCE="$REPO_ROOT/resources/renderer/enhanced"
UI_SOURCE="$REPO_ROOT/resources/ui/custom_widgets"

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
    usage
    exit 0
fi

if [[ -n "$GAME_DIR" ]]; then
    BZR_GAME_PATH="$GAME_DIR"
fi

detect_bzr_game_paths

if [[ ${#BZR_GAME_PATHS[@]} -eq 0 ]]; then
    echo "error: could not find Battlezone 98 Redux (AppID $APPID)." >&2
    echo "Install the game in Steam, or pass the game directory explicitly." >&2
    echo >&2
    echo "Typical paths:" >&2
    echo "  Native:  ~/.local/share/Steam/steamapps/common/Battlezone 98 Redux" >&2
    echo "  Flatpak: ~/.var/app/com.valvesoftware.Steam/data/Steam/steamapps/common/Battlezone 98 Redux" >&2
    echo "  Snap:    ~/snap/steam/common/.local/share/Steam/steamapps/common/Battlezone 98 Redux" >&2
    exit 1
fi

if [[ ! -f "$DLL" ]]; then
    echo "error: winmm.dll not found: $DLL" >&2
    echo "Build Release | Win32 on Windows (see README), then copy bin/Release/winmm.dll here" >&2
    echo "or pass the DLL path as the second argument." >&2
    exit 1
fi

if [[ ! -f "$PATCHES" ]]; then
    echo "error: patches.json not found: $PATCHES" >&2
    exit 1
fi

if [[ ! -f "$OPENSHIM_INI" ]]; then
    echo "error: openshim.ini not found: $OPENSHIM_INI" >&2
    exit 1
fi

if [[ ! -f "$NET_INI" ]]; then
    echo "error: net.ini not found: $NET_INI" >&2
    exit 1
fi

if [[ ${#BZR_GAME_PATHS[@]} -gt 1 ]]; then
    echo "Found ${#BZR_GAME_PATHS[@]} Battlezone installs; deploying to all:"
    printf '  %s\n' "${BZR_GAME_PATHS[@]}"
    echo
fi

stamp="$(date +%Y%m%d-%H%M%S)"

deploy_file() {
    local src="$1" dst="$2"
    local dst_dir
    dst_dir="$(dirname "$dst")"
    mkdir -p "$dst_dir"
    if [[ -f "$dst" ]]; then
        cp -f "$dst" "$dst.bak-$stamp"
    fi
    cp -f "$src" "$dst"
    echo "  deployed $(basename "$dst") ($(stat -c %s "$dst") bytes)"
}

verify_patches_json() {
    local repo_json="$1" game_json="$2"
    python3 - "$repo_json" "$game_json" <<'PY'
import json
import sys

repo_path, game_path = sys.argv[1:3]
with open(repo_path, encoding="utf-8") as fh:
    repo = json.load(fh)
with open(game_path, encoding="utf-8") as fh:
    game = json.load(fh)

missing = []
for group in ("patches", "globals", "static_pointers"):
    repo_names = {entry["name"] for entry in repo.get(group, [])}
    game_names = {entry["name"] for entry in game.get(group, [])}
    missing.extend(sorted(repo_names - game_names))

if missing:
    print("missing patch names:", ", ".join(missing), file=sys.stderr)
    sys.exit(1)
PY
}

deploy_one_game() {
    local game_dir="$1"
    if ! _bzr_game_exe_present "$game_dir"; then
        echo "error: game executable not found in: $game_dir" >&2
        return 1
    fi

    echo "Deploying OpenShim to: $game_dir"
    deploy_file "$DLL" "$game_dir/winmm.dll"
    deploy_file "$PATCHES" "$game_dir/scripts/patches.json"
    deploy_file "$OPENSHIM_INI" "$game_dir/openshim.ini"
    deploy_file "$NET_INI" "$game_dir/net.ini"

    if [[ -d "$RENDER_SOURCE" && -f "$RENDER_SOURCE/resources.version" ]]; then
        local render_target="$game_dir/openshim/renderer/enhanced"
        mkdir -p "$render_target"
        cp -f "$RENDER_SOURCE"/* "$render_target/"
        echo "  deployed renderer resources"
    fi

    if [[ -d "$UI_SOURCE" ]]; then
        local ui_target="$game_dir/BZ_ASSETS_CORE/common/ui/CustomWidgets"
        mkdir -p "$ui_target"
        local ui_file
        for ui_file in uiline.png uiplate.png uibtn.png uibtnhv.png; do
            if [[ -f "$UI_SOURCE/$ui_file" ]]; then
                cp -f "$UI_SOURCE/$ui_file" "$ui_target/"
            fi
        done
        echo "  deployed UI flat tiles (when present under resources/ui/custom_widgets)"
    fi

    verify_patches_json "$PATCHES" "$game_dir/scripts/patches.json"
    echo "  patches.json verified"
}

for game_dir in "${BZR_GAME_PATHS[@]}"; do
    deploy_one_game "$game_dir"
    echo
done

echo "Deploy complete. Launch Battlezone 98 Redux (AppID $APPID) through Steam."
echo "Backups use suffix .bak-$stamp"
if [[ "${OPENSHIM_INSTALLER:-}" != "1" ]]; then
    echo "Proton launch options (quotes required):"
    echo '  Native / Flatpak:  WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%'
    echo '  Snap Steam:        WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%'
fi
