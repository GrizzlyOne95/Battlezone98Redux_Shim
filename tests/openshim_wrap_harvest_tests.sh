#!/usr/bin/env bash
# Session-file harvest in upload/openshim_wrap.sh: fresh files ride along,
# stale ones (written before this session started) do not, and the
# append-only bzloader.log is bounded to its tail.
set -euo pipefail

repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
test_root="$(mktemp -d)"
trap 'rm -rf "$test_root"' EXIT

export HOME="$test_root/home"
export XDG_CONFIG_HOME="$test_root/config"
export XDG_DATA_HOME="$test_root/data"
mkdir -p "$HOME"

# shellcheck source=../upload/openshim_wrap.sh
source "$repo_root/upload/openshim_wrap.sh"

failures=0
fail() { echo "FAIL: $*" >&2; failures=$((failures + 1)); }

game="$test_root/game"
bundle="$test_root/bundle"
mkdir -p "$game/logs" "$bundle"

start_epoch=2000000000
fresh=$((start_epoch + 60))
stale=$((start_epoch - 3600))

put() {
    local path="$1" epoch="$2"
    printf '%s\n' "$(basename "$path")" >"$path"
    touch -d "@$epoch" "$path"
}

# OpenShim writes logs/<name>; the stock game writes <name> in the root.
put "$game/logs/BZOgreLogfile.log" "$fresh"
put "$game/logs/crc32host.log" "$fresh"
put "$game/crc32mission.log" "$fresh"
put "$game/logs/bzrnet_trace.jsonl" "$fresh"
put "$game/logs/bzrnet_session.json" "$stale"
put "$game/logs/bz_relay_control.jsonl" "$stale"
put "$game/logs/bz_buffer_log.bin" "$fresh"

seq 1 $((BZLOADER_TAIL_LINES + 500)) >"$game/bzloader.log"
touch -d "@$fresh" "$game/bzloader.log"

harvest_session_files "$game" "$bundle"

for f in BZOgreLogfile.log crc32host.log crc32mission.log bzrnet_trace.jsonl bz_buffer_log.bin; do
    [[ -f "$bundle/$f" ]] || fail "fresh $f was not harvested"
done
for f in bzrnet_session.json bz_relay_control.jsonl; do
    [[ ! -e "$bundle/$f" ]] || fail "stale $f was harvested"
done

if [[ ! -f "$bundle/bzloader.log" ]]; then
    fail "fresh bzloader.log was not harvested"
else
    lines="$(wc -l <"$bundle/bzloader.log")"
    (( lines == BZLOADER_TAIL_LINES )) || fail "bzloader.log has $lines lines, want $BZLOADER_TAIL_LINES"
    [[ "$(tail -n 1 "$bundle/bzloader.log")" == "$((BZLOADER_TAIL_LINES + 500))" ]] \
        || fail "bzloader.log tail does not end at the newest line"
fi

# A loader log no run of this session touched stays out.
rm -rf "$bundle"; mkdir -p "$bundle"
touch -d "@$stale" "$game/bzloader.log"
harvest_session_files "$game" "$bundle"
[[ ! -e "$bundle/bzloader.log" ]] || fail "stale bzloader.log was harvested"

# Nothing present is not an error.
rm -rf "$bundle"; mkdir -p "$bundle"
harvest_session_files "$test_root/empty-game" "$bundle"
[[ -z "$(ls -A "$bundle")" ]] || fail "harvest from a missing game dir produced files"

if (( failures > 0 )); then
    echo "$failures openshim harvest test(s) failed" >&2
    exit 1
fi

echo 'OpenShim harvest tests passed'
