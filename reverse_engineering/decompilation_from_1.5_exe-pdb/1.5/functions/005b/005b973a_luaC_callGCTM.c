/*
 * Entry: 005b973a
 * Name: luaC_callGCTM
 * Namespace: Global
 * Signature: void luaC_callGCTM(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_callGCTM(lua_State *param_1)

{
  lua_State *unaff_ESI;
  
  while (param_1->l_G->tmudata != (GCObject *)0x0) {
    GCTM(unaff_ESI);
  }
  return;
}
