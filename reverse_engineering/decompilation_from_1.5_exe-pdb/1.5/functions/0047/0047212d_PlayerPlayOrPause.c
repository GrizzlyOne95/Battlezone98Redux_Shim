/*
 * Entry: 0047212d
 * Name: PlayerPlayOrPause
 * Namespace: Global
 * Signature: void PlayerPlayOrPause(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerPlayOrPause(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (CD_OK != 0) {
    iVar2 = 0xf;
    if (0xe < param_1) {
      iVar2 = param_1 + 1;
    }
    iVar1 = PlayerState();
    if (iVar1 == 2) {
      if (0x32 < param_1) {
        param_1 = 0x32;
      }
      CDPlayAudio(*(ulong *)((int)&ThisDisc + (param_1 - ThisDisc.LowestTrack) * 4 + 8),
                  *(ulong *)((int)&ThisDisc + (iVar2 - ThisDisc.LowestTrack) * 4 + 8));
    }
    else {
      if (iVar1 == 3) {
        PlayerDisplayInfo(&pPauseInfo);
        CDPauseAudio();
        return;
      }
      if (iVar1 == 4) {
        CDResumeAudio();
        return;
      }
    }
  }
  return;
}
