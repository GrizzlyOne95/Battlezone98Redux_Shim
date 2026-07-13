/*
 * Entry: 005bd193
 * Name: luaF_freeclosure
 * Namespace: Global
 * Signature: void luaF_freeclosure(lua_State * param_1, Closure * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaF_freeclosure(lua_State *param_1,Closure *param_2)

{
  uint uVar1;
  
  if ((param_2->c).isC == '\0') {
    uVar1 = (uint)(param_2->c).nupvalues * 4 + 0x14;
  }
  else {
    uVar1 = (uint)(param_2->c).nupvalues * 0x10 + 0x18;
  }
  luaM_realloc_(param_1,param_2,uVar1,0);
  return;
}
