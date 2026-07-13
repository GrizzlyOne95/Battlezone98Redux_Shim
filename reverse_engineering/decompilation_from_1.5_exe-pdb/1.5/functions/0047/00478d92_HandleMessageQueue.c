/*
 * Entry: 00478d92
 * Name: HandleMessageQueue
 * Namespace: Global
 * Signature: void HandleMessageQueue(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandleMessageQueue(VIDEO_DEVICE *param_1)

{
  BOOL BVar1;
  tagMSG local_20;
  
  if (param_1->ShutDownReq == 0) {
    while( true ) {
      BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
      if (BVar1 == 0) break;
      if ((local_20.hwnd == (HWND)0x0) || (local_20.message != 0x12)) {
        TranslateMessage(&local_20);
        DispatchMessageA(&local_20);
      }
      else {
        ExitCode = local_20.wParam;
        param_1->ShutDownReq = 1;
      }
    }
  }
  return;
}
