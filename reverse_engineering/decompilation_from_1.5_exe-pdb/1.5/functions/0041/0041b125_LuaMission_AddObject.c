/*
 * Entry: 0041b125
 * Name: LuaMission::AddObject
 * Namespace: LuaMission
 * Signature: void AddObject(LuaMission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LuaMission::AddObject(LuaMission *this,GameObject *param_1)

{
  int iVar1;
  lua_State *plVar2;
  char *pcVar3;
  
  AiMission::AddObject((AiMission *)this,param_1);
  if (this->L != (lua_State *)0x0) {
    lua_getfield(this->L,-0x2712,"AddObject");
    iVar1 = lua_type(this->L,-1);
    if (iVar1 == 6) {
      iVar1 = GameObject::GetHandle(param_1);
      PushHandle(this->L,iVar1);
      plVar2 = this->L;
      pcVar3 = "Lua script AddObject error:\n%s";
      iVar1 = lua_pcall(plVar2,1,0,0);
      LuaCheckStatus(iVar1,plVar2,pcVar3);
    }
    else {
      lua_settop(this->L,-2);
    }
  }
  return;
}
