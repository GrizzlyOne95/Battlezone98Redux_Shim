/*
 * Entry: 0059a442
 * Name: _SetCursorPos@8
 * Namespace: Global
 * Signature: BOOL _SetCursorPos@8(int X, int Y)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetCursorPos_8(int X,int Y)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a442. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetCursorPos(X,Y);
  return BVar1;
}
