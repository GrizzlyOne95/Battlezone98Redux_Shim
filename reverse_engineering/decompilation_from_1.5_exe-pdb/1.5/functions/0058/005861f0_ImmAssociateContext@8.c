/*
 * Entry: 005861f0
 * Name: _ImmAssociateContext@8
 * Namespace: Global
 * Signature: HIMC _ImmAssociateContext@8(HWND param_1, HIMC param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HIMC _ImmAssociateContext_8(HWND param_1,HIMC param_2)

{
  HIMC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005861f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = ImmAssociateContext(param_1,param_2);
  return pHVar1;
}
