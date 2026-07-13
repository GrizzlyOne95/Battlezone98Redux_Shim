/*
 * Entry: 0059a622
 * Name: _DPtoLP@12
 * Namespace: Global
 * Signature: BOOL _DPtoLP@12(HDC hdc, LPPOINT lppt, int c)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _DPtoLP_12(HDC hdc,LPPOINT lppt,int c)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a622. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DPtoLP(hdc,lppt,c);
  return BVar1;
}
