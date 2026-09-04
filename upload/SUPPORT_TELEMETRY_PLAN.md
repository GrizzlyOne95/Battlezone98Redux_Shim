# OpenShim remote support telemetry plan

This branch starts from the merge result of PiercingXX PR #116 and evolves its opt-in Discord session uploader into a crash-resilient remote support telemetry client.

## Goal

Make remote support require only an explicit Steam launch option. While support mode is active, logs should be available remotely during the session and crash artifacts should remain recoverable after an abrupt game exit. Normal OpenShim launches must never upload anything.

## Architecture

```text
OpenShim / Battlezone
  -> existing flushed local logs + crash dumps
  -> out-of-process wrapper/sidecar
       -> local spool
       -> HTTPS support endpoint
            -> live structured logs
            -> artifact storage
            -> Discord notifications
```

The native `winmm.dll` must not contain permanent service credentials or perform blocking network I/O. The wrapper remains the crash-resilient process boundary.

## Client transport contract

The wrapper should evolve away from a Discord-specific webhook and use a configurable HTTPS endpoint.

### Session create

`POST /v1/session`

Request example:

```json
{
  "protocol": 1,
  "platform": "windows",
  "distribution": "steam",
  "wrapper_version": "OpenShim-upload-20260904"
}
```

Response example:

```json
{
  "support_id": "OCP-A71F93",
  "session_token": "opaque-short-lived-token"
}
```

The token is scoped to one support session and expires. No permanent backend secret is shipped to users.

### Live log batches

`POST /v1/session/{support_id}/logs`

Batch by approximately one second or 32-64 KiB rather than one HTTP request per log line. Each batch carries a monotonically increasing sequence number. The wrapper must spool a batch locally before attempting upload and delete/acknowledge it only after a successful response.

```json
{
  "sequence": 37,
  "events": [
    {
      "timestamp": "2026-09-04T20:04:31.118Z",
      "level": "INFO",
      "component": "hooks",
      "message": "..."
    }
  ]
}
```

### Artifact upload

`POST /v1/session/{support_id}/artifact`

Used after exit/crash for `openshim.log`, `openshim_crash.log`, session-fresh `openshim_crash_*.dmp`, and other explicitly allowed diagnostics. Large artifacts belong in object storage behind the endpoint rather than Discord attachments.

### Session finish

`POST /v1/session/{support_id}/finish`

Include exit code, clean/abrupt classification, final batch sequence, and which artifacts were captured.

## Existing PR #116 behavior to preserve

- Wrapper launch option is the explicit consent boundary.
- No wrapper in the launch options means no upload.
- Wrapper remains outside Battlezone so it survives a game crash.
- Preserve pre-launch snapshots before logs are overwritten.
- Preserve local outbox/retry behavior when networking is unavailable.
- Preserve Windows, Linux, Flatpak, and Snap handling.
- Preserve collection of OpenShim crash logs/minidumps.
- Backend failure must never prevent Battlezone from starting or running.

## Changes from the current Discord prototype

- Do not keep a Discord webhook URL on tester machines in the final design.
- Replace direct Discord POSTs with a support endpoint (`OPENSHIM_SUPPORT_ENDPOINT` during development).
- Discord becomes server-side notification only.
- Remove Discord attachment-size splitting once artifact storage is active.
- Add live tailing of `logs/openshim.log` on Windows first.
- Keep final bundle/artifact upload after process exit.

## Privacy defaults

Before upload, sanitize or omit:

- authentication/session tokens;
- Discord/webhook credentials;
- IPv4/IPv6 addresses unless an explicitly requested network-diagnostic mode is enabled;
- Windows usernames in absolute paths;
- hostname by default.

Do not create a persistent machine identifier. Generate a new support session identity for each run.

`multi.ini` should not be uploaded wholesale by default once structured metadata extraction exists; prefer a whitelist of support-relevant settings.

## Initial qualification gate

Windows/Steam is the first required target.

1. Normal launch without the wrapper produces zero telemetry traffic.
2. Support launch creates and displays a support ID.
3. `openshim.log` reaches the endpoint live while the game is running.
4. Network loss spools locally and does not affect the game.
5. Network recovery drains queued batches in sequence.
6. Clean exit uploads final artifacts and marks the session complete.
7. Access violation leaves the already-uploaded live timeline and uploads `openshim_crash.log` plus a minidump after process death.
8. Task Manager termination retains the live timeline and performs best-effort finalization.
9. Backend/quota failure never changes Battlezone behavior.
10. Removing the wrapper disables all future telemetry.

Linux/Flatpak/Snap qualification follows after Windows; Snap may remain post-session/outbox-only initially if live streaming from inside its sandbox is impractical.
