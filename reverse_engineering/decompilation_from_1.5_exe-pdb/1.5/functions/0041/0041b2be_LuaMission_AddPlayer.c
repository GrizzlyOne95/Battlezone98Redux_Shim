/*
 * Entry: 0041b2be
 * Name: LuaMission::AddPlayer
 * Namespace: LuaMission
 * Signature: void AddPlayer(LuaMission * this, NetPlayer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LuaMission::AddPlayer(LuaMission *this,NetPlayer *param_1)

{
  int iVar1;
  lua_State *plVar2;
  char *pcVar3;
  
  AiMission::AddPlayer((AiMission *)this,param_1);
  if (this->L != (lua_State *)0x0) {
    lua_getfield(this->L,-0x2712,"AddPlayer");
    iVar1 = lua_type(this->L,-1);
    if (iVar1 == 6) {
      lua_pushinteger(this->L,(uint)param_1->playerId);
      lua_pushstring(this->L,param_1->playerName);
      lua_pushinteger(this->L,(uint)param_1->bTeamNumber);
      plVar2 = this->L;
      pcVar3 = "Lua script AddPlayer error:\n%s";
      iVar1 = lua_pcall(plVar2,3,0,0);
      LuaCheckStatus(iVar1,plVar2,pcVar3);
    }
    else {
      lua_settop(this->L,-2);
    }
  }
  return;
}
