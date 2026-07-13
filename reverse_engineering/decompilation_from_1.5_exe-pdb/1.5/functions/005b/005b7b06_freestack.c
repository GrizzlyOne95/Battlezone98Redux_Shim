/*
 * Entry: 005b7b06
 * Name: freestack
 * Namespace: Global
 * Signature: void freestack(lua_State * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl freestack(lua_State *param_1,lua_State *param_2)

{
  int unaff_ESI;
  
  luaM_realloc_(param_1,*(void **)(unaff_ESI + 0x28),*(int *)(unaff_ESI + 0x30) * 0x18,0);
  luaM_realloc_(param_1,*(void **)(unaff_ESI + 0x20),*(int *)(unaff_ESI + 0x2c) << 4,0);
  return;
}
