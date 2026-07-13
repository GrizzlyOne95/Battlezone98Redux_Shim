/*
 * Entry: 0059a556
 * Name: _DeleteObject@4
 * Namespace: Global
 * Signature: BOOL _DeleteObject@4(HGDIOBJ ho)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _DeleteObject_4(HGDIOBJ ho)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a556. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteObject(ho);
  return BVar1;
}
