"""Run the sibling's existing protocol clients through the M1 tunnel.

All server state/logs live in --out. No game install or server source is edited.
Requires the server's normal Python dependencies. This is not native gameplay.
"""
import argparse
import asyncio
import json
import os
import pathlib
import socket
import subprocess
import sys
import time

from socket_tunnel_integration import Process


async def lobby_flow(compat):
    first = await compat.BZRClient.connect('127.0.0.1', 1337, 'tunnel-host')
    second = await compat.BZRClient.connect('127.0.0.1', 1337, 'tunnel-guest')
    try:
        for client, uid in ((first, 'U_TUNNEL_A'), (second, 'U_TUNNEL_B')):
            await compat.auth_stock(client, client.name, uid)
            assert await compat.wait_authorized(client) == uid
            await compat.enter_lounge_bool(client)
            await client.wait_for({'OnDoEnterLounge', 'OnLobbyListChanged'})
        mark = len(first.inbox)
        await compat.create_game_minimal(first)
        created = compat.last_of(await first.wait_for({'OnLobbyCreated'}, since=mark), 'OnLobbyCreated')['data']
        assert created['success'] is True
        mark = len(second.inbox)
        await second.send('GetLobbyList', True)
        listed = compat.last_of(await second.wait_for({'OnGetLobbyList'}, since=mark), 'OnGetLobbyList')
        assert str(created['id']) in json.dumps(listed['data'])
        mark = len(second.inbox)
        await second.send('DoJoinLobby', {'id': created['id'], 'password': ''})
        joined = compat.last_of(await second.wait_for({'OnLobbyJoined'}, since=mark), 'OnLobbyJoined')['data']
        assert joined.get('reasonCode') == 0, joined
        return 'two synthetic stock-profile clients authorized, listed, created and joined a lobby over the tunnel'
    finally:
        await first.close()
        await second.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--server-repo', required=True, type=pathlib.Path)
    parser.add_argument('--exe', required=True)
    parser.add_argument('--out', required=True, type=pathlib.Path)
    args = parser.parse_args()
    repo, out = args.server_repo.resolve(), args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    sys.dont_write_bytecode = True
    sys.path.insert(0, str(repo))
    import stock_client_compat_test as compat
    import smoke_test
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1')
    processes = []
    with (out / 'server.log').open('w') as log:
        server = subprocess.Popen([sys.executable, str(repo / 'server.py'), '--ws-host', '127.0.0.2',
            '--udp-host', '127.0.0.2', '--relay-host', '127.0.0.2', '--relay-pair-ports',
            '--relay-pair-port-start', '1340', '--relay-pair-port-end', '1369', '--health-port', '0',
            '--state-file', str(out / 'state.json'), '--audit-log', str(out / 'audit.jsonl')],
            cwd=out, env=env, stdout=log, stderr=subprocess.STDOUT, creationflags=subprocess.CREATE_NO_WINDOW)
        try:
            deadline = time.monotonic() + 10
            while True:
                assert server.poll() is None, (out / 'server.log').read_text()
                try:
                    with socket.create_connection(('127.0.0.2', 1337), .2):
                        break
                except OSError:
                    assert time.monotonic() < deadline, 'server start timeout'
                    time.sleep(.1)
            processes.append(Process(args.exe, out, 'bridge', 'bridge'))
            processes.append(Process(args.exe, out, 'agent', 'agent'))
            time.sleep(1.3)
            result = {'lobby': asyncio.run(lobby_flow(compat))}
            ok, detail = asyncio.run(smoke_test.ws_smoke('127.0.0.1', 1337, 3))
            assert ok, detail
            result['ws_smoke'] = detail
            # The sibling's direct-path UDP smoke expects the client's own
            # endpoint. Here the server must advertise the BRIDGE endpoint;
            # this is the reason native tunnel sessions force /iprelay.
            payload = bytes.fromhex('40020000019c744772360000000000000000')
            with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
                udp.settimeout(3)
                udp.sendto(payload, ('127.0.0.1', 1338))
                reply, source = udp.recvfrom(1024)
                assert source == ('127.0.0.1', 1338)
                assert reply.startswith(payload) and len(reply) == len(payload) + 7
                assert reply[-7:-2] == b'\x04' + socket.inet_aton('127.0.0.10')
                assert int.from_bytes(reply[-2:], 'big') > 0
            result['udp_handshake'] = 'unchanged probe payload; server advertises bridge source 127.0.0.10 and its mapped UDP port (forced relay required)'
            (out / 'result.json').write_text(json.dumps(result, indent=2))
            print(json.dumps(result, indent=2))
        finally:
            for process in reversed(processes):
                process.close()
            server.terminate()
            server.wait(5)


if __name__ == '__main__':
    main()
