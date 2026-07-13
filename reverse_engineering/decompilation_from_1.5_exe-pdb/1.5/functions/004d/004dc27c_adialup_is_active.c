/*
 * Entry: 004dc27c
 * Name: adialup_is_active
 * Namespace: Global
 * Signature: int adialup_is_active(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

int __cdecl adialup_is_active(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  FARPROC pFVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  undefined4 local_1d54;
  HMODULE local_1d50;
  uint local_1d4c [29];
  undefined1 local_1cd8 [7088];
  undefined4 local_128;
  int local_124;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1cd8;
  hModule = LoadLibraryA("rasapi32.dll");
  if (hModule != (HMODULE)0x0) {
    local_1d50 = hModule;
    pFVar1 = GetProcAddress(hModule,"RasEnumConnectionsA");
    pFVar2 = GetProcAddress(hModule,"RasGetConnectStatusA");
    if ((pFVar1 != (FARPROC)0x0) && (pFVar2 != (FARPROC)0x0)) {
      local_1d4c[1] = 0x2d0;
      local_1d54 = 0x1c20;
      local_1d4c[0] = 10;
      iVar3 = (*pFVar1)(local_1d4c + 1,&local_1d54,local_1d4c);
      hModule = local_1d50;
      if (iVar3 == 0) {
        uVar4 = 0;
        if (local_1d4c[0] == 0) {
LAB_004dc30e:
          FreeLibrary(local_1d50);
          return uVar4;
        }
        if (local_1d4c[0] != 0) {
          puVar5 = local_1d4c + 2;
          do {
            local_128 = 0x120;
            (*pFVar2)(*puVar5,&local_128);
            if (local_124 == 0x2000) {
              uVar4 = 1;
              goto LAB_004dc30e;
            }
            uVar4 = uVar4 + 1;
            puVar5 = puVar5 + 0xb4;
            hModule = local_1d50;
          } while (uVar4 < local_1d4c[0]);
        }
      }
    }
    FreeLibrary(hModule);
  }
  return 0;
}
