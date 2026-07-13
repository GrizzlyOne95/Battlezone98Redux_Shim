/*
 * Entry: 0041b930
 * Name: GetLabel
 * Namespace: Global
 * Signature: int GetLabel(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetLabel(lua_State *param_1)

{
  int iVar1;
  GameObject *pGVar2;
  
  iVar1 = GetHandle(param_1,1);
  pGVar2 = GameObjectHandle::GetObj(iVar1);
  if (pGVar2 != (GameObject *)0x0) {
    lua_pushstring(param_1,pGVar2->label);
    return 1;
  }
  return 0;
}
