/*
 * Entry: 004975fa
 * Name: GameObject_GetOBJ76
 * Namespace: Global
 * Signature: _OBJ76 * GameObject_GetOBJ76(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl GameObject_GetOBJ76(int param_1)

{
  GameObject *pGVar1;
  _OBJ76 *p_Var2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return (_OBJ76 *)0x0;
  }
                    /* WARNING: Could not recover jumptable at 0x0049760e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  p_Var2 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
  return p_Var2;
}
