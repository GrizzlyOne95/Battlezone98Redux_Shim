/*
 * Entry: 005bf0ce
 * Name: db_gethook
 * Namespace: Global
 * Signature: int db_gethook(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl db_gethook(lua_State *param_1)

{
  lua_State *plVar1;
  uint uVar2;
  _func___cdecl_void_lua_State_ptr_lua_Debug_ptr *p_Var3;
  uint uVar4;
  int iVar5;
  lua_State *unaff_EDI;
  bool bVar6;
  char local_10 [8];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  plVar1 = getthread(param_1,(int *)unaff_EDI);
  uVar2 = lua_gethookmask(plVar1);
  p_Var3 = lua_gethook(plVar1);
  if ((p_Var3 == (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)0x0) || (p_Var3 == hookf)) {
    gethooktable(unaff_EDI);
    lua_pushlightuserdata(param_1,plVar1);
    lua_rawget(param_1,-2);
    lua_remove(param_1,-2);
  }
  else {
    lua_pushlstring(param_1,"external hook",0xd);
  }
  bVar6 = (uVar2 & 1) != 0;
  if (bVar6) {
    local_10[0] = 'c';
  }
  uVar4 = (uint)bVar6;
  if ((uVar2 & 2) != 0) {
    local_10[uVar4] = 'r';
    uVar4 = uVar4 + 1;
  }
  if ((uVar2 & 4) != 0) {
    local_10[uVar4] = 'l';
    uVar4 = uVar4 + 1;
  }
  local_10[uVar4] = '\0';
  lua_pushstring(param_1,local_10);
  iVar5 = lua_gethookcount(plVar1);
  lua_pushinteger(param_1,iVar5);
  return 3;
}
