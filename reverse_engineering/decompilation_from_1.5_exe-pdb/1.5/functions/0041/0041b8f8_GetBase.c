/*
 * Entry: 0041b8f8
 * Name: GetBase
 * Namespace: Global
 * Signature: int GetBase(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetBase(lua_State *param_1)

{
  int iVar1;
  GameObject *pGVar2;
  uint uVar3;
  
  iVar1 = GetHandle(param_1,1);
  pGVar2 = GameObjectHandle::GetObj(iVar1);
  if (pGVar2 != (GameObject *)0x0) {
    uVar3 = 8;
    iVar1 = (**(code **)pGVar2->_padding_)();
    lua_pushlstring(param_1,(char *)(iVar1 + 0x30),uVar3);
    return 1;
  }
  return 0;
}
