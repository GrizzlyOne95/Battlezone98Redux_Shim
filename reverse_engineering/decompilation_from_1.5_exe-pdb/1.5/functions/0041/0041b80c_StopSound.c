/*
 * Entry: 0041b80c
 * Name: StopSound
 * Namespace: Global
 * Signature: int StopSound(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StopSound(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  GameObject *pGVar3;
  _gas_object *p_Var4;
  _OBJ76 *p_Var5;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  p_Var5 = (_OBJ76 *)0x0;
  iVar2 = lua_type(param_1,2);
  if (0 < iVar2) {
    iVar2 = GetHandle(param_1,2);
    pGVar3 = GameObjectHandle::GetObj(iVar2);
    if (pGVar3 != (GameObject *)0x0) {
      p_Var5 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x30))();
    }
  }
  p_Var4 = FindGASObject(pcVar1,p_Var5);
  if (p_Var4 != (_gas_object *)0x0) {
    StopGASEvent(p_Var4);
  }
  return 0;
}
