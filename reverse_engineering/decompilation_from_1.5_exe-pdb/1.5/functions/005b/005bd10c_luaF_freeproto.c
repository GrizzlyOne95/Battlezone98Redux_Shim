/*
 * Entry: 005bd10c
 * Name: luaF_freeproto
 * Namespace: Global
 * Signature: void luaF_freeproto(lua_State * param_1, Proto * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaF_freeproto(lua_State *param_1,Proto *param_2)

{
  luaM_realloc_(param_1,param_2->code,param_2->sizecode << 2,0);
  luaM_realloc_(param_1,param_2->p,param_2->sizep << 2,0);
  luaM_realloc_(param_1,param_2->k,param_2->sizek << 4,0);
  luaM_realloc_(param_1,param_2->lineinfo,param_2->sizelineinfo << 2,0);
  luaM_realloc_(param_1,param_2->locvars,param_2->sizelocvars * 0xc,0);
  luaM_realloc_(param_1,param_2->upvalues,param_2->sizeupvalues << 2,0);
  luaM_realloc_(param_1,param_2,0x4c,0);
  return;
}
