/*
 * Entry: 00540228
 * Name: ThreadSyncTimer
 * Namespace: Global
 * Signature: uint ThreadSyncTimer(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl ThreadSyncTimer(void *param_1)

{
  HANDLE hHandle;
  DWORD DVar1;
  
  hHandle = *(HANDLE *)param_1;
  DVar1 = WaitForSingleObject(hHandle,0);
  while (DVar1 == 0x102) {
    Sleep(0x32);
    DVar1 = WaitForSingleObject(hHandle,0);
    if (DVar1 == 0x102) {
      doSyncTimer();
    }
    DVar1 = WaitForSingleObject(hHandle,0);
  }
  return 0;
}
