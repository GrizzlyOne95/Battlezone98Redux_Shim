/*
 * Entry: 0047207e
 * Name: PlayerInit
 * Namespace: Global
 * Signature: int PlayerInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PlayerInit(void)

{
  int iVar1;
  Disc *unaff_ESI;
  
  pShuffle = 0;
  pRepeat = 0;
  iVar1 = CDInit();
  if (iVar1 != 0) {
    return 0;
  }
  CD_OK = 1;
  pState = PlayerState();
  if (pState != 1) {
    if ((pState == 2) || (pState == 3)) {
      pDiscInit(unaff_ESI);
    }
    else if (pState == 4) {
      pDiscInit(unaff_ESI);
      pGetQInfo((PS *)unaff_ESI);
    }
    if (nSaveVolumeFlag == 0) {
      nSaveVolumeFlag = 1;
      nSaveVolume = -0x4440445;
      if (auxCDRomID != -1) {
        auxGetVolume(auxCDRomID,&auxCDRomVol);
      }
    }
    SetCDVolume((uint)(UserProfilePtr->audioControl).music);
    return 1;
  }
  PlayerDone();
  CD_OK = 0;
  return 0;
}
