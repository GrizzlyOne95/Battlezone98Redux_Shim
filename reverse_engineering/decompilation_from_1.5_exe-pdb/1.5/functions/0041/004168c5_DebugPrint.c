/*
 * Entry: 004168c5
 * Name: DebugPrint
 * Namespace: Global
 * Signature: int DebugPrint(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl DebugPrint(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  DWORD local_100c;
  char local_1008 [4096];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar2 = _vsnprintf_s(local_1008,0x1000,0x1000,param_1,&stack0x00000008);
  OutputDebugStringA(local_1008);
  pcVar3 = local_1008;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  WriteConsoleA(console_stdout,local_1008,(int)pcVar3 - (int)(local_1008 + 1),&local_100c,
                (LPVOID)0x0);
  return iVar2;
}
