/*
 * Entry: 005c1aa8
 * Name: ll_register
 * Namespace: Global
 * Signature: void * * ll_register(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void ** __cdecl ll_register(lua_State *param_1,char *param_2)

{
  int iVar1;
  lua_State *unaff_ESI;
  void **local_4;
  
  lua_pushfstring(unaff_ESI,"%s%s");
  lua_gettable(unaff_ESI,-10000);
  iVar1 = lua_type(unaff_ESI,-1);
  if (iVar1 == 0) {
    lua_settop(unaff_ESI,-2);
    local_4 = lua_newuserdata(unaff_ESI,4);
    *local_4 = (void *)0x0;
    lua_getfield(unaff_ESI,-10000,"_LOADLIB");
    lua_setmetatable(unaff_ESI,-2);
    lua_pushfstring(unaff_ESI,"%s%s");
    lua_pushvalue(unaff_ESI,-2);
    lua_settable(unaff_ESI,-10000);
  }
  else {
    local_4 = lua_touserdata(unaff_ESI,-1);
  }
  return local_4;
}
