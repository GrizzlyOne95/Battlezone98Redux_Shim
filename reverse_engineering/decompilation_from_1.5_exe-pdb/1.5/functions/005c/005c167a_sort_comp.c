/*
 * Entry: 005c167a
 * Name: sort_comp
 * Namespace: Global
 * Signature: int sort_comp(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sort_comp(lua_State *param_1,int param_2,int param_3)

{
  int in_EAX;
  int iVar1;
  int in_ECX;
  lua_State *unaff_ESI;
  
  iVar1 = lua_type(unaff_ESI,2);
  if (iVar1 == 0) {
    iVar1 = lua_lessthan(unaff_ESI,in_ECX,in_EAX);
  }
  else {
    lua_pushvalue(unaff_ESI,2);
    lua_pushvalue(unaff_ESI,in_ECX + -1);
    lua_pushvalue(unaff_ESI,in_EAX + -2);
    lua_call(unaff_ESI,2,1);
    iVar1 = lua_toboolean(unaff_ESI,-1);
    lua_settop(unaff_ESI,-2);
  }
  return iVar1;
}
