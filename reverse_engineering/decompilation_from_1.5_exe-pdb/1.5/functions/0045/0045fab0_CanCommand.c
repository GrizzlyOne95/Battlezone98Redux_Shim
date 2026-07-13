/*
 * Entry: 0045fab0
 * Name: CanCommand
 * Namespace: Global
 * Signature: bool CanCommand(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CanCommand(int param_1)

{
  undefined1 uVar1;
  GameObject *pGVar2;
  
  pGVar2 = GameObjectHandle::GetObj(param_1);
  if (pGVar2 == (GameObject *)0x0) {
    return false;
  }
                    /* WARNING: Could not recover jumptable at 0x0045fac5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(pGVar2->_padding_ + 0x38))();
  return (bool)uVar1;
}
