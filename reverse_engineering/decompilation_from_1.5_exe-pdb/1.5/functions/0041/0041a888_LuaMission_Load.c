/*
 * Entry: 0041a888
 * Name: LuaMission::Load
 * Namespace: LuaMission
 * Signature: bool Load(LuaMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LuaMission::Load(LuaMission *this,_iobuf *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  bool bVar4;
  lua_State *plVar5;
  LuaMission *local_8;
  
  if (missionSave) {
    bVar4 = version == 0x414;
  }
  else {
    bVar4 = 0x413 < version;
  }
  local_8 = this;
  if (bVar4) {
    ::in(param_1,&this->started,1);
  }
  else {
    this->started = !missionSave;
  }
  if ((this->L != (lua_State *)0x0) && (missionSave == false)) {
    lua_getfield(this->L,-0x2712,"Load");
    iVar2 = lua_type(this->L,-1);
    local_8 = (LuaMission *)0x0;
    if (iVar2 == 6) {
      ::in(param_1,(int *)&local_8,4);
      iVar2 = 0;
      if (0 < (int)local_8) {
        do {
          iVar1 = iVar2 + 1;
          Trace("-- Load %d\n");
          LoadValue(param_1,this->L,true,0);
          pcVar3 = ",\n";
          if ((int)&local_8[-1].field_0x47 <= iVar2) {
            pcVar3 = "\n";
          }
          Trace(pcVar3);
          iVar2 = iVar1;
        } while (iVar1 < (int)local_8);
      }
      plVar5 = this->L;
      pcVar3 = "Lua script Load error:\n%s";
      iVar2 = lua_pcall(plVar5,(int)local_8,0,0);
      LuaCheckStatus(iVar2,plVar5,pcVar3);
    }
    else {
      ::in(param_1,(int *)&local_8,4);
      iVar2 = 0;
      if (0 < (int)local_8) {
        do {
          LoadValue(param_1,this->L,false,0);
          iVar2 = iVar2 + 1;
        } while (iVar2 < (int)local_8);
      }
      lua_settop(this->L,-2);
    }
  }
  bVar4 = AiMission::Load((AiMission *)this,param_1);
  return bVar4;
}
