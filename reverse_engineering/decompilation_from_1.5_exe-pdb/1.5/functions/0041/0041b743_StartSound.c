/*
 * Entry: 0041b743
 * Name: StartSound
 * Namespace: Global
 * Signature: int StartSound(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl StartSound(lua_State *param_1)

{
  int iVar1;
  GameObject *pGVar2;
  _OBJ76 *p_Var3;
  GAS_PREP_INFO local_54;
  char *local_38;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var3 = (_OBJ76 *)0x0;
  local_38 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar1 = lua_type(param_1,2);
  if (0 < iVar1) {
    iVar1 = GetHandle(param_1,2);
    pGVar2 = GameObjectHandle::GetObj(iVar1);
    if (pGVar2 != (GameObject *)0x0) {
      p_Var3 = (_OBJ76 *)(**(code **)(pGVar2->_padding_ + 0x30))();
    }
  }
  InitGASCtrl(&local_34);
  local_34.flags = 1;
  InitGASPrep(&local_54);
  local_54.pri = luaL_optinteger(param_1,3,local_54.pri);
  iVar1 = lua_toboolean(param_1,4);
  local_54.loopMode = (long)(iVar1 != 0);
  local_54.volume = luaL_optinteger(param_1,5,local_54.volume);
  local_54.sampleRate = luaL_optinteger(param_1,6,local_54.sampleRate);
  StartGASEvent(local_38,p_Var3,&local_34,&local_54);
  return 0;
}
