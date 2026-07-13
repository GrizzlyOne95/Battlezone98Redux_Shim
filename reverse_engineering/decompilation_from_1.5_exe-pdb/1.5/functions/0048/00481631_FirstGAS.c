/*
 * Entry: 00481631
 * Name: FirstGAS
 * Namespace: Global
 * Signature: int FirstGAS(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FirstGAS(HWND__ *param_1)

{
  int *piVar1;
  int iVar2;
  int unaff_ESI;
  GAS_MASTER *unaff_EDI;
  GAS_MASTER *pGVar3;
  
  GM = (GAS_MASTER *)0x0;
  pGVar3 = &GAS_Master;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    pGVar3->DSHandle = (IDirectSound *)0x0;
    pGVar3 = (GAS_MASTER *)&pGVar3->primaryBuffer;
  }
  if ((UseAudio != 0) && (iVar2 = StartGAS((HWND__ *)UseDS3DAudio,unaff_EDI,unaff_ESI), iVar2 != 0))
  {
    GM = &GAS_Master;
    SetDS3DDefaults();
    SetGASMaxObjects((uint)(UserProfilePtr->audioControl).channels);
    SetGASVolumeLevels();
    SetGASMasterVolumes(-1,-1,-1);
    PlayerInit();
    SoundHeap = (void *)0x1;
    UsedMemory = 0;
    piVar1 = &copies[0].count;
    minFreeCopies = 0;
    do {
      freeCopy = minFreeCopies;
      ((CopyInfo *)(piVar1 + -2))->prev = -1;
      piVar1[-1] = freeCopy - 1;
      *piVar1 = 0;
      piVar1[1] = 0;
      piVar1 = piVar1 + 4;
      minFreeCopies = freeCopy + 1;
    } while ((uint)minFreeCopies < 0x1e);
    gasPaused = false;
    freeCopies = minFreeCopies;
    mHdl = Mono_Register(GAS_Refresh);
    lastMonoLine = 0;
    return 1;
  }
  return 0;
}
