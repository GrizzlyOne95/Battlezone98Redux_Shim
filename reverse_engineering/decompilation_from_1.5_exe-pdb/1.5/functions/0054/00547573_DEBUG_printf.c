/*
 * Entry: 00547573
 * Name: DEBUG_printf
 * Namespace: Global
 * Signature: void DEBUG_printf(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DEBUG_printf(char *param_1)

{
  char cVar1;
  char *pcVar2;
  DWORD local_40c;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  if (DebugOutputMethod == 1) {
    DEBUG_monoMessage(local_408);
  }
  else if (DebugOutputMethod == 2) {
    OutputDebugStringA(local_408);
    SetConsoleTextAttribute(console_stdout,7);
    pcVar2 = local_408;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    WriteConsoleA(console_stdout,local_408,(int)pcVar2 - (int)(local_408 + 1),&local_40c,(LPVOID)0x0
                 );
  }
  else if (DebugOutputMethod == 3) {
    if (DebugWindowHandle != (HWND__ *)0x0) {
      MessageBoxA((HWND)DebugWindowHandle,local_408,DebugWindowTitle,DebugWindowStyle);
    }
  }
  else if (DebugOutputMethod == 4) {
    DEBUG_fileLine(local_408);
  }
  return;
}
