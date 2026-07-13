/*
 * Entry: 005c18f5
 * Name: sort
 * Namespace: Global
 * Signature: int sort(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl sort(lua_State *param_1)

{
  uint uVar1;
  int iVar2;
  
  luaL_checktype(param_1,1,5);
  uVar1 = lua_objlen(param_1,1);
  luaL_checkstack(param_1,0x28,"");
  iVar2 = lua_type(param_1,2);
  if (0 < iVar2) {
    luaL_checktype(param_1,2,6);
  }
  lua_settop(param_1,2);
  auxsort(param_1,1,uVar1);
  return 0;
}
