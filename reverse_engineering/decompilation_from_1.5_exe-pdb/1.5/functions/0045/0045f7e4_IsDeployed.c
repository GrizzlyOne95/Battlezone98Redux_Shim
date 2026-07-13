/*
 * Entry: 0045f7e4
 * Name: IsDeployed
 * Namespace: Global
 * Signature: bool IsDeployed(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsDeployed(int param_1)

{
  undefined1 uVar1;
  GameObject *pGVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  
  pGVar2 = GameObjectHandle::GetObj(param_1);
  if (pGVar2 != (GameObject *)0x0) {
    p_Var3 = (_OBJ76 *)(**(code **)(pGVar2->_padding_ + 0x30))();
    iVar4 = IsCraft(p_Var3);
    if (iVar4 != 0) {
                    /* WARNING: Could not recover jumptable at 0x0045f811. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar1 = (**(code **)(pGVar2->_padding_ + 100))();
      return (bool)uVar1;
    }
  }
  return false;
}
