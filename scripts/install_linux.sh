#!/usr/bin/env bash
#
# One-line Linux / Proton installer. Paste from the README:
#   curl -fsSL https://raw.githubusercontent.com/PiercingXX/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --native
#   curl -fsSL https://raw.githubusercontent.com/PiercingXX/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --snap
#
# This script downloads the matching git ref, finds a Win32 winmm.dll
# (explicit path, Workshop OpenShim, or GitHub release), and deploys it.
#
set -euo pipefail

# Baked: this file's home. Override with OPENSHIM_REPO / OPENSHIM_REF.
REPO_SLUG="${OPENSHIM_REPO:-PiercingXX/Battlezone98Redux_Shim}"
REF="${OPENSHIM_REF:-main}"
RELEASE_REPO="${OPENSHIM_RELEASE_REPO:-GrizzlyOne95/Battlezone98Redux_Shim}"
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
    --dll         Win32 winmm.dll to deploy
    --ref         Git ref to fetch (default: $REF)

Environment:
  OPENSHIM_REPO / OPENSHIM_REF / OPENSHIM_DLL / OPENSHIM_RELEASE_REPO
  BZR_GAME_PATH
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

find_workshop_dll() {
    local roots=(
        "$HOME/.local/share/Steam"
        "$HOME/.steam/steam"
        "$HOME/.steam/root"
        "$HOME/snap/steam/common/.local/share/Steam"
        "$HOME/snap/steam/current/.local/share/Steam"
        "$HOME/.var/app/com.valvesoftware.Steam/data/Steam"
        "$HOME/.var/app/com.valvesoftware.Steam/.local/share/Steam"
    )
    [[ -n "${STEAM_ROOT:-}" ]] && roots+=("$STEAM_ROOT")
    local root dll vdf line lib
    for root in "${roots[@]}"; do
        dll="$root/steamapps/workshop/content/$APPID/$WORKSHOP_ITEM/winmm.dll"
        if [[ -f "$dll" ]]; then
            printf '%s\n' "$dll"
            return 0
        fi
        for vdf in "$root/steamapps/libraryfolders.vdf" "$root/config/libraryfolders.vdf"; do
            [[ -f "$vdf" ]] || continue
            while IFS= read -r line || [[ -n "$line" ]]; do
                if [[ "$line" =~ \"path\"[[:space:]]+\"(.*)\" ]]; then
                    lib="${BASH_REMATCH[1]//\\\\//}"
                    dll="$lib/steamapps/workshop/content/$APPID/$WORKSHOP_ITEM/winmm.dll"
                    if [[ -f "$dll" ]]; then
                        printf '%s\n' "$dll"
                        return 0
                    fi
                fi
            done < "$vdf"
        done
    done
    return 1
}

download_release_dll() {
    local dest="$1"
    local repo
    for repo in "$REPO_SLUG" "$RELEASE_REPO"; do
        if download_to "https://github.com/${repo}/releases/latest/download/winmm.dll" "$dest" 2>/dev/null; then
            if [[ -s "$dest" ]]; then
                echo "Using GitHub release winmm.dll from $repo" >&2
                return 0
            fi
        fi
        rm -f "$dest"
    done
    return 1
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

src=""
script_dir=""
if [[ -n "${BASH_SOURCE[0]:-}" ]]; then
    script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" 2>/dev/null && pwd || true)"
fi
if [[ -n "$script_dir" && -f "$script_dir/steam_game_paths.sh" && -f "$script_dir/deploy_linux_proton.sh" ]]; then
    src="$(cd "$script_dir/.." && pwd)"
    echo "Using local repo: $src"
else
    if [[ "$REF" =~ ^[0-9a-fA-F]{7,40}$ ]]; then
        ARCHIVE_URL="https://github.com/${REPO_SLUG}/archive/${REF}.tar.gz"
    else
        ARCHIVE_URL="https://github.com/${REPO_SLUG}/archive/refs/heads/${REF}.tar.gz"
    fi

    work="$(mktemp -d)"
    trap 'rm -rf "$work"' EXIT

    echo "Downloading $REPO_SLUG @$REF ..."
    download_to "$ARCHIVE_URL" "$work/src.tar.gz"
    if ! tar -tzf "$work/src.tar.gz" >/dev/null 2>&1; then
        echo "Downloaded archive is not a readable tarball." >&2
        exit 1
    fi
    mkdir -p "$work/src"
    tar -xzf "$work/src.tar.gz" -C "$work/src" --strip-components=1
    src="$work/src"
fi

# shellcheck source=scripts/steam_game_paths.sh
source "$src/scripts/steam_game_paths.sh"

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

if [[ -z "${work:-}" ]]; then
    work="$(mktemp -d)"
    trap 'rm -rf "$work"' EXIT
fi

dll=""
if [[ -n "$DLL_PATH" ]]; then
    dll="$DLL_PATH"
elif dll="$(find_workshop_dll)"; then
    echo "Using Workshop OpenShim DLL: $dll"
elif download_release_dll "$work/winmm.dll"; then
    dll="$work/winmm.dll"
fi

if [[ -z "$dll" || ! -f "$dll" ]]; then
    echo "error: no winmm.dll found." >&2
    echo "Subscribe to OpenShim on Workshop, pass --dll, or copy a Release | Win32 build." >&2
    exit 1
fi

deploy="$src/scripts/deploy_linux_proton.sh"
chmod +x "$deploy" "$src/scripts/steam_game_paths.sh"

echo "Installing to:"
printf '  %s\n' "${BZR_GAME_PATHS[@]}"

export OPENSHIM_INSTALLER=1
for game_dir in "${BZR_GAME_PATHS[@]}"; do
    BZR_GAME_PATH="$game_dir" "$deploy" "$game_dir" "$dll"
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
