/*
 * Entry: 00471eb5
 * Name: PlayerTrack
 * Namespace: Global
 * Signature: void PlayerTrack(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerTrack(int param_1)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  PS local_14;
  
  if (CD_OK != 0) {
    iVar2 = 0xf;
    if (0xe < param_1) {
      iVar2 = param_1 + 1;
    }
    iVar1 = PlayerState();
    if ((((1 < iVar1) && (iVar1 < 5)) &&
        (PlayerDisplayInfo(&local_14), ThisDisc.LowestTrack <= param_1)) &&
       (param_1 <= ThisDisc.HighestTrack)) {
      if (iVar1 == 3) {
        CDStopAudio();
        uVar3 = *(ulong *)((int)&ThisDisc + (iVar2 - ThisDisc.LowestTrack) * 4 + 8);
      }
      else {
        uVar3 = *(ulong *)((int)&ThisDisc + (iVar2 - ThisDisc.LowestTrack) * 4 + 8);
        if (iVar1 == 4) {
          CDPlayAudio(*(ulong *)((int)&ThisDisc + (param_1 - ThisDisc.LowestTrack) * 4 + 8),uVar3);
          pPauseInfo.track = param_1;
          pPauseInfo.minutes = 0;
          pPauseInfo.seconds = 0;
          return;
        }
      }
      CDPlayAudio(*(ulong *)((int)&ThisDisc + (param_1 - ThisDisc.LowestTrack) * 4 + 8),uVar3);
    }
  }
  return;
}
