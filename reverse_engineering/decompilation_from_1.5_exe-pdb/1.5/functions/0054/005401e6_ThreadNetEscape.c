/*
 * Entry: 005401e6
 * Name: ThreadNetEscape
 * Namespace: Global
 * Signature: uint ThreadNetEscape(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl ThreadNetEscape(void *param_1)

{
  HANDLE hHandle;
  DWORD DVar1;
  
  hHandle = *(HANDLE *)param_1;
  DVar1 = WaitForSingleObject(hHandle,0);
  while (DVar1 == 0x102) {
    Sleep(0x14);
    DVar1 = WaitForSingleObject(hHandle,0);
    if (DVar1 == 0x102) {
      DoNetEscapeFrame();
    }
    DVar1 = WaitForSingleObject(hHandle,0);
  }
  return 0;
}
