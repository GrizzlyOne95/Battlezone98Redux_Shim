/*
 * Entry: 0059a550
 * Name: _GetStockObject@4
 * Namespace: Global
 * Signature: HGDIOBJ _GetStockObject@4(int i)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HGDIOBJ _GetStockObject_4(int i)

{
  HGDIOBJ pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a550. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetStockObject(i);
  return pvVar1;
}
