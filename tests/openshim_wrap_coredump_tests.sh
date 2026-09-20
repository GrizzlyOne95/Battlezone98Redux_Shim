#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
test_root="$(mktemp -d)"
trap 'rm -rf "$test_root"' EXIT

export HOME="$test_root/home"
export XDG_CONFIG_HOME="$test_root/config"
export XDG_DATA_HOME="$test_root/data"
export OPENSHIM_CORE_PATTERN='|/usr/lib/systemd/systemd-coredump %P %u %g %s %t %c %h'
export OPENSHIM_COREDUMPCTL_BIN="$test_root/fake-coredumpctl"
export FAKE_CALL_LOG="$test_root/calls.log"
mkdir -p "$HOME"

# shellcheck source=../upload/openshim_wrap.sh
source "$repo_root/upload/openshim_wrap.sh"

cat >"$OPENSHIM_COREDUMPCTL_BIN" <<'EOF'
#!/usr/bin/env bash
set -u
printf '%s\n' "$*" >>"$FAKE_CALL_LOG"

has_arg() {
    local wanted="$1" arg
    shift
    for arg in "$@"; do
        [[ "$arg" == "$wanted" ]] && return 0
    done
    return 1
}

if [[ "$*" == *'--field=COREDUMP_PID'* ]]; then
    case "${FAKE_MODE:-match}" in
        match) printf '333\n222\n111\n' ;;
        debug_permission|debug_unavailable) printf '111\n' ;;
        no_match) printf '222\n' ;;
        permission)
            echo 'Failed to search journal: Permission denied' >&2
            exit 1
            ;;
        no_entries)
            echo 'No coredumps found.' >&2
            exit 1
            ;;
        failed)
            echo 'journal transport failed' >&2
            exit 2
            ;;
    esac
    exit 0
fi

if has_arg info "$@"; then
    case "$*" in
        *COREDUMP_PID=111*)
            cat <<INFO
           PID: 111 (battlezone98re)
           UID: $(id -u) (tester)
       Command Line: /usr/bin/wine /games/Battlezone 98 Redux/battlezone98redux.exe
        Executable: /usr/lib/wine/wine64-preloader
           Storage: /var/lib/systemd/coredump/core.wine.zst (present)
INFO
            ;;
        *COREDUMP_PID=333*)
            cat <<INFO
           PID: 333 (battlezone98re)
           UID: $(id -u) (tester)
       Command Line: /usr/bin/wine /games/Other Copy/battlezone98redux.exe
        Executable: /usr/lib/wine/wine64-preloader
INFO
            ;;
        *)
            cat <<INFO
           PID: 222 (other-game)
           UID: $(id -u) (tester)
       Command Line: /usr/bin/wine /games/OtherGame/other.exe
        Executable: /usr/lib/wine/wine64-preloader
INFO
            ;;
    esac
    exit 0
fi

if has_arg debug "$@"; then
    if [[ "${FAKE_MODE:-}" == debug_permission ]]; then
        echo 'Failed to retrieve core: Permission denied' >&2
        exit 1
    fi
    if [[ "${FAKE_MODE:-}" == debug_unavailable ]]; then
        echo 'Core dump is not available: No such file' >&2
        exit 1
    fi
    cat <<'TRACE'
Thread 1 (Thread 0x1):
#0  0x00000001 in crash_here ()
#1  0x00000002 in wine_entry ()
TRACE
    exit 0
fi

echo "unexpected fake coredumpctl arguments: $*" >&2
exit 3
EOF
chmod +x "$OPENSHIM_COREDUMPCTL_BIN"

failures=0
check_line() {
    local file="$1" expected="$2"
    if ! grep -Fqx "$expected" "$file"; then
        echo "FAIL: $file missing: $expected" >&2
        failures=$((failures + 1))
    fi
}

new_case() {
    local name="$1"
    CASE_DIR="$test_root/$name"
    META="$CASE_DIR/meta.txt"
    mkdir -p "$CASE_DIR"
    : >"$META"
    : >"$FAKE_CALL_LOG"
}

# The exact game-directory candidate outranks a newer same-named executable in
# another directory, while an unrelated Wine crash is rejected.
new_case match
FAKE_MODE=match collect_systemd_coredump "$CASE_DIR" "$META" \
    "/games/Battlezone 98 Redux" 1000 1100 abrupt-exit
check_line "$META" 'coredump_capture=available'
check_line "$META" 'coredump_match=found'
check_line "$META" 'coredump_pid=111'
check_line "$META" 'coredump_match_score=100'
check_line "$META" 'coredump_metadata=captured'
check_line "$META" 'coredump_backtrace=captured'
check_line "$META" 'coredump_backtrace_source=debugger'
check_line "$CASE_DIR/systemd-coredump.query.txt" 'matched_pid=111'
check_line "$CASE_DIR/systemd-coredump.query.txt" 'query_since_epoch=995'
check_line "$CASE_DIR/systemd-coredump.query.txt" 'query_until_epoch=1115'
[[ -s "$CASE_DIR/systemd-coredump.metadata.txt" ]] || { echo 'FAIL: metadata missing' >&2; failures=$((failures + 1)); }
[[ -s "$CASE_DIR/systemd-coredump.backtrace.txt" ]] || { echo 'FAIL: backtrace missing' >&2; failures=$((failures + 1)); }
grep -Fq -- '--since @995 --until @1115' "$FAKE_CALL_LOG" || { echo 'FAIL: bounded time query missing' >&2; failures=$((failures + 1)); }

# Truncated Linux comm is accepted only in combination with Wine/Proton.
cat >"$test_root/truncated.info" <<'EOF'
           PID: 444 (battlezone98re)
           UID: 1000 (tester)
        Executable: /opt/steam/compatibilitytools.d/proton/files/bin/wine64
EOF
[[ "$(coredump_match_score "$test_root/truncated.info" /games/BZR 1000)" == 60 ]] || {
    echo 'FAIL: truncated Battlezone comm + Proton executable did not match' >&2
    failures=$((failures + 1))
}
cat >"$test_root/unrelated.info" <<'EOF'
           PID: 445 (other-game)
           UID: 1000 (tester)
        Executable: /opt/steam/compatibilitytools.d/proton/files/bin/wine64
EOF
[[ "$(coredump_match_score "$test_root/unrelated.info" /games/BZR 1000)" == 0 ]] || {
    echo 'FAIL: unrelated Proton process matched' >&2
    failures=$((failures + 1))
}
cat >"$test_root/wrong-owner.info" <<'EOF'
           PID: 446 (battlezone98re)
           UID: 2000 (other-user)
       Command Line: /usr/bin/wine /games/BZR/battlezone98redux.exe
        Executable: /usr/lib/wine/wine64-preloader
EOF
[[ "$(coredump_match_score "$test_root/wrong-owner.info" /games/BZR 1000)" == 0 ]] || {
    echo 'FAIL: another user coredump matched' >&2
    failures=$((failures + 1))
}

new_case no_match
FAKE_MODE=no_match collect_systemd_coredump "$CASE_DIR" "$META" /games/BZR 1000 1100 abrupt-exit
check_line "$META" 'coredump_match=no-matching-dump'
check_line "$META" 'coredump_metadata=not-captured'
check_line "$META" 'coredump_backtrace=not-attempted'

new_case permission
FAKE_MODE=permission collect_systemd_coredump "$CASE_DIR" "$META" /games/BZR 1000 1100 abrupt-exit
check_line "$META" 'coredump_match=permission-denied'
grep -Fqi 'permission denied' "$CASE_DIR/systemd-coredump.query.txt" || {
    echo 'FAIL: permission diagnostic was not bundled' >&2
    failures=$((failures + 1))
}

new_case no_entries
FAKE_MODE=no_entries collect_systemd_coredump "$CASE_DIR" "$META" /games/BZR 1000 1100 abrupt-exit
check_line "$META" 'coredump_match=no-matching-dump'

new_case query_failed
FAKE_MODE=failed collect_systemd_coredump "$CASE_DIR" "$META" /games/BZR 1000 1100 abrupt-exit
check_line "$META" 'coredump_match=query-failed'

new_case debug_permission
FAKE_MODE=debug_permission collect_systemd_coredump "$CASE_DIR" "$META" \
    "/games/Battlezone 98 Redux" 1000 1100 abrupt-exit
check_line "$META" 'coredump_match=found'
check_line "$META" 'coredump_backtrace=permission-denied'
grep -Fqi 'permission denied' "$CASE_DIR/systemd-coredump.backtrace.txt" || {
    echo 'FAIL: backtrace permission diagnostic was not bundled' >&2
    failures=$((failures + 1))
}

new_case debug_unavailable
FAKE_MODE=debug_unavailable collect_systemd_coredump "$CASE_DIR" "$META" \
    "/games/Battlezone 98 Redux" 1000 1100 abrupt-exit
check_line "$META" 'coredump_backtrace=unavailable:core-not-accessible'

new_case missing_tool
OPENSHIM_COREDUMPCTL_BIN="$test_root/not-installed" \
    collect_systemd_coredump "$CASE_DIR" "$META" /games/BZR 1000 1100 abrupt-exit
check_line "$META" 'coredump_capture=unavailable:coredumpctl-not-found'
check_line "$META" 'coredump_match=not-attempted-capture-unavailable'

new_case clean
OPENSHIM_COREDUMPCTL_BIN="$test_root/fake-coredumpctl" \
    collect_systemd_coredump "$CASE_DIR" "$META" /games/BZR 1000 1100 clean
check_line "$META" 'coredump_match=not-attempted-clean-termination'
check_line "$META" 'coredump_backtrace=not-attempted'
[[ ! -s "$FAKE_CALL_LOG" ]] || { echo 'FAIL: clean termination queried coredumpctl' >&2; failures=$((failures + 1)); }

if (( failures > 0 )); then
    echo "$failures openshim coredump test(s) failed" >&2
    exit 1
fi

echo 'OpenShim coredump tests passed'
