"""Exercise the real in-process host implementation in an isolated test owner."""
import asyncio
import json
from pathlib import Path
import socket
import struct
import subprocess
import sys
import tempfile
import time
import websockets


async def event(ws, kind):
    for _ in range(200):
        message = json.loads(await asyncio.wait_for(ws.recv(), 3))
        if message['type'] == kind:
            return message['data']
    raise AssertionError(f'missing {kind}')


async def send(ws, kind, content):
    await ws.send(json.dumps({'type': kind, 'content': content}))


async def test(exe, stop):
    proc = subprocess.Popen([exe, '127.0.0.1', '21347', str(stop)], stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)
    try:
        assert await asyncio.to_thread(proc.stdout.readline) == 'IN_PROCESS_LAN_READY\n'
        # Discovery and the stock UDP endpoint probe are served by the same owner.
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
            udp.settimeout(3)
            nonce = b'12345678'
            udp.sendto(b'BZRLAN1?' + nonce + bytes(80), ('127.0.0.1', 21337))
            packet, _ = udp.recvfrom(256)
            assert packet[:16] == b'BZRLAN1!' + nonce
            assert struct.unpack('!H', packet[16:18])[0] == 21347
            probe = b'\x40\x02' + struct.pack('!Q', int(time.time()*1000)) + bytes(8)
            udp.sendto(probe, ('127.0.0.1', 21348))
            reply, _ = udp.recvfrom(256)
            assert reply[:18] == probe and reply[18] == 4
            assert reply[19:23] == socket.inet_aton('127.0.0.1')
        async with websockets.connect('ws://127.0.0.1:21347', ping_interval=None) as a, \
                   websockets.connect('ws://127.0.0.1:21347', ping_interval=None) as b:
            await send(a, 'Authorization', {'authtype': 'steam', 'id': 'S111', 'name': 'Online',
                                            'steamAppTicket': 'not-a-ticket', 'clientVersion': '2.2.301'})
            assert not (await event(a, 'OnAuthorization'))['success']
            for ws, identity in [(a, 'B111'), (b, 'B222')]:
                await send(ws, 'Authorization', {'authtype': 'lan', 'id': identity, 'name': identity,
                                                'clientVersion': '2.2.301'})
                admission = await event(ws, 'OnAuthorization')
                assert admission['id'] == identity and admission['isAuth']
                assert admission['authType'] == 'lan' and admission['name'] == identity
                assert admission['lanAddresses'] == [] and admission['wanAddress'] == ''
            rooms = (await event(a, 'OnLobbyListChanged'))['lobbies']
            assert rooms['1']['isChat'] and rooms['1']['name'] == '~chat~pub~~default'
            await send(b, 'DoJoinLobby', {'id': 1})
            assert (await event(b, 'OnLobbyJoined'))['id'] == 1
            await send(a, 'CreateGame', {'name': 'In-process test', 'memberLimit': 2})
            created = await event(a, 'OnLobbyCreated')
            await send(b, 'DoJoinLobby', {'id': created['id'], 'password': ''})
            assert (await event(b, 'OnLobbyJoined'))['success']
            await send(b, 'DoUpdateLAN', ['8.8.8.8:4567'])
            assert (await event(a, 'OnLANUpdated'))['lanAddresses'] == ['127.0.0.1:4567']
            await send(a, 'SetLobbyData', {'key': 'gameSettings', 'value': 'map/settings'})
            await event(b, 'OnLobbyDataChanged')
            await send(b, 'SetPlayerData', {'key': 'ready', 'value': 'map/settings'})
            assert (await event(a, 'OnUserDataChanged'))['member'] == 'B222'
            await send(b, 'DoP2PConnect', {'player': 'B111', 'reset': False})
            assert (await event(a, 'OnLobbyMemberP2PConnect'))['player'] == 'B222'
            await send(a, 'DoSendChat', 'LAN message')
            assert (await event(b, 'OnChatMessage'))['text'] == 'LAN message'
            await a.close()
            assert (await event(b, 'OnLobbyRemoved'))['id'] == created['id']
        # A different owner cannot adopt or share the listener.
        conflict = subprocess.run([exe, '127.0.0.1', '21347'], capture_output=True, text=True, timeout=5)
        assert conflict.returncode != 0 and 'bind failed' in conflict.stdout
        # An upgraded socket still has to admit a local profile within 10 s.
        async with websockets.connect('ws://127.0.0.1:21347', ping_interval=None) as idle:
            try:
                await asyncio.wait_for(idle.recv(), 12)
                raise AssertionError('idle unauthenticated connection was retained')
            except websockets.exceptions.ConnectionClosed:
                pass
        print('PASS: in-process WS admission, room cache/create/join/settings/ready/chat/peer signal/owner exit; UDP probe/discovery; exclusive bind')
    finally:
        stop.write_text('stop')
        proc.wait(timeout=5)
        assert proc.returncode == 0


if __name__ == '__main__':
    with tempfile.TemporaryDirectory(prefix='bzr-embedded-lan-') as directory:
        asyncio.run(test(sys.argv[1], Path(directory)/'stop'))
