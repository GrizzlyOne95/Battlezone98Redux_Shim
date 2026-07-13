/*
 * Entry: 0041b421
 * Name: LuaMission::Command
 * Namespace: LuaMission
 * Signature: bool Command(LuaMission * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LuaMission::Command(LuaMission *this,char *param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  bool bVar4;
  lua_State *plVar5;
  
  bVar4 = false;
  if (this->L == (lua_State *)0x0) {
    bVar4 = false;
  }
  else {
    lua_getfield(this->L,-0x2712,"Command");
    iVar1 = lua_type(this->L,-1);
    if (iVar1 == 6) {
      iVar1 = lua_gettop(this->L);
      pcVar2 = strchr(param_1,0x20);
      if (pcVar2 == (char *)0x0) {
LAB_0041b4a2:
        lua_pushstring(this->L,param_1);
      }
      else {
        lua_pushlstring(this->L,param_1,(int)pcVar2 - (int)param_1);
        for (; *pcVar2 != '\0'; pcVar2 = pcVar2 + 1) {
          param_1 = pcVar2;
          if (*pcVar2 != ' ') goto LAB_0041b4a2;
        }
      }
      iVar3 = lua_gettop(this->L);
      plVar5 = this->L;
      pcVar2 = "Lua script Command error:\n%s";
      iVar1 = lua_pcall(plVar5,iVar3 - iVar1,1,0);
      LuaCheckStatus(iVar1,plVar5,pcVar2);
      iVar1 = lua_toboolean(this->L,-1);
      bVar4 = iVar1 != 0;
      lua_settop(this->L,-2);
    }
    else {
      lua_settop(this->L,-2);
    }
  }
  return bVar4;
}
