/*
 * Entry: 004bd7dc
 * Name: GetOneKey
 * Namespace: Global
 * Signature: short GetOneKey(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

short __cdecl GetOneKey(void)

{
  BOOL BVar1;
  tagMSG local_24;
  short local_8 [2];
  
  giddi_read_key(local_8);
  if (local_8[0] == 0) {
    BVar1 = PeekMessageA(&local_24,(HWND)0x0,0x100,0x109,1);
    if (BVar1 != 0) {
      ProcessKeyboardMessages(local_24.message,local_24.wParam,local_24.lParam);
      giddi_read_key(local_8);
    }
  }
  return local_8[0];
}
