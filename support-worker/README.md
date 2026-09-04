# OpenShim support Worker

Prototype backend for the opt-in remote-support telemetry flow described in `upload/SUPPORT_TELEMETRY_PLAN.md`.

This is intentionally separate from the native shim. The public client talks only to this Worker; permanent Better Stack and Discord credentials remain server-side.

## Endpoints

- `GET /health`
- `POST /v1/session`
- `POST /v1/session/{support_id}/logs`
- `POST /v1/session/{support_id}/artifact`
- `POST /v1/session/{support_id}/finish`

All per-session endpoints after creation require `Authorization: Bearer <session_token>`.

## Cloudflare setup

1. Create an R2 bucket, for example `openshim-support`.
2. Copy `wrangler.jsonc.example` to `wrangler.jsonc` and set the bucket name plus the Better Stack ingest host for the source.
3. Add secrets with Wrangler rather than committing them:

```text
npx wrangler secret put BETTERSTACK_SOURCE_TOKEN
npx wrangler secret put DISCORD_WEBHOOK
```

4. Deploy the Worker and use its HTTPS URL as the support client endpoint.

The R2 bucket is accessed through the Worker binding, so no R2 access key is exposed to the client.

## Better Stack

Create a Logs source and use its source ingest host in `BETTERSTACK_INGEST_HOST`. The Worker posts an array of JSON events using the source token as a Bearer token. Client event timestamps are normalized into Better Stack's `dt` field.

A non-success response from Better Stack is intentionally returned to the wrapper as a failed log batch. The wrapper must retain that batch in its local spool and retry it later instead of acknowledging data that was never ingested.

## Discord

`DISCORD_WEBHOOK` is optional. It is only used for low-volume session start/finish/crash notifications and never receives the full live log stream or crash artifacts.

## R2 layout

```text
sessions/
  OCP-XXXXXXXX/
    session.json
    finish.json
    artifacts/
      <timestamp>-openshim.log
      <timestamp>-openshim_crash.log
      <timestamp>-openshim_crash_*.dmp
```

Live log batches are not duplicated into R2 in this prototype. Client-side spooling is the delivery guarantee; Better Stack is the searchable live store, while the final local logs are uploaded as R2 artifacts.

## Security properties

- Session tokens are random and short-lived (12 hours by default).
- Only SHA-256 hashes of session tokens are stored in R2 session metadata.
- No permanent backend credential is sent to OpenShim users.
- Artifact names are reduced to safe basenames.
- Payload and artifact sizes are bounded.
- Backend/Discord failure is never supposed to affect Battlezone itself; the wrapper owns retry/fallback behavior.

Before public deployment, add Cloudflare-side rate limiting/abuse controls and set an R2 lifecycle retention policy.
