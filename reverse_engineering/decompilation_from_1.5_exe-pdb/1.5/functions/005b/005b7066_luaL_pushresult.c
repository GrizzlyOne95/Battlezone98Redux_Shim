/*
 * Entry: 005b7066
 * Name: luaL_pushresult
 * Namespace: Global
 * Signature: void luaL_pushresult(luaL_Buffer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_pushresult(luaL_Buffer *param_1)

{
  luaL_Buffer *unaff_ESI;
  
  emptybuffer(unaff_ESI);
  lua_concat(param_1->L,param_1->lvl);
  param_1->lvl = 1;
  return;
}
