/*
 * Entry: 0041ae74
 * Name: LuaMission::Start
 * Namespace: LuaMission
 * Signature: void Start(LuaMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LuaMission::Start(LuaMission *this)

{
  int iVar1;
  lua_State *plVar2;
  char *pcVar3;
  
  AiMission::Start((AiMission *)this);
  if ((this->started == false) && (this->L != (lua_State *)0x0)) {
    lua_getfield(this->L,-0x2712,"Start");
    iVar1 = lua_type(this->L,-1);
    if (iVar1 == 6) {
      plVar2 = this->L;
      pcVar3 = "Lua script Start error:\n%s";
      iVar1 = lua_pcall(plVar2,0,0,0);
      LuaCheckStatus(iVar1,plVar2,pcVar3);
    }
    else {
      lua_settop(this->L,-2);
    }
    this->started = true;
  }
  return;
}
