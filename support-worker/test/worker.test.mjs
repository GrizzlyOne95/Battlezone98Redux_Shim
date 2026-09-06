import assert from 'node:assert/strict';
import test from 'node:test';
import worker from '../src/index.js';

class FakeR2Object {
  constructor(value) {
    this.value = value;
  }

  async text() {
    if (typeof this.value === 'string') return this.value;
    if (this.value instanceof ArrayBuffer) {
      return new TextDecoder().decode(new Uint8Array(this.value));
    }
    if (ArrayBuffer.isView(this.value)) {
      return new TextDecoder().decode(this.value);
    }
    return String(this.value);
  }
}

class FakeR2Bucket {
  constructor() {
    this.objects = new Map();
  }

  async head(key) {
    return this.objects.has(key) ? { key } : null;
  }

  async get(key) {
    if (!this.objects.has(key)) return null;
    return new FakeR2Object(this.objects.get(key).value);
  }

  async put(key, value, options = {}) {
    let stored = value;
    if (value instanceof ArrayBuffer) stored = value.slice(0);
    else if (ArrayBuffer.isView(value)) stored = value.slice();
    this.objects.set(key, { value: stored, options });
    return { key };
  }
}

function jsonRequest(url, body, token = '') {
  const headers = { 'Content-Type': 'application/json' };
  if (token) headers.Authorization = `Bearer ${token}`;
  return new Request(url, {
    method: 'POST',
    headers,
    body: JSON.stringify(body),
  });
}

async function createSession(env) {
  const response = await worker.fetch(
    jsonRequest('https://support.test/v1/session', {
      protocol: 1,
      platform: 'windows',
      distribution: 'steam',
      wrapper_version: 'test-wrapper',
    }),
    env,
  );
  assert.equal(response.status, 201);
  const body = await response.json();
  assert.match(body.support_id, /^OCP-[A-F0-9]{8}$/);
  assert.equal(typeof body.session_token, 'string');
  assert.ok(body.session_token.length >= 64);
  return body;
}

test('health reports protocol version', async () => {
  const response = await worker.fetch(new Request('https://support.test/health'), {});
  assert.equal(response.status, 200);
  assert.deepEqual(await response.json(), { ok: true, protocol: 1 });
});

test('log, artifact, and finish retries are idempotent', async () => {
  const bucket = new FakeR2Bucket();
  const env = {
    SUPPORT_BUCKET: bucket,
    BETTERSTACK_INGEST_HOST: 'https://logs.example.test',
    BETTERSTACK_SOURCE_TOKEN: 'source-token',
  };

  const originalFetch = globalThis.fetch;
  let upstreamLogCalls = 0;
  globalThis.fetch = async (url, options = {}) => {
    assert.equal(String(url), env.BETTERSTACK_INGEST_HOST);
    assert.equal(options.method, 'POST');
    assert.equal(options.headers.Authorization, 'Bearer source-token');
    ++upstreamLogCalls;
    return new Response('', { status: 202 });
  };

  try {
    const session = await createSession(env);
    const base = `https://support.test/v1/session/${session.support_id}`;

    const unauthorized = await worker.fetch(
      jsonRequest(`${base}/logs`, { sequence: 0, events: [{ message: 'x' }] }),
      env,
    );
    assert.equal(unauthorized.status, 401);

    const logBody = {
      sequence: 0,
      events: [{ dt: '2026-09-04T20:04:31.118Z', level: 'INFO', message: 'hello' }],
    };
    const firstLog = await worker.fetch(jsonRequest(`${base}/logs`, logBody, session.session_token), env);
    assert.equal(firstLog.status, 200);
    assert.equal(upstreamLogCalls, 1);

    const retryLog = await worker.fetch(jsonRequest(`${base}/logs`, logBody, session.session_token), env);
    assert.equal(retryLog.status, 200);
    assert.equal((await retryLog.json()).duplicate, true);
    assert.equal(upstreamLogCalls, 1, 'retry must not be forwarded to Better Stack twice');

    const artifactBytes = new TextEncoder().encode('sanitized diagnostic text');
    const artifactHeaders = {
      Authorization: `Bearer ${session.session_token}`,
      'Content-Type': 'text/plain',
      'X-Artifact-Name': 'openshim.log',
    };
    const firstArtifact = await worker.fetch(new Request(`${base}/artifact`, {
      method: 'POST',
      headers: artifactHeaders,
      body: artifactBytes,
    }), env);
    assert.equal(firstArtifact.status, 201);
    const firstArtifactBody = await firstArtifact.json();
    assert.match(firstArtifactBody.sha256, /^[a-f0-9]{64}$/);

    const retryArtifact = await worker.fetch(new Request(`${base}/artifact`, {
      method: 'POST',
      headers: artifactHeaders,
      body: artifactBytes,
    }), env);
    assert.equal(retryArtifact.status, 200);
    const retryArtifactBody = await retryArtifact.json();
    assert.equal(retryArtifactBody.duplicate, true);
    assert.equal(retryArtifactBody.key, firstArtifactBody.key);

    const artifactKeys = [...bucket.objects.keys()].filter((key) => key.includes('/artifacts/'));
    assert.equal(artifactKeys.length, 1, 'artifact retry must resolve to one R2 object');

    const finishBody = {
      exit_code: 0,
      clean_exit: true,
      crashed: false,
      final_sequence: 0,
      artifacts: ['openshim.log'],
    };
    const firstFinish = await worker.fetch(jsonRequest(`${base}/finish`, finishBody, session.session_token), env);
    assert.equal(firstFinish.status, 200);

    const retryFinish = await worker.fetch(jsonRequest(`${base}/finish`, finishBody, session.session_token), env);
    assert.equal(retryFinish.status, 200);
    assert.equal((await retryFinish.json()).duplicate, true);
  } finally {
    globalThis.fetch = originalFetch;
  }
});

test('unsupported protocol is rejected before session creation', async () => {
  const env = { SUPPORT_BUCKET: new FakeR2Bucket() };
  const response = await worker.fetch(
    jsonRequest('https://support.test/v1/session', { protocol: 999 }),
    env,
  );
  assert.equal(response.status, 400);
  assert.equal((await response.json()).error, 'unsupported_protocol');
});
