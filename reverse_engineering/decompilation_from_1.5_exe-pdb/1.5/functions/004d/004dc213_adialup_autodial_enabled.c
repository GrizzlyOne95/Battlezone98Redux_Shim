/*
 * Entry: 004dc213
 * Name: adialup_autodial_enabled
 * Namespace: Global
 * Signature: int adialup_autodial_enabled(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl adialup_autodial_enabled(void)

{
  LSTATUS LVar1;
  DWORD local_10;
  int local_c;
  HKEY local_8;
  
  LVar1 = RegOpenKeyExA((HKEY)0x80000001,
                        "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",0,0x20019,
                        &local_8);
  if (LVar1 == 0) {
    local_c = 0;
    local_10 = 4;
    LVar1 = RegQueryValueExA(local_8,"EnableAutodial",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_c,
                             &local_10);
    CloseHandle(local_8);
    if (LVar1 == 0) {
      return (uint)(local_c != 0);
    }
  }
  return 0;
}
