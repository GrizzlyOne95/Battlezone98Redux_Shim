/*
 * Entry: 0059a4b4
 * Name: _GetKeyboardType@4
 * Namespace: Global
 * Signature: int _GetKeyboardType@4(int nTypeFlag)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _GetKeyboardType_4(int nTypeFlag)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetKeyboardType(nTypeFlag);
  return iVar1;
}
