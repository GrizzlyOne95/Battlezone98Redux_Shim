/*
 * Entry: 00547652
 * Name: DEBUG_systemError
 * Namespace: Global
 * Signature: void DEBUG_systemError(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DEBUG_systemError(char *param_1)

{
  int iVar1;
  DWORD local_40c;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (insideError == 0) {
    insideError = 1;
    iVar1 = _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
    local_408[iVar1] = '\n';
    local_408[iVar1 + 1] = '\0';
    OutputDebugStringA(local_408);
    SetConsoleTextAttribute(console_stdout,0xd);
    WriteConsoleA(console_stdout,local_408,iVar1 + 1,&local_40c,(LPVOID)0x0);
    UnlockMouse();
    Device_Graphic_Close(&Device);
    MessageBoxA((HWND)DebugWindowHandle,local_408,DebugWindowTitle,0x10);
    LastInputs();
                    /* WARNING: Subroutine does not return */
    exit(0x70);
  }
  return;
}
