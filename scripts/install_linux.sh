#!/usr/bin/env bash
#
# One-line Linux / Proton installer. Paste from the README:
#   curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --native
#   curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --snap
#
# The default path downloads ONE versioned release bundle, OpenShim-Suite.zip,
# verifies it against the published SHA-256, and deploys the whole compatibility
# set: winmm.dll, scripts/patches.json, openshim.ini, net.ini, the mandatory
# Enhanced renderer resources, and the custom UI widget tiles. Downloading the
# loose per-file assets instead would silently drop the resource trees, and the
# Enhanced renderer refuses to enable without its validated resource set.
#
# --dll is an advanced override and only proceeds when a matching artifact set
# sits beside that DLL.
#
set -euo pipefail

# Canonical install source is the upstream repo. Override with OPENSHIM_REPO.
REPO_SLUG="${OPENSHIM_REPO:-GrizzlyOne95/Battlezone98Redux_Shim}"
REF="${OPENSHIM_REF:-main}"
FLAVOR="all"
GAME_PATH="${BZR_GAME_PATH:-}"
DLL_PATH="${OPENSHIM_DLL:-}"

# One matched artifact set, resolved once and deployed to every game directory.
DLL=""
PATCHES=""
OPENSHIM_INI=""
NET_INI=""
RENDER_SRC=""
UI_SRC=""
MANIFEST_SRC=""

# UI tiles the game actually loads out of the custom-widget resource tree.
UI_TILES=(uiline.png uiplate.png uibtn.png uibtnhv.png)

usage() {
    cat <<EOF
Usage:
  install_linux.sh [--native | --snap] [--game-path DIR] [--dll FILE] [--ref git-ref]

    --native      Native Steam and Flatpak installs only
    --snap        Snap Steam installs only
    --game-path   One game directory (overrides flavour filter)
    --dll         Advanced: Win32 winmm.dll. Requires patches.json, openshim.ini,
                  and net.ini in the same directory (or scripts/patches.json),
                  and resources/renderer/enhanced for the Enhanced renderer.
    --ref         Git ref used only to fetch steam_game_paths.sh (default: $REF)

Environment:
  OPENSHIM_REPO / OPENSHIM_REF / OPENSHIM_DLL / BZR_GAME_PATH
  OPENSHIM_WEBHOOK / OPENSHIM_PLAYER   test-crew log upload (never committed)
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

file_size() {
    # wc -c is portable; stat's size flag is not (GNU -c %s vs BSD -f %z).
    wc -c < "$1" | tr -d '[:space:]'
}

sha256_of() {
    local file="$1"
    if command -v sha256sum >/dev/null 2>&1; then
        sha256sum "$file" | awk '{print $1}'
        return
    fi
    if command -v shasum >/dev/null 2>&1; then
        shasum -a 256 "$file" | awk '{print $1}'
        return
    fi
    if command -v openssl >/dev/null 2>&1; then
        openssl dgst -sha256 "$file" | awk '{print $NF}'
        return
    fi
    return 1
}

verify_sha256() {
    local file="$1" expected="$2" actual=""
    if [[ ! "$expected" =~ ^[0-9a-fA-F]{64}$ ]]; then
        echo "error: published checksum for $(basename "$file") is not a SHA-256 digest." >&2
        return 1
    fi
    if ! actual="$(sha256_of "$file")"; then
        echo "error: need sha256sum, shasum, or openssl to verify $(basename "$file")." >&2
        return 1
    fi
    if [[ "${actual,,}" != "${expected,,}" ]]; then
        echo "error: SHA-256 mismatch for $(basename "$file")." >&2
        echo "  expected ${expected,,}" >&2
        echo "  actual   ${actual,,}" >&2
        return 1
    fi
    echo "  verified $(basename "$file") sha256=${actual,,}"
}

extract_zip() {
    local zip="$1" dest="$2"
    mkdir -p "$dest"
    if command -v unzip >/dev/null 2>&1; then
        unzip -q -o "$zip" -d "$dest"
        return
    fi
    if command -v python3 >/dev/null 2>&1; then
        python3 -m zipfile -e "$zip" "$dest"
        return
    fi
    if command -v bsdtar >/dev/null 2>&1; then
        bsdtar -xf "$zip" -C "$dest"
        return
    fi
    echo "error: need unzip, python3, or bsdtar to unpack OpenShim-Suite.zip." >&2
    return 1
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

# Resolve one artifact set out of a tree. OpenShim-Suite.zip deliberately
# mirrors the repository layout, so the extracted bundle and a local checkout
# resolve through exactly this one path. A flat directory beside an explicit
# --dll is accepted too. Succeeds only when the core four are all present.
find_artifact_set() {
    local root="$1" dll_override="${2:-}"
    DLL=""
    PATCHES=""
    OPENSHIM_INI=""
    NET_INI=""
    RENDER_SRC=""
    UI_SRC=""

    if [[ -n "$dll_override" ]]; then
        DLL="$dll_override"
    elif [[ -f "$root/bin/Release/winmm.dll" ]]; then
        DLL="$root/bin/Release/winmm.dll"
    elif [[ -f "$root/winmm.dll" ]]; then
        DLL="$root/winmm.dll"
    fi

    if [[ -f "$root/scripts/patches.json" ]]; then
        PATCHES="$root/scripts/patches.json"
    elif [[ -f "$root/patches.json" ]]; then
        PATCHES="$root/patches.json"
    fi

    if [[ -f "$root/openshim.ini" ]]; then
        OPENSHIM_INI="$root/openshim.ini"
    fi
    if [[ -f "$root/net.ini" ]]; then
        NET_INI="$root/net.ini"
    fi

    # The version marker gates the runtime validator, so a tree without it is
    # not a deployable resource set even if some payloads are there.
    if [[ -f "$root/resources/renderer/enhanced/resources.version" ]]; then
        RENDER_SRC="$root/resources/renderer/enhanced"
    fi
    if [[ -d "$root/resources/ui/custom_widgets" ]]; then
        UI_SRC="$root/resources/ui/custom_widgets"
    fi
    if [[ -f "$root/resources/openshim/OpenShimAssets.ini" ]]; then
        MANIFEST_SRC="$root/resources/openshim/OpenShimAssets.ini"
    else
        MANIFEST_SRC=""
    fi

    [[ -n "$DLL" && -f "$DLL" && -n "$PATCHES" && -n "$OPENSHIM_INI" && -n "$NET_INI" ]]
}

download_suite() {
    local dest="$1"
    local base="https://github.com/${REPO_SLUG}/releases/latest/download"
    local zip="$dest/OpenShim-Suite.zip"
    local sums="$dest/OpenShim-Suite.zip.sha256"
    local expected=""

    mkdir -p "$dest"
    echo "Downloading matched release bundle from $REPO_SLUG ..."
    if ! download_to "$base/OpenShim-Suite.zip" "$zip" || [[ ! -s "$zip" ]]; then
        echo "error: could not download OpenShim-Suite.zip from $REPO_SLUG." >&2
        return 1
    fi
    if ! download_to "$base/OpenShim-Suite.zip.sha256" "$sums" || [[ ! -s "$sums" ]]; then
        echo "error: that release publishes no OpenShim-Suite.zip.sha256, so the" >&2
        echo "bundle cannot be verified. Refusing to deploy it." >&2
        return 1
    fi

    expected="$(awk 'NR==1{print $1}' "$sums")"
    verify_sha256 "$zip" "$expected" || return 1
    extract_zip "$zip" "$dest/suite" || return 1

    if [[ -f "$dest/suite/release_metadata.json" ]]; then
        local tag
        tag="$(sed -n 's/.*"Tag"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/p' \
            "$dest/suite/release_metadata.json" | head -n 1)"
        [[ -n "$tag" ]] && echo "  bundle release: $tag"
    fi
}

verify_patches_json() {
    local repo_json="$1" game_json="$2"
    if ! command -v python3 >/dev/null 2>&1; then
        echo "  warning: python3 not found; skipped patches.json verification" >&2
        return 0
    fi
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

deploy_file() {
    local src="$1" dst="$2" stamp="$3"
    mkdir -p "$(dirname "$dst")"
    if [[ -f "$dst" ]]; then
        cp -f "$dst" "$dst.bak-$stamp"
    fi
    cp -f "$src" "$dst"
    echo "  deployed $(basename "$dst") ($(file_size "$dst") bytes)"
}

deploy_matched() {
    local game_dir="$1"
    local stamp
    stamp="$(date +%Y%m%d-%H%M%S)"

    echo "Installing OpenShim to: $game_dir"
    deploy_file "$DLL" "$game_dir/winmm.dll" "$stamp"
    deploy_file "$PATCHES" "$game_dir/scripts/patches.json" "$stamp"
    deploy_file "$OPENSHIM_INI" "$game_dir/openshim.ini" "$stamp"
    deploy_file "$NET_INI" "$game_dir/net.ini" "$stamp"

    if [[ -n "$RENDER_SRC" ]]; then
        local render_target="$game_dir/openshim/renderer/enhanced"
        mkdir -p "$render_target"
        cp -f "$RENDER_SRC"/* "$render_target/"
        echo "  deployed Enhanced renderer resources"
    fi

    if [[ -n "$MANIFEST_SRC" ]]; then
        local manifest_target="$game_dir/openshim/OpenShimAssets.ini"
        mkdir -p "$(dirname "$manifest_target")"
        cp -f "$MANIFEST_SRC" "$manifest_target"
        echo "  deployed asset manifest"
    fi

    if [[ -n "$UI_SRC" ]]; then
        local ui_target="$game_dir/BZ_ASSETS_CORE/common/ui/CustomWidgets"
        mkdir -p "$ui_target"
        local ui_file
        for ui_file in "${UI_TILES[@]}"; do
            if [[ -f "$UI_SRC/$ui_file" ]]; then
                cp -f "$UI_SRC/$ui_file" "$ui_target/"
            fi
        done
        echo "  deployed UI widget tiles"
    fi

    verify_patches_json "$PATCHES" "$game_dir/scripts/patches.json"
    echo "  patches.json verified"
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

# Only a checkout that supplied its own steam_game_paths.sh counts as a local
# repo; a piped run resolves script_dir to the caller's cwd, which is not one.
repo_root=""
if [[ -n "$script_dir" && "$src" == "$script_dir" ]]; then
    repo_root="$(cd "$script_dir/.." 2>/dev/null && pwd || true)"
fi

if [[ -n "$DLL_PATH" ]]; then
    dll_dir="$(cd "$(dirname "$DLL_PATH")" 2>/dev/null && pwd || true)"
    if [[ -z "$dll_dir" ]]; then
        echo "error: --dll path does not exist: $DLL_PATH" >&2
        exit 1
    fi
    if ! find_artifact_set "$dll_dir" "$dll_dir/$(basename "$DLL_PATH")"; then
        echo "error: --dll requires a matched set: patches.json, openshim.ini, and net.ini" >&2
        echo "beside the DLL (or scripts/patches.json). Refusing to mix versions." >&2
        exit 1
    fi
    echo "Using explicit DLL with matched companions: $DLL"
    if [[ -z "$RENDER_SRC" ]]; then
        echo "warning: no resources/renderer/enhanced beside the DLL." >&2
        echo "The Enhanced renderer will stay unavailable in this install." >&2
    fi
elif [[ -n "$repo_root" ]] && find_artifact_set "$repo_root"; then
    echo "Using local Release build with matched companions: $DLL"
    if [[ -z "$RENDER_SRC" ]]; then
        echo "warning: no resources/renderer/enhanced in $repo_root." >&2
        echo "The Enhanced renderer will stay unavailable in this install." >&2
    fi
elif download_suite "$work/bundle" && find_artifact_set "$work/bundle/suite"; then
    echo "Using verified release bundle: $DLL"
    if [[ -z "$RENDER_SRC" ]]; then
        echo "error: the release bundle carries no Enhanced renderer resource set." >&2
        echo "Refusing to deploy a bundle that would leave Enhanced unavailable." >&2
        exit 1
    fi
else
    echo "error: could not obtain a matched OpenShim release bundle from $REPO_SLUG." >&2
    echo "Pass --dll with a matching artifact set, or set OPENSHIM_REPO to a repo" >&2
    echo "that publishes OpenShim-Suite.zip releases." >&2
    exit 1
fi

# Refuse the whole run before touching anything: with several installs detected,
# aborting mid-loop would leave earlier directories rewritten and later ones not.
for game_dir in "${BZR_GAME_PATHS[@]}"; do
    if [[ -f "$game_dir/winmm.dll" ]] && ! is_openshim_dll "$game_dir/winmm.dll"; then
        echo "error: refusing to overwrite non-OpenShim winmm.dll in $game_dir" >&2
        echo "Remove or rename that proxy first if you intend to replace it." >&2
        echo "Nothing was installed." >&2
        exit 1
    fi
done

echo "Installing to:"
printf '  %s\n' "${BZR_GAME_PATHS[@]}"

for game_dir in "${BZR_GAME_PATHS[@]}"; do
    deploy_matched "$game_dir"
    echo
done

# ── Automatic log upload (test crew) ─────────────────────────────────────────
# Zero prompts: the webhook rides in on OPENSHIM_WEBHOOK, pinned in the
# private Discord channel, never in this public repo. No OPENSHIM_WEBHOOK
# means no uploader and no questions. Consent is the Steam launch option.
wrapper_ready=0
wrapper_dir="${XDG_DATA_HOME:-$HOME/.local/share}/openshim"
conf_dir="${XDG_CONFIG_HOME:-$HOME/.config}/openshim"
wrapper_src=""
if [[ -n "$repo_root" && -f "$repo_root/upload/openshim_wrap.sh" ]]; then
    wrapper_src="$repo_root/upload/openshim_wrap.sh"
elif [[ -n "${OPENSHIM_WEBHOOK:-}" || -f "$wrapper_dir/openshim_wrap.sh" ]]; then
    if download_to "https://raw.githubusercontent.com/${REPO_SLUG}/${REF}/upload/openshim_wrap.sh" \
            "$work/openshim_wrap.sh" && [[ -s "$work/openshim_wrap.sh" ]]; then
        wrapper_src="$work/openshim_wrap.sh"
    else
        echo "Warning: could not fetch upload/openshim_wrap.sh from $REPO_SLUG@$REF." >&2
    fi
fi
wrapper_ver_of() {
    [[ -f "$1" ]] || { echo "none"; return; }
    sed -n 's/^WRAPPER_VERSION="\(.*\)"$/\1/p' "$1" | head -1 \
        | grep . || echo "unversioned"
}
install_wrapper_copy() {
    local dest_dir="$1"
    mkdir -p "$dest_dir"
    command cp -f "$wrapper_src" "$dest_dir/openshim_wrap.sh"
    chmod +x "$dest_dir/openshim_wrap.sh"
}

if [[ -n "${OPENSHIM_WEBHOOK:-}" && -n "$wrapper_src" ]]; then
    if [[ "$OPENSHIM_WEBHOOK" != https://discord.com/api/webhooks/* \
       && "$OPENSHIM_WEBHOOK" != https://discordapp.com/api/webhooks/* ]]; then
        echo "Warning: OPENSHIM_WEBHOOK is not a Discord webhook URL; skipping upload setup." >&2
    else
        mkdir -p "$wrapper_dir" "$conf_dir"
        old_wrapper_ver="$(wrapper_ver_of "$wrapper_dir/openshim_wrap.sh")"
        new_wrapper_ver="$(wrapper_ver_of "$wrapper_src")"
        install_wrapper_copy "$wrapper_dir"
        if [[ "$old_wrapper_ver" == "$new_wrapper_ver" ]]; then
            echo "Uploader wrapper: $new_wrapper_ver (already current)."
        else
            echo "Uploader wrapper: $old_wrapper_ver -> $new_wrapper_ver."
        fi
        (
            umask 077
            cat >"$conf_dir/upload.conf" <<EOF
# Written by install_linux.sh. Do not commit this file.
OPENSHIM_WEBHOOK='$OPENSHIM_WEBHOOK'
OPENSHIM_PLAYER='${OPENSHIM_PLAYER:-}'
OPENSHIM_INCLUDE_PROTON=0
EOF
        )
        chmod 600 "$conf_dir/upload.conf"

        for sandbox_dir in \
            "$HOME/snap/steam/common/.local/share/openshim" \
            "$HOME/.var/app/com.valvesoftware.Steam/data/openshim"; do
            [[ -d "${sandbox_dir%/openshim}/Steam" ]] || continue
            install_wrapper_copy "$sandbox_dir"
            command cp -f "$conf_dir/upload.conf" "$sandbox_dir/upload.conf"
            chmod 600 "$sandbox_dir/upload.conf"
            echo "Mirrored the uploader into $sandbox_dir (sandboxed Steam)."

            if [[ "$sandbox_dir" == "$HOME/snap/steam/"* ]] \
               && command -v systemctl >/dev/null 2>&1; then
                unit_dir="${XDG_CONFIG_HOME:-$HOME/.config}/systemd/user"
                mkdir -p "$unit_dir" "$sandbox_dir/outbox"
                cat >"$unit_dir/openshim-retry.service" <<UNIT
[Unit]
Description=Send parked OpenShim session bundles

[Service]
Type=oneshot
ExecStart="$sandbox_dir/openshim_wrap.sh" --retry
UNIT
                cat >"$unit_dir/openshim-retry.path" <<UNIT
[Unit]
Description=Watch the OpenShim outbox the snap sandbox cannot send from

[Path]
PathChanged=$sandbox_dir/outbox
Unit=openshim-retry.service

[Install]
WantedBy=paths.target
UNIT
                cat >"$unit_dir/openshim-retry.timer" <<UNIT
[Unit]
Description=Backstop drain for the OpenShim outbox

[Timer]
OnBootSec=2min
OnUnitActiveSec=10min

[Install]
WantedBy=timers.target
UNIT
                systemctl --user daemon-reload 2>/dev/null || true
                drain_ok=0
                systemctl --user enable --now openshim-retry.path 2>/dev/null && drain_ok=1
                systemctl --user enable --now openshim-retry.timer 2>/dev/null || true
                if [[ "$drain_ok" == "1" ]]; then
                    echo "Enabled openshim-retry.path: Snap-parked bundles are sent within seconds."
                else
                    echo "Could not enable the drain units; send parked bundles by hand with:"
                    echo "  \"$sandbox_dir/openshim_wrap.sh\" --retry"
                fi
            fi
        done

        echo "Automatic log upload configured for '${OPENSHIM_PLAYER:-your in-game name (read at upload time)}'."
        wrapper_ready=1
    fi
elif [[ -f "$wrapper_dir/openshim_wrap.sh" && -n "$wrapper_src" ]]; then
    old_wrapper_ver="$(wrapper_ver_of "$wrapper_dir/openshim_wrap.sh")"
    new_wrapper_ver="$(wrapper_ver_of "$wrapper_src")"
    install_wrapper_copy "$wrapper_dir"
    for sandbox_dir in \
        "$HOME/snap/steam/common/.local/share/openshim" \
        "$HOME/.var/app/com.valvesoftware.Steam/data/openshim"; do
        [[ -f "$sandbox_dir/openshim_wrap.sh" ]] || continue
        install_wrapper_copy "$sandbox_dir"
        echo "Refreshed the sandboxed uploader in $sandbox_dir."
    done
    if [[ "$old_wrapper_ver" == "$new_wrapper_ver" ]]; then
        echo "Uploader wrapper: $new_wrapper_ver (already current; saved webhook untouched)."
    else
        echo "Uploader wrapper: $old_wrapper_ver -> $new_wrapper_ver (saved webhook untouched)."
    fi
    wrapper_ready=1
fi

have_snap_install=0
have_native_install=0
for gp in "${BZR_GAME_PATHS[@]}"; do
    if [[ "$gp" == "$HOME/snap/steam/"* ]]; then
        have_snap_install=1
    else
        have_native_install=1
    fi
done

play_line='WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%'
upload_native='WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" "${XDG_DATA_HOME:-$HOME/.local/share}/openshim/openshim_wrap.sh" %command%'
upload_snap='WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" "$SNAP_USER_COMMON/.local/share/openshim/openshim_wrap.sh" %command%'

if [[ "$wrapper_ready" == "1" ]]; then
    uploader_status="Log uploader: OK"
elif [[ -n "${OPENSHIM_WEBHOOK:-}" ]]; then
    uploader_status="LOG UPLOADER: NOT INSTALLED - scroll up for the reason"
else
    uploader_status="Log uploader: not requested (no OPENSHIM_WEBHOOK - correct for normal players)"
fi

cat <<EOF

Install complete.
OpenShim DLL: OK    $uploader_status

Steam launch options still need to be set once
(Steam → Battlezone 98 Redux → Properties → Launch Options).
Copy the line for the Steam you actually launch from. Don't guess:
a wrapper path that does not exist inside the sandbox kills the launch.
EOF

if [[ "$wrapper_ready" == "1" ]]; then
    if [[ "$have_native_install" == "1" ]]; then
        echo
        echo "Native Steam or Flatpak:"
        echo "  $upload_native"
    fi
    if [[ "$have_snap_install" == "1" ]]; then
        echo
        echo "Snap Steam:"
        echo "  $upload_snap"
    fi
    if [[ "$have_native_install" != "1" && "$have_snap_install" != "1" ]]; then
        echo
        echo "  $upload_native"
    fi
    echo
    echo "Without the wrapper on that line, nothing is ever uploaded."
else
    echo
    echo "  $play_line"
fi

echo
echo "Quotes are required. Drop dsound=n,b if you are not using the dsound netcode proxy."
