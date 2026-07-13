/*
 * Entry: 00573f34
 * Name: do_joystick
 * Namespace: Global
 * Signature: int do_joystick(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_joystick(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x110,shell_hwnd,JoystickDlgProc,0);
  return iVar1;
}
