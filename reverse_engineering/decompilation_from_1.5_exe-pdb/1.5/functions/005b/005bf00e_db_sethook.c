/*
 * Entry: 005bf00e
 * Name: db_sethook
 * Namespace: Global
 * Signature: int db_sethook(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_sethook(lua_State *param_1)

{
  int iVar1;
  lua_State *plVar2;
  int iVar3;
  lua_State *unaff_EDI;
  lua_State *plVar4;
  _func___cdecl_void_lua_State_ptr_lua_Debug_ptr *local_c;
  char *local_8;
  
  plVar2 = getthread(param_1,(int *)unaff_EDI);
  iVar1 = (int)local_c + 1;
  iVar3 = lua_type(param_1,iVar1);
  if (iVar3 < 1) {
    lua_settop(param_1,iVar1);
    iVar3 = 0;
    local_c = (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)0x0;
    local_8 = (char *)0x0;
  }
  else {
    luaL_checklstring(param_1,(int)local_c + 2,(uint *)0x0);
    luaL_checktype(param_1,iVar1,6);
    plVar4 = param_1;
    local_8 = (char *)luaL_optinteger(param_1,(int)local_c + 3,0);
    local_c = hookf;
    iVar3 = makemask(local_8,(int)plVar4);
  }
  gethooktable(unaff_EDI);
  lua_pushlightuserdata(param_1,plVar2);
  lua_pushvalue(param_1,iVar1);
  lua_rawset(param_1,-3);
  lua_settop(param_1,-2);
  lua_sethook(plVar2,local_c,iVar3,(int)local_8);
  return 0;
}
