/*
 * Entry: 00582025
 * Name: Pause
 * Namespace: Global
 * Signature: void Pause(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Pause(void)

{
  int iVar1;
  DWORD DVar2;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && (bPaused == 0)) {
    DVar2 = timeGetTime();
    dwSofar = DVar2 - dwPrevious;
    bPaused = 1;
  }
  return;
}
