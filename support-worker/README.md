# OpenShim support Worker

Backend for the opt-in remote-support telemetry flow described in
`upload/SUPPORT_TELEMETRY_PLAN.md`.

This is intentionally separate from the native shim. The public client talks
only to this Worker; permanent Better Stack and Discord credentials remain
server-side.

## Endpoints

- `GET /health`
- `POST /v1/session`
- `POST /v1/session/{support_id}/logs`
- `POST /v1/session/{support_id}/artifact`
- `POST /v1/session/{support_id}/finish`

All per-session endpoints after creation require
`Authorization: Bearer <session_token>`.

## Provision a test deployment

Prerequisites:

- a Cloudflare account with Workers/R2 enabled;
- a Better Stack Logs source;
- Node.js/npm on the machine doing the deployment;
- optionally, a Discord webhook for the private support channel.

From this directory:

```powershell
npx wrangler@latest login
npx wrangler@latest r2 bucket create openshim-support
Copy-Item .\wrangler.jsonc.example .\wrangler.jsonc
```

Edit `wrangler.jsonc` and replace:

```text
https://REPLACE_WITH_SOURCE_INGEST_HOST
```

with the **Ingesting host** shown by the Better Stack source.

Store credentials as Worker secrets, never in Git:

```powershell
npx wrangler@latest secret put BETTERSTACK_SOURCE_TOKEN --config wrangler.jsonc
npx wrangler@latest secret put DISCORD_WEBHOOK --config wrangler.jsonc
```

`DISCORD_WEBHOOK` is optional. If no Discord alert is wanted, simply do not
create that secret.

Deploy:

```powershell
npx wrangler@latest deploy --config wrangler.jsonc
```

Wrangler prints the resulting HTTPS Worker URL. Verify it before configuring a
tester:

```powershell
Invoke-RestMethod https://YOUR-WORKER.workers.dev/health
```

Expected response:

```json
{"ok":true,"protocol":1}
```

The R2 bucket is accessed through the Worker binding, so no R2 access key is
exposed to the client.

## Better Stack

Create an HTTP/Logs source and copy its **Source token** and **Ingesting host**.
The Worker posts an array of JSON events to that ingest host using the source
token as a Bearer token. Client timestamps are normalized into Better Stack's
`dt` field, so they remain searchable by their original OpenShim time.

A non-success response from Better Stack is intentionally returned to the
wrapper as a failed log batch. The wrapper retains that batch in its local disk
spool and retries it later instead of acknowledging data that was never
indexed.

Log sequence acknowledgements are stored in R2 after Better Stack accepts a
batch. If the HTTP success response is lost and the client retries the same
sequence, the Worker acknowledges it without forwarding the batch twice.

## Discord

`DISCORD_WEBHOOK` is optional. It is only used for low-volume session
start/finish/crash notifications. Discord never receives the live log stream,
the final logs, or minidumps through this path.

## R2 layout

```text
sessions/
  OCP-XXXXXXXX/
    session.json
    finish.json
    acks/
      logs/
        000000000000.json
        000000000001.json
    artifacts/
      <sha256>-openshim.log
      <sha256>-openshim_crash.log
      <sha256>-BZLogger.tail.txt
      <sha256>-openshim_crash_*.dmp
```

Artifacts are content-addressed. Retrying the same artifact after a lost HTTP
success response resolves to the same R2 key rather than creating another
copy.

Live log payloads themselves are not duplicated into R2. Client-side spooling
is the delivery guarantee; Better Stack is the searchable live store, while
final sanitized text logs are uploaded as R2 artifacts.

## Configure a Windows tester

Until there is a production Worker URL, use the dedicated support installer on
the telemetry branch:

```powershell
$env:OPENSHIM_SUPPORT_ENDPOINT='https://YOUR-WORKER.workers.dev'
irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/agent/openshim-support-telemetry/scripts/install_support_windows.ps1 | iex
```

The installer prints the exact Steam launch option:

```text
cmd /c ""%LOCALAPPDATA%\openshim\openshim_support_wrap.bat" %command%"
```

That launch option is the consent boundary. Removing it returns the tester to a
normal OpenShim launch with no support telemetry.

The newest session ID is both printed at launch and persisted to:

```text
%LOCALAPPDATA%\openshim\latest-support-id.txt
```

Minidump upload stays off by default because a dump can contain arbitrary
process memory. For a qualification run where the tester explicitly agrees to
send dumps, set this before running the support installer:

```powershell
$env:OPENSHIM_SUPPORT_INCLUDE_DUMPS='1'
```

Text crash diagnostics still upload without that setting.

## Security and privacy properties

- Session tokens are random and short-lived (12 hours by default).
- Only SHA-256 hashes of session tokens are stored in R2 session metadata.
- No permanent backend credential is sent to OpenShim users.
- Artifact names are reduced to safe basenames.
- Artifact bodies are content-addressed by SHA-256.
- Payload and artifact sizes are bounded.
- Routine client sanitization removes Discord webhook URLs, IPv4 addresses,
  and the account-name portion of `C:\Users\...` paths before upload.
- Minidumps require a second, explicit opt-in.
- Backend/Discord failure must not prevent Battlezone from launching; the
  wrapper owns local spooling/retry.

Before wider/public deployment:

1. add Cloudflare-side rate limiting/abuse controls for session creation;
2. set an R2 lifecycle retention policy (for example 30 days for ordinary
   support material and 90 days for explicitly collected crash artifacts);
3. inspect real sanitized payloads from the first controlled Windows test;
4. do not retarget draft PR #117 to `main` until PR #116 is incorporated and
   the stacked diff is revalidated.
