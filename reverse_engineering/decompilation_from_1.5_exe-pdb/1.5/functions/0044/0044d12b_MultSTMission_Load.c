/*
 * Entry: 0044d12b
 * Name: MultSTMission::Load
 * Namespace: MultSTMission
 * Signature: bool Load(MultSTMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall MultSTMission::Load(MultSTMission *this,_iobuf *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  bool bVar4;
  lua_State *plVar5;
  MultSTMission *pMStack_8;
  
  if (missionSave) {
    bVar4 = version == 0x414;
  }
  else {
    bVar4 = 0x413 < version;
  }
  pMStack_8 = this;
  if (bVar4) {
    ::in(param_1,(bool *)&this->_padding_,1);
  }
  else {
    *(bool *)&this->_padding_ = !missionSave;
  }
  if (((lua_State *)this->_padding_ != (lua_State *)0x0) && (missionSave == false)) {
    lua_getfield((lua_State *)this->_padding_,-0x2712,"Load");
    iVar2 = lua_type((lua_State *)this->_padding_,-1);
    pMStack_8 = (MultSTMission *)0x0;
    if (iVar2 == 6) {
      ::in(param_1,(int *)&pMStack_8,4);
      iVar2 = 0;
      if (0 < (int)pMStack_8) {
        do {
          iVar1 = iVar2 + 1;
          Trace("-- Load %d\n");
          LoadValue(param_1,(lua_State *)this->_padding_,true,0);
          pcVar3 = ",\n";
          if ((int)((int)&pMStack_8[-1].dwLastTime + 3) <= iVar2) {
            pcVar3 = "\n";
          }
          Trace(pcVar3);
          iVar2 = iVar1;
        } while (iVar1 < (int)pMStack_8);
      }
      plVar5 = (lua_State *)this->_padding_;
      pcVar3 = "Lua script Load error:\n%s";
      iVar2 = lua_pcall(plVar5,(int)pMStack_8,0,0);
      LuaCheckStatus(iVar2,plVar5,pcVar3);
    }
    else {
      ::in(param_1,(int *)&pMStack_8,4);
      iVar2 = 0;
      if (0 < (int)pMStack_8) {
        do {
          LoadValue(param_1,(lua_State *)this->_padding_,false,0);
          iVar2 = iVar2 + 1;
        } while (iVar2 < (int)pMStack_8);
      }
      lua_settop((lua_State *)this->_padding_,-2);
    }
  }
  bVar4 = AiMission::Load((AiMission *)this,param_1);
  return bVar4;
}
