/*
 * Entry: 00471e01
 * Name: pMoveTrack
 * Namespace: Global
 * Signature: void pMoveTrack(Disc * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl pMoveTrack(Disc *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *unaff_EDI;
  PS local_14;
  
  if (((CD_OK != 0) && (iVar2 = PlayerState(), 2 < iVar2)) && (iVar2 < 5)) {
    PlayerDisplayInfo(&local_14);
    iVar1 = (int)param_1->StartOfTrack + local_14.track + -8;
    if ((*unaff_EDI <= iVar1) && (iVar1 <= unaff_EDI[1])) {
      if (iVar2 == 3) {
        CDStopAudio();
        iVar2 = (iVar1 - ThisDisc.LowestTrack) * 4;
        CDPlayAudio(*(ulong *)((int)&ThisDisc + iVar2 + 8),*(ulong *)((int)&ThisDisc + iVar2 + 0xc))
        ;
      }
      else if (iVar2 == 4) {
        iVar2 = (iVar1 - ThisDisc.LowestTrack) * 4;
        CDPlayAudio(*(ulong *)((int)&ThisDisc + iVar2 + 8),*(ulong *)((int)&ThisDisc + iVar2 + 0xc))
        ;
        CDStopAudio();
        pPauseInfo.minutes = 0;
        pPauseInfo.seconds = 0;
        pPauseInfo.track = iVar1;
      }
    }
  }
  return;
}
