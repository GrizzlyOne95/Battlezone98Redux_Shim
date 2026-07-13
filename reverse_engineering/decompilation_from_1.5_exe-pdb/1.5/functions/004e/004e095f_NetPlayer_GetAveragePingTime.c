/*
 * Entry: 004e095f
 * Name: NetPlayer::GetAveragePingTime
 * Namespace: NetPlayer
 * Signature: ulong GetAveragePingTime(NetPlayer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __thiscall NetPlayer::GetAveragePingTime(NetPlayer *this)

{
  uint uVar1;
  uint uVar2;
  ulong *puVar3;
  uint uVar4;
  
  uVar1 = this->iHistQueueSize;
  uVar2 = 0;
  if (0 < (int)uVar1) {
    puVar3 = &this->hist[0].dwDelay;
    uVar4 = uVar1;
    do {
      uVar2 = uVar2 + *puVar3;
      puVar3 = puVar3 + 7;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
    uVar2 = uVar2 / uVar1;
  }
  return uVar2;
}
