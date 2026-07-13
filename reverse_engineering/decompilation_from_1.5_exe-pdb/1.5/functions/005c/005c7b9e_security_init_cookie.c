/*
 * Entry: 005c7b9e
 * Name: __security_init_cookie
 * Namespace: Global
 * Signature: void __security_init_cookie(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl __security_init_cookie(void)

{
  DWORD DVar1;
  DWORD DVar2;
  DWORD DVar3;
  uint uVar4;
  LARGE_INTEGER local_14;
  _FILETIME local_c;
  
  local_c.dwLowDateTime = 0;
  local_c.dwHighDateTime = 0;
  if ((__security_cookie == 0xbb40e64e) || ((__security_cookie & 0xffff0000) == 0)) {
    GetSystemTimeAsFileTime(&local_c);
    uVar4 = local_c.dwHighDateTime ^ local_c.dwLowDateTime;
    DVar1 = GetCurrentProcessId();
    DVar2 = GetCurrentThreadId();
    DVar3 = GetTickCount();
    QueryPerformanceCounter(&local_14);
    __security_cookie = uVar4 ^ DVar1 ^ DVar2 ^ DVar3 ^ local_14.s.HighPart ^ local_14.s.LowPart;
    if (__security_cookie == 0xbb40e64e) {
      __security_cookie = 0xbb40e64f;
    }
    else if ((__security_cookie & 0xffff0000) == 0) {
      __security_cookie = __security_cookie | __security_cookie << 0x10;
    }
  }
  __security_cookie_complement = ~__security_cookie;
  return;
}
