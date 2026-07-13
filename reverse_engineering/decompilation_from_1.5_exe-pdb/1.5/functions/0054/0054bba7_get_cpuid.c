/*
 * Entry: 0054bba7
 * Name: get_cpuid
 * Namespace: Global
 * Signature: uint get_cpuid(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl get_cpuid(void)

{
  uint uVar1;
  _SYSTEM_INFO local_28;
  
  GetSystemInfo(&local_28);
  if (local_28.dwProcessorType == 0x182) {
    uVar1 = 3;
  }
  else if (local_28.dwProcessorType == 0x1e6) {
    uVar1 = 4;
  }
  else if (local_28.dwProcessorType == 0x24a) {
    uVar1 = 5;
  }
  else {
    uVar1 = 6;
  }
  return uVar1;
}
