/*
 * Entry: 0059a562
 * Name: _SelectObject@8
 * Namespace: Global
 * Signature: HGDIOBJ _SelectObject@8(HDC hdc, HGDIOBJ h)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HGDIOBJ _SelectObject_8(HDC hdc,HGDIOBJ h)

{
  HGDIOBJ pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a562. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = SelectObject(hdc,h);
  return pvVar1;
}
