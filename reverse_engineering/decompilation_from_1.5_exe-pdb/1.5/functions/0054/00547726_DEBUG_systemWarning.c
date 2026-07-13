/*
 * Entry: 00547726
 * Name: DEBUG_systemWarning
 * Namespace: Global
 * Signature: void DEBUG_systemWarning(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DEBUG_systemWarning(char *param_1)

{
  int iVar1;
  DWORD local_40c;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  local_408[iVar1] = '\n';
  local_408[iVar1 + 1] = '\0';
  OutputDebugStringA(local_408);
  SetConsoleTextAttribute(console_stdout,0xc);
  WriteConsoleA(console_stdout,local_408,iVar1 + 1,&local_40c,(LPVOID)0x0);
  UnlockMouse();
  EnsurePalette();
  iVar1 = MessageBoxA((HWND)DebugWindowHandle,local_408,DebugWindowTitle,0x31);
  if (iVar1 == 2) {
    LastInputs();
    Device_Graphic_Close(&Device);
                    /* WARNING: Subroutine does not return */
    exit(0x71);
  }
  LockMouse();
  (*Device.VideoMode.OverlayPalette)(&Device,Device.Palette);
  return;
}
