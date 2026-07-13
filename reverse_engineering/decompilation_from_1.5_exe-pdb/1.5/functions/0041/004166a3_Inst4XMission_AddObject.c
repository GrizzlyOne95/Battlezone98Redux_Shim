/*
 * Entry: 004166a3
 * Name: Inst4XMission::AddObject
 * Namespace: Inst4XMission
 * Signature: void AddObject(Inst4XMission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst4XMission::AddObject(Inst4XMission *this,GameObject *param_1)

{
  int iVar1;
  lua_State *plVar2;
  char *pcVar3;
  
  AiMission::AddObject((AiMission *)this,param_1);
  if ((lua_State *)this->_padding_ != (lua_State *)0x0) {
    lua_getfield((lua_State *)this->_padding_,-0x2712,"AddObject");
    iVar1 = lua_type((lua_State *)this->_padding_,-1);
    if (iVar1 == 6) {
      iVar1 = GameObject::GetHandle(param_1);
      PushHandle((lua_State *)this->_padding_,iVar1);
      plVar2 = (lua_State *)this->_padding_;
      pcVar3 = "Lua script AddObject error:\n%s";
      iVar1 = lua_pcall(plVar2,1,0,0);
      LuaCheckStatus(iVar1,plVar2,pcVar3);
    }
    else {
      lua_settop((lua_State *)this->_padding_,-2);
    }
  }
  return;
}
