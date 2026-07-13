/*
 * Entry: 004e295e
 * Name: NetPlayer::GotSyncPacketAck
 * Namespace: NetPlayer
 * Signature: void GotSyncPacketAck(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NetPlayer::GotSyncPacketAck(ushort param_1)

{
  NetPlayer *pNVar1;
  
  pNVar1 = Find(param_1);
  if (pNVar1 != (NetPlayer *)0x0) {
    pNVar1->bGotSyncPacketAck = true;
  }
  return;
}
