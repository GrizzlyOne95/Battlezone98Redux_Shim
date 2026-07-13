/*
 * Entry: 00472197
 * Name: PlayerPlay
 * Namespace: Global
 * Signature: void PlayerPlay(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerPlay(void)

{
  int iVar1;
  
  if (CD_OK != 0) {
    iVar1 = PlayerState();
    if (iVar1 == 2) {
      CDPlayAudio(ThisDisc.StartOfTrack[0],0);
    }
    else {
      if (iVar1 == 3) {
        PlayerDisplayInfo(&pPauseInfo);
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
