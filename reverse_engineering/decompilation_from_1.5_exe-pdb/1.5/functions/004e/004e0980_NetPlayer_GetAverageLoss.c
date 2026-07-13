/*
 * Entry: 004e0980
 * Name: NetPlayer::GetAverageLoss
 * Namespace: NetPlayer
 * Signature: ulong GetAverageLoss(NetPlayer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __thiscall NetPlayer::GetAverageLoss(NetPlayer *this)

{
  ulong uVar1;
  uint uVar2;
  
  uVar1 = 100;
  for (uVar2 = this->dwPingReplies & 0x3ff; uVar2 != 0; uVar2 = uVar2 >> 1) {
    if ((uVar2 & 1) != 0) {
      uVar1 = uVar1 - 10;
    }
  }
  return uVar1;
}
