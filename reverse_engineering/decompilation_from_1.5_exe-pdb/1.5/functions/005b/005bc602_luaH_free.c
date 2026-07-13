/*
 * Entry: 005bc602
 * Name: luaH_free
 * Namespace: Global
 * Signature: void luaH_free(lua_State * param_1, Table * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaH_free(lua_State *param_1,Table *param_2)

{
  if (param_2->node != &dummynode_) {
    luaM_realloc_(param_1,param_2->node,(1 << (param_2->lsizenode & 0x1f)) << 5,0);
  }
  luaM_realloc_(param_1,param_2->array,param_2->sizearray << 4,0);
  luaM_realloc_(param_1,param_2,0x20,0);
  return;
}
