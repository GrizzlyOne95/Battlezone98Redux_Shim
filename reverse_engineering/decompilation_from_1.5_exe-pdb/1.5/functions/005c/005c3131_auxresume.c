/*
 * Entry: 005c3131
 * Name: auxresume
 * Namespace: Global
 * Signature: int auxresume(lua_State * param_1, lua_State * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl auxresume(lua_State *param_1,lua_State *param_2,int param_3)

{
  lua_State *in_EAX;
  int iVar1;
  int iVar2;
  lua_State *unaff_ESI;
  lua_State *unaff_EDI;
  
  iVar1 = costatus(unaff_EDI,unaff_ESI);
  iVar2 = lua_checkstack(in_EAX,(int)param_1);
  if (iVar2 == 0) {
    luaL_error(unaff_EDI,"too many arguments to resume");
  }
  if (iVar1 == 1) {
    lua_xmove(unaff_EDI,in_EAX,(int)param_1);
    lua_setlevel(unaff_EDI,in_EAX);
    iVar1 = lua_resume(in_EAX,(int)param_1);
    if ((iVar1 == 0) || (iVar1 == 1)) {
      iVar1 = lua_gettop(in_EAX);
      iVar2 = lua_checkstack(unaff_EDI,iVar1 + 1);
      if (iVar2 == 0) {
        luaL_error(unaff_EDI,"too many results to resume");
      }
      lua_xmove(in_EAX,unaff_EDI,iVar1);
      return iVar1;
    }
    lua_xmove(in_EAX,unaff_EDI,1);
  }
  else {
    lua_pushfstring(unaff_EDI,"cannot resume %s coroutine");
  }
  return -1;
}
