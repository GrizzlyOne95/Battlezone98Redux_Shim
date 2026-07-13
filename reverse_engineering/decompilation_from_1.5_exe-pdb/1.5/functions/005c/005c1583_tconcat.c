/*
 * Entry: 005c1583
 * Name: tconcat
 * Namespace: Global
 * Signature: int tconcat(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl tconcat(lua_State *param_1)

{
  luaL_Buffer *plVar1;
  int iVar2;
  luaL_Buffer *plVar3;
  int unaff_EDI;
  uint local_21c;
  char *local_218;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_214.buffer + 0x6c);
  local_218 = luaL_optlstring(param_1,2,"",&local_21c);
  luaL_checktype(param_1,1,5);
  plVar1 = (luaL_Buffer *)luaL_optinteger(param_1,3,1);
  iVar2 = lua_type(param_1,4);
  if (iVar2 < 1) {
    plVar3 = (luaL_Buffer *)lua_objlen(param_1,1);
  }
  else {
    plVar3 = (luaL_Buffer *)luaL_checkinteger(param_1,4);
  }
  luaL_buffinit(param_1,&local_214);
  for (; (int)plVar1 < (int)plVar3; plVar1 = (luaL_Buffer *)((int)&plVar1->p + 1)) {
    addfield((lua_State *)&local_214,plVar1,unaff_EDI);
    luaL_addlstring(&local_214,local_218,local_21c);
  }
  if (plVar1 == plVar3) {
    addfield((lua_State *)&local_214,plVar1,unaff_EDI);
  }
  luaL_pushresult(&local_214);
  return 1;
}
