/*
 * Entry: 0059a26e
 * Name: _LockResource@4
 * Namespace: Global
 * Signature: LPVOID _LockResource@4(HGLOBAL hResData)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LPVOID _LockResource_4(HGLOBAL hResData)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a26e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LockResource(hResData);
  return pvVar1;
}
