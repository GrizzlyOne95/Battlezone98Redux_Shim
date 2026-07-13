/*
 * Entry: 0041ad29
 * Name: LuaMission::Save
 * Namespace: LuaMission
 * Signature: bool Save(LuaMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LuaMission::Save(LuaMission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  lua_State *plVar4;
  char *pcVar5;
  int local_10;
  int local_c;
  int local_8;
  
  if (!missionSave) {
    ::out(param_1,&this->started,1,"started");
  }
  iVar3 = 0;
  if ((this->L != (lua_State *)0x0) && (missionSave == false)) {
    lua_getfield(this->L,-0x2712,"Save");
    iVar2 = lua_type(this->L,-1);
    if (iVar2 == 6) {
      local_c = lua_gettop(this->L);
      pcVar5 = "Lua script Save error:\n%s";
      plVar4 = this->L;
      iVar2 = lua_pcall(plVar4,0,-1,0);
      bVar1 = LuaCheckStatus(iVar2,plVar4,pcVar5);
      if (bVar1) {
        iVar2 = 1 - local_c;
        local_10 = iVar2;
        local_8 = lua_gettop(this->L);
        local_8 = local_8 + iVar2;
        ::out(param_1,&local_8,4,"count");
        if (0 < local_8) {
          do {
            iVar2 = iVar3 + local_c;
            Trace("-- Save %d\n");
            SaveValue(param_1,this->L,iVar2,0);
            pcVar5 = ",\n";
            if (local_8 + -1 <= iVar3) {
              pcVar5 = "\n";
            }
            Trace(pcVar5);
            iVar3 = iVar3 + 1;
          } while (iVar3 < local_8);
        }
      }
    }
    else {
      local_10 = 0;
      ::out(param_1,&local_10,4,"count");
      lua_settop(this->L,-2);
    }
  }
  bVar1 = AiMission::Save((AiMission *)this,param_1);
  return bVar1;
}
