/*
 * Entry: 0041ba93
 * Name: GetPilotClass
 * Namespace: Global
 * Signature: int GetPilotClass(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPilotClass(lua_State *param_1)

{
  int iVar1;
  GameObject *pGVar2;
  
  iVar1 = GetHandle(param_1,1);
  pGVar2 = GameObjectHandle::GetObj(iVar1);
  if ((pGVar2 != (GameObject *)0x0) && (pGVar2->curPilot != (GameObjectClass *)0x0)) {
    lua_pushlstring(param_1,(char *)&pGVar2->curPilot->cfg,8);
    return 1;
  }
  return 0;
}
