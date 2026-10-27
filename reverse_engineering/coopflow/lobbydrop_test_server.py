# Test-only DedicatedServer patch for the lobby-drop scenario (OpenShim PR #615).
# Usage: python lobbydrop_test_server.py <copy of DedicatedServer>/server.py
# Adds POST /test/drop-ws {"match": <name or user id substring>, "silent": bool}
# on the health port: it aborts that session's websocket TCP transport.
# silent=true also leaves the session registered, as when the server never
# saw the drop (the DedicatedServer #16 takeover path). Never ship this.
import sys, pathlib
p = pathlib.Path(sys.argv[1]); s = p.read_text(encoding='utf-8')
# 1) unregister keeps a "silent" session registered (the server never noticed the drop)
old = "        session = self.state.sessions_by_ws.pop(ws, None)\n        if not session:\n            return\n"
new = old + "        if getattr(session, '_test_silent', False):\n            self.log.info('TEST drop-ws: %s left registered (silent)', session.user_id)\n            return\n"
assert s.count(old) == 1; s = s.replace(old, new)
# 2) POST /test/drop-ws {"match": "<name or user_id substring>", "silent": bool}
anchor = '        if method == "POST" and path == "/relay/impairment":\n'
ep = '''        if method == "POST" and path == "/test/drop-ws":
            raw = await asyncio.wait_for(reader.readexactly(content_length), timeout=2.0) if content_length else b"{}"
            body = json.loads(raw.decode("utf-8") or "{}")
            match = str(body.get("match", "")); silent = bool(body.get("silent", False))
            hits = [x for x in list(ws_server.state.sessions_by_ws.values()) if match and (match in str(x.name) or match in str(x.user_id))]
            for x in hits:
                x._test_silent = silent
                ws_server.log.info("TEST drop-ws: aborting %s (%s) silent=%s", x.user_id, x.name, silent)
                x.ws.transport.abort()
            writer.write(_http_json(200, {"ok": True, "dropped": [str(x.user_id) for x in hits], "silent": silent}))
            await writer.drain()
            return

'''
assert s.count(anchor) == 1; s = s.replace(anchor, ep + anchor)
p.write_text(s, encoding='utf-8'); print('patched')
