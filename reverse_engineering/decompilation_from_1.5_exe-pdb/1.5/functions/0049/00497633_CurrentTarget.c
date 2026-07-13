/*
 * Entry: 00497633
 * Name: CurrentTarget
 * Namespace: Global
 * Signature: _OBJ76 * CurrentTarget(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl CurrentTarget(_OBJ76 *param_1)

{
  void *pvVar1;
  GameObject *pGVar2;
  _OBJ76 *p_Var3;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
  pGVar2 = GameObject::GetObj(*(int *)((int)pvVar1 + 0x214));
  if (pGVar2 != (GameObject *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0049765a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    p_Var3 = (_OBJ76 *)(**(code **)(pGVar2->_padding_ + 0x30))();
    return p_Var3;
  }
  return (_OBJ76 *)0x0;
}
