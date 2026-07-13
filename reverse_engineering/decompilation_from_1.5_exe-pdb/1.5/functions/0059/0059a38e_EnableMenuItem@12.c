/*
 * Entry: 0059a38e
 * Name: _EnableMenuItem@12
 * Namespace: Global
 * Signature: BOOL _EnableMenuItem@12(HMENU hMenu, UINT uIDEnableItem, UINT uEnable)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _EnableMenuItem_12(HMENU hMenu,UINT uIDEnableItem,UINT uEnable)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a38e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EnableMenuItem(hMenu,uIDEnableItem,uEnable);
  return BVar1;
}
