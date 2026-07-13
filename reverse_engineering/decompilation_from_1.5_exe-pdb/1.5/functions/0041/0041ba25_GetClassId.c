/*
 * Entry: 0041ba25
 * Name: GetClassId
 * Namespace: Global
 * Signature: int GetClassId(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetClassId(lua_State *param_1)

{
  int iVar1;
  GameObject *pGVar2;
  
  iVar1 = GetHandle(param_1,1);
  pGVar2 = GameObjectHandle::GetObj(iVar1);
  if (pGVar2 != (GameObject *)0x0) {
    iVar1 = (**(code **)pGVar2->_padding_)();
    lua_pushinteger(param_1,*(int *)(iVar1 + 0x28));
    return 1;
  }
  return 0;
}
