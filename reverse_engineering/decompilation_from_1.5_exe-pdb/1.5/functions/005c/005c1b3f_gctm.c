/*
 * Entry: 005c1b3f
 * Name: gctm
 * Namespace: Global
 * Signature: int gctm(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl gctm(lua_State *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = luaL_checkudata(param_1,1,"_LOADLIB");
  if ((HMODULE)*puVar1 != (HMODULE)0x0) {
    FreeLibrary((HMODULE)*puVar1);
  }
  *puVar1 = 0;
  return 0;
}
