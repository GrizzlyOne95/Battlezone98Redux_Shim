/*
 * Entry: 005beaae
 * Name: treatstackoption
 * Namespace: Global
 * Signature: void treatstackoption(lua_State * param_1, lua_State * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl treatstackoption(lua_State *param_1,lua_State *param_2,char *param_3)

{
  lua_State *unaff_ESI;
  
  if (unaff_ESI == param_1) {
    lua_pushvalue(unaff_ESI,-2);
    lua_remove(unaff_ESI,-3);
  }
  else {
    lua_xmove(param_1,unaff_ESI,1);
  }
  lua_setfield(unaff_ESI,-2,(char *)param_2);
  return;
}
