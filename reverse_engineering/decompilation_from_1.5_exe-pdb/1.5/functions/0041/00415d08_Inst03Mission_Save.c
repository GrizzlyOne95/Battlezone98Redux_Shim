/*
 * Entry: 00415d08
 * Name: Inst03Mission::Save
 * Namespace: Inst03Mission
 * Signature: bool Save(Inst03Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst03Mission::Save(Inst03Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  lua_State *plVar4;
  char *pcVar5;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  
  if (!missionSave) {
    ::out(param_1,(bool *)&this->_padding_,1,"started");
  }
  iVar3 = 0;
  if (((lua_State *)this->_padding_ != (lua_State *)0x0) && (missionSave == false)) {
    lua_getfield((lua_State *)this->_padding_,-0x2712,"Save");
    iVar2 = lua_type((lua_State *)this->_padding_,-1);
    if (iVar2 == 6) {
      iStack_c = lua_gettop((lua_State *)this->_padding_);
      pcVar5 = "Lua script Save error:\n%s";
      plVar4 = (lua_State *)this->_padding_;
      iVar2 = lua_pcall(plVar4,0,-1,0);
      bVar1 = LuaCheckStatus(iVar2,plVar4,pcVar5);
      if (bVar1) {
        iVar2 = 1 - iStack_c;
        iStack_10 = iVar2;
        iStack_8 = lua_gettop((lua_State *)this->_padding_);
        iStack_8 = iStack_8 + iVar2;
        ::out(param_1,&iStack_8,4,"count");
        if (0 < iStack_8) {
          do {
            iVar2 = iVar3 + iStack_c;
            Trace("-- Save %d\n");
            SaveValue(param_1,(lua_State *)this->_padding_,iVar2,0);
            pcVar5 = ",\n";
            if (iStack_8 + -1 <= iVar3) {
              pcVar5 = "\n";
            }
            Trace(pcVar5);
            iVar3 = iVar3 + 1;
          } while (iVar3 < iStack_8);
        }
      }
    }
    else {
      iStack_10 = 0;
      ::out(param_1,&iStack_10,4,"count");
      lua_settop((lua_State *)this->_padding_,-2);
    }
  }
  bVar1 = AiMission::Save((AiMission *)this,param_1);
  return bVar1;
}
