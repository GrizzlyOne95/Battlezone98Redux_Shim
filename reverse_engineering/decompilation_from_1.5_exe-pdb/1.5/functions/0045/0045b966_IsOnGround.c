/*
 * Entry: 0045b966
 * Name: IsOnGround
 * Namespace: Global
 * Signature: bool IsOnGround(Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsOnGround(Craft *param_1)

{
  undefined1 uVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0045b96c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(param_1->_padding_ + 0x68))();
  return (bool)uVar1;
}
