const PROTOCOL_VERSION = 1;
const SESSION_TTL_MS = 12 * 60 * 60 * 1000;
const MAX_LOG_BATCH_BYTES = 512 * 1024;
const MAX_ARTIFACT_BYTES = 25 * 1024 * 1024;

export default {
  async fetch(request, env) {
    try {
      return await route(request, env);
    } catch (error) {
      console.error("support-worker unhandled error", error);
      return json({ error: "internal_error" }, 500);
    }
  },
};

async function route(request, env) {
  const url = new URL(request.url);
  const path = url.pathname.replace(/\/+$/, "") || "/";

  if (request.method === "GET" && path === "/health") {
    return json({ ok: true, protocol: PROTOCOL_VERSION });
  }

  if (request.method === "POST" && path === "/v1/session") {
    return createSession(request, env);
  }

  const match = path.match(/^\/v1\/session\/([A-Z0-9-]+)\/(logs|artifact|finish)$/);
  if (!match || request.method !== "POST") {
    return json({ error: "not_found" }, 404);
  }

  const supportId = match[1];
  const action = match[2];
  const auth = await authorizeSession(request, env, supportId);
  if (!auth.ok) return auth.response;

  if (action === "logs") return ingestLogs(request, env, supportId);
  if (action === "artifact") return uploadArtifact(request, env, supportId);
  return finishSession(request, env, supportId);
}

async function createSession(request, env) {
  requireBinding(env, "SUPPORT_BUCKET");

  const body = await readJsonLimited(request, 64 * 1024);
  if (!body.ok) return body.response;
  if (body.value.protocol !== PROTOCOL_VERSION) {
    return json({ error: "unsupported_protocol", supported: PROTOCOL_VERSION }, 400);
  }

  const now = new Date();
  const expiresAt = new Date(now.getTime() + SESSION_TTL_MS);
  const sessionToken = randomHex(32);
  const tokenHash = await sha256HexString(sessionToken);

  let supportId = null;
  for (let attempt = 0; attempt < 5; ++attempt) {
    const candidate = `OCP-${randomHex(4).toUpperCase()}`;
    const existing = await env.SUPPORT_BUCKET.head(sessionKey(candidate));
    if (!existing) {
      supportId = candidate;
      break;
    }
  }
  if (!supportId) return json({ error: "session_id_collision" }, 503);

  const session = {
    protocol: PROTOCOL_VERSION,
    support_id: supportId,
    created_at: now.toISOString(),
    expires_at: expiresAt.toISOString(),
    token_sha256: tokenHash,
    client: sanitizeSessionClient(body.value),
  };

  await env.SUPPORT_BUCKET.put(sessionKey(supportId), JSON.stringify(session, null, 2), {
    httpMetadata: { contentType: "application/json" },
  });

  await notifyDiscord(env, `OpenShim support session started: **${supportId}**`);

  return json({
    support_id: supportId,
    session_token: sessionToken,
    expires_at: expiresAt.toISOString(),
    protocol: PROTOCOL_VERSION,
  }, 201);
}

async function authorizeSession(request, env, supportId) {
  requireBinding(env, "SUPPORT_BUCKET");

  const auth = request.headers.get("Authorization") || "";
  if (!auth.startsWith("Bearer ")) {
    return { ok: false, response: json({ error: "missing_token" }, 401) };
  }

  const object = await env.SUPPORT_BUCKET.get(sessionKey(supportId));
  if (!object) return { ok: false, response: json({ error: "unknown_session" }, 404) };

  let session;
  try {
    session = JSON.parse(await object.text());
  } catch {
    return { ok: false, response: json({ error: "invalid_session_state" }, 500) };
  }

  if (Date.parse(session.expires_at) <= Date.now()) {
    return { ok: false, response: json({ error: "session_expired" }, 401) };
  }

  const token = auth.slice("Bearer ".length).trim();
  const providedHash = await sha256HexString(token);
  if (!timingSafeEqual(providedHash, session.token_sha256)) {
    return { ok: false, response: json({ error: "invalid_token" }, 401) };
  }

  return { ok: true, session };
}

async function ingestLogs(request, env, supportId) {
  requireBinding(env, "SUPPORT_BUCKET");
  requireBinding(env, "BETTERSTACK_INGEST_HOST");
  requireBinding(env, "BETTERSTACK_SOURCE_TOKEN");

  const body = await readJsonLimited(request, MAX_LOG_BATCH_BYTES);
  if (!body.ok) return body.response;

  const sequence = body.value.sequence;
  const events = body.value.events;
  if (!Number.isInteger(sequence) || sequence < 0 || !Array.isArray(events) || events.length === 0) {
    return json({ error: "invalid_log_batch" }, 400);
  }

  // The client writes each batch to disk before sending it. If Better Stack
  // accepted a batch but the HTTP success response was lost, the client will
  // retry the same sequence. Persist an acknowledgement in R2 so ordinary
  // retries do not duplicate the whole batch in the live log store.
  const ackKey = logAckKey(supportId, sequence);
  const existingAck = await env.SUPPORT_BUCKET.head(ackKey);
  if (existingAck) {
    return json({ ok: true, sequence, duplicate: true });
  }

  const normalized = events.slice(0, 5000).map((event) => {
    const safe = event && typeof event === "object" ? { ...event } : { message: String(event) };
    safe.support_id = supportId;
    safe.sequence = sequence;
    if (!safe.dt) safe.dt = safe.timestamp || new Date().toISOString();
    delete safe.timestamp;
    return safe;
  });

  const response = await fetch(env.BETTERSTACK_INGEST_HOST, {
    method: "POST",
    headers: {
      "Authorization": `Bearer ${env.BETTERSTACK_SOURCE_TOKEN}`,
      "Content-Type": "application/json",
    },
    body: JSON.stringify(normalized),
  });

  // A non-2xx response intentionally fails the client batch. The wrapper keeps
  // its local spool and retries later instead of silently losing diagnostics.
  if (!response.ok) {
    console.warn("Better Stack rejected batch", supportId, sequence, response.status);
    return json({ error: "log_sink_unavailable", upstream_status: response.status }, 502);
  }

  await env.SUPPORT_BUCKET.put(
    ackKey,
    JSON.stringify({ support_id: supportId, sequence, accepted_at: new Date().toISOString() }),
    { httpMetadata: { contentType: "application/json" } },
  );

  return json({ ok: true, sequence });
}

async function uploadArtifact(request, env, supportId) {
  requireBinding(env, "SUPPORT_BUCKET");

  const lengthHeader = request.headers.get("Content-Length");
  if (lengthHeader && Number(lengthHeader) > MAX_ARTIFACT_BYTES) {
    return json({ error: "artifact_too_large", max_bytes: MAX_ARTIFACT_BYTES }, 413);
  }

  const rawName = request.headers.get("X-Artifact-Name") || "artifact.bin";
  const fileName = sanitizeFileName(rawName);
  const bytes = await request.arrayBuffer();
  if (bytes.byteLength > MAX_ARTIFACT_BYTES) {
    return json({ error: "artifact_too_large", max_bytes: MAX_ARTIFACT_BYTES }, 413);
  }

  // Content-address artifacts. A retry after a lost success response resolves
  // to the same R2 key and therefore does not create timestamped duplicates.
  const contentSha256 = await sha256HexBytes(bytes);
  const key = artifactKey(supportId, contentSha256, fileName);
  const existing = await env.SUPPORT_BUCKET.head(key);
  if (existing) {
    return json({ ok: true, key, bytes: bytes.byteLength, sha256: contentSha256, duplicate: true });
  }

  await env.SUPPORT_BUCKET.put(key, bytes, {
    httpMetadata: {
      contentType: request.headers.get("Content-Type") || "application/octet-stream",
    },
    customMetadata: {
      support_id: supportId,
      original_name: fileName,
      sha256: contentSha256,
    },
  });

  return json({ ok: true, key, bytes: bytes.byteLength, sha256: contentSha256 }, 201);
}

async function finishSession(request, env, supportId) {
  requireBinding(env, "SUPPORT_BUCKET");

  const finishKey = `sessions/${supportId}/finish.json`;
  const existingFinish = await env.SUPPORT_BUCKET.head(finishKey);
  if (existingFinish) {
    // A retried finish should not generate repeated Discord notifications.
    return json({ ok: true, duplicate: true });
  }

  const body = await readJsonLimited(request, 64 * 1024);
  if (!body.ok) return body.response;

  const finish = {
    support_id: supportId,
    finished_at: new Date().toISOString(),
    exit_code: integerOrNull(body.value.exit_code),
    clean_exit: Boolean(body.value.clean_exit),
    crashed: Boolean(body.value.crashed),
    final_sequence: integerOrNull(body.value.final_sequence),
    artifacts: Array.isArray(body.value.artifacts)
      ? body.value.artifacts.slice(0, 64).map((v) => String(v).slice(0, 256))
      : [],
  };

  await env.SUPPORT_BUCKET.put(
    finishKey,
    JSON.stringify(finish, null, 2),
    { httpMetadata: { contentType: "application/json" } },
  );

  const status = finish.crashed ? "CRASHED" : finish.clean_exit ? "completed" : "ended abruptly";
  await notifyDiscord(env, `OpenShim support session **${supportId}** ${status}.`);
  return json({ ok: true });
}

function sanitizeSessionClient(body) {
  const allowed = [
    "platform",
    "distribution",
    "wrapper_version",
    "openshim_version",
    "openshim_commit",
    "game_version",
    "exe_sha256",
  ];
  const client = {};
  for (const key of allowed) {
    if (body[key] !== undefined && body[key] !== null) {
      client[key] = String(body[key]).slice(0, 256);
    }
  }
  return client;
}

async function notifyDiscord(env, message) {
  if (!env.DISCORD_WEBHOOK) return;
  try {
    const response = await fetch(env.DISCORD_WEBHOOK, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ content: message }),
    });
    if (!response.ok) console.warn("Discord webhook returned", response.status);
  } catch (error) {
    // Notifications are deliberately best-effort and never affect telemetry.
    console.warn("Discord notification failed", error);
  }
}

async function readJsonLimited(request, maxBytes) {
  const lengthHeader = request.headers.get("Content-Length");
  if (lengthHeader && Number(lengthHeader) > maxBytes) {
    return { ok: false, response: json({ error: "payload_too_large", max_bytes: maxBytes }, 413) };
  }

  const text = await request.text();
  if (new TextEncoder().encode(text).byteLength > maxBytes) {
    return { ok: false, response: json({ error: "payload_too_large", max_bytes: maxBytes }, 413) };
  }

  try {
    return { ok: true, value: JSON.parse(text) };
  } catch {
    return { ok: false, response: json({ error: "invalid_json" }, 400) };
  }
}

function sessionKey(supportId) {
  return `sessions/${supportId}/session.json`;
}

function logAckKey(supportId, sequence) {
  return `sessions/${supportId}/acks/logs/${String(sequence).padStart(12, "0")}.json`;
}

function artifactKey(supportId, sha256, fileName) {
  return `sessions/${supportId}/artifacts/${sha256}-${fileName}`;
}

function sanitizeFileName(value) {
  const base = String(value).split(/[\\/]/).pop() || "artifact.bin";
  const safe = base.replace(/[^A-Za-z0-9._-]/g, "_").replace(/^\.+/, "");
  return (safe || "artifact.bin").slice(0, 160);
}

function integerOrNull(value) {
  return Number.isInteger(value) ? value : null;
}

function requireBinding(env, name) {
  if (!env[name]) throw new Error(`Missing Worker binding/secret: ${name}`);
}

function randomHex(byteCount) {
  const bytes = new Uint8Array(byteCount);
  crypto.getRandomValues(bytes);
  return [...bytes].map((b) => b.toString(16).padStart(2, "0")).join("");
}

async function sha256HexString(value) {
  return sha256HexBytes(new TextEncoder().encode(value));
}

async function sha256HexBytes(value) {
  const digest = new Uint8Array(await crypto.subtle.digest("SHA-256", value));
  return [...digest].map((b) => b.toString(16).padStart(2, "0")).join("");
}

function timingSafeEqual(a, b) {
  if (typeof a !== "string" || typeof b !== "string" || a.length !== b.length) return false;
  let diff = 0;
  for (let i = 0; i < a.length; ++i) diff |= a.charCodeAt(i) ^ b.charCodeAt(i);
  return diff === 0;
}

function json(value, status = 200) {
  return new Response(JSON.stringify(value), {
    status,
    headers: {
      "Content-Type": "application/json; charset=utf-8",
      "Cache-Control": "no-store",
    },
  });
}
