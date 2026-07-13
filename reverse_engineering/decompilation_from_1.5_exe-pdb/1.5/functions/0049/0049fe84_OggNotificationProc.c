/*
 * Entry: 0049fe84
 * Name: OggNotificationProc
 * Namespace: Global
 * Signature: uint OggNotificationProc(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl OggNotificationProc(void *param_1)

{
  bool bVar1;
  DWORD DVar2;
  int iVar3;
  
  bVar1 = false;
  SetThreadName(0xffffffff,"OggDecoder");
  do {
    DVar2 = MsgWaitForMultipleObjects(1,param_1,0,0xffffffff,0);
    if (DVar2 == 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)((int)param_1 + 0x2f4));
      if (*(CStreamingOggSound **)((int)param_1 + 0x18) == (CStreamingOggSound *)0x0) {
LAB_0049fed0:
        bVar1 = true;
      }
      else {
        iVar3 = CStreamingOggSound::HandleWaveStreamNotification
                          (*(CStreamingOggSound **)((int)param_1 + 0x18),
                           (uint)*(byte *)((int)param_1 + 0xc));
        if (iVar3 < 0) goto LAB_0049fed0;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)((int)param_1 + 0x2f4));
    }
    if (bVar1) {
      return 0;
    }
  } while( true );
}
