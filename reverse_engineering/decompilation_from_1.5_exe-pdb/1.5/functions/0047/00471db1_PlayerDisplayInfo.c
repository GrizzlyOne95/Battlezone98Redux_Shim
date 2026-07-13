/*
 * Entry: 00471db1
 * Name: PlayerDisplayInfo
 * Namespace: Global
 * Signature: void PlayerDisplayInfo(PS * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PlayerDisplayInfo(PS *param_1)

{
  int iVar1;
  PS *unaff_ESI;
  
  if (CD_OK != 0) {
    iVar1 = PlayerState();
    if (0 < iVar1) {
      if (iVar1 < 3) {
        param_1->track = 0;
        param_1->minutes = 0;
        param_1->seconds = 0;
        param_1->frame = 0;
      }
      else {
        if (iVar1 == 3) {
          pGetQInfo(unaff_ESI);
          return;
        }
        if (iVar1 == 4) {
          param_1->track = pPauseInfo.track;
          param_1->minutes = pPauseInfo.minutes;
          param_1->seconds = pPauseInfo.seconds;
          param_1->frame = pPauseInfo.frame;
          return;
        }
      }
    }
  }
  return;
}
