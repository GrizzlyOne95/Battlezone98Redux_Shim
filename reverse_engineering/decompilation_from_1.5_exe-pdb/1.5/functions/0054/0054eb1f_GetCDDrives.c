/*
 * Entry: 0054eb1f
 * Name: GetCDDrives
 * Namespace: Global
 * Signature: void GetCDDrives(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl GetCDDrives(void)

{
  DWORD DVar1;
  UINT UVar2;
  char cVar3;
  int iVar4;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  builtin_strncpy(local_18," :\\",4);
  DVar1 = GetLogicalDrives();
  cVar3 = '\0';
  iVar4 = 0;
  do {
    if ((DVar1 & 1 << ((byte)iVar4 & 0x1f)) != 0) {
      local_18[0] = cVar3 + 'A';
      UVar2 = GetDriveTypeA(local_18);
      if (UVar2 == 5) {
        IsCD[iVar4] = '\x01';
      }
    }
    cVar3 = cVar3 + '\x01';
    iVar4 = iVar4 + 1;
  } while (cVar3 < '\x1a');
  return;
}
