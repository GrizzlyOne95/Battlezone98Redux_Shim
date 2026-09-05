#!/bin/sh
# Blocks a commit that would put a Discord webhook URL into this repository.
#
# The test-crew log uploader takes its webhook from OPENSHIM_WEBHOOK, supplied
# by a pinned command in the private Discord channel. It is deliberately never
# committed: GitHub's secret scanning revokes Discord webhooks it finds in a
# push, so a single accidental commit breaks log collection for everyone and
# the URL has to be reissued.
#
# Installed by setup-dev.ps1 / setup-dev.sh as .git/hooks/pre-commit.
# Bypass for a deliberate, reviewed exception: git commit --no-verify

set -e

# Matches https://discord.com/api/webhooks/<id>/<token> and the discordapp.com
# alias. The token is long and mixed-case; a bare ".../webhooks/" prefix with no
# token is a documentation reference and is allowed through.
pattern='https://discord(app)?\.com/api/webhooks/[0-9]{5,}/[A-Za-z0-9_-]{20,}'

# Only added lines matter: an existing match already in history is not something
# this commit can fix, and blocking on it would wedge every later commit.
added=$(git diff --cached --unified=0 --no-color -- . | grep -E '^\+' | grep -Ev '^\+\+\+' || true)

hits=$(printf '%s\n' "$added" | grep -Eo "$pattern" || true)
if [ -n "$hits" ]; then
    files=$(git diff --cached --name-only || true)
    echo "pre-commit: refusing to commit a Discord webhook URL." >&2
    echo >&2
    printf '%s\n' "$hits" | sed 's/\(webhooks\/[0-9]*\/\).*/\1<token redacted>/' >&2
    echo >&2
    echo "Staged files:" >&2
    printf '%s\n' "$files" | sed 's/^/  /' >&2
    echo >&2
    echo "GitHub secret scanning revokes Discord webhooks found in a push, which" >&2
    echo "would break test-crew log uploads until the webhook is reissued. The" >&2
    echo "uploader reads OPENSHIM_WEBHOOK at install time instead - keep the URL" >&2
    echo "in the pinned Discord message, not in a tracked file." >&2
    echo >&2
    echo "If this really is intended, re-run with: git commit --no-verify" >&2
    exit 1
fi

exit 0
