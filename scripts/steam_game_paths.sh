#!/usr/bin/env bash
#
# steam_game_paths.sh — Locate Battlezone 98 Redux installs under native,
# Flatpak, and Snap Steam layouts.
#
# Usage:
#   source scripts/steam_game_paths.sh
#   detect_bzr_game_paths
#   printf '%s\n' "${BZR_GAME_PATHS[@]}"
#
# Each returned path contains battlezone98redux.exe or BZR.exe.

: "${BZR_GAME_NAME:=Battlezone 98 Redux}"
: "${BZR_STEAM_APPID:=301650}"

_bzr_game_exe_present() {
    local game_dir="$1"
    [[ -f "$game_dir/battlezone98redux.exe" || -f "$game_dir/BZR.exe" ]]
}

_bzr_add_game_path() {
    local candidate="$1"
    [[ -n "$candidate" ]] || return 0
    [[ -d "$candidate" ]] || return 0
    _bzr_game_exe_present "$candidate" || return 0

    local existing
    for existing in "${BZR_GAME_PATHS[@]:-}"; do
        [[ "$existing" == "$candidate" ]] && return 0
    done
    BZR_GAME_PATHS+=("$candidate")
}

_bzr_add_library_root() {
    local library_root="$1"
    [[ -n "$library_root" ]] || return 0
    _bzr_add_game_path "$library_root/steamapps/common/$BZR_GAME_NAME"
}

_bzr_parse_libraryfolders_vdf() {
    local vdf="$1"
    [[ -f "$vdf" ]] || return 0

    local line path
    while IFS= read -r line || [[ -n "$line" ]]; do
        # "path" "<steam library root>"
        if [[ "$line" =~ \"path\"[[:space:]]+\"(.*)\" ]]; then
            path="${BASH_REMATCH[1]}"
            path="${path//\\\\//}"
            _bzr_add_library_root "$path"
        fi
    done < "$vdf"
}

_bzr_add_steam_root() {
    local steam_root="$1"
    [[ -d "$steam_root" ]] || return 0
    _bzr_add_library_root "$steam_root"
    _bzr_parse_libraryfolders_vdf "$steam_root/steamapps/libraryfolders.vdf"
    _bzr_parse_libraryfolders_vdf "$steam_root/config/libraryfolders.vdf"
}

detect_bzr_game_paths() {
    BZR_GAME_PATHS=()

    local candidates=(
        "$HOME/.local/share/Steam/steamapps/common/$BZR_GAME_NAME"
        "$HOME/.steam/steam/steamapps/common/$BZR_GAME_NAME"
        "$HOME/.steam/root/steamapps/common/$BZR_GAME_NAME"
        "$HOME/snap/steam/common/.local/share/Steam/steamapps/common/$BZR_GAME_NAME"
        "$HOME/snap/steam/current/.local/share/Steam/steamapps/common/$BZR_GAME_NAME"
        "$HOME/.var/app/com.valvesoftware.Steam/data/Steam/steamapps/common/$BZR_GAME_NAME"
        "$HOME/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/$BZR_GAME_NAME"
    )

    local candidate
    for candidate in "${candidates[@]}"; do
        _bzr_add_game_path "$candidate"
    done

    local steam_roots=(
        "$HOME/.local/share/Steam"
        "$HOME/.steam/steam"
        "$HOME/.steam/root"
        "$HOME/snap/steam/common/.local/share/Steam"
        "$HOME/snap/steam/current/.local/share/Steam"
        "$HOME/.var/app/com.valvesoftware.Steam/data/Steam"
        "$HOME/.var/app/com.valvesoftware.Steam/.local/share/Steam"
    )

    local steam_root
    for steam_root in "${steam_roots[@]}"; do
        _bzr_add_steam_root "$steam_root"
    done

    if [[ -n "${STEAM_ROOT:-}" ]]; then
        _bzr_add_steam_root "$STEAM_ROOT"
    fi

    if [[ -n "${BZR_GAME_PATH:-}" ]]; then
        BZR_GAME_PATHS=("$BZR_GAME_PATH")
    fi
}
