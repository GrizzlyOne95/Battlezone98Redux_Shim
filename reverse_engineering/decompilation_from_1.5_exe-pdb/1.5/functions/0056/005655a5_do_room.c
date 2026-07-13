/*
 * Entry: 005655a5
 * Name: do_room
 * Namespace: Global
 * Signature: int do_room(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_room(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x98,shell_hwnd,RoomDlgProc,0);
  return iVar1;
}
