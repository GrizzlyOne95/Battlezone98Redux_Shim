/*
 * Entry: 0054bc30
 * Name: InitMachineCaps
 * Namespace: Global
 * Signature: MACHINE_CAPS * InitMachineCaps(MACHINE_CAPS * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MACHINE_CAPS * __cdecl InitMachineCaps(MACHINE_CAPS *__return_storage_ptr__)

{
  int iVar1;
  MACHINE_CAPS *pMVar2;
  MACHINE_CAPS *pMVar3;
  _MEMORYSTATUS local_24;
  
  GlobalMemoryStatus(&local_24);
  ThisMachineCaps.PhysicalRAM = local_24.dwTotalPhys;
  ThisMachineCaps.VMFreeSpace = local_24.dwAvailPageFile;
  pMVar2 = &ThisMachineCaps;
  pMVar3 = __return_storage_ptr__;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar3->PhysicalRAM = pMVar2->PhysicalRAM;
    pMVar2 = (MACHINE_CAPS *)&pMVar2->VideoRAM;
    pMVar3 = (MACHINE_CAPS *)&pMVar3->VideoRAM;
  }
  return __return_storage_ptr__;
}
