/*
 * Entry: 0054bc1b
 * Name: GetMachineCaps
 * Namespace: Global
 * Signature: MACHINE_CAPS * GetMachineCaps(MACHINE_CAPS * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MACHINE_CAPS * __cdecl GetMachineCaps(MACHINE_CAPS *__return_storage_ptr__)

{
  int iVar1;
  MACHINE_CAPS *pMVar2;
  MACHINE_CAPS *pMVar3;
  
  pMVar2 = &ThisMachineCaps;
  pMVar3 = __return_storage_ptr__;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar3->PhysicalRAM = pMVar2->PhysicalRAM;
    pMVar2 = (MACHINE_CAPS *)&pMVar2->VideoRAM;
    pMVar3 = (MACHINE_CAPS *)&pMVar3->VideoRAM;
  }
  return __return_storage_ptr__;
}
