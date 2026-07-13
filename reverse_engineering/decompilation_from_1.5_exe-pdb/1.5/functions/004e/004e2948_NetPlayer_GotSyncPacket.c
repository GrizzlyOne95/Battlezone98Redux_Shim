/*
 * Entry: 004e2948
 * Name: NetPlayer::GotSyncPacket
 * Namespace: NetPlayer
 * Signature: void GotSyncPacket(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NetPlayer::GotSyncPacket(ushort param_1)

{
  NetPlayer *pNVar1;
  
  pNVar1 = Find(param_1);
  if (pNVar1 != (NetPlayer *)0x0) {
    pNVar1->bGotSyncPacket = true;
  }
  return;
}
