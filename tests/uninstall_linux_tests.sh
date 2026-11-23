#!/usr/bin/env bash
# Fixture test for scripts/uninstall_linux.sh. Builds a fake game directory
# holding everything install_linux.sh deploys (plus the residue the Workshop
# updater and the installer's backups leave), runs the uninstaller against it
# with --game-path, and checks what is gone and what survived. No game install
# or network access required: the checkout's own steam_game_paths.sh is used.
set -euo pipefail

repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
uninstaller="$repo_root/scripts/uninstall_linux.sh"
test_root="$(mktemp -d)"
trap 'rm -rf "$test_root"' EXIT

failures=0
check() {
    local ok="$1" message="$2"
    if [[ "$ok" == "0" ]]; then
        echo "FAIL: $message" >&2
        failures=$((failures + 1))
    fi
}
present() { [[ -e "$1" ]] && echo 1 || echo 0; }
absent() { [[ -e "$1" ]] && echo 0 || echo 1; }

# The ASCII marker every shipped OpenShim binary carries; the foreign proxy
# carries no marker.
openshim_marker='MZ....OpenShimGetVersion....BZLoader....'
foreign_marker='MZ....SomeOtherProxy........................'

write_fixture() {
    local path="$1" content="${2:-fixture}"
    mkdir -p "$(dirname "$path")"
    printf '%s' "$content" > "$path"
}

new_game_fixture() {
    local root="$1"
    rm -rf "$root"
    mkdir -p "$root"
    write_fixture "$root/battlezone98redux.exe" "MZ game"

    write_fixture "$root/winmm.dll" "$openshim_marker"
    write_fixture "$root/winmm.dll.previous" "$openshim_marker"
    write_fixture "$root/winmm.dll.bak-20260101-000000" "$openshim_marker"
    write_fixture "$root/winmm.dll.bak-20260102-000000" "$foreign_marker"
    write_fixture "$root/bzloader.dll" "$openshim_marker"
    write_fixture "$root/bzloader.dll.bak-20260101-000000" "$openshim_marker"
    write_fixture "$root/plugins/openshim.dll" "$openshim_marker"
    write_fixture "$root/plugins/openshim.dll.bak-20260101-000000" "$openshim_marker"

    write_fixture "$root/openshim/patches.json" "{}"
    write_fixture "$root/openshim/patches.json.previous" "{}"
    write_fixture "$root/scripts/patches.json" "{}"
    write_fixture "$root/scripts/patches.json.previous" "{}"
    write_fixture "$root/scripts/patches.json.bak-20260101-000000" "{}"
    write_fixture "$root/scripts/stock_mission.lua" "-- the game's own script"

    write_fixture "$root/openshim/renderer/enhanced/resources.version" "3"
    write_fixture "$root/openshim/renderer/enhanced/openshim_enhanced_base.program" "program"
    write_fixture "$root/openshim/OpenShimAssets.ini" "[Assets]"

    # Widget tiles beside a file that is not the installer's, in the current
    # folder and in the legacy one older releases used.
    local tile ui_dir
    for ui_dir in openshim/ui BZ_ASSETS_CORE/common/ui/CustomWidgets; do
        for tile in uiline.png uiplate.png uibtn.png uibtnhv.png odyssey.ogv openshim_widgets.sha256; do
            write_fixture "$root/$ui_dir/$tile" "png"
        done
        write_fixture "$root/$ui_dir/player_widget.png" "png"
    done

    # New layout: ini, state, cache, LAN tools and stock backups under openshim/.
    write_fixture "$root/openshim/openshim.ini" "[Player]"
    write_fixture "$root/openshim/openshim.ini.bak-20260101-000000" "[Player]"
    write_fixture "$root/openshim/openshim.ini.pre-reset-20260101-000000.bak" "[Player]"
    write_fixture "$root/openshim/openshim.ini.canonical" "[Shipped]"
    write_fixture "$root/openshim/state/openshim_update.status" "state=complete"
    write_fixture "$root/openshim/cache/shaders/a.bin" "cache"
    write_fixture "$root/openshim/tools/lan/BZRServer.exe" "server"
    write_fixture "$root/openshim/stock-backup/net.ini" "[Stock]"
    write_fixture "$root/openshim/stock-backup/Ogre.cfg" "stock ogre"
    write_fixture "$root/Ogre.cfg" "openshim ogre"
    # Old-layout leftovers and player data.
    write_fixture "$root/tools/lan/BZRServer.exe" "server"
    write_fixture "$root/shader_cache/a.bin" "cache"
    write_fixture "$root/steam_tunnel_peers.txt" "peers"
    write_fixture "$root/bzloader.log" "loader"
    write_fixture "$root/Save/slot1.sav" "save"
    write_fixture "$root/career_stats.cfg" "stats"
    write_fixture "$root/bans.cfg" "bans"
    write_fixture "$root/flags.cfg" "flags"
    write_fixture "$root/multi.ini" "multi"
    write_fixture "$root/openshim.ini" "[Player]"
    write_fixture "$root/openshim.ini.bak-20260101-000000" "[Player]"
    write_fixture "$root/openshim.ini.pre-reset-20260101-000000.bak" "[Player]"
    write_fixture "$root/openshim.ini.canonical" "[Shipped]"
    write_fixture "$root/net.ini" "[OpenShimNetwork]"
    write_fixture "$root/net.ini.bak-20260101-000000" "[Network]"
    write_fixture "$root/net.ini.previous" "[Network]"
    write_fixture "$root/logs/openshim.log" "log"
    write_fixture "$root/openshim_update.status" "state=complete"
}

game="$test_root/Battlezone 98 Redux"

# --- dry run touches nothing --------------------------------------------------
new_game_fixture "$game"
before="$(cd "$game" && find . | sort)"
output="$(bash "$uninstaller" --game-path "$game" --dry-run 2>&1)" && ok=1 || ok=0
check "$ok" "dry run exits cleanly: $output"
after="$(cd "$game" && find . | sort)"
check "$([[ "$before" == "$after" ]] && echo 1 || echo 0)" "dry run leaves the folder as it was"
check "$([[ "$output" == *"would remove"* ]] && echo 1 || echo 0)" "dry run reports what it would remove"

# --- default run --------------------------------------------------------------
new_game_fixture "$game"
output="$(bash "$uninstaller" --game-path "$game" 2>&1)" && ok=1 || ok=0
check "$ok" "default run exits cleanly: $output"

for relative in \
    winmm.dll winmm.dll.previous winmm.dll.bak-20260101-000000 \
    bzloader.dll bzloader.dll.bak-20260101-000000 \
    plugins/openshim.dll plugins/openshim.dll.bak-20260101-000000 plugins \
    scripts/patches.json scripts/patches.json.previous scripts/patches.json.bak-20260101-000000 \
    openshim/renderer/enhanced/resources.version openshim/renderer/enhanced openshim/renderer \
    openshim/OpenShimAssets.ini \
    openshim/ui/uiline.png openshim/ui/uiplate.png openshim/ui/uibtn.png openshim/ui/uibtnhv.png \
    openshim/ui/odyssey.ogv openshim/ui/openshim_widgets.sha256 \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/uiline.png BZ_ASSETS_CORE/common/ui/CustomWidgets/uiplate.png \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/uibtn.png BZ_ASSETS_CORE/common/ui/CustomWidgets/uibtnhv.png \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/odyssey.ogv BZ_ASSETS_CORE/common/ui/CustomWidgets/openshim_widgets.sha256 \
    openshim.ini.canonical openshim_update.status \
    openshim/patches.json openshim/patches.json.previous openshim/openshim.ini.canonical \
    openshim/state openshim/cache openshim/tools openshim/stock-backup openshim/ui \
    tools shader_cache steam_tunnel_peers.txt bzloader.log; do
    check "$(absent "$game/$relative")" "removed: $relative"
done
for relative in \
    battlezone98redux.exe winmm.dll.bak-20260102-000000 \
    scripts/stock_mission.lua scripts \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/player_widget.png BZ_ASSETS_CORE/common/ui/CustomWidgets \
    openshim openshim/openshim.ini openshim/openshim.ini.bak-20260101-000000 \
    openshim/openshim.ini.pre-reset-20260101-000000.bak \
    openshim.ini openshim.ini.bak-20260101-000000 openshim.ini.pre-reset-20260101-000000.bak \
    net.ini net.ini.bak-20260101-000000 net.ini.previous Ogre.cfg \
    Save/slot1.sav career_stats.cfg bans.cfg flags.cfg multi.ini \
    logs/openshim.log; do
    check "$(present "$game/$relative")" "kept: $relative"
done
check "$([[ "$(cat "$game/net.ini")" == "[Stock]" ]] && echo 1 || echo 0)" "net.ini was restored from openshim/stock-backup"
check "$([[ "$(cat "$game/Ogre.cfg")" == "stock ogre" ]] && echo 1 || echo 0)" "Ogre.cfg was restored from openshim/stock-backup"
check "$([[ "$(cat "$game/career_stats.cfg")" == "stats" ]] && echo 1 || echo 0)" "player data content is untouched"
check "$([[ "$output" == *"KEEPING"*"winmm.dll.bak-20260102-000000"* ]] && echo 1 || echo 0)" "the foreign backup is reported as kept"
check "$([[ "$output" == *"left in place"* ]] && echo 1 || echo 0)" "the closing note says what was left"
check "$([[ "$output" == *"WINEDLLOVERRIDES"* ]] && echo 1 || echo 0)" "the closing note reminds about the launch option"

# --- UI folders and an openshim/ holding no player ini are removed entirely ---
new_game_fixture "$game"
rm -f "$game"/openshim/openshim.ini* "$game/openshim/ui/player_widget.png" "$game/BZ_ASSETS_CORE/common/ui/CustomWidgets/player_widget.png"
output="$(bash "$uninstaller" --game-path "$game" 2>&1)" && ok=1 || ok=0
check "$ok" "owned-only UI run exits cleanly: $output"
for relative in openshim/ui openshim BZ_ASSETS_CORE/common/ui/CustomWidgets; do
    check "$(absent "$game/$relative")" "owned-only UI run removed: $relative"
done
check "$(present "$game/BZ_ASSETS_CORE/common/ui")" "owned-only UI run keeps the game's ui folder"

# --- purge run also removes the player ini and its backups --------------------
new_game_fixture "$game"
output="$(bash "$uninstaller" --game-path "$game" --purge-config 2>&1)" && ok=1 || ok=0
check "$ok" "purge run exits cleanly: $output"
for relative in openshim.ini openshim.ini.bak-20260101-000000 openshim.ini.pre-reset-20260101-000000.bak \
        openshim/openshim.ini openshim/openshim.ini.bak-20260101-000000 \
        openshim/openshim.ini.pre-reset-20260101-000000.bak openshim; do
    check "$(absent "$game/$relative")" "purge removed: $relative"
done
for relative in net.ini net.ini.bak-20260101-000000 net.ini.previous logs/openshim.log career_stats.cfg Save/slot1.sav; do
    check "$(present "$game/$relative")" "purge kept: $relative"
done

# --- unknown entries in openshim/ stay; .before-uninstall copies never overwrite
new_game_fixture "$game"
write_fixture "$game/openshim/my_mod/keep.txt" "mine"
write_fixture "$game/openshim/notes.txt" "mine"
write_fixture "$game/openshim/patches.json.superseded" "{}"
write_fixture "$game/Ogre.cfg.before-uninstall-20200101-000000" "earlier"
output="$(bash "$uninstaller" --game-path "$game" 2>&1)" && ok=1 || ok=0
check "$ok" "unknown-entry run exits cleanly: $output"
for relative in openshim/my_mod/keep.txt openshim/notes.txt openshim; do
    check "$(present "$game/$relative")" "unknown entry kept: $relative"
done
check "$(absent "$game/openshim/patches.json.superseded")" "patches.json.superseded is removed with the family"
check "$([[ "$output" == *"notes.txt : not an OpenShim file"* ]] && echo 1 || echo 0)" "an unknown file is reported"
check "$([[ "$output" == *"my_mod : not an OpenShim folder"* ]] && echo 1 || echo 0)" "an unknown folder is reported"
check "$([[ "$(cat "$game/Ogre.cfg.before-uninstall-20200101-000000")" == "earlier" ]] && echo 1 || echo 0)" "an earlier .before-uninstall copy is not overwritten"
copies="$(ls "$game"/Ogre.cfg.before-uninstall-* | wc -l)"
check "$([[ "$copies" == "2" ]] && echo 1 || echo 0)" "this run's .before-uninstall copy has its own name"

# --- openshim/ that is itself a symlink is not entered --------------------------
new_game_fixture "$game"
mv "$game/openshim" "$test_root/elsewhere"
ln -s "$test_root/elsewhere" "$game/openshim"
output="$(bash "$uninstaller" --game-path "$game" 2>&1)" && ok=1 || ok=0
check "$ok" "linked openshim run exits cleanly: $output"
check "$(present "$test_root/elsewhere/patches.json")" "a linked openshim/ target is untouched"
check "$([[ "$output" == *"openshim : it is a link"* ]] && echo 1 || echo 0)" "a linked openshim/ is reported"
rm -f "$game/openshim"

# --- a foreign winmm.dll is never removed ---------------------------------------
new_game_fixture "$game"
write_fixture "$game/winmm.dll" "$foreign_marker"
output="$(bash "$uninstaller" --game-path "$game" 2>&1)" && ok=1 || ok=0
check "$ok" "foreign proxy run exits cleanly: $output"
check "$(present "$game/winmm.dll")" "a foreign winmm.dll survives"
check "$(absent "$game/bzloader.dll")" "OpenShim's loader still goes beside a foreign proxy"

# --- a second run is a clean no-op ---------------------------------------------
output="$(bash "$uninstaller" --game-path "$game" 2>&1)" && ok=1 || ok=0
check "$ok" "second run on an already-clean folder exits cleanly: $output"

# --- a wrong --game-path is refused, not silently ignored -----------------------
mkdir -p "$test_root/not-a-game"
output="$(bash "$uninstaller" --game-path "$test_root/not-a-game" 2>&1)" && ok=1 || ok=0
check "$([[ "$ok" == "0" ]] && echo 1 || echo 0)" "a directory without the game executable is refused"
check "$([[ "$output" == *"not a Battlezone 98 Redux install"* ]] && echo 1 || echo 0)" "the refusal names the reason"

if [[ "$failures" -ne 0 ]]; then
    echo "uninstall_linux_tests: $failures check(s) failed" >&2
    exit 1
fi
echo "uninstall_linux_tests: PASS"
