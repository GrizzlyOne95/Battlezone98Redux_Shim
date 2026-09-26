#!/usr/bin/env bash
#
# One-line Linux / Proton uninstaller. Paste from the README:
#   curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_linux.sh | bash -s -- --native
#   curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_linux.sh | bash -s -- --snap
#
# Removes everything install_linux.sh deploys, from every detected game
# directory of the chosen Steam flavour (or the one named by --game-path): the
# three-binary load chain (winmm.dll, bzloader.dll, plugins/openshim.dll),
# scripts/patches.json, the Enhanced renderer resources and asset manifest
# under openshim/, the four UI widget tiles, openshim.ini.canonical, the
# .bak-<stamp> copies the installer made of those files on each run, and what
# the Workshop updater leaves behind (winmm.dll.previous,
# scripts/patches.json.previous, openshim_update.status).
#
# A binary is removed only when it identifies as OpenShim; a foreign winmm.dll
# (another proxy) is kept and reported. openshim.ini and its backups, net.ini
# and its backups, and logs/ are left in place so a reinstall finds the
# player's settings; net.ini in particular is a game file OpenShim replaced,
# and the stock bytes are not known here.
#
# The Steam launch options and the optional log-upload wrapper are outside the
# game directory; the script says where they are and leaves them.

set -euo pipefail

REPO_SLUG="${OPENSHIM_REPO:-GrizzlyOne95/Battlezone98Redux_Shim}"
REF="${OPENSHIM_REF:-main}"
FLAVOR="all"
GAME_PATH="${BZR_GAME_PATH:-}"
PURGE_CONFIG="${OPENSHIM_PURGE_CONFIG:-0}"
DRY_RUN="${OPENSHIM_DRY_RUN:-0}"

# UI tiles the installer writes into the game's custom-widget resource tree.
UI_TILES=("uiline.png" "uiplate.png" "uibtn.png" "uibtnhv.png")

usage() {
    cat <<EOF
Usage:
  uninstall_linux.sh [--native | --snap] [--game-path DIR] [--ref git-ref] [--purge-config] [--dry-run]

    --native        Native Steam and Flatpak installs only
    --snap          Snap Steam installs only
    --game-path     One game directory (overrides flavour filter)
    --ref           Git ref used only to fetch steam_game_paths.sh (default: $REF)
    --purge-config  Also remove openshim.ini and its backups
    --dry-run       Print what would be removed, remove nothing

Environment:
  OPENSHIM_REPO / OPENSHIM_REF / BZR_GAME_PATH
  OPENSHIM_PURGE_CONFIG / OPENSHIM_DRY_RUN   same as the flags when 1
EOF
}

validate_ref() {
    local ref="$1"
    if [[ ! "$ref" =~ ^[A-Za-z0-9._/-]+$ || "$ref" == -* || "$ref" == *..* || "$ref" == *//* || "$ref" == */ ]]; then
        echo "error: refusing malformed OPENSHIM_REF '$ref'" >&2
        exit 1
    fi
}

download_to() {
    local url="$1" dest="$2"
    if command -v curl >/dev/null 2>&1; then
        curl -fsSL "$url" -o "$dest"
    elif command -v wget >/dev/null 2>&1; then
        wget -qO "$dest" "$url"
    else
        echo "error: need curl or wget to fetch $url" >&2
        return 1
    fi
}

is_snap_game() {
    [[ "$1" == "$HOME/snap/steam/"* ]]
}

filter_flavor() {
    local flavor="$1"
    local kept=()
    local path
    for path in "${BZR_GAME_PATHS[@]:-}"; do
        case "$flavor" in
            all) kept+=("$path") ;;
            snap) is_snap_game "$path" && kept+=("$path") ;;
            native) is_snap_game "$path" || kept+=("$path") ;;
        esac
    done
    if [[ ${#kept[@]} -gt 0 ]]; then
        BZR_GAME_PATHS=("${kept[@]}")
    else
        BZR_GAME_PATHS=()
    fi
}

# Every OpenShim binary (bootstrap, loader, plugin) carries the ASCII string
# "OpenShim". A winmm.dll without it is somebody else's proxy.
is_openshim_dll() {
    local dll="$1"
    [[ -f "$dll" ]] && grep -a -q "OpenShim" "$dll"
}

removed=0
kept=0
failed=0

remove_planned() {
    local path="$1"
    if [[ "$DRY_RUN" == "1" ]]; then
        echo "  would remove $path"
        removed=$((removed + 1))
        return 0
    fi
    if rm -rf -- "$path"; then
        echo "  removed $path"
        removed=$((removed + 1))
    else
        echo "  FAILED  $path"
        failed=$((failed + 1))
    fi
}

remove_if_present() {
    local path="$1"
    [[ -f "$path" ]] && remove_planned "$path"
    return 0
}

remove_openshim_binary() {
    local path="$1"
    [[ -f "$path" ]] || return 0
    if is_openshim_dll "$path"; then
        remove_planned "$path"
    else
        echo "  KEEPING $path : it does not identify as OpenShim"
        kept=$((kept + 1))
    fi
}

# $1 = file whose ".bak-<stamp>" siblings go; $2 = "identity" to check each one.
remove_backups() {
    local path="$1" mode="${2:-}"
    local dir backup
    dir="$(dirname "$path")"
    [[ -d "$dir" ]] || return 0
    for backup in "$path".bak-*; do
        [[ -f "$backup" ]] || continue
        if [[ "$mode" == "identity" ]]; then
            remove_openshim_binary "$backup"
        else
            remove_planned "$backup"
        fi
    done
}

remove_dir_if_empty() {
    local dir="$1"
    [[ -d "$dir" && "$DRY_RUN" != "1" ]] || return 0
    if [[ -z "$(ls -A -- "$dir")" ]]; then
        rmdir -- "$dir" && echo "  removed empty folder $dir"
    fi
}

uninstall_from() {
    local game_dir="$1"
    local relative patches openshim_dir render_dir ui_dir tile ini reset

    echo
    echo "Game folder: $game_dir"

    # Load chain, plus the previous-version copy the Workshop updater keeps.
    for relative in winmm.dll winmm.dll.previous bzloader.dll plugins/openshim.dll; do
        remove_openshim_binary "$game_dir/$relative"
    done
    for relative in winmm.dll bzloader.dll plugins/openshim.dll; do
        remove_backups "$game_dir/$relative" identity
    done
    remove_dir_if_empty "$game_dir/plugins"

    # patches.json travels with the DLL and nothing else writes that name.
    patches="$game_dir/scripts/patches.json"
    remove_if_present "$patches"
    remove_if_present "$patches.previous"
    remove_backups "$patches"

    # Enhanced renderer resources and the asset manifest. openshim/ is created
    # by the installer, but only its own entries are removed; anything else a
    # player put there is reported and left.
    openshim_dir="$game_dir/openshim"
    render_dir="$openshim_dir/renderer/enhanced"
    [[ -d "$render_dir" ]] && remove_planned "$render_dir"
    remove_if_present "$openshim_dir/OpenShimAssets.ini"
    remove_dir_if_empty "$openshim_dir/renderer"
    remove_dir_if_empty "$openshim_dir"
    if [[ "$DRY_RUN" != "1" && -d "$openshim_dir" ]]; then
        echo "  KEEPING $openshim_dir : it still holds files the installer did not put there"
        kept=$((kept + 1))
    fi

    # The four widget tiles; the folder may hold the game's or the player's own
    # widgets, so it goes only when those four were all it contained.
    ui_dir="$game_dir/BZ_ASSETS_CORE/common/ui/CustomWidgets"
    for tile in "${UI_TILES[@]}"; do
        remove_if_present "$ui_dir/$tile"
    done
    remove_dir_if_empty "$ui_dir"

    # Installer-owned copy of the shipped preset, and the updater's status file.
    remove_if_present "$game_dir/openshim.ini.canonical"
    remove_if_present "$game_dir/openshim_update.status"

    if [[ "$PURGE_CONFIG" == "1" ]]; then
        ini="$game_dir/openshim.ini"
        remove_if_present "$ini"
        remove_backups "$ini"
        for reset in "$ini".pre-reset-*.bak; do
            [[ -f "$reset" ]] && remove_planned "$reset"
        done
    fi
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --native) FLAVOR="native"; shift ;;
        --snap) FLAVOR="snap"; shift ;;
        --game-path)
            [[ $# -ge 2 ]] || { echo "Missing value for --game-path" >&2; exit 1; }
            GAME_PATH="$2"
            shift 2
            ;;
        --ref)
            [[ $# -ge 2 ]] || { echo "Missing value for --ref" >&2; exit 1; }
            REF="$2"
            shift 2
            ;;
        --purge-config) PURGE_CONFIG="1"; shift ;;
        --dry-run) DRY_RUN="1"; shift ;;
        -h|--help) usage; exit 0 ;;
        *)
            echo "Unknown argument: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
done

validate_ref "$REF"

work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

# Same discovery as install_linux.sh: the checkout's own steam_game_paths.sh
# when run from one, otherwise the copy at the same ref.
src=""
script_dir=""
if [[ -n "${BASH_SOURCE[0]:-}" ]]; then
    script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" 2>/dev/null && pwd || true)"
fi
if [[ -n "$script_dir" && -f "$script_dir/steam_game_paths.sh" ]]; then
    src="$script_dir"
else
    download_to "https://raw.githubusercontent.com/${REPO_SLUG}/${REF}/scripts/steam_game_paths.sh" \
        "$work/steam_game_paths.sh"
    src="$work"
fi

# shellcheck source=scripts/steam_game_paths.sh
source "$src/steam_game_paths.sh"

if [[ -n "$GAME_PATH" ]]; then
    if [[ ! -f "$GAME_PATH/battlezone98redux.exe" && ! -f "$GAME_PATH/BZR.exe" ]]; then
        echo "error: --game-path is not a Battlezone 98 Redux install: $GAME_PATH" >&2
        exit 1
    fi
    BZR_GAME_PATH="$GAME_PATH"
fi
detect_bzr_game_paths
if [[ -z "$GAME_PATH" ]]; then
    filter_flavor "$FLAVOR"
fi

if [[ ${#BZR_GAME_PATHS[@]} -eq 0 ]]; then
    echo "error: no Battlezone 98 Redux install found for this Steam flavour." >&2
    case "$FLAVOR" in
        native) echo "Use the Snap paste command if you installed Steam from Snap." >&2 ;;
        snap) echo "Use the Native/Flatpak paste command if you are not on Snap Steam." >&2 ;;
    esac
    exit 1
fi

# Refuse before touching anything: a running game holds the DLLs open under
# Proton, and a half-removed load chain is the one state nothing handles.
for game_dir in "${BZR_GAME_PATHS[@]}"; do
    if pgrep -f "$game_dir/battlezone98redux.exe" >/dev/null 2>&1 || \
       pgrep -f "$game_dir/BZR.exe" >/dev/null 2>&1; then
        echo "error: Battlezone 98 Redux is running from $game_dir. Close the game, then run the uninstaller again. Nothing was removed." >&2
        exit 1
    fi
done

[[ "$DRY_RUN" == "1" ]] && echo "Dry run: nothing will be removed."

for game_dir in "${BZR_GAME_PATHS[@]}"; do
    uninstall_from "$game_dir"
done

echo
if [[ "$DRY_RUN" == "1" ]]; then
    echo "Dry run complete: $removed item(s) would be removed, $kept kept."
else
    echo "Uninstall complete: $removed item(s) removed, $kept kept."
fi
if [[ "$PURGE_CONFIG" == "1" ]]; then
    echo "openshim.ini and its backups were removed. net.ini and logs were left in place."
else
    echo "openshim.ini, net.ini, their backups, and logs were left in place."
    echo "Run again with --purge-config to remove openshim.ini as well."
fi

cat <<EOF

Steam launch options are not touched: remove the WINEDLLOVERRIDES line from
Steam -> Battlezone 98 Redux -> Properties -> Launch Options, or the game will
keep looking for a proxy that is no longer there.
EOF

for wrapper_dir in "${XDG_DATA_HOME:-$HOME/.local/share}/openshim" "$HOME/snap/steam/common/.local/share/openshim"; do
    if [[ -d "$wrapper_dir" ]]; then
        echo "The optional log-upload wrapper is still installed at $wrapper_dir;"
        echo "delete that folder (and its systemd --user timer, if you enabled one) once the launch option no longer names it."
    fi
done

if [[ "$failed" -gt 0 ]]; then
    echo "error: $failed item(s) could not be removed (listed above as FAILED)." >&2
    exit 1
fi
