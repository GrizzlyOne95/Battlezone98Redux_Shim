/*
 * Entry: 005bee44
 * Name: auxupvalue
 * Namespace: Global
 * Signature: int auxupvalue(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl auxupvalue(lua_State *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  lua_State *unaff_ESI;
  
  iVar1 = luaL_checkinteger(unaff_ESI,2);
  luaL_checktype(unaff_ESI,1,6);
  iVar2 = lua_iscfunction(unaff_ESI,1);
  if (iVar2 == 0) {
    if (param_1 == (lua_State *)0x0) {
      pcVar3 = lua_setupvalue(unaff_ESI,1,iVar1);
    }
    else {
      pcVar3 = lua_getupvalue(unaff_ESI,1,iVar1);
    }
    if (pcVar3 != (char *)0x0) {
      lua_pushstring(unaff_ESI,pcVar3);
      lua_insert(unaff_ESI,-1 - (int)param_1);
      return (int)(undefined1 *)((int)&param_1->next + 1);
    }
  }
  return 0;
}
