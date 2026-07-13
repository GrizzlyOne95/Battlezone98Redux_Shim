/*
 * Entry: 004bd82f
 * Name: giddi_flush_key
 * Namespace: Global
 * Signature: int giddi_flush_key(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_flush_key(void)

{
  BOOL BVar1;
  tagMSG local_20;
  
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x100,0x109,1);
  if (BVar1 != 0) {
    ProcessKeyboardMessages(local_20.message,local_20.wParam,local_20.lParam);
  }
  bufferIn = 0;
  bufferOut = 0;
  return 0;
}
