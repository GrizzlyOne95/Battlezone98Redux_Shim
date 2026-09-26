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

    write_fixture "$root/scripts/patches.json" "{}"
    write_fixture "$root/scripts/patches.json.previous" "{}"
    write_fixture "$root/scripts/patches.json.bak-20260101-000000" "{}"
    write_fixture "$root/scripts/stock_mission.lua" "-- the game's own script"

    write_fixture "$root/openshim/renderer/enhanced/resources.version" "3"
    write_fixture "$root/openshim/renderer/enhanced/openshim_enhanced_base.program" "program"
    write_fixture "$root/openshim/OpenShimAssets.ini" "[Assets]"

    local tile
    for tile in uiline.png uiplate.png uibtn.png uibtnhv.png; do
        write_fixture "$root/BZ_ASSETS_CORE/common/ui/CustomWidgets/$tile" "png"
    done
    write_fixture "$root/BZ_ASSETS_CORE/common/ui/CustomWidgets/player_widget.png" "png"

    write_fixture "$root/openshim.ini" "[Player]"
    write_fixture "$root/openshim.ini.bak-20260101-000000" "[Player]"
    write_fixture "$root/openshim.ini.pre-reset-20260101-000000.bak" "[Player]"
    write_fixture "$root/openshim.ini.canonical" "[Shipped]"
    write_fixture "$root/net.ini" "[Network]"
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
    openshim/OpenShimAssets.ini openshim \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/uiline.png BZ_ASSETS_CORE/common/ui/CustomWidgets/uiplate.png \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/uibtn.png BZ_ASSETS_CORE/common/ui/CustomWidgets/uibtnhv.png \
    openshim.ini.canonical openshim_update.status; do
    check "$(absent "$game/$relative")" "removed: $relative"
done
for relative in \
    battlezone98redux.exe winmm.dll.bak-20260102-000000 \
    scripts/stock_mission.lua scripts \
    BZ_ASSETS_CORE/common/ui/CustomWidgets/player_widget.png BZ_ASSETS_CORE/common/ui/CustomWidgets \
    openshim.ini openshim.ini.bak-20260101-000000 openshim.ini.pre-reset-20260101-000000.bak \
    net.ini net.ini.bak-20260101-000000 net.ini.previous \
    logs/openshim.log; do
    check "$(present "$game/$relative")" "kept: $relative"
done
check "$([[ "$output" == *"KEEPING"*"winmm.dll.bak-20260102-000000"* ]] && echo 1 || echo 0)" "the foreign backup is reported as kept"
check "$([[ "$output" == *"left in place"* ]] && echo 1 || echo 0)" "the closing note says what was left"
check "$([[ "$output" == *"WINEDLLOVERRIDES"* ]] && echo 1 || echo 0)" "the closing note reminds about the launch option"

# --- purge run also removes the player ini and its backups --------------------
new_game_fixture "$game"
output="$(bash "$uninstaller" --game-path "$game" --purge-config 2>&1)" && ok=1 || ok=0
check "$ok" "purge run exits cleanly: $output"
for relative in openshim.ini openshim.ini.bak-20260101-000000 openshim.ini.pre-reset-20260101-000000.bak; do
    check "$(absent "$game/$relative")" "purge removed: $relative"
done
for relative in net.ini net.ini.bak-20260101-000000 net.ini.previous logs/openshim.log; do
    check "$(present "$game/$relative")" "purge kept: $relative"
done

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
