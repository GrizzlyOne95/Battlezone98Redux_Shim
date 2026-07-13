/*
 * Entry: 0045b96f
 * Name: IsFlying
 * Namespace: Global
 * Signature: bool IsFlying(Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsFlying(Craft *param_1)

{
  undefined1 uVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0045b975. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(param_1->_padding_ + 100))();
  return (bool)uVar1;
}
