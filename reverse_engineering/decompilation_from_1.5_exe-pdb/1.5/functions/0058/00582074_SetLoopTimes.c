/*
 * Entry: 00582074
 * Name: SetLoopTimes
 * Namespace: Global
 * Signature: void SetLoopTimes(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl SetLoopTimes(void)

{
  float fVar1;
  DWORD DVar2;
  int iVar3;
  
  while (DVar2 = timeGetTime(), dwPrevious == DVar2) {
    Sleep(1);
  }
  DVar2 = timeGetTime();
  dwFrameCount = dwFrameCount + 1;
  if ((bPaused == 0) || (iVar3 = Net_IsNetGame(), iVar3 != 0)) {
    dwTimeStep = DVar2 - dwPrevious;
    dwPrevious = DVar2;
  }
  else {
    dwTimeStep = 0;
  }
  iVar3 = Net_IsNetGame();
  if (iVar3 == 0) {
    dwTime = dwTime + dwTimeStep;
  }
  else if (BAddOffset == 0) {
    dwTime = (DVar2 - dwStartTime) - dwOffset;
  }
  else {
    dwTime = (dwOffset - dwStartTime) + DVar2;
  }
  dwTimeLocal = dwTimeLocal + dwTimeStep;
  if (200 < dwTimeStep) {
    dwTimeStep = 200;
  }
  fVar1 = (float)(int)dwTime;
  if ((int)dwTime < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  fTime = fVar1 * TICKS2SEC;
  fVar1 = (float)(int)dwTimeStep;
  if ((int)dwTimeStep < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  fTimeStep = (fVar1 * TICKS2SEC + fTimeStep) * 0.5;
  if (fTimeStep < 1e-07) {
    fTimeStep = 1e-07;
  }
  if (fTimeStep == 0.0) {
    fTimeStepInv = (float)_DAT_0022592c;
  }
  else {
    fTimeStepInv = 1.0 / fTimeStep;
  }
  fVar1 = (float)(int)dwTimeLocal;
  if ((int)dwTimeLocal < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  fTimeLocal = fVar1 * TICKS2SEC;
  return;
}
