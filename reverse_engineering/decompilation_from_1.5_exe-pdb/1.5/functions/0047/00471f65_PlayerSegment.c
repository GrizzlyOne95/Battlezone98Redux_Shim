/*
 * Entry: 00471f65
 * Name: PlayerSegment
 * Namespace: Global
 * Signature: void PlayerSegment(ulong param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerSegment(ulong param_1,ulong param_2)

{
  int iVar1;
  PS local_14;
  
  if ((((CD_OK != 0) && (iVar1 = PlayerState(), 1 < iVar1)) && (iVar1 < 5)) &&
     (PlayerDisplayInfo(&local_14), param_1 < param_2)) {
    if (iVar1 == 3) {
      CDStopAudio();
    }
    else if (iVar1 == 4) {
      CDPlayAudio(param_1,param_2);
      pPauseInfo.track = 0;
      pPauseInfo.minutes = 0;
      pPauseInfo.seconds = 0;
      return;
    }
    CDPlayAudio(param_1,param_2);
  }
  return;
}
