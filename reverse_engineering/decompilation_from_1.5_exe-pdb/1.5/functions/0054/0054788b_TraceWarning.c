/*
 * Entry: 0054788b
 * Name: TraceWarning
 * Namespace: Global
 * Signature: void TraceWarning(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl TraceWarning(char *param_1)

{
  char cVar1;
  char *pcVar2;
  DWORD local_40c;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  OutputDebugStringA(local_408);
  SetConsoleTextAttribute(console_stdout,6);
  pcVar2 = local_408;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  WriteConsoleA(console_stdout,local_408,(int)pcVar2 - (int)(local_408 + 1),&local_40c,(LPVOID)0x0);
  return;
}
