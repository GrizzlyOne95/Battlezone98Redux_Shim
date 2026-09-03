#!/usr/bin/env bash
#
# One-line Linux / Proton installer. Paste from the README:
#   curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --native
#   curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --snap
#
# The default path downloads one GitHub release artifact set (DLL + patches.json
# + INIs from the same release). --dll is an advanced override and only
# proceeds when matching companions sit beside that DLL.
#
set -euo pipefail

# Canonical install source is the upstream repo. Override with OPENSHIM_REPO.
REPO_SLUG="${OPENSHIM_REPO:-GrizzlyOne95/Battlezone98Redux_Shim}"
REF="${OPENSHIM_REF:-main}"
WORKSHOP_ITEM="${OPENSHIM_WORKSHOP_ID:-3686673790}"
APPID=301650
FLAVOR="all"
GAME_PATH="${BZR_GAME_PATH:-}"
DLL_PATH="${OPENSHIM_DLL:-}"

usage() {
    cat <<EOF
Usage:
  install_linux.sh [--native | --snap] [--game-path DIR] [--dll FILE] [--ref git-ref]

    --native      Native Steam and Flatpak installs only
    --snap        Snap Steam installs only
    --game-path   One game directory (overrides flavour filter)
    --dll         Advanced: Win32 winmm.dll. Requires patches.json, openshim.ini,
                  and net.ini in the same directory (or scripts/patches.json).
    --ref         Git ref used only to fetch steam_game_paths.sh (default: $REF)

Environment:
  OPENSHIM_REPO / OPENSHIM_REF / OPENSHIM_DLL / BZR_GAME_PATH
EOF
}

validate_ref() {
    local ref="$1"
    if [[ -z "$ref" || ! "$ref" =~ ^[A-Za-z0-9._/-]+$ ]]; then
        echo "Refusing git ref '$ref'." >&2
        exit 1
    fi
    case "$ref" in
        -*|*..*|*//*|*/) echo "Refusing malformed git ref '$ref'." >&2; exit 1 ;;
    esac
}

download_to() {
    local url="$1"
    local out="$2"
    if command -v curl >/dev/null 2>&1; then
        curl -fsSL "$url" -o "$out"
        return
    fi
    if command -v wget >/dev/null 2>&1; then
        wget -qO "$out" "$url"
        return
    fi
    echo "Missing curl or wget." >&2
    exit 2
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

is_openshim_dll() {
    local dll="$1"
    [[ -f "$dll" ]] && grep -a -q "OpenShim" "$dll"
}

find_companions() {
    local dir="$1"
    PATCHES=""
    OPENSHIM_INI=""
    NET_INI=""
    if [[ -f "$dir/scripts/patches.json" ]]; then
        PATCHES="$dir/scripts/patches.json"
    elif [[ -f "$dir/patches.json" ]]; then
        PATCHES="$dir/patches.json"
    fi
    [[ -f "$dir/openshim.ini" ]] && OPENSHIM_INI="$dir/openshim.ini"
    [[ -f "$dir/net.ini" ]] && NET_INI="$dir/net.ini"
    [[ -n "$PATCHES" && -n "$OPENSHIM_INI" && -n "$NET_INI" ]]
}

download_matched_release() {
    local dest="$1"
    local repo base
    mkdir -p "$dest"
    for repo in "$REPO_SLUG"; do
        base="https://github.com/${repo}/releases/latest/download"
        echo "Downloading matched release set from $repo ..."
        if download_to "$base/winmm.dll" "$dest/winmm.dll" \
            && download_to "$base/patches.json" "$dest/patches.json" \
            && download_to "$base/openshim.ini" "$dest/openshim.ini" \
            && download_to "$base/net.ini" "$dest/net.ini" \
            && [[ -s "$dest/winmm.dll" && -s "$dest/patches.json" ]]; then
            echo "Using GitHub release artifacts from $repo"
            return 0
        fi
        rm -f "$dest/winmm.dll" "$dest/patches.json" "$dest/openshim.ini" "$dest/net.ini"
    done
    return 1
}

deploy_matched() {
    local game_dir="$1" dll="$2" patches="$3" ini="$4" net="$5"
    if [[ -f "$game_dir/winmm.dll" ]] && ! is_openshim_dll "$game_dir/winmm.dll"; then
        echo "error: refusing to overwrite non-OpenShim winmm.dll in $game_dir" >&2
        echo "Remove or rename that proxy first if you intend to replace it." >&2
        return 1
    fi
    echo "Installing OpenShim to: $game_dir"
    mkdir -p "$game_dir/scripts"
    local stamp
    stamp="$(date +%Y%m%d-%H%M%S)"
    local src dst
    for src in "$dll" "$patches" "$ini" "$net"; do
        case "$(basename "$src")" in
            winmm.dll) dst="$game_dir/winmm.dll" ;;
            patches.json) dst="$game_dir/scripts/patches.json" ;;
            openshim.ini) dst="$game_dir/openshim.ini" ;;
            net.ini) dst="$game_dir/net.ini" ;;
            *) continue ;;
        esac
        if [[ -f "$dst" ]]; then
            cp -f "$dst" "$dst.bak-$stamp"
        fi
        cp -f "$src" "$dst"
        echo "  deployed $(basename "$dst") ($(stat -c %s "$dst") bytes)"
    done
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
        --dll)
            [[ $# -ge 2 ]] || { echo "Missing value for --dll" >&2; exit 1; }
            DLL_PATH="$2"
            shift 2
            ;;
        --ref)
            [[ $# -ge 2 ]] || { echo "Missing value for --ref" >&2; exit 1; }
            REF="$2"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
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

dll=""
PATCHES=""
OPENSHIM_INI=""
NET_INI=""

if [[ -n "$DLL_PATH" ]]; then
    dll="$DLL_PATH"
    if ! find_companions "$(dirname "$dll")"; then
        echo "error: --dll requires a matched set: patches.json, openshim.ini, and net.ini" >&2
        echo "beside the DLL (or scripts/patches.json). Refusing to mix versions." >&2
        exit 1
    fi
    echo "Using explicit DLL with matched companions: $dll"
elif [[ -n "$script_dir" && -f "$script_dir/../bin/Release/winmm.dll" ]] \
    && find_companions "$(cd "$script_dir/.." && pwd)"; then
    dll="$(cd "$script_dir/.." && pwd)/bin/Release/winmm.dll"
    echo "Using local Release build with matched companions: $dll"
elif download_matched_release "$work/release"; then
    dll="$work/release/winmm.dll"
    PATCHES="$work/release/patches.json"
    OPENSHIM_INI="$work/release/openshim.ini"
    NET_INI="$work/release/net.ini"
else
    echo "error: could not download a matched OpenShim release set from $REPO_SLUG." >&2
    echo "Pass --dll with matching companions, or set OPENSHIM_REPO to a repo that publishes releases." >&2
    exit 1
fi

if [[ -z "$dll" || ! -f "$dll" || -z "$PATCHES" || -z "$OPENSHIM_INI" || -z "$NET_INI" ]]; then
    echo "error: matched OpenShim artifact set is incomplete." >&2
    exit 1
fi

echo "Installing to:"
printf '  %s\n' "${BZR_GAME_PATHS[@]}"

for game_dir in "${BZR_GAME_PATHS[@]}"; do
    deploy_matched "$game_dir" "$dll" "$PATCHES" "$OPENSHIM_INI" "$NET_INI"
    echo
done

cat <<'EOF'

Install complete.

Steam launch options still need to be set once
(Steam → Battlezone 98 Redux → Properties → Launch Options).

Native Steam or Flatpak:
  WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%

Snap Steam:
  WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%

Quotes are required. Drop dsound=n,b if you are not using the dsound netcode proxy.
EOF
