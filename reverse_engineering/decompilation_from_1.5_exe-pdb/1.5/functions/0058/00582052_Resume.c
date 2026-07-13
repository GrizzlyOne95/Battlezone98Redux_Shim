/*
 * Entry: 00582052
 * Name: Resume
 * Namespace: Global
 * Signature: void Resume(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Resume(void)

{
  DWORD DVar1;
  
  if (bPaused != 0) {
    DVar1 = timeGetTime();
    dwPrevious = DVar1 - dwSofar;
    bPaused = 0;
  }
  return;
}
