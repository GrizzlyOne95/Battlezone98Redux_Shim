/*
 * Entry: 0054ecf0
 * Name: I76Warning
 * Namespace: Global
 * Signature: void I76Warning(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl I76Warning(char *param_1)

{
  int iVar1;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  UnlockMouse();
  iVar1 = (*Device.VideoMode.ChangeMode)(&Device,0);
  if (iVar1 == 0) {
    DEBUG_systemError("Interstate 76 Init_Graphic_System");
  }
  (*Device.Refresh.BlitFill)(&Device,0);
  (*Device.VideoMode.OverlayPalette)(&Device,(RGB *)&WindowsPalette);
  (*Device.Refresh.Blit)(&Device);
  iVar1 = MessageBoxA((HWND)Device.hwndApp,local_408,"Battlezone",0x31);
  if (iVar1 == 2) {
    LastInputs();
                    /* WARNING: Subroutine does not return */
    exit(0x72);
  }
  (*Device.VideoMode.OverlayPalette)(&Device,Device.Palette);
  (*Device.Refresh.Blit)(&Device);
  LockMouse();
  return;
}
