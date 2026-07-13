/*
 * Entry: 005bff8c
 * Name: writer
 * Namespace: Global
 * Signature: int writer(lua_State * param_1, void * param_2, uint param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl writer(lua_State *param_1,void *param_2,uint param_3,void *param_4)

{
  luaL_addlstring(param_4,param_2,param_3);
  return 0;
}
