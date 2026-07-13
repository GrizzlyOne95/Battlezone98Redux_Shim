/*
 * Entry: 0041ca92
 * Name: LuaMission::Receive
 * Namespace: LuaMission
 * Signature: int Receive(LuaMission * this, ushort param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall LuaMission::Receive(LuaMission *this,ushort param_1,char *param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  undefined2 in_stack_00000006;
  lua_State *plVar3;
  
  iVar1 = 0;
  if (this->L != (lua_State *)0x0) {
    lua_getfield(this->L,-0x2712,"Receive");
    iVar1 = lua_type(this->L,-1);
    if (iVar1 == 6) {
      lua_pushinteger(this->L,(uint)_param_1 & 0xffff);
      pcVar2 = param_2;
      lua_pushlstring(this->L,param_2 + 1,1);
      _param_1 = pcVar2 + 2;
      pcVar2 = pcVar2 + param_3;
      iVar1 = 2;
      while (_param_1 < pcVar2) {
        iVar1 = iVar1 + 1;
        UnpackValue((char **)&param_1,this->L);
      }
      plVar3 = this->L;
      pcVar2 = "Lua script Receive error:\n%s";
      iVar1 = lua_pcall(plVar3,iVar1,1,0);
      LuaCheckStatus(iVar1,plVar3,pcVar2);
      iVar1 = lua_toboolean(this->L,-1);
      lua_settop(this->L,-2);
    }
    else {
      lua_settop(this->L,-2);
      iVar1 = 0;
    }
  }
  return iVar1;
}
