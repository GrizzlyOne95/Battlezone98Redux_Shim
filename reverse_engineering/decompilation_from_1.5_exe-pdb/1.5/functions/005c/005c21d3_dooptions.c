/*
 * Entry: 005c21d3
 * Name: dooptions
 * Namespace: Global
 * Signature: void dooptions(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dooptions(lua_State *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 2;
  if (1 < param_2) {
    do {
      lua_pushvalue(param_1,iVar1);
      lua_pushvalue(param_1,-2);
      lua_call(param_1,1,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 <= param_2);
  }
  return;
}
